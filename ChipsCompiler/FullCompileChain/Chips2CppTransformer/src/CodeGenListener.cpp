#include "CodeGenListener.h"

#include <sstream>

std::string CodeGenListener::translateStatements(
    const std::vector<ChipsParser::StatementContext *> &statements, int indent)
{
    std::ostringstream oss;
    for (auto *stmt : statements)
    {
        oss << translateStatement(stmt, indent);
    }
    return oss.str();
}

std::string CodeGenListener::translateStatement(ChipsParser::StatementContext *stmt, int indent)
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

    // StatementDeclaration / StatementAssignment / StatementContextualAssignment
    // already include their trailing ';' per the grammar, and already look
    // like valid C++, so copy the original text as-is.
    // return pad + tokens_.getText(stmt) + "\n";

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
        // foreach x in y[*] { ... }  ->  for (auto& x : y) { ... }

        for (auto *idx : loopIn->suffixes()->expr())
        {
            source += "[" + tokens_.getText(idx) + "]";
        }

        oss << pad << "for (auto& " << varName << " : " << source << ")\n";
        oss << pad << "{\n";
        oss << translateStatements(ctx->statement(), indent + 4);
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

        std::string genVar = "__gen_" + varName;
        std::string indices("");
        for (auto *idx : loopIn->suffixes()->expr())
        {
            indices += "[" + tokens_.getText(idx) + "]";
        }

        oss << pad << "{\n";
        oss << pad << "    auto " << genVar << " = " << source << "(" << argList << ")"+indices+";\n";
        oss << pad << "    for(size_t i = 0; i<"+genVar+".size(); ++i) {\n";
        oss << translateStatements(ctx->statement(), indent + 8);
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
    oss << translateStatements(ctx->statement(), indent + 4);
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
    oss << translateStatements(ctx->statement(), indent + 4);
    oss << pad << "}\n";
    return oss.str();
}

void CodeGenListener::emitSection(const std::string &funcName,
                                   const std::string &suffix,
                                   const std::vector<ChipsParser::StatementContext *> &statements)
{
    out_ << "void " << funcName << "_" << suffix << "()\n{\n";
    out_ << translateStatements(statements, 4);
    out_ << "}\n\n";
}

void CodeGenListener::exitL_function_def(ChipsParser::L_function_defContext *ctx)
{
    const std::string name = ctx->IDENTIFIER()->getText();

    emitSection(name, "init", ctx->init_section()->statement());
    emitSection(name, "then", ctx->then_section()->statement());
}

void CodeGenListener::exitP_function_def(ChipsParser::P_function_defContext *ctx)
{
    const std::string name = ctx->IDENTIFIER()->getText();

    emitSection(name, "init", ctx->init_section()->statement());
    emitSection(name, "then", ctx->then_section()->statement());
}