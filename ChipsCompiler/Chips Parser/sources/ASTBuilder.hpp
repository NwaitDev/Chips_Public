#ifndef AST_BUILD_HPP
#define AST_BUILD_HPP

#include "ChipsBaseVisitor.h"
#include "ast_base.hpp"
#include "ast_program.hpp"
#include "ast_lrxvalues.hpp"
#include "ast_statements.hpp"
#include "ast_variables.hpp"
#include "ast_builder_details.hpp"

#include <any>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include "cxxabi.h"

using namespace chips;



class ASTBuilder : public ChipsBaseVisitor {
    private:
        template<dataflow_type dft>
        struct VarDeclPair {
            std::unique_ptr<dataflow_primitive_variable<dft>> var;
            dataflow_declaration<dft, statement_env::DEFINITION> decl;
            VarDeclPair(std::string name){
                    var = std::make_unique<dataflow_primitive_variable<dft>>(name, decl);
                    decl.set_variable(var);
                }
        };


    public:

    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    // PROGRAM LEVEL VISIT METHODS

    std::any visitProgram(ChipsParser::ProgramContext* ctx) override {
        program_node prgm;
        std::cout<< "nb preambles " <<ctx->preamble().size()<<std::endl;
        for(ChipsParser::PreambleContext* pc : ctx->preamble()){

            #define APPEND_CASTED_DEF(POTENTIAL) \
            if(POTENTIAL* stuff = dynamic_cast<POTENTIAL*>(pc); stuff != nullptr){ \
                prgm.get_preamble().add_definition(std::any_cast<definition_variant>(visit(stuff))); \
                continue; \
            }

            APPEND_CASTED_DEF(ChipsParser::ObjectDefinitionContext)
            APPEND_CASTED_DEF(ChipsParser::CollectiveOperationDefinitionContext)
            APPEND_CASTED_DEF(ChipsParser::ImplementationDefinitionContext)
            APPEND_CASTED_DEF(ChipsParser::FunctionDefinitionContext)

            #undef APPEND_CASTED_DEF

            std::cerr<<"Unknown definition type in the preamble section!\n";
        }

        std::cout<< "nb statements in system section root level: "
                <<ctx->system()->s_statement().size()<<std::endl;
        for (ChipsParser::S_statementContext* ssc : ctx->system()->s_statement())
        {

            #define SSTATEMENT_CAST(POTENTIAL) \
            if(ChipsParser::ObjectDeclarationContext* stuff = dynamic_cast<ChipsParser::ObjectDeclarationContext*>(ssc);stuff != nullptr){ \
                prgm.get_system().add_system_statement(std::any_cast<system_statement_variant>(visit(stuff))); \
                continue; \
            }

            SSTATEMENT_CAST(ChipsParser::ObjectDeclarationContext)
            SSTATEMENT_CAST(ChipsParser::FeedingStatementContext)
            SSTATEMENT_CAST(ChipsParser::LinkingStatementContext)
            SSTATEMENT_CAST(ChipsParser::ImplementationStatementContext)
            SSTATEMENT_CAST(ChipsParser::SLoopStatementContext)
            SSTATEMENT_CAST(ChipsParser::SIfElseStatementContext)
            SSTATEMENT_CAST(ChipsParser::SIfStatementContext)
            SSTATEMENT_CAST(ChipsParser::RegularStatementContext)
            #undef SSTATEMENT_CAST

            std::cerr<<"Unknown statement type in the system section root level!\n";
        }
        
        return prgm;
    }


    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////



    





    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

    // expr

    std::any visitFunction(ChipsParser::FunctionContext* ctx) override {
        std::string fname = ctx->IDENTIFIER()->getText();
        std::cout<<"function_visited, symbol: "<<fname<<" ";
        if(fname.compare("is_fresh") == 0){
            return std::make_shared<direct<dataflow_type::BOOL, expression_env::PRIMITIVE>>(false);
        }
        if(fname.compare("range") == 0)
            return std::make_shared<direct<dataflow_type::INT, expression_env::PRIMITIVE>>(0);
        if(fname.compare("zeros") == 0)
            return std::make_shared<direct<dataflow_type::INT, expression_env::PRIMITIVE>>(0);
        throw std::runtime_error("could not recognize the function"+fname);
    }

    std::any visitLT(ChipsParser::LTContext* ctx) override {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::LTBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "LT");
    }

    std::any visitLEQ(ChipsParser::LEQContext* ctx) override {
       return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::LEQBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "LEQ");
    }

    std::any visitGT(ChipsParser::GTContext* ctx) override {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::GTBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "GT");
    }

    std::any visitGEQ(ChipsParser::GEQContext* ctx) override {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::GEQBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "GEQ");
    }

    std::any visitEQ(ChipsParser::EQContext* ctx) override {
        return ast_builder_detail::dispatch_binary<ast_builder_detail::EQBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "EQ");
    }

    std::any visitNEQ(ChipsParser::NEQContext* ctx) override {
        return ast_builder_detail::dispatch_binary<ast_builder_detail::NEQBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "NEQ");
    }

    std::any visitAND(ChipsParser::ANDContext* ctx) override {
        return ast_builder_detail::dispatch_boolean_binary<ast_builder_detail::ANDBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "AND");
    }

    std::any visitOR(ChipsParser::ORContext* ctx) override {
        return ast_builder_detail::dispatch_boolean_binary<ast_builder_detail::ORBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "OR");
    }


    std::any visitPLUS(ChipsParser::PLUSContext* ctx) override {
        // std::cout << "visitPLUS()" << std::endl;
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::PlusBuilder>(
            visit(ctx->expr1()), visit(ctx->expr0()), "PLUS");
    }

    std::any visitSUB(ChipsParser::SUBContext* ctx) override {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::SubBuilder>(
            visit(ctx->expr1()), visit(ctx->expr0()), "SUB");
    }

    std::any visitNegate(ChipsParser::NegateContext* ctx) override {
        return ast_builder_detail::dispatch_numeric_unary<ast_builder_detail::NegateBuilder>(
            visit(ctx->expr1()), "Negate");
    }


    std::any visitMULT(ChipsParser::MULTContext* ctx) override {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::MultBuilder>(
            visit(ctx->expr2()), visit(ctx->expr1()), "MULT");
    }

    std::any visitDIV(ChipsParser::DIVContext* ctx) override {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::DivBuilder>(
            visit(ctx->expr2()), visit(ctx->expr1()), "DIV");
    }

    std::any visitMOD(ChipsParser::MODContext* ctx) override {
        
        auto left_prim = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr2()));
        auto right_prim = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr1()));
        if (left_prim && right_prim) {
            return ast_builder_detail::ModBuilder<dataflow_type::INT, expression_env::PRIMITIVE>::build(left_prim, right_prim);   
        }

        auto left_collect = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(visit(ctx->expr2()));
        auto right_collect = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(visit(ctx->expr1()));
        if(left_collect && right_collect){
            return ast_builder_detail::ModBuilder<dataflow_type::INT, expression_env::COLLECTIVE>::build(left_collect, right_collect);
        }

        auto left_system = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(visit(ctx->expr2()));
        auto right_system = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(visit(ctx->expr1()));
        if(left_system && right_system){
            return ast_builder_detail::ModBuilder<dataflow_type::INT, expression_env::SYSTEM>::build(left_system, right_system);
        }

        throw std::runtime_error("MOD : opérandes doivent être des entiers (INT)");
    }

    std::any visitNOT(ChipsParser::NOTContext* ctx) override {
        return ast_builder_detail::dispatch_boolean_unary<ast_builder_detail::NOTBuilder>(
            visit(ctx->expr2()), "NOT");
    }

    // atom
    std::any visitIntLiteral(ChipsParser::IntLiteralContext *ctx) override {
        // std::cout << "visitIntLit()" << std::endl;
        return std::make_shared<direct<dataflow_type::INT, expression_env::PRIMITIVE>>(std::stoll(ctx->INT()->getText()));
    }

    std::any visitFloatLiteral(ChipsParser::FloatLiteralContext *ctx) override {
        // std::cout << "visitFloatLit()" << std::endl;
        return std::make_shared<direct<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(std::stod(ctx->FLOAT()->getText()));
    }

    std::any visitBoolLiteral(ChipsParser::BoolLiteralContext* ctx) override {
        std::string text = ctx->BOOL()->getText();
        bool value = (text == "true");
        return std::make_shared<direct<dataflow_type::BOOL, expression_env::PRIMITIVE>>(value);
    }

    std::any visitParens(ChipsParser::ParensContext* ctx) override {
        auto result = visit(ctx->expr());

        // Essayez pour INT, FLOAT, BOOL
        if (auto v = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(result))
            v->set_parenthesage(true);
        else if (auto v = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(result))
            v->set_parenthesage(true);
        else if (auto v = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(result))
            v->set_parenthesage(true);

        return result;
    }

    std::any visitCastAs(ChipsParser::CastAsContext* ctx) override {
        // std::cout << "visitCastAs()" << std::endl;
        return visit(ctx->cast());
    }

    std::any handle_cast(dataflow_type target, std::any operand_any) {
        // PRIMITIVE
        switch(target) {
            case dataflow_type::INT:
                if(auto src = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(operand_any))
                    return std::make_shared<cast_as<dataflow_type::INT, expression_env::PRIMITIVE>>(
                        std::reinterpret_pointer_cast<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>>(src));
                if(auto src = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(operand_any))
                    return std::make_shared<cast_as<dataflow_type::INT, expression_env::PRIMITIVE>>(
                        std::reinterpret_pointer_cast<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>>(src));
                break;
            case dataflow_type::FLOAT:
                if(auto src = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(operand_any))
                    return std::make_shared<cast_as<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(
                        std::reinterpret_pointer_cast<rvalue<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(src));
                if(auto src = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(operand_any))
                    return std::make_shared<cast_as<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(
                        std::reinterpret_pointer_cast<rvalue<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(src));
                break;
            default:
                break;
        }
        // COLLECTIVE
        switch(target) {
            case dataflow_type::INT:
                if(auto src = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::COLLECTIVE>(operand_any))
                    return std::make_shared<cast_as<dataflow_type::INT, expression_env::COLLECTIVE>>(
                        std::reinterpret_pointer_cast<rvalue<dataflow_type::INT, expression_env::COLLECTIVE>>(src));
                if(auto src = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(operand_any))
                    return std::make_shared<cast_as<dataflow_type::INT, expression_env::COLLECTIVE>>(
                        std::reinterpret_pointer_cast<rvalue<dataflow_type::INT, expression_env::COLLECTIVE>>(src));
                break;
            case dataflow_type::FLOAT:
                if(auto src = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(operand_any))
                    return std::make_shared<cast_as<dataflow_type::FLOAT, expression_env::COLLECTIVE>>(
                        std::reinterpret_pointer_cast<rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>>(src));
                if(auto src = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::COLLECTIVE>(operand_any))
                    return std::make_shared<cast_as<dataflow_type::FLOAT, expression_env::COLLECTIVE>>(
                        std::reinterpret_pointer_cast<rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>>(src));
                break;
            default:
                break;
        }
        // SYSTEM
        switch(target) {
            case dataflow_type::INT:
                if(auto src = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::SYSTEM>(operand_any))
                    return std::make_shared<cast_as<dataflow_type::INT, expression_env::SYSTEM>>(
                        std::reinterpret_pointer_cast<rvalue<dataflow_type::INT, expression_env::SYSTEM>>(src));
                if(auto src = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(operand_any))
                    return std::make_shared<cast_as<dataflow_type::INT, expression_env::SYSTEM>>(
                        std::reinterpret_pointer_cast<rvalue<dataflow_type::INT, expression_env::SYSTEM>>(src));
                break;
            case dataflow_type::FLOAT:
                if(auto src = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(operand_any))
                    return std::make_shared<cast_as<dataflow_type::FLOAT, expression_env::SYSTEM>>(
                        std::reinterpret_pointer_cast<rvalue<dataflow_type::FLOAT, expression_env::SYSTEM>>(src));
                if(auto src = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::SYSTEM>(operand_any))
                    return std::make_shared<cast_as<dataflow_type::FLOAT, expression_env::SYSTEM>>(
                        std::reinterpret_pointer_cast<rvalue<dataflow_type::FLOAT, expression_env::SYSTEM>>(src));
                break;
            default:
                break;
        }
        throw std::runtime_error("cast_as : seuls les casts numériques INT↔FLOAT sont supportés.");
    }

    std::any visitCast(ChipsParser::CastContext* ctx) override {
        // std::cout << "visitCast()" << std::endl;

        // Type
        dataflow_type target = std::any_cast<dataflow_type>(visit(ctx->df_type()));

        // Operande
        std::any operand_any = visit(ctx->expr());

       return handle_cast(target, operand_any);
    }

    // Type primitif
    std::any visitIntType(ChipsParser::IntTypeContext* /*ctx*/) override {
        return dataflow_type::INT;
    }

    std::any visitFloatType(ChipsParser::FloatTypeContext* /*ctx*/) override {
        return dataflow_type::FLOAT;
    }

    std::any visitBoolType(ChipsParser::BoolTypeContext* /*ctx*/) override {
        return dataflow_type::BOOL;
    }

    std::any visitSuffixes(ChipsParser::SuffixesContext* ctx) override {
        //TODO: Implémenter
        return std::any{};
    }

    /**
     * STATEMENT
     */
    std::any handle_statement_declaration(dataflow_type type, std::any suffixes, std::string identifier){
        switch(type){
            case dataflow_type::INT: {
                dataflow_primitive_variable<dataflow_type::INT> var_temp(identifier, nullptr);
                dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION> decl(var_temp);
                dataflow_primitive_variable<dataflow_type::INT> var(identifier, &decl);
                decl.m_variable = var;
                return decl;
            }
            case dataflow_type::FLOAT: {
                dataflow_primitive_variable<dataflow_type::FLOAT> var_temp(identifier, nullptr);
                dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION> decl(var_temp);
                dataflow_primitive_variable<dataflow_type::FLOAT> var(identifier, &decl);
                decl.m_variable = var;
                return decl;
            }
            case dataflow_type::BOOL: {
                dataflow_primitive_variable<dataflow_type::BOOL> var_temp(identifier, nullptr);
                dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION> decl(var_temp);
                dataflow_primitive_variable<dataflow_type::BOOL> var(identifier, &decl);
                decl.m_variable = var;
                return decl;
            }
        }
    }

    // std::any visitStatementDeclaration(ChipsParser::StatementDeclarationContext* ctx) override {
    //     std::cout << "visitStatementDeclaration()" << std::endl;

    //     dataflow_type type_any = std::any_cast<dataflow_type>(visit(ctx->df_type()));
    //     std::any suffixes = visit(ctx->suffixes());
    //     std::string var_name = ctx->IDENTIFIER()->getText();
    //     // std::any assign = visit(ctx->may_assign());
    //     std::any assign;

    //     if(ctx->expr()){
    //         assign = visit(ctx->expr());
    //     }else{
    //         assign = std::any{};
    //     }

    //     if(!assign.has_value()){
    //         std::cout << "ASSIGN VIDE" << std::endl;
    //         return handle_statement_declaration(type_any, suffixes, var_name);
    //     }
    //     return std::any{};        
    // }

    // std::any visitStatementAssignment(ChipsParser::StatementAssignmentContext* ctx) override {
    //     return std::any{};
    // }   

    // std::any visitStatementContextualAssignment(ChipsParser::StatementContextualAssignment* ctx) override {

    // }

    // std::any visitMay_assign(ChipsParser::May_assignContext *ctx) override {
    //     // std::cout << "visitMay_assign()" << std::endl;

    //     if(ctx->expr() != nullptr){
    //         return visit(ctx->expr());
    //     }
    //     return std::any{};
    // }

    // pass to children
    std::any visitPassExpr0(ChipsParser::PassExpr0Context* ctx) override {
        return visit(ctx->expr0());
    }

    std::any visitPassExpr1(ChipsParser::PassExpr1Context* ctx) override {
        return visit(ctx->expr1());
    }

    std::any visitPassExpr2(ChipsParser::PassExpr2Context* ctx) override {
        return visit(ctx->expr2());
    }

    private:

        void print_any_type(const std::any& a){
            std::cout << "Type: " << a.type().name();
            int status;
            char* demangled = abi::__cxa_demangle(a.type().name(), 0, 0, &status);
            if(status == 0 && demangled){
                std::cout << " (" << demangled << ")";
                free(demangled);
            }
            std::cout << std::endl;
        }
};

#endif