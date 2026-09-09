#include "CodeGenListener.h"
#include "Dictionary.hpp"

#include <sstream>

bool CodeGenListener::lookupVarType(const std::string &name, std::string &type) const
{
    if (std::holds_alternative<ChipsParser::L_function_defContext*>(current_def))
        return dico.lookupL(std::get<ChipsParser::L_function_defContext*>(current_def), name, type);

    if (std::holds_alternative<ChipsParser::P_function_defContext*>(current_def))
        return dico.lookupP(std::get<ChipsParser::P_function_defContext*>(current_def), name, type);

    return false;
}


std::string CodeGenListener::translateStatements(
    const std::vector<ChipsParser::StatementContext *> &statements, int indent, bool inScope)
{
    std::ostringstream oss;
    for (auto *stmt : statements)
    {
        oss << translateStatement(stmt, indent, inScope);
    }
    return oss.str();
}

std::string CodeGenListener::translateStatement(ChipsParser::StatementContext *stmt, int indent, bool inScope)
{
    std::string pad(indent, ' ');

    if (auto *loop = dynamic_cast<ChipsParser::StatementLoopContext *>(stmt))
    {
        return translateLoop(loop->loop_statement(), indent);
    }

    if (auto *ifElse = dynamic_cast<ChipsParser::StatementIfElseContext *>(stmt))
    {
        return translateIfElse(ifElse->if_else_statement(), indent);
    }

    if (auto *ifOnly = dynamic_cast<ChipsParser::StatementIfContext *>(stmt))
    {
        return translateIf(ifOnly->if_statement(), indent);
    }

    if (auto *decl = dynamic_cast<ChipsParser::StatementDeclarationContext *>(stmt))
    {
        return translateDecl(decl, indent, inScope);
    }

    if (auto *assign = dynamic_cast<ChipsParser::StatementAssignmentContext *>(stmt))
    {
        return translateAssignment(assign, indent);
    }

    if (auto *assign = dynamic_cast<ChipsParser::StatementContextualAssignmentContext *>(stmt))
    {
        return translateContextualAssignment(assign, indent);
    }

    std::string text("");
    antlr4::misc::Interval interval = stmt->getSourceInterval();
    for (int i = interval.a; i <= interval.b; i++)
    {
        text += tokens_.get(i)->getText();
    }
    std::cout << "unhandled: " << text << std::endl;
    std::cout << "(it has been copied verbatim)" << std::endl;
    return pad + text + "\n";
}

std::string CodeGenListener::translateLoop(ChipsParser::Loop_statementContext *ctx, int indent)
{
    std::string pad(indent, ' ');
    std::string varName = ctx->IDENTIFIER()->getText();
    auto *loopIn = ctx->loop_in();
    std::string source = loopIn->IDENTIFIER()->getText();

    std::ostringstream oss;

    if (loopIn->expr().empty())
    {
        for (auto *idx : loopIn->suffixes()->expr())
        {
            source += "[" + translateExpr(idx) + "]";
        }

        oss << pad << "for (auto " << varName << " : " << source << ")\n";
        oss << pad << "{\n";
        oss << translateStatements(ctx->statement(), indent + 4, true);
        oss << pad << "}\n";
    }
    else
    {
        // foreach x in y(a, b) { ... }
        // y(a, b) is called once to build a generator; the generator is then
        // invoked once per iteration to produce the next value of x.
        std::string argList;
        auto args = loopIn->expr();
        for (size_t i = 0; i < args.size(); ++i)
        {
            if (i)
                argList += ", ";
            argList += tokens_.getText(args[i]);
        }

        std::string genVar = varName;
        std::string indices("");
        for (auto *idx : loopIn->suffixes()->expr())
        {
            indices += "[" + tokens_.getText(idx) + "]";
        }

        oss << pad << "{\n";
        oss << pad << "    auto " << genVar << " = " << source << "(" << argList << ")" + indices + ";\n";
        oss << pad << "    for(chips_int i{0}; i<" + genVar + ".size(); i = i+chips_int{1}) {\n";
        oss << translateStatements(ctx->statement(), indent + 8, true);
        oss << pad << "    }\n";
        oss << pad << "}\n";
    }

    return oss.str();
}

std::string CodeGenListener::translateIf(ChipsParser::If_statementContext *ctx, int indent)
{
    std::string pad(indent, ' ');
    std::string cond = translateExpr(ctx->expr());

    std::ostringstream oss;
    oss << pad << "if (" << cond << ")\n";
    oss << pad << "{\n";
    oss << translateStatements(ctx->statement(), indent + 4, true);
    oss << pad << "}\n";
    return oss.str();
}

std::string CodeGenListener::translateIfElse(ChipsParser::If_else_statementContext *ctx, int indent)
{
    std::string pad(indent, ' ');

    std::ostringstream oss;
    oss << translateIf(ctx->if_statement(), indent);
    oss << pad << "else\n";
    oss << pad << "{\n";
    oss << translateStatements(ctx->statement(), indent + 4, true);
    oss << pad << "}\n";
    return oss.str();
}

std::string CodeGenListener::translateSuffixes(ChipsParser::SuffixesContext *s)
{

    std::vector<std::string> dimExprs;
    for (auto *e : s->expr())
    {
        dimExprs.emplace_back(translateExpr(e));
    }

    std::ostringstream oss;
    if(dimExprs.size()!=0){
        for (size_t i = 0; i < dimExprs.size(); ++i)
        {
            oss << '[' << dimExprs[i] << ']';
        }
        oss << ".to_chips()";
    }
    return oss.str();
}

std::string CodeGenListener::translateDecl(ChipsParser::StatementDeclarationContext *ctx, int indent, bool inScope)
{
    std::string chipType = chipsTypeFor(ctx->df_type());
    std::string varName = ctx->IDENTIFIER()->getText();
    std::string pad(indent, ' ');

    if (!inScope)
    {
        if (std::holds_alternative<ChipsParser::CollectiveOperationDefinitionContext *>(current_def))
        {
            /* code */
        }
        else if (std::holds_alternative<ChipsParser::L_function_defContext *>(current_def))
        {
            dico.addLogical(std::get<ChipsParser::L_function_defContext *>(current_def), varName, chipType);
        }
        else if (std::holds_alternative<ChipsParser::P_function_defContext *>(current_def))
        {
            dico.addPhysical(std::get<ChipsParser::P_function_defContext *>(current_def), varName, chipType);
        }
        if (ctx->ASSIGN())
        {
            return pad + ctx->IDENTIFIER()->getText() +" = " + translateExpr(ctx->expr())+";\n";
        }
        return std::string{};
    }

    std::string ctorArgs;
    if (auto *suffixes = ctx->suffixes())
    {
        ctorArgs = translateSuffixes(suffixes);
    }

    std::string initializer;
    if (ctx->ASSIGN())
    {
        initializer = " = " + translateExpr(ctx->expr());
    }

    std::ostringstream out;
    out << pad << chipType << ' ' << varName;

    if (!ctorArgs.empty())
    {
        out << '(' << ctorArgs << ");\n";
    }
    else
    {
        out << ";\n";
    }

    if (!initializer.empty())
        out << pad << varName << initializer << ";\n";

    return out.str();
}

std::string CodeGenListener::translateAssignment(ChipsParser::StatementAssignmentContext *ctx, int indent)
{
    std::string varName = ctx->IDENTIFIER()->getText();
    std::string pad(indent, ' ');
    return pad + varName + " = " + translateExpr(ctx->expr()) + ";\n";
}

std::string CodeGenListener::translateContextualAssignment(ChipsParser::StatementContextualAssignmentContext *ctx, int indent)
{
    std::string pad(indent, ' ');
    std::string varName = ctx->IDENTIFIER()->getText();
    std::string rhs = translateExpr(ctx->expr());

    std::string type;
    if (!lookupVarType(varName, type))
    {
        type = chipsTypeFor(ctx->expr());

        if (std::holds_alternative<ChipsParser::L_function_defContext*>(current_def))
            dico.addLogical(std::get<ChipsParser::L_function_defContext*>(current_def), varName, type);
        else if (std::holds_alternative<ChipsParser::P_function_defContext*>(current_def))
            dico.addPhysical(std::get<ChipsParser::P_function_defContext*>(current_def), varName, type);
    }

    std::ostringstream oss;
    oss << pad << varName << translateSuffixes(ctx->suffixes()) << " = " << rhs << ";\n";
    return oss.str();
}

std::string CodeGenListener::translateFunction(ChipsParser::FunctionContext *ctx)
{
    std::ostringstream out;
    out << ctx->IDENTIFIER()->getText() << '(';

    const auto &args = ctx->expr();
    for (size_t i = 0; i < args.size(); ++i)
    {
        out << translateExpr(args[i]);
        if (i + 1 < args.size())
            out << ", ";
    }
    out << ')';
    return out.str();
}

std::string CodeGenListener::translateExpr(ChipsParser::ExprContext *ctx)
{
    if (auto *geq = dynamic_cast<ChipsParser::GEQContext *>(ctx))
        return translateExpr0(geq->expr0()) + " >= " + translateExpr(geq->expr());

    if (auto *gt = dynamic_cast<ChipsParser::GTContext *>(ctx))
        return translateExpr0(gt->expr0()) + " > " + translateExpr(gt->expr());

    if (auto *orctx = dynamic_cast<ChipsParser::ORContext *>(ctx))
        return translateExpr0(orctx->expr0()) + " || " + translateExpr(orctx->expr());

    if (auto *andctx = dynamic_cast<ChipsParser::ANDContext *>(ctx))
        return translateExpr0(andctx->expr0()) + " && " + translateExpr(andctx->expr());

    if (auto *lt = dynamic_cast<ChipsParser::LTContext *>(ctx))
        return translateExpr0(lt->expr0()) + " < " + translateExpr(lt->expr());

    if (auto *leq = dynamic_cast<ChipsParser::LEQContext *>(ctx))
        return translateExpr0(leq->expr0()) + " <= " + translateExpr(leq->expr());

    if (auto *neq = dynamic_cast<ChipsParser::NEQContext *>(ctx))
        return translateExpr0(neq->expr0()) + " != " + translateExpr(neq->expr());

    if (auto *eq = dynamic_cast<ChipsParser::EQContext *>(ctx))
        return translateExpr0(eq->expr0()) + " == " + translateExpr(eq->expr());

    if (auto *pass0 = dynamic_cast<ChipsParser::PassExpr0Context *>(ctx))
        return translateExpr0(pass0->expr0());

    std::cout << "unhandled: " << ctx->getText() <<std::endl;
    throw ctx;
}

std::string CodeGenListener::translateExpr0(ChipsParser::Expr0Context *ctx)
{
    if (auto *sub = dynamic_cast<ChipsParser::SUBContext *>(ctx))
        return translateExpr01(sub->expr01()) + " - " + translateExpr0(sub->expr0());

    if (auto *plus = dynamic_cast<ChipsParser::PLUSContext *>(ctx))
        return translateExpr01(plus->expr01()) + " + " + translateExpr0(plus->expr0());

    if (auto *pass01 = dynamic_cast<ChipsParser::PassExpr01Context *>(ctx))
        return translateExpr01(pass01->expr01());

    std::cout << "unhandled: " << ctx->getText() <<std::endl;
    throw ctx;
}

std::string CodeGenListener::translateExpr01(ChipsParser::Expr01Context *ctx)
{
    if (auto *neg = dynamic_cast<ChipsParser::NegateContext *>(ctx))
        return "-" + translateExpr1(neg->expr1());

    if (auto *pass1 = dynamic_cast<ChipsParser::PassExpr1Context *>(ctx))
        return translateExpr1(pass1->expr1());

    std::cout << "unhandled: " << ctx->getText() <<std::endl;
    throw ctx;
}

std::string CodeGenListener::translateExpr1(ChipsParser::Expr1Context *ctx)
{
    if (auto *div = dynamic_cast<ChipsParser::DIVContext *>(ctx))
        return translateExpr2(div->expr2()) + " / " + translateExpr1(div->expr1());

    if (auto *notexpr = dynamic_cast<ChipsParser::NOTContext *>(ctx))
        return "!" + translateExpr2(notexpr->expr2());

    if (auto *mod = dynamic_cast<ChipsParser::MODContext *>(ctx))
        return translateExpr2(mod->expr2()) + " % " + translateExpr1(mod->expr1());

    if (auto *mult = dynamic_cast<ChipsParser::MULTContext *>(ctx))
        return translateExpr2(mult->expr2()) + " * " + translateExpr1(mult->expr1());

    if (auto *pass2 = dynamic_cast<ChipsParser::PassExpr2Context *>(ctx))
        return translateExpr2(pass2->expr2());

    std::cout << "unhandled: " << ctx->getText() <<std::endl;
    throw ctx;
}

std::string CodeGenListener::translateExpr2(ChipsParser::Expr2Context *ctx)
{
    if (auto *casting = dynamic_cast<ChipsParser::CastAsContext *>(ctx))
        return "static_cast<chips_" + casting->cast()->df_type()->getText() + ">(" + translateExpr(casting->cast()->expr()) + ")";

    if (auto *fctcall = dynamic_cast<ChipsParser::FunctionContext *>(ctx))
        return translateFunction(fctcall);

    if (auto *literal = dynamic_cast<ChipsParser::BoolLiteralContext *>(ctx))
        return "chips_bool{" + literal->BOOL()->getText() + "}";

    if (auto *literal = dynamic_cast<ChipsParser::FloatLiteralContext *>(ctx))
        return "chips_float{" + literal->FLOAT()->getText() + "}";

    if (auto *literal = dynamic_cast<ChipsParser::IntLiteralContext *>(ctx))
        return "chips_int{" + literal->INT()->getText() + "}";

    if (auto *variable = dynamic_cast<ChipsParser::VarContext *>(ctx))
        return variable->IDENTIFIER()->getText() + translateSuffixes(variable->suffixes());

    if (auto *parens = dynamic_cast<ChipsParser::ParensContext *>(ctx))
        return "(" + translateExpr(parens->expr()) + ")";
    
    if (auto *ctxvar = dynamic_cast<ChipsParser::VarContextContext *>(ctx))
        return ctxvar->IDENTIFIER()->getText() + translateSuffixes(ctxvar->suffixes());

    std::cout << "unhandled: " << ctx->getText() <<std::endl;
    throw ctx;
}

std::string CodeGenListener::chipsTypeFor(ChipsParser::Df_typeContext *typeCtx)
{
    if (dynamic_cast<ChipsParser::BoolTypeContext *>(typeCtx))
        return "chips_bool";
    if (dynamic_cast<ChipsParser::IntTypeContext *>(typeCtx))
        return "chips_int";
    if (dynamic_cast<ChipsParser::FloatTypeContext *>(typeCtx))
        return "chips_float";
    return "/* unknown type */";
}

std::string CodeGenListener::chipsTypeFor(ChipsParser::ExprContext *ctx)
{
    if (auto *geq = dynamic_cast<ChipsParser::GEQContext *>(ctx))
        return "chips_bool";
    if (auto *gt = dynamic_cast<ChipsParser::GTContext *>(ctx))
        return "chips_bool";
    if (auto *orctx = dynamic_cast<ChipsParser::ORContext *>(ctx))
        return "chips_bool";
    if (auto *andctx = dynamic_cast<ChipsParser::ANDContext *>(ctx))
        return "chips_bool";
    if (auto *lt = dynamic_cast<ChipsParser::LTContext *>(ctx))
        return "chips_bool";
    if (auto *leq = dynamic_cast<ChipsParser::LEQContext *>(ctx))
        return "chips_bool";
    if (auto *neq = dynamic_cast<ChipsParser::NEQContext *>(ctx))
        return "chips_bool";
    if (auto *eq = dynamic_cast<ChipsParser::EQContext *>(ctx))
        return "chips_bool";

    if (auto *pass0 = dynamic_cast<ChipsParser::PassExpr0Context *>(ctx))
        return chipsTypeFor(pass0->expr0());

    return "/* unknown type */";
}

std::string CodeGenListener::chipsTypeFor(ChipsParser::Expr0Context *ctx)
{
    if (auto *sub = dynamic_cast<ChipsParser::SUBContext *>(ctx))
        return chipsTypeFor(sub->expr01());

    if (auto *plus = dynamic_cast<ChipsParser::PLUSContext *>(ctx))
        return chipsTypeFor(plus->expr01());

    if (auto *pass01 = dynamic_cast<ChipsParser::PassExpr01Context *>(ctx))
        return chipsTypeFor(pass01->expr01());

    return "/* unknown type */";
}

std::string CodeGenListener::chipsTypeFor(ChipsParser::Expr01Context *ctx)
{
    if (auto *neg = dynamic_cast<ChipsParser::NegateContext *>(ctx))
        return chipsTypeFor(neg->expr1());

    if (auto *pass1 = dynamic_cast<ChipsParser::PassExpr1Context *>(ctx))
        return chipsTypeFor(pass1->expr1());

    return "/* unknown type */";
}

std::string CodeGenListener::chipsTypeFor(ChipsParser::Expr1Context *ctx)
{
    if (auto *div = dynamic_cast<ChipsParser::DIVContext *>(ctx))
        return chipsTypeFor(div->expr2());

    if (auto *notexpr = dynamic_cast<ChipsParser::NOTContext *>(ctx))
        return "chips_bool";

    if (auto *mod = dynamic_cast<ChipsParser::MODContext *>(ctx))
        return chipsTypeFor(mod->expr2());

    if (auto *mult = dynamic_cast<ChipsParser::MULTContext *>(ctx))
        return chipsTypeFor(mult->expr2());

    if (auto *pass2 = dynamic_cast<ChipsParser::PassExpr2Context *>(ctx))
        return chipsTypeFor(pass2->expr2());

    return "/* unknown type */";
}

std::string CodeGenListener::chipsTypeFor(ChipsParser::Expr2Context *ctx)
{
    if (auto *casting = dynamic_cast<ChipsParser::CastAsContext *>(ctx))
        return "chips_" + casting->cast()->df_type()->getText();

    if (auto *fctcall = dynamic_cast<ChipsParser::FunctionContext *>(ctx))
        return "chips_int /* unresolved function return type */";

    if (dynamic_cast<ChipsParser::BoolLiteralContext *>(ctx))
        return "chips_bool";

    if (dynamic_cast<ChipsParser::FloatLiteralContext *>(ctx))
        return "chips_float";

    if (dynamic_cast<ChipsParser::IntLiteralContext *>(ctx))
        return "chips_int";

    if (auto *variable = dynamic_cast<ChipsParser::VarContext *>(ctx))
    {
        std::string type;
        if (lookupVarType(variable->IDENTIFIER()->getText(), type))
            return type;
        return "chips_any";
    }

    if (auto *parens = dynamic_cast<ChipsParser::ParensContext *>(ctx))
        return chipsTypeFor(parens->expr());

    return "/* unknown type */";
}

std::string CodeGenListener::translateParams(const std::vector<ChipsParser::Df_parameter_declContext *> &params)
{
    std::ostringstream oss;
    for (size_t i = 0; i < params.size(); ++i)
    {
        if (i)
            oss << ", ";
        std::string param_type = chipsTypeFor(params[i]->df_type());
        oss << param_type << "& " << params[i]->IDENTIFIER()->getText();
        
    }
    return oss.str();
}

std::string CodeGenListener::translateParams(const std::vector<ChipsParser::Pdf_parameter_declContext *> &params)
{
    std::ostringstream oss;
    for (size_t i = 0; i < params.size(); ++i)
    {
        if (i)
            oss << ", ";

        ChipsParser::Df_typeContext *typeCtx = nullptr;
        auto *ptype = params[i]->pdf_parameter_type();
        if (auto *f = dynamic_cast<ChipsParser::FunctionParameterTypeContext *>(ptype)) /*then*/ typeCtx = f->df_type();
        else if (auto *s = dynamic_cast<ChipsParser::SensorParameterTypeContext *>(ptype)) /*then*/ typeCtx = s->df_type();

        std::string param_type = chipsTypeFor(typeCtx);
        oss << param_type << "& " << params[i]->IDENTIFIER()->getText();
    }
    return oss.str();
}

std::string CodeGenListener::translateOutputs(const std::vector<ChipsParser::Named_outputContext *> &outputs)
{
    std::ostringstream oss;
    for (size_t i = 0; i < outputs.size(); ++i)
    {
        if (i)
            oss << ", ";
        const std::string &name = outputs[i]->IDENTIFIER()->getText();
        ChipsParser::ExprContext *firstExpr = outputs[i]->expr(0);
        oss << chipsTypeFor(firstExpr) << "& " << name << "_out";
    }
    return oss.str();
}

std::string CodeGenListener::translateOutputs(const std::vector<ChipsParser::P_named_outputContext *> &outputs)
{
    std::ostringstream oss;
    for (size_t i = 0; i < outputs.size(); ++i)
    {
        if (i)
            oss << ", ";

        std::string name;
        ChipsParser::ExprContext *firstExpr = nullptr;

        if (auto *actuator = dynamic_cast<ChipsParser::ActuatorOutputContext *>(outputs[i]))
        {
            name = actuator->IDENTIFIER()->getText();
            firstExpr = actuator->expr(0);
        }
        else if (auto *fctOut = dynamic_cast<ChipsParser::FunctionOutputContext *>(outputs[i]))
        {
            auto *namedOut = fctOut->named_output();
            name = namedOut->IDENTIFIER()->getText();
            firstExpr = namedOut->expr(0);
        }

        oss << chipsTypeFor(firstExpr) << "& " << name <<"_out";
    }
    return oss.str();
}

std::string CodeGenListener::outputText(){

    std::string pad(4, ' ');
    std::string out{};

    if (std::holds_alternative<ChipsParser::L_function_defContext*>(current_def))
    {
        for(auto *output : std::get<ChipsParser::L_function_defContext*>(current_def)->named_output())
        {
            out += pad + output->IDENTIFIER()->getText() + "_out = " + translateExpr(output->expr()[0]) + ";\n";
        }
    }
    if (std::holds_alternative<ChipsParser::P_function_defContext*>(current_def))
    {
        for(auto *output : std::get<ChipsParser::P_function_defContext*>(current_def)->p_named_output())
        {
            ChipsParser::ExprContext *firstExpr = nullptr;

            if (auto *actuator = dynamic_cast<ChipsParser::ActuatorOutputContext *>(output))
            {
                firstExpr = actuator->expr(0);
                out += pad + actuator->IDENTIFIER()->getText() + "_out = " + translateExpr(firstExpr) + ";\n";
            }
            else if (auto *fctOut = dynamic_cast<ChipsParser::FunctionOutputContext *>(output))
            {
                auto *namedOut = fctOut->named_output();
                firstExpr = namedOut->expr(0);
                out += pad + namedOut->IDENTIFIER()->getText() + "_out = " + translateExpr(firstExpr) + ";\n";
            }
        }
    }
    return out;
}

void CodeGenListener::emitSection(const std::string &funcName, const std::string &suffix, const std::vector<ChipsParser::StatementContext *> &statements, const std::string &params, const std::string &outputs, const bool& inScope)
{

    std::string inner_decls;
    const std::string stmts_txt = translateStatements(statements, 4, inScope);
    if (std::holds_alternative<ChipsParser::L_function_defContext *>(current_def))
    {
        inner_decls = dico.serializeL(std::get<ChipsParser::L_function_defContext *>(current_def));
    }
    else
    {
        inner_decls = dico.serializeP(std::get<ChipsParser::P_function_defContext *>(current_def));
    }


    std::vector<std::string> parts;
    if (!params.empty())
        parts.push_back(params);
    if (!inner_decls.empty())
        parts.push_back(inner_decls);
    if (!outputs.empty())
        parts.push_back(outputs);

    std::ostringstream signature;
    for (size_t i = 0; i < parts.size(); ++i)
    {
        if (i)
            signature << ", ";
        signature << parts[i];
    }

    out_ << "void " << funcName << "_" << suffix << "(" << signature.str() << ")\n{\n";
    out_ << stmts_txt;
    if (suffix.compare("then") == 0)
    {
        out_ << outputText();
    }
    out_ << "}\n\n";
}

void CodeGenListener::exitL_function_def(ChipsParser::L_function_defContext *ctx)
{
    current_def = ctx;
    const std::string name = ctx->IDENTIFIER()->getText();
    const std::string params = translateParams(ctx->df_parameter_decl());
    const std::string outputs = translateOutputs(ctx->named_output());

    emitSection(name, "init", ctx->init_section()->statement(), params, outputs,false);
    emitSection(name, "then", ctx->then_section()->statement(), params, outputs,true);
}

void CodeGenListener::exitP_function_def(ChipsParser::P_function_defContext *ctx)
{
    current_def = ctx;
    const std::string name = ctx->IDENTIFIER()->getText();
    const std::string params = translateParams(ctx->pdf_parameter_decl());
    const std::string outputs = translateOutputs(ctx->p_named_output());

    emitSection(name, "init", ctx->init_section()->statement(), params, outputs,false);
    emitSection(name, "then", ctx->then_section()->statement(), params, outputs,true);
}