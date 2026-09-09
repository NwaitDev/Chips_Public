#include "CodeGenListener.h"
#include "Dictionary.hpp"

#include <sstream>
#include <cctype>

std::string CodeGenListener::capitalize(const std::string &s)
{
    std::string r = s;
    if (!r.empty())
        r[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(r[0])));
    return r;
}

bool CodeGenListener::lookupVarType(const std::string &name, std::string &type) const
{
    if (std::holds_alternative<ChipsParser::L_function_defContext*>(current_def))
        return dico.lookupL(std::get<ChipsParser::L_function_defContext*>(current_def), name, type);

    if (std::holds_alternative<ChipsParser::P_function_defContext*>(current_def))
        return dico.lookupP(std::get<ChipsParser::P_function_defContext*>(current_def), name, type);

    if (std::holds_alternative<ChipsParser::Collective_op_defContext*>(current_def))
    {
        auto *cctx = std::get<ChipsParser::Collective_op_defContext*>(current_def);
        return isSpreadOp(cctx) ? dico.lookupSpread(cctx, name, type) : dico.lookupCollect(cctx, name, type);
    }

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
        if (std::holds_alternative<ChipsParser::Collective_op_defContext *>(current_def))
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
    registerChannels(ObjectType{ctx});

    emitSection(name, "init", ctx->init_section()->statement(), params, outputs,false);
    emitSection(name, "then", ctx->then_section()->statement(), params, outputs,true);
}


// ---------- Collective function definition relative ----------

bool CodeGenListener::isSpreadOp(ChipsParser::Collective_op_defContext *ctx) const
{
    return ctx->c_signature()->c_keywords()->SPREAD_KW() != nullptr;
}

std::string CodeGenListener::translateCStatements(const std::vector<ChipsParser::C_statementContext *> &statements, int indent)
{
    std::ostringstream oss;
    for (auto *stmt : statements)
        oss << translateCStatement(stmt, indent);
    return oss.str();
}

std::string CodeGenListener::translateCStatement(ChipsParser::C_statementContext *stmt, int indent)
{
    std::string pad(indent, ' ');

    if (auto *loop = dynamic_cast<ChipsParser::CollectiveLoopStatementContext *>(stmt))
        return translateCLoop(loop->c_loop_statement(), indent);

    if (auto *ifElse = dynamic_cast<ChipsParser::CollectiveIfElseStatementContext *>(stmt))
        return translateCIfElse(ifElse->c_if_else_statement(), indent);

    if (auto *ifOnly = dynamic_cast<ChipsParser::CollectiveIfStatementContext *>(stmt))
        return translateCIf(ifOnly->c_if_statement(), indent);

    if (auto *decl = dynamic_cast<ChipsParser::CollectiveVariableDeclarationContext *>(stmt))
        return translateCDecl(decl->cdf_full_declaration(), indent);

    if (auto *assign = dynamic_cast<ChipsParser::CollectiveAssignmentContext *>(stmt))
        return translateCAssignment(assign, indent);

    if (auto *assign = dynamic_cast<ChipsParser::ContextualAssignmentContext *>(stmt))
        return translateCContextualAssignment(assign, indent);

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

std::string CodeGenListener::translateCLoop(ChipsParser::C_loop_statementContext *ctx, int indent)
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
        oss << translateCStatements(ctx->c_statement(), indent + 4);
        oss << pad << "}\n";
    }
    else
    {
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
        oss << translateCStatements(ctx->c_statement(), indent + 8);
        oss << pad << "    }\n";
        oss << pad << "}\n";
    }

    return oss.str();
}

std::string CodeGenListener::translateCIf(ChipsParser::C_if_statementContext *ctx, int indent)
{
    std::string pad(indent, ' ');
    std::string cond = translateCExpr(ctx->c_expr());

    std::ostringstream oss;
    oss << pad << "if (" << cond << ")\n";
    oss << pad << "{\n";
    oss << translateCStatements(ctx->c_statement(), indent + 4);
    oss << pad << "}\n";
    return oss.str();
}

std::string CodeGenListener::translateCIfElse(ChipsParser::C_if_else_statementContext *ctx, int indent)
{
    std::string pad(indent, ' ');

    std::ostringstream oss;
    oss << translateCIf(ctx->c_if_statement(), indent);
    oss << pad << "else\n";
    oss << pad << "{\n";
    oss << translateCStatements(ctx->c_statement(), indent + 4);
    oss << pad << "}\n";
    return oss.str();
}

std::string CodeGenListener::translateCDecl(ChipsParser::Cdf_full_declarationContext *ctx, int indent)
{
    std::string chipType = chipsTypeFor(ctx->df_type());
    std::string varName = ctx->IDENTIFIER()->getText();
    std::string pad(indent, ' ');

    auto *cctx = std::get<ChipsParser::Collective_op_defContext*>(current_def);
    if (isSpreadOp(cctx))
        dico.addSpread(cctx, varName, chipType);
    else
        dico.addCollect(cctx, varName, chipType);

    std::string ctorArgs;
    if (auto *suffixes = ctx->suffixes())
    {
        ctorArgs = translateSuffixes(suffixes);
    }

    std::string initializer;
    if (ctx->ASSIGN())
    {
        initializer = " = " + translateCExpr(ctx->c_expr());
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

std::string CodeGenListener::translateCAssignment(ChipsParser::CollectiveAssignmentContext *ctx, int indent)
{
    std::string pad(indent, ' ');
    std::string varName = ctx->IDENTIFIER()->getText();
    std::string lhs = varName + translateCSuffixes(ctx->c_suffixes());

    if (dynamic_cast<ChipsParser::StopContext *>(ctx->c_expr()))
        return pad + lhs + ".stopFlag = true;\n";

    std::string rhs = translateCExpr(ctx->c_expr());
    return pad + lhs + " = " + rhs + ";\n";
}

std::string CodeGenListener::translateCContextualAssignment(ChipsParser::ContextualAssignmentContext *ctx, int indent)
{
    std::string pad(indent, ' ');
    std::string varName = ctx->IDENTIFIER()->getText();
    std::string lhs = varName + translateCSuffixes(ctx->c_suffixes());

    if (dynamic_cast<ChipsParser::StopContext *>(ctx->c_expr()))
        return pad + lhs + ".stopFlag = true;\n";

    std::string rhs = translateCExpr(ctx->c_expr());

    std::string type;
    if (!lookupVarType(varName, type))
    {
        type = chipsTypeFor(ctx->c_expr());

        auto *cctx = std::get<ChipsParser::Collective_op_defContext*>(current_def);
        if (isSpreadOp(cctx))
            dico.addSpread(cctx, varName, type);
        else
            dico.addCollect(cctx, varName, type);
    }

    return pad + lhs + " = " + rhs + ";\n";
}

std::string CodeGenListener::translateCSuffixes(ChipsParser::C_suffixesContext *s)
{
    std::vector<std::string> dimExprs;
    for (auto *e : s->c_stopless_expr())
    {
        dimExprs.emplace_back(translateCStoplessExpr(e));
    }

    std::ostringstream oss;
    if (dimExprs.size() != 0)
    {
        for (size_t i = 0; i < dimExprs.size(); ++i)
        {
            oss << '[' << dimExprs[i] << ']';
        }
        oss << ".to_chips()";
    }
    return oss.str();
}

std::string CodeGenListener::translateCFunctionCall(ChipsParser::FunctionCallContext *ctx)
{
    std::ostringstream out;
    out << ctx->IDENTIFIER()->getText() << '(';

    const auto &args = ctx->c_expr();
    for (size_t i = 0; i < args.size(); ++i)
    {
        out << translateCExpr(args[i]);
        if (i + 1 < args.size())
            out << ", ";
    }
    out << ')';
    return out.str();
}

std::string CodeGenListener::translateCCast(ChipsParser::C_castContext *ctx)
{
    return "static_cast<chips_" + ctx->df_type()->getText() + ">(" + translateCStoplessExpr(ctx->c_stopless_expr()) + ")";
}

std::string CodeGenListener::translateCExpr(ChipsParser::C_exprContext *ctx)
{
    if (auto *stopless = dynamic_cast<ChipsParser::CStoplessExpressionContext *>(ctx))
        return translateCStoplessExpr(stopless->c_stopless_expr());

    std::cout << "unhandled: " << ctx->getText() << std::endl;
    throw ctx;
}

std::string CodeGenListener::translateCStoplessExpr(ChipsParser::C_stopless_exprContext *ctx)
{
    if (auto *lt = dynamic_cast<ChipsParser::CLTContext *>(ctx))
        return translateCStoplessExpr0(lt->c_stopless_expr0()) + " < " + translateCStoplessExpr(lt->c_stopless_expr());

    if (auto *gt = dynamic_cast<ChipsParser::CGTContext *>(ctx))
        return translateCStoplessExpr0(gt->c_stopless_expr0()) + " > " + translateCStoplessExpr(gt->c_stopless_expr());

    if (auto *leq = dynamic_cast<ChipsParser::CLEQContext *>(ctx))
        return translateCStoplessExpr0(leq->c_stopless_expr0()) + " <= " + translateCStoplessExpr(leq->c_stopless_expr());

    if (auto *geq = dynamic_cast<ChipsParser::CGEQContext *>(ctx))
        return translateCStoplessExpr0(geq->c_stopless_expr0()) + " >= " + translateCStoplessExpr(geq->c_stopless_expr());

    if (auto *neq = dynamic_cast<ChipsParser::CNEQContext *>(ctx))
        return translateCStoplessExpr0(neq->c_stopless_expr0()) + " != " + translateCStoplessExpr(neq->c_stopless_expr());

    if (auto *eq = dynamic_cast<ChipsParser::CEQContext *>(ctx))
        return translateCStoplessExpr0(eq->c_stopless_expr0()) + " == " + translateCStoplessExpr(eq->c_stopless_expr());

    if (auto *andctx = dynamic_cast<ChipsParser::CANDContext *>(ctx))
        return translateCStoplessExpr0(andctx->c_stopless_expr0()) + " && " + translateCStoplessExpr(andctx->c_stopless_expr());

    if (auto *orctx = dynamic_cast<ChipsParser::CORContext *>(ctx))
        return translateCStoplessExpr0(orctx->c_stopless_expr0()) + " || " + translateCStoplessExpr(orctx->c_stopless_expr());

    if (auto *pass0 = dynamic_cast<ChipsParser::PassCExpr0Context *>(ctx))
        return translateCStoplessExpr0(pass0->c_stopless_expr0());

    std::cout << "unhandled: " << ctx->getText() << std::endl;
    throw ctx;
}

std::string CodeGenListener::translateCStoplessExpr0(ChipsParser::C_stopless_expr0Context *ctx)
{
    if (auto *sub = dynamic_cast<ChipsParser::CSUBContext *>(ctx))
        return translateCStoplessExpr01(sub->c_stopless_expr01()) + " - " + translateCStoplessExpr0(sub->c_stopless_expr0());

    if (auto *plus = dynamic_cast<ChipsParser::CPLUSContext *>(ctx))
        return translateCStoplessExpr01(plus->c_stopless_expr01()) + " + " + translateCStoplessExpr0(plus->c_stopless_expr0());

    if (auto *pass01 = dynamic_cast<ChipsParser::PassCExpr01Context *>(ctx))
        return translateCStoplessExpr01(pass01->c_stopless_expr01());

    std::cout << "unhandled: " << ctx->getText() << std::endl;
    throw ctx;
}

std::string CodeGenListener::translateCStoplessExpr01(ChipsParser::C_stopless_expr01Context *ctx)
{
    if (auto *neg = dynamic_cast<ChipsParser::CNegateContext *>(ctx))
        return "-" + translateCStoplessExpr1(neg->c_stopless_expr1());

    if (auto *pass1 = dynamic_cast<ChipsParser::PassCExpr1Context *>(ctx))
        return translateCStoplessExpr1(pass1->c_stopless_expr1());

    std::cout << "unhandled: " << ctx->getText() << std::endl;
    throw ctx;
}

std::string CodeGenListener::translateCStoplessExpr1(ChipsParser::C_stopless_expr1Context *ctx)
{
    if (auto *div = dynamic_cast<ChipsParser::CDIVContext *>(ctx))
        return translateCStoplessExpr2(div->c_stopless_expr2()) + " / " + translateCStoplessExpr1(div->c_stopless_expr1());

    if (auto *notexpr = dynamic_cast<ChipsParser::CNOTContext *>(ctx))
        return "!" + translateCStoplessExpr2(notexpr->c_stopless_expr2());

    if (auto *mod = dynamic_cast<ChipsParser::CMODContext *>(ctx))
        return translateCStoplessExpr2(mod->c_stopless_expr2()) + " % " + translateCStoplessExpr1(mod->c_stopless_expr1());

    if (auto *mult = dynamic_cast<ChipsParser::CMULTContext *>(ctx))
        return translateCStoplessExpr2(mult->c_stopless_expr2()) + " * " + translateCStoplessExpr1(mult->c_stopless_expr1());

    if (auto *pass2 = dynamic_cast<ChipsParser::PassCExpr2Context *>(ctx))
        return translateCStoplessExpr2(pass2->c_stopless_expr2());

    std::cout << "unhandled: " << ctx->getText() << std::endl;
    throw ctx;
}

std::string CodeGenListener::translateCStoplessExpr2(ChipsParser::C_stopless_expr2Context *ctx)
{
    if (auto *casting = dynamic_cast<ChipsParser::CCastAsContext *>(ctx))
        return translateCCast(casting->c_cast());

    if (auto *fctcall = dynamic_cast<ChipsParser::FunctionCallContext *>(ctx))
        return translateCFunctionCall(fctcall);

    if (auto *literal = dynamic_cast<ChipsParser::CBOOLContext *>(ctx))
        return "chips_bool{" + literal->BOOL()->getText() + "}";

    if (auto *literal = dynamic_cast<ChipsParser::CFLOATContext *>(ctx))
        return "chips_float{" + literal->FLOAT()->getText() + "}";

    if (auto *literal = dynamic_cast<ChipsParser::CINTContext *>(ctx))
        return "chips_int{" + literal->INT()->getText() + "}";

    if (dynamic_cast<ChipsParser::INPUTContext *>(ctx))
        return "input";

    if (auto *variable = dynamic_cast<ChipsParser::CVariableExpressionContext *>(ctx))
    {
        return variable->IDENTIFIER()->getText() + translateCSuffixes(variable->c_suffixes());
    }

    if (auto *ctxvar = dynamic_cast<ChipsParser::CtxVariableExpressionContext *>(ctx))
        return ctxvar->IDENTIFIER()->getText() + translateCSuffixes(ctxvar->c_suffixes());

    if (auto *accu = dynamic_cast<ChipsParser::ChanneledAccuExpressionContext *>(ctx))
        return accu->IDENTIFIER(0)->getText() + "." + accu->IDENTIFIER(1)->getText() + translateCSuffixes(accu->c_suffixes());

    if (auto *parens = dynamic_cast<ChipsParser::CParenthesisContext *>(ctx))
        return "(" + translateCStoplessExpr(parens->c_stopless_expr()) + ")";

    std::cout << "unhandled: " << ctx->getText() << std::endl;
    throw ctx;
}

std::string CodeGenListener::chipsTypeFor(ChipsParser::C_exprContext *ctx)
{
    if (auto *stopless = dynamic_cast<ChipsParser::CStoplessExpressionContext *>(ctx))
        return chipsTypeFor(stopless->c_stopless_expr());

    if (dynamic_cast<ChipsParser::StopContext *>(ctx))
        return "chips_bool";

    return "/* unknown type */";
}

std::string CodeGenListener::chipsTypeFor(ChipsParser::C_stopless_exprContext *ctx)
{
    if (dynamic_cast<ChipsParser::CLTContext *>(ctx))  return "chips_bool";
    if (dynamic_cast<ChipsParser::CGTContext *>(ctx))  return "chips_bool";
    if (dynamic_cast<ChipsParser::CLEQContext *>(ctx)) return "chips_bool";
    if (dynamic_cast<ChipsParser::CGEQContext *>(ctx)) return "chips_bool";
    if (dynamic_cast<ChipsParser::CNEQContext *>(ctx)) return "chips_bool";
    if (dynamic_cast<ChipsParser::CEQContext *>(ctx))  return "chips_bool";
    if (dynamic_cast<ChipsParser::CANDContext *>(ctx)) return "chips_bool";
    if (dynamic_cast<ChipsParser::CORContext *>(ctx))  return "chips_bool";

    if (auto *pass0 = dynamic_cast<ChipsParser::PassCExpr0Context *>(ctx))
        return chipsTypeFor(pass0->c_stopless_expr0());

    return "/* unknown type */";
}

std::string CodeGenListener::chipsTypeFor(ChipsParser::C_stopless_expr0Context *ctx)
{
    if (auto *sub = dynamic_cast<ChipsParser::CSUBContext *>(ctx))
        return chipsTypeFor(sub->c_stopless_expr01());

    if (auto *plus = dynamic_cast<ChipsParser::CPLUSContext *>(ctx))
        return chipsTypeFor(plus->c_stopless_expr01());

    if (auto *pass01 = dynamic_cast<ChipsParser::PassCExpr01Context *>(ctx))
        return chipsTypeFor(pass01->c_stopless_expr01());

    return "/* unknown type */";
}

std::string CodeGenListener::chipsTypeFor(ChipsParser::C_stopless_expr01Context *ctx)
{
    if (auto *neg = dynamic_cast<ChipsParser::CNegateContext *>(ctx))
        return chipsTypeFor(neg->c_stopless_expr1());

    if (auto *pass1 = dynamic_cast<ChipsParser::PassCExpr1Context *>(ctx))
        return chipsTypeFor(pass1->c_stopless_expr1());

    return "/* unknown type */";
}

std::string CodeGenListener::chipsTypeFor(ChipsParser::C_stopless_expr1Context *ctx)
{
    if (auto *div = dynamic_cast<ChipsParser::CDIVContext *>(ctx))
        return chipsTypeFor(div->c_stopless_expr2());

    if (dynamic_cast<ChipsParser::CNOTContext *>(ctx))
        return "chips_bool";

    if (auto *mod = dynamic_cast<ChipsParser::CMODContext *>(ctx))
        return chipsTypeFor(mod->c_stopless_expr2());

    if (auto *mult = dynamic_cast<ChipsParser::CMULTContext *>(ctx))
        return chipsTypeFor(mult->c_stopless_expr2());

    if (auto *pass2 = dynamic_cast<ChipsParser::PassCExpr2Context *>(ctx))
        return chipsTypeFor(pass2->c_stopless_expr2());

    return "/* unknown type */";
}

std::string CodeGenListener::chipsTypeFor(ChipsParser::C_stopless_expr2Context *ctx)
{
    if (auto *casting = dynamic_cast<ChipsParser::CCastAsContext *>(ctx))
        return "chips_" + casting->c_cast()->df_type()->getText();

    if (dynamic_cast<ChipsParser::FunctionCallContext *>(ctx))
        return "chips_int /* unresolved function return type */";

    if (dynamic_cast<ChipsParser::CBOOLContext *>(ctx))
        return "chips_bool";

    if (dynamic_cast<ChipsParser::CFLOATContext *>(ctx))
        return "chips_float";

    if (dynamic_cast<ChipsParser::CINTContext *>(ctx))
        return "chips_int";

    if (dynamic_cast<ChipsParser::INPUTContext *>(ctx))
        return "chips_any /* input */";

    if (auto *variable = dynamic_cast<ChipsParser::CVariableExpressionContext *>(ctx))
    {
        std::string type;
        if (lookupVarType(variable->IDENTIFIER()->getText(), type))
            return type;
        return "chips_any";
    }

    if (auto *parens = dynamic_cast<ChipsParser::CParenthesisContext *>(ctx))
        return chipsTypeFor(parens->c_stopless_expr());

    return "/* unknown type */";
}



std::string CodeGenListener::aggregateStructName(const std::vector<ChipsParser::Cdf_defaulted_declContext *> &params)
{
    std::string name = "Aggr";
    for (auto *p : params)
        name += capitalize(p->df_type()->getText());
    name += "_t";
    return name;
}

std::string CodeGenListener::aggregateStructDef(const std::vector<ChipsParser::Cdf_defaulted_declContext *> &params)
{
    std::ostringstream oss;
    oss << "struct " << aggregateStructName(params) << "{\n";
    for (auto *p : params)
    {
        oss << "    " << chipsTypeFor(p->df_type()) << ' ' << p->IDENTIFIER()->getText()
            << '{' << translateCExpr(p->c_expr()) << "};\n";
    }
    oss << "};\n\n";
    return oss.str();
}

void CodeGenListener::emitAggregateStructIfNeeded(ChipsParser::Collective_op_defContext *ctx)
{
    const auto &params = ctx->c_signature()->cdf_defaulted_decl();
    if (params.empty())
        return;

    const std::string name = aggregateStructName(params);
    if (emittedAggrStructs_.count(name))
        return;

    out_ << aggregateStructDef(params);
    emittedAggrStructs_.insert(name);
}


void CodeGenListener::registerChannels(const ObjectType &key)
{
    ChipsParser::With_sectionContext *withSection = std::visit(
        [](auto *ctx) -> ChipsParser::With_sectionContext*
        {
            return ctx->with_section();
        },
        key);

    if (!withSection)
        return;

    for (auto *stmt : withSection->with_statement())
    {
        auto *chanDecl = dynamic_cast<ChipsParser::ChannelDeclarationContext *>(stmt);
        if (!chanDecl)
            continue;

        const std::string type = chanDecl->IDENTIFIER(0)->getText();
        const std::string name = chanDecl->IDENTIFIER(1)->getText();
        channels_[key].insert({type, name});
    }
}

void CodeGenListener::exitObject_def(ChipsParser::Object_defContext *ctx)
{
    registerChannels(ObjectType{ctx});
}

const std::set<std::pair<std::string, std::string>> *CodeGenListener::findChannelsForObjectName(const std::string &name) const
{
    for (const auto &[key, chans] : channels_)
    {
        if (const auto *objCtxPtr = std::get_if<ChipsParser::Object_defContext*>(&key))
        {
            if ((*objCtxPtr)->IDENTIFIER()->getText() == name)
                return &chans;
        }
        if (const auto *objCtxPtr = std::get_if<ChipsParser::P_function_defContext*>(&key))
        {
            if ((*objCtxPtr)->IDENTIFIER()->getText() == name)
                return &chans;
        }
    }
    return nullptr;
}

// // // // // // // // // // // // // // // // // // // // // // // // // // // // void CodeGenListener::storeCollectiveVar(
// // // // // // // // // // // // // // // // // // // // // // // // // // // //     ChipsParser::Collective_op_defContext* ctx,
// // // // // // // // // // // // // // // // // // // // // // // // // // // //     const std::string& var_name,
// // // // // // // // // // // // // // // // // // // // // // // // // // // //     const std::string& type)
// // // // // // // // // // // // // // // // // // // // // // // // // // // // {
// // // // // // // // // // // // // // // // // // // // // // // // // // // //     if (!ctx || var_name.empty()) {
// // // // // // // // // // // // // // // // // // // // // // // // // // // //         throw std::invalid_argument("Invalid arguments");
// // // // // // // // // // // // // // // // // // // // // // // // // // // //     }
// // // // // // // // // // // // // // // // // // // // // // // // // // // //     collective_vars_[ctx][var_name] = type;
// // // // // // // // // // // // // // // // // // // // // // // // // // // // }

std::string CodeGenListener::extractParameters(ChipsParser::Collective_op_defContext *ctx)
{
    auto *signature = ctx->c_signature();
    const std::string structName = aggregateStructName(signature->cdf_defaulted_decl());

    std::ostringstream oss;
    oss << "chips_int& channel_indicator";
    oss << ", " << structName << "& _accumulator";

    const std::string supportTypeName = signature->IDENTIFIER(1)->getText();
    if (const auto *chans = findChannelsForObjectName(supportTypeName))
    {
        for (const auto &[type, name] : *chans)
        {
            oss << ", " << structName << "& " << name << "_acc";
        }
    }

    return oss.str();
}

void CodeGenListener::exitCollective_op_def(ChipsParser::Collective_op_defContext *ctx)
{
    current_def = ctx;
    const std::string suffix = isSpreadOp(ctx) ? "_down" : "_up";
    
    emitAggregateStructIfNeeded(ctx);


    out_ << "\nvoid " << ctx->c_signature()->IDENTIFIER(0)->getText()<< suffix << "("<< extractParameters(ctx) <<")\n{\n";
    out_ << translateCStatements(ctx->c_statement(), 4);
    out_ << "}\n";
}
