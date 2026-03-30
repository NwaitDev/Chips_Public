#ifndef AST_BUILD_HPP
#define AST_BUILD_HPP

#include "chips_headers.hpp"
#include "ast_builder_details.hpp"

#include <any>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include "cxxabi.h"

using namespace chips;

class ASTBuilder : public ChipsBaseVisitor
{
private:
    expression_env current_env = expression_env::PRIMITIVE;

    // Arène de noeuds alloués sur le tas dans le builder.
    // Les shared_ptr ici prolongent la durée de vie de tous les nœuds
    // intermédiaires (decl, var, left) dont d'autres nœuds gardent
    // des raw pointers. À vider explicitement si besoin de reset.
    std::vector<std::shared_ptr<ast_node>> node_arena;

public:

    std::any visitProgram(ChipsParser::ProgramContext *ctx);
    
    std::any visitObjectDefinition(ChipsParser::ObjectDefinitionContext *ctx);

    std::any visitCollectiveOperationDefinition(ChipsParser::CollectiveOperationDefinitionContext *ctx);

    std::any visitImplementationDefinition(ChipsParser::ImplementationDefinitionContext *ctx);

    std::any visitObject_def(ChipsParser::Object_defContext *ctx);

    std::any visitImplementation_def(ChipsParser::Implementation_defContext *ctx);

    std::any visitNode_mapping(ChipsParser::Node_mappingContext *ctx);

    std::any visitLogicalDefintion(ChipsParser::LogicalDefintionContext *ctx);

    std::any visitPhysicalDefinition(ChipsParser::PhysicalDefinitionContext *ctx);

    std::any visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx);

    std::any visitDefaultOutput(ChipsParser::DefaultOutputContext *ctx);

    std::any visitChanneledOutput(ChipsParser::ChanneledOutputContext *ctx);

    std::any visitL_function_def(ChipsParser::L_function_defContext *ctx);

    std::any visitP_function_def(ChipsParser::P_function_defContext *ctx);

    std::any visitC_signature(ChipsParser::C_signatureContext *ctx);

    std::any visitC_keywords(ChipsParser::C_keywordsContext *ctx);

    std::any visitWith_section(ChipsParser::With_sectionContext *ctx);

    std::any visitChannelDeclaration(ChipsParser::ChannelDeclarationContext *ctx);

    std::any visitContextualDeclaration(ChipsParser::ContextualDeclarationContext *ctx);

    std::any visitWithRegularStatement(ChipsParser::WithRegularStatementContext *ctx);

    std::any visitInit_section(ChipsParser::Init_sectionContext *ctx);

    std::any visitThen_section(ChipsParser::Then_sectionContext *ctx);

    template<dataflow_type dft, statement_env sttenv>
    std::any make_variable_expression(dataflow_assignment<dft,sttenv>& node){
        std::cout << "make variable expression assign" << std::endl;
        return std::any{};
    }

    template<dataflow_type dft, statement_env sttenv>
    std::any make_variable_expression(dataflow_declaration<dft,sttenv>& node){
        std::cout << "make variable expression decl" << std::endl;
        return std::any{};
    }

    std::any visitVar(ChipsParser::VarContext *ctx) override
    {
        std::cout << "visitVar()" << std::endl;
        std::string var_name = ctx->IDENTIFIER()->getText();
        std::optional<std::any> variable = SymbolTable::getInstance().lookupVariable(var_name);
        std::any suffixes = visit(ctx->suffixes());

        if(!variable.has_value()){
            throw std::runtime_error("'" + var_name + "' was never declarated before");
        }

        switch(current_env){
            case expression_env::PRIMITIVE: {
                try{
                    auto dims = std::any_cast<std::vector<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>*>>(suffixes);
                    auto var_ptr = std::any_cast<std::shared_ptr<dataflow_primitive_variable<dataflow_type::INT>>>(variable.value());
                    auto expr = std::make_shared<variable_expression<dataflow_type::INT, expression_env::PRIMITIVE>>(var_ptr.get(), dims);
                    return expr;
                }catch(const std::bad_any_cast& e){
                    throw std::runtime_error("bad any cast");
                }
            }
            // ... autres cas à compléter si besoin
        }
        throw std::runtime_error("visitVar: unsupported environment");
    }

    std::any visitVarContext(ChipsParser::VarContextContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method VarContextContext");
    }

    std::any visitCStoplessExpression(ChipsParser::CStoplessExpressionContext *ctx);

    std::any visitStop(ChipsParser::StopContext *ctx);

    std::any visitCLT(ChipsParser::CLTContext *ctx);

    std::any visitCGT(ChipsParser::CGTContext *ctx);

    std::any visitCLEQ(ChipsParser::CLEQContext *ctx);

    std::any visitCGEQ(ChipsParser::CGEQContext *ctx);

    std::any visitCNEQ(ChipsParser::CNEQContext *ctx);

    std::any visitCEQ(ChipsParser::CEQContext *ctx);

    std::any visitCAND(ChipsParser::CANDContext *ctx);

    std::any visitCOR(ChipsParser::CORContext *ctx);

    std::any visitPassCExpr0(ChipsParser::PassCExpr0Context *ctx);

    std::any visitCPLUS(ChipsParser::CPLUSContext *ctx);

    std::any visitCSUB(ChipsParser::CSUBContext *ctx);

    std::any visitCNegate(ChipsParser::CNegateContext *ctx);

    std::any visitPassCExpr1(ChipsParser::PassCExpr1Context *ctx);

    std::any visitCMULT(ChipsParser::CMULTContext *ctx);

    std::any visitCDIV(ChipsParser::CDIVContext *ctx);

    std::any visitCMOD(ChipsParser::CMODContext *ctx);

    std::any visitCNOT(ChipsParser::CNOTContext *ctx);

    std::any visitPassCExpr2(ChipsParser::PassCExpr2Context *ctx);

    std::any visitCVariableExpression(ChipsParser::CVariableExpressionContext *ctx);

    std::any visitCINT(ChipsParser::CINTContext *ctx);

    std::any visitCFLOAT(ChipsParser::CFLOATContext *ctx);

    std::any visitCBOOL(ChipsParser::CBOOLContext *ctx);

    std::any visitINPUT(ChipsParser::INPUTContext *ctx);

    std::any visitCtxVariableExpression(ChipsParser::CtxVariableExpressionContext *ctx);

    std::any visitChanneledAccuExpression(ChipsParser::ChanneledAccuExpressionContext *ctx);

    std::any visitFunctionCall(ChipsParser::FunctionCallContext *ctx);

    std::any visitCParenthesis(ChipsParser::CParenthesisContext *ctx);

    std::any visitCCastAs(ChipsParser::CCastAsContext *ctx);

    std::any visitC_cast(ChipsParser::C_castContext *ctx);

    std::any visitC_suffixes(ChipsParser::C_suffixesContext *ctx);

    std::any visitSSuffixableVariableExpression(ChipsParser::SSuffixableVariableExpressionContext *ctx);

    std::any visitSSuffixableFunctionCallExpression(ChipsParser::SSuffixableFunctionCallExpressionContext *ctx);

    std::any visitSSuffixableBlockOutputExpression(ChipsParser::SSuffixableBlockOutputExpressionContext *ctx);

    std::any visitBlock(ChipsParser::BlockContext *ctx);

    std::any visitLoop_in(ChipsParser::Loop_inContext *ctx);

    std::any visitLoop_statement(ChipsParser::Loop_statementContext *ctx);

    std::any visitC_loop_statement(ChipsParser::C_loop_statementContext *ctx);

    std::any visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx);

    std::any visitIf_else_statement(ChipsParser::If_else_statementContext *ctx);

    std::any visitS_if_else_statement(ChipsParser::S_if_else_statementContext *ctx);

    std::any visitC_if_else_statement(ChipsParser::C_if_else_statementContext *ctx);

    std::any visitIf_statement(ChipsParser::If_statementContext *ctx);

    std::any visitS_if_statement(ChipsParser::S_if_statementContext *ctx);

    std::any visitC_if_statement(ChipsParser::C_if_statementContext *ctx);

    std::any visitStatementAssignment(ChipsParser::StatementAssignmentContext *ctx) override
    {
        std::cout << "visitStatementAssignment()" << std::endl;

        current_env = expression_env::PRIMITIVE;

        std::any suffixes = visit(ctx->suffixes());
        std::string var_name = ctx->IDENTIFIER()->getText();
        std::any assign = visit(ctx->expr());

        // if(suffixes.has_value()){
        //     std::cout << "SUFFIXES VALUE" << std::endl;;
        // }else{
        //     std::cout << "SUFFIXES NOT VALUE" << std::endl;
        // }

        std::optional<std::any> variable = SymbolTable::getInstance().lookupVariable(var_name);

        if(!variable.has_value()){
            throw std::runtime_error("'"+var_name+"' was never declarated before");
        }

        //TODO regarder affectation de suffixes
        auto dims = std::any_cast<std::vector<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>*>>(suffixes);

        if(auto right = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(assign)){
            try{
                auto var_ptr = std::any_cast<std::shared_ptr<dataflow_primitive_variable<dataflow_type::INT>>>(variable.value());
                auto left = std::make_shared<variable_expression<dataflow_type::INT, expression_env::PRIMITIVE>>(var_ptr.get(), dims);
                node_arena.push_back(left);
                node_arena.push_back(right);
                dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION> assignment(left.get(), right.get());
                return assignment;
            }catch(const std::bad_any_cast& e){
                throw std::runtime_error("Erreur de cast dans la récupération du pointeur de variable INT depuis la SymbolTable");
            }           
        } else if(auto right = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(assign)){
            try{
                auto dims = std::any_cast<std::vector<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>*>>(suffixes);
                auto var_ptr = std::any_cast<std::shared_ptr<dataflow_primitive_variable<dataflow_type::FLOAT>>>(variable.value());
                auto left = std::make_shared<variable_expression<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(var_ptr.get(), dims);
                node_arena.push_back(left);
                node_arena.push_back(right);
                dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION> assignment(left.get(), right.get());
                return assignment;
            }catch(const std::bad_any_cast& e){
                throw std::runtime_error("Erreur de cast dans la récupération du pointeur de variable FLOAT depuis la SymbolTable");
            }
        } else if(auto right = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(assign)){
            try{
                auto dims = std::any_cast<std::vector<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>*>>(suffixes);
                auto var_ptr = std::any_cast<std::shared_ptr<dataflow_primitive_variable<dataflow_type::BOOL>>>(variable.value());
                auto left = std::make_shared<variable_expression<dataflow_type::BOOL, expression_env::PRIMITIVE>>(var_ptr.get(), dims);
                node_arena.push_back(left);
                node_arena.push_back(right);
                dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION> assignment(left.get(), right.get());
                return assignment;
            }catch(const std::bad_any_cast& e){
                throw std::runtime_error("Erreur de cast dans la récupération du pointeur de variable BOOL depuis la SymbolTable");
            }
        }

        throw std::runtime_error("Unimplemented visitStatementAssignment for other expression_env");
    }

    std::any visitStatementContextualAssignment(ChipsParser::StatementContextualAssignmentContext *ctx);

    std::any visitStatementLoop(ChipsParser::StatementLoopContext *ctx);

    std::any visitStatementIfElse(ChipsParser::StatementIfElseContext *ctx);

    std::any visitStatementIf(ChipsParser::StatementIfContext *ctx);

    std::any visitObjectDeclaration(ChipsParser::ObjectDeclarationContext *ctx);

    std::any visitFeedingStatement(ChipsParser::FeedingStatementContext *ctx);

    std::any visitLinkingStatement(ChipsParser::LinkingStatementContext *ctx);

    std::any visitImplementationStatement(ChipsParser::ImplementationStatementContext *ctx);

    std::any visitSLoopStatement(ChipsParser::SLoopStatementContext *ctx);

    std::any visitSIfElseStatement(ChipsParser::SIfElseStatementContext *ctx);

    std::any visitSIfStatement(ChipsParser::SIfStatementContext *ctx);

    std::any visitRegularStatement(ChipsParser::RegularStatementContext *ctx);

    std::any visitSBlockOutputExpression(ChipsParser::SBlockOutputExpressionContext *ctx);

    std::any visitSCollectiveCastExpression(ChipsParser::SCollectiveCastExpressionContext *ctx);

    std::any visitSRegularExpression(ChipsParser::SRegularExpressionContext *ctx);

    std::any visitCollective_operation(ChipsParser::Collective_operationContext *ctx);

    std::any visitCollectiveVariableDeclaration(ChipsParser::CollectiveVariableDeclarationContext *ctx);

    std::any visitCollectiveAssignment(ChipsParser::CollectiveAssignmentContext *ctx);

    std::any visitContextualAssignment(ChipsParser::ContextualAssignmentContext *ctx);

    std::any visitCollectiveLoopStatement(ChipsParser::CollectiveLoopStatementContext *ctx);

    std::any visitCollectiveIfElseStatement(ChipsParser::CollectiveIfElseStatementContext *ctx);

    std::any visitCollectiveIfStatement(ChipsParser::CollectiveIfStatementContext *ctx);

    std::any visitNamed_output(ChipsParser::Named_outputContext *ctx);

    std::any visitActuatorOutput(ChipsParser::ActuatorOutputContext *ctx);

    std::any visitFunctionOutput(ChipsParser::FunctionOutputContext *ctx);

    std::any visitDf_parameter_decl(ChipsParser::Df_parameter_declContext *ctx);

    std::any visit_dft(ChipsParser::Df_typeContext* dft);

    std::any visitFunctionParameterType(ChipsParser::FunctionParameterTypeContext *ctx);

    std::any visitSensorParameterType(ChipsParser::SensorParameterTypeContext *ctx);

    std::any visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *ctx);

    std::any visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *ctx);

    std::any visitCdf_full_declaration(ChipsParser::Cdf_full_declarationContext *ctx);

    std::any visitFunction(ChipsParser::FunctionContext *ctx);

    std::any visitLT(ChipsParser::LTContext *ctx);

    std::any visitLEQ(ChipsParser::LEQContext *ctx);

    std::any visitGT(ChipsParser::GTContext *ctx);

    std::any visitGEQ(ChipsParser::GEQContext *ctx);

    std::any visitEQ(ChipsParser::EQContext *ctx);

    std::any visitNEQ(ChipsParser::NEQContext *ctx);

    std::any visitAND(ChipsParser::ANDContext *ctx);

    std::any visitOR(ChipsParser::ORContext *ctx);

    std::any visitPLUS(ChipsParser::PLUSContext *ctx);

    std::any visitSUB(ChipsParser::SUBContext *ctx);

    std::any visitNegate(ChipsParser::NegateContext *ctx);

    std::any visitMULT(ChipsParser::MULTContext *ctx);

    std::any visitDIV(ChipsParser::DIVContext *ctx);

    std::any visitMOD(ChipsParser::MODContext *ctx);

    std::any visitNOT(ChipsParser::NOTContext *ctx);

    std::any visitIntLiteral(ChipsParser::IntLiteralContext *ctx);

    std::any visitFloatLiteral(ChipsParser::FloatLiteralContext *ctx);

    std::any visitBoolLiteral(ChipsParser::BoolLiteralContext *ctx);

    std::any visitParens(ChipsParser::ParensContext* ctx);

    std::any visitCastAs(ChipsParser::CastAsContext *ctx);

    std::any handle_cast(dataflow_type target, std::any operand_any);

    std::any visitCast(ChipsParser::CastContext *ctx);

    // Type primitif
    std::any visitIntType(ChipsParser::IntTypeContext * /*ctx*/);

    std::any visitFloatType(ChipsParser::FloatTypeContext * /*ctx*/);

    std::any visitBoolType(ChipsParser::BoolTypeContext * /*ctx*/);

    std::any visitSuffixes(ChipsParser::SuffixesContext* ctx) override {
        switch(current_env){
            case expression_env::PRIMITIVE: {
                std::vector<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>*> dims;

                for(auto* expr : ctx->expr()){
                    std::any val = visit(expr);
                    auto node = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(val);
                    if(!node){
                        throw std::runtime_error(
                            "suffixes : l'expression d'indice doit être de type INT "
                            "(env PRIMITIVE).");
                    }
                    node_arena.push_back(node);
                    dims.push_back(node.get());
                }
                return dims;
            }

            case expression_env::COLLECTIVE: {
                std::vector<rvalue<dataflow_type::INT, expression_env::COLLECTIVE>*> dims;

                for(auto* expr : ctx->expr()){
                    std::any val = visit(expr);
                    auto node = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(val);
                    if(!node){
                         throw std::runtime_error(
                            "suffixes : l'expression d'indice doit être de type INT "
                            "(env COLLECTIVE).");
                    }
                    dims.push_back(node.get());
                }
                return dims;
            }

            case expression_env::SYSTEM: {
                std::vector<rvalue<dataflow_type::INT, expression_env::SYSTEM>*> dims;

                for(auto* expr : ctx->expr()){
                    std::any val = visit(expr);
                    auto node = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(val);
                    if(!node){
                         throw std::runtime_error(
                            "suffixes : l'expression d'indice doit être de type INT "
                            "(env SYSTEM).");
                    }
                    dims.push_back(node.get());
                }
                return dims;
            }
        }
    }

    /**
     * STATEMENT
     */
    std::any handle_statement_declaration(dataflow_type type, std::any suffixes, std::string identifier, std::any assign, bool have_assign){
        /**
         * vartmp = dataflow_primitive_variable(identifier, nullptr);
         * decl = dataflow_declaration(vartmp);
         * var = dataflow_primitive_variable(identifier, &decl);
         * decl.m_variable = var;
         * left = variable_expression(decl.get_variable());
         * right = visit(assign);
         * assignment = dataflow_assignment(left, right);
         * return assignment;
         */
        auto dims = std::any_cast<std::vector<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>*>>(suffixes);
        switch(type){
            case dataflow_type::INT: {
                auto decl = std::make_shared<dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>>(
                    dataflow_primitive_variable<dataflow_type::INT>(identifier, nullptr));
                auto var = std::make_shared<dataflow_primitive_variable<dataflow_type::INT>>(
                    identifier, decl.get(), dims);
                decl->set_variable(*var);
                node_arena.push_back(decl);
                node_arena.push_back(var);
                if(!have_assign){
                    // Stocke un shared_ptr dans la SymbolTable
                    if(!SymbolTable::getInstance().declareVariable(identifier, var)){
                        throw std::runtime_error("Redeclare a variable already declared");
                    }
                    return *decl;
                }
                auto left = std::make_shared<variable_expression<dataflow_type::INT, expression_env::PRIMITIVE>>(var.get());
                node_arena.push_back(std::static_pointer_cast<ast_node>(left));
                auto right = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(assign);
                if(!right) throw std::runtime_error("handle_statement_declaration INT: expression droite invalide");
                dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION> assignment(left.get(), right.get());
                if(!SymbolTable::getInstance().declareVariable(identifier, var)){
                    throw std::runtime_error("Redeclare a variable already declared");
                }
                return assignment;
            }
            case dataflow_type::FLOAT: {
                auto decl = std::make_shared<dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>>(
                    dataflow_primitive_variable<dataflow_type::FLOAT>(identifier, nullptr));
                auto var = std::make_shared<dataflow_primitive_variable<dataflow_type::FLOAT>>(
                    identifier, decl.get(), dims);
                decl->set_variable(*var);
                node_arena.push_back(decl);
                node_arena.push_back(var);
                if(!have_assign){
                    if(!SymbolTable::getInstance().declareVariable(identifier, var)){
                        throw std::runtime_error("Redeclare a variable already declared");
                    }
                    return *decl;
                }
                auto left = std::make_shared<variable_expression<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(var.get());
                node_arena.push_back(std::static_pointer_cast<ast_node>(left));
                auto right = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(assign);
                if(!right) throw std::runtime_error("handle_statement_declaration FLOAT: expression droite invalide");
                dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION> assignment(left.get(), right.get());
                if(!SymbolTable::getInstance().declareVariable(identifier, var)){
                    throw std::runtime_error("Redeclare a variable already declared");
                }
                return assignment;
            }
            case dataflow_type::BOOL: {
                auto decl = std::make_shared<dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>>(
                    dataflow_primitive_variable<dataflow_type::BOOL>(identifier, nullptr));
                auto var = std::make_shared<dataflow_primitive_variable<dataflow_type::BOOL>>(
                    identifier, decl.get(), dims);
                decl->set_variable(*var);
                node_arena.push_back(decl);
                node_arena.push_back(var);
                if(!have_assign){
                    if(!SymbolTable::getInstance().declareVariable(identifier, var)){
                        throw std::runtime_error("Redeclare a variable already declared");
                    }
                    return *decl;
                }
                auto left = std::make_shared<variable_expression<dataflow_type::BOOL, expression_env::PRIMITIVE>>(var.get());
                node_arena.push_back(std::static_pointer_cast<ast_node>(left));
                auto right = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(assign);
                if(!right) throw std::runtime_error("handle_statement_declaration BOOL: expression droite invalide");
                dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION> assignment(left.get(), right.get());
                if(!SymbolTable::getInstance().declareVariable(identifier, var)){
                    throw std::runtime_error("Redeclare a variable already declared");
                }
                return assignment;
            }
        }
    }

    std::any visitStatementDeclaration(ChipsParser::StatementDeclarationContext* ctx) override {
        std::cout << "visitStatementDeclaration()" << std::endl;

        dataflow_type type_any = std::any_cast<dataflow_type>(visit(ctx->df_type()));
        current_env = expression_env::PRIMITIVE;
        std::any suffixes = visit(ctx->suffixes());
        std::string var_name = ctx->IDENTIFIER()->getText();
        // std::any assign = visit(ctx->may_assign());
        std::any assign;

        if(ctx->expr()){
            assign = visit(ctx->expr());
        }else{
            assign = std::any{};
        }

        if(!assign.has_value()){
            std::cout << "ASSIGN VIDE" << std::endl;
            auto decl = handle_statement_declaration(type_any, suffixes, var_name, assign, false);
            return decl;
        }else{
            std::cout << "ASSIGN REMPLI" << std::endl;
            auto assignment = handle_statement_declaration(type_any, suffixes, var_name, assign, true);
            return assignment;
        }
        return std::any{};        
    }
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
    std::any visitPassExpr0(ChipsParser::PassExpr0Context *ctx);

    std::any visitPassExpr1(ChipsParser::PassExpr1Context *ctx);

    std::any visitPassExpr2(ChipsParser::PassExpr2Context *ctx);
};

#endif