#include "CodeGenListener.h"

#include <sstream>

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

    if (auto *decl = dynamic_cast<ChipsParser::StatementDeclarationContext *>(stmt)){
        return translateDecl(decl, indent, inScope);
    }

    std::string text("");
    antlr4::misc::Interval interval = stmt->getSourceInterval();
    for (int i = interval.a; i <= interval.b; i++) {
        text += tokens_.get(i)->getText()+" ";
    }
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
            source += "["+translateExpr(idx)+"]";
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
            if (i) argList += ", ";
            argList += tokens_.getText(args[i]);
        }

        std::string genVar = varName;
        std::string indices("");
        for (auto *idx : loopIn->suffixes()->expr())
        {
            indices += "[" + tokens_.getText(idx) + "]";
        }

        oss << pad << "{\n";
        oss << pad << "    auto " << genVar << " = " << source << "(" << argList << ")"+indices+";\n";
        oss << pad << "    for(chips_int i{0}; i<"+genVar+".size(); i = i+chips_int{1}) {\n";
        oss << translateStatements(ctx->statement(), indent + 8, true);
        oss << pad << "    }\n";
        oss << pad << "}\n";
    }

    return oss.str();
}

std::string CodeGenListener::translateIf(ChipsParser::If_statementContext *ctx, int indent)
{
    std::string pad(indent, ' ');
    std::string cond = tokens_.getText(ctx->expr());

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
    // The generated context normally contains a std::vector<ExprContext*> called
    // `expr()` (one for each pair of brackets).  If your grammar uses a
    // different accessor, replace the loop accordingly.
    std::vector<std::string> dimExprs;
    for (auto *e : s->expr()) {                     // iterate over every size expr
        dimExprs.emplace_back(translateExpr(e));    // reuse the existing expr helper
    }

    // Join with commas: "3, 5, n+2"
    std::ostringstream oss;
    for (size_t i = 0; i < dimExprs.size(); ++i) {
        if (i) oss << ", ";
        oss << dimExprs[i];
    }
    return oss.str();
}


std::string CodeGenListener::translateDecl(ChipsParser::StatementDeclarationContext *ctx, int indent, bool inScope)
{
    if (!inScope)
        return std::string{};
    
    std::string pad(indent, ' ');

    std::string chipType;
    auto *typeCtx = ctx->df_type();

    if (auto *b = dynamic_cast<ChipsParser::BoolTypeContext*>(typeCtx)) {
        chipType = "chips_bool";
    }
    else if (auto *i = dynamic_cast<ChipsParser::IntTypeContext*>(typeCtx)) {
        chipType = "chips_int";
    }
    else if (auto *f = dynamic_cast<ChipsParser::FloatTypeContext*>(typeCtx)) {
        chipType = "chips_float";
    }
    else {
        // Should never happen
        chipType = "/* unknown type */";
    }

    std::string varName = ctx->IDENTIFIER()->getText();


    std::string ctorArgs;
    if (auto *suffixes = ctx->suffixes()) {
        ctorArgs = translateSuffixes(suffixes);
    }

    std::string initializer;
    if (ctx->ASSIGN()) {
        // we already have a helper that turns an ExprContext into a C++ string
        initializer = " = " + translateExpr(ctx->expr());
    }

    std::ostringstream out;
    out << pad << chipType << ' ' << varName;

    if (!ctorArgs.empty()) {
        out << '(' << ctorArgs << ");\n";
    } else{
        out << ";\n";
    }

    if(!initializer.empty())
        out << pad << varName << initializer << ";\n";

    return out.str();
}

std::string CodeGenListener::translateFunction(ChipsParser::FunctionContext *ctx)
{
    std::ostringstream out;
    out << ctx->IDENTIFIER()->getText() << '(';

    const auto &args = ctx->expr();
    for (size_t i = 0; i < args.size(); ++i) {
        out << translateExpr(args[i]);
        if (i + 1 < args.size()) out << ", ";
    }
    out << ')';
    return out.str();
}

std::string CodeGenListener::translateExpr(ChipsParser::ExprContext* ctx)
{
    if (auto *geq = dynamic_cast<ChipsParser::GEQContext*>(ctx))
        return translateExpr0(geq->expr0()) + " >= " + translateExpr(geq->expr()); 

    if (auto *gt = dynamic_cast<ChipsParser::GTContext*>(ctx))
        return translateExpr0(gt->expr0()) + " > " + translateExpr(gt->expr());

    if (auto *orctx = dynamic_cast<ChipsParser::ORContext*>(ctx))
        return translateExpr0(orctx->expr0()) + " || " + translateExpr(orctx->expr());

    if (auto *andctx = dynamic_cast<ChipsParser::ANDContext*>(ctx))
        return translateExpr0(andctx->expr0()) + " && " + translateExpr(andctx->expr());

    if (auto *lt = dynamic_cast<ChipsParser::LTContext*>(ctx))
        return translateExpr0(lt->expr0()) + " < " + translateExpr(lt->expr());

    if (auto *leq = dynamic_cast<ChipsParser::LEQContext*>(ctx))
        return translateExpr0(leq->expr0()) + " <= " + translateExpr(leq->expr());
    
    if (auto *neq = dynamic_cast<ChipsParser::NEQContext*>(ctx))
        return translateExpr0(neq->expr0()) + " != " + translateExpr(neq->expr());
    
    if (auto *eq = dynamic_cast<ChipsParser::EQContext*>(ctx))
        return translateExpr0(eq->expr0()) + " == " + translateExpr(eq->expr());
    
    if (auto *pass0 = dynamic_cast<ChipsParser::PassExpr0Context*>(ctx))
        return translateExpr0(pass0->expr0());

    return ctx->getText();   // fallback for any unhandled rule
}

std::string CodeGenListener::translateExpr0(ChipsParser::Expr0Context* ctx)
{
    if (auto *sub = dynamic_cast<ChipsParser::SUBContext*>(ctx))
        return translateExpr01(sub->expr01()) + " - " + translateExpr0(sub->expr0());
    
    if (auto *plus = dynamic_cast<ChipsParser::PLUSContext*>(ctx))
        return translateExpr01(plus->expr01()) + " + " + translateExpr0(plus->expr0());

    if (auto *pass01 = dynamic_cast<ChipsParser::PassExpr01Context*>(ctx))
        return translateExpr01(pass01->expr01());

    return ctx->getText();   // fallback for any unhandled rule
}

std::string CodeGenListener::translateExpr01(ChipsParser::Expr01Context* ctx)
{        
    if (auto *neg = dynamic_cast<ChipsParser::NegateContext*>(ctx))
        return "-" + translateExpr1(neg->expr1());
    
    if (auto *pass1 = dynamic_cast<ChipsParser::PassExpr1Context*>(ctx))
        return translateExpr1(pass1->expr1());
    
    return ctx->getText();   // fallback for any unhandled rule
}

std::string CodeGenListener::translateExpr1(ChipsParser::Expr1Context* ctx)
{
    if (auto *div = dynamic_cast<ChipsParser::DIVContext*>(ctx))
        return translateExpr2(div->expr2()) + " / " + translateExpr1(div->expr1());
    
    if (auto *notexpr = dynamic_cast<ChipsParser::NOTContext*>(ctx))
        return "!" + translateExpr2(notexpr->expr2());
    
    if (auto *mod = dynamic_cast<ChipsParser::MODContext*>(ctx))
        return translateExpr2(mod->expr2()) + " % " + translateExpr1(mod->expr1());
    
    if (auto *mult = dynamic_cast<ChipsParser::MULTContext*>(ctx))
        return translateExpr2(mult->expr2()) + " * " + translateExpr1(mult->expr1());
    
    if (auto *pass2 = dynamic_cast<ChipsParser::PassExpr2Context*>(ctx))
        return translateExpr2(pass2->expr2());

    return ctx->getText();   // fallback for any unhandled rule
}

std::string CodeGenListener::translateExpr2(ChipsParser::Expr2Context* ctx)
{   
    if (auto *casting = dynamic_cast<ChipsParser::CastAsContext*>(ctx))
        return "static_cast<chips_"+ casting->cast()->df_type()->getText() +">("+translateExpr(casting->cast()->expr())+")";
    
    if (auto* fctcall = dynamic_cast<ChipsParser::FunctionContext*>(ctx))
        return translateFunction(fctcall);
    
    if (auto* literal = dynamic_cast<ChipsParser::BoolLiteralContext*>(ctx))
        return literal->BOOL()->getText();
    
    if (auto* literal = dynamic_cast<ChipsParser::FloatLiteralContext*>(ctx))
        return literal->FLOAT()->getText();
    
    if (auto* literal = dynamic_cast<ChipsParser::IntLiteralContext*>(ctx))
        return literal->INT()->getText();
    
    if (auto* variable = dynamic_cast<ChipsParser::VarContext*>(ctx))
        return variable->IDENTIFIER()->getText()+translateSuffixes(variable->suffixes());

    if (auto* parens = dynamic_cast<ChipsParser::ParensContext*>(ctx))
        return "("+translateExpr(parens->expr())+")";

    return ctx->getText();   // fallback for any unhandled rule
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

std::string CodeGenListener::translateParams(const std::vector<ChipsParser::Df_parameter_declContext *> &params)
{
    std::ostringstream oss;
    for (size_t i = 0; i < params.size(); ++i)
    {
        if (i) oss << ", ";
        oss << chipsTypeFor(params[i]->df_type()) << "& " << params[i]->IDENTIFIER()->getText();
    }
    return oss.str();
}

std::string CodeGenListener::translateParams(const std::vector<ChipsParser::Pdf_parameter_declContext *> &params)
{
    std::ostringstream oss;
    for (size_t i = 0; i < params.size(); ++i)
    {
        if (i) oss << ", ";

        ChipsParser::Df_typeContext *typeCtx = nullptr;
        auto *ptype = params[i]->pdf_parameter_type();
        if (auto *f = dynamic_cast<ChipsParser::FunctionParameterTypeContext *>(ptype))
            typeCtx = f->df_type();
        else if (auto *s = dynamic_cast<ChipsParser::SensorParameterTypeContext *>(ptype))
            typeCtx = s->df_type();

        oss << chipsTypeFor(typeCtx) << "& " << params[i]->IDENTIFIER()->getText();
    }
    return oss.str();
}

void CodeGenListener::emitSection(const std::string &funcName, const std::string &suffix, const std::vector<ChipsParser::StatementContext *> &statements, const std::string &params)
{
    out_ << "void " << funcName << "_" << suffix << "(" << params << ")\n{\n";
    out_ << translateStatements(statements, 4, false);
    out_ << "}\n\n";
}

void CodeGenListener::exitL_function_def(ChipsParser::L_function_defContext *ctx)
{
    const std::string name = ctx->IDENTIFIER()->getText();
    const std::string params = translateParams(ctx->df_parameter_decl());

    emitSection(name, "init", ctx->init_section()->statement(), params);
    emitSection(name, "then", ctx->then_section()->statement(), params);
}

void CodeGenListener::exitP_function_def(ChipsParser::P_function_defContext *ctx)
{
    const std::string name = ctx->IDENTIFIER()->getText();
    const std::string params = translateParams(ctx->pdf_parameter_decl());

    emitSection(name, "init", ctx->init_section()->statement(), params);
    emitSection(name, "then", ctx->then_section()->statement(), params);
}