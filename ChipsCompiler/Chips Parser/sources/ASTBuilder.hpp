#ifndef AST_BUILD_HPP
#define AST_BUILD_HPP

#include "ChipsBaseVisitor.h"
#include "ast_base.hpp"
#include "ast_builder_details.hpp"
#include "ast_inoutputs.hpp"
#include "ast_lrxvalues.hpp"
#include "ast_program.hpp"
#include "ast_statements.hpp"
#include "ast_system_specific.hpp"
#include "ast_variables.hpp"
#include "ast_definitions.hpp"
#include "meta_type_conversions.hpp"
#include "ChipsSymbolTable.hpp"

#include <any>
#include <memory>
#include <stdexcept>
#include <typeinfo>
#include "cxxabi.h"

using namespace chips;

class ASTBuilder : public ChipsBaseVisitor
{
private:
    template <dataflow_type dft>
    struct VarDeclPair
    {
        std::unique_ptr<dataflow_primitive_variable<dft>> var;
        dataflow_declaration<dft, statement_env::DEFINITION> decl;
        VarDeclPair(std::string name)
        {
            var = std::make_unique<dataflow_primitive_variable<dft>>(name, decl);
            decl.set_variable(var);
        }
    };

    expression_env current_env = expression_env::PRIMITIVE;

public:
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    // PROGRAM LEVEL VISIT METHODS


    std::any visitProgram(ChipsParser::ProgramContext *ctx) override
    {
        program_node prgm;
        std::cout<<"visit program"<<std::endl;
        // std::cout << "nb preambles " << ctx->preamble().size() << std::endl;
        for (ChipsParser::PreambleContext *pc : ctx->preamble())
        {

#define APPEND_CASTED_DEF(POTENTIAL)                                                         \
    if (POTENTIAL *stuff = dynamic_cast<POTENTIAL *>(pc); stuff != nullptr)                  \
    {                                                                                        \
        prgm.get_preamble().add_definition(std::any_cast<definition_variant>(visit(stuff))); \
        continue;                                                                            \
    }

            APPEND_CASTED_DEF(ChipsParser::ObjectDefinitionContext)
            APPEND_CASTED_DEF(ChipsParser::CollectiveOperationDefinitionContext)
            APPEND_CASTED_DEF(ChipsParser::ImplementationDefinitionContext)
            APPEND_CASTED_DEF(ChipsParser::FunctionDefinitionContext)

#undef APPEND_CASTED_DEF

            std::cerr << "Unknown definition type in the preamble section!\n";
        }

        std::cout << "nb statements in system section root level: "
                  << ctx->system()->s_statement().size() << std::endl;
        for (ChipsParser::S_statementContext *ssc : ctx->system()->s_statement())
        {

#define SSTATEMENT_CAST(POTENTIAL)                                                                                                   \
    if (ChipsParser::ObjectDeclarationContext *stuff = dynamic_cast<ChipsParser::ObjectDeclarationContext *>(ssc); stuff != nullptr) \
    {                                                                                                                                \
        prgm.get_system().add_system_statement(std::any_cast<system_statement_variant>(visit(stuff)));                               \
        continue;                                                                                                                    \
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

            std::cerr << "Unknown statement type in the system section root level!\n";
        }

        return prgm;
    }

    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

    std::any visitObjectDefinition(ChipsParser::ObjectDefinitionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method ObjectDefinitionContext");
    }


    std::any visitCollectiveOperationDefinition(ChipsParser::CollectiveOperationDefinitionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CollectiveOperationDefinitionContext");
    }

    std::any visitImplementationDefinition(ChipsParser::ImplementationDefinitionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method ImplementationDefinitionContext");
    }

    std::any visitObject_def(ChipsParser::Object_defContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Object_defContext");
    }

    std::any visitImplementation_def(ChipsParser::Implementation_defContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Implementation_defContext");
    }

    std::any visitNode_mapping(ChipsParser::Node_mappingContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Node_mappingContext");
    }

    std::any visitLogicalDefintion(ChipsParser::LogicalDefintionContext *ctx) override
    {
        std::cout<<"visit logical definition"<<std::endl;
        ChipsParser::L_function_defContext* lfd = ctx->l_function_def();
        std::string identifier = lfd->IDENTIFIER()->getText();
        std::vector<ChipsParser::Df_parameter_declContext*> old_ast_params = lfd->df_parameter_decl();
        std::vector<function_parameter_variant> params;
        for (ChipsParser::Df_parameter_declContext* stuff : old_ast_params)
        {
            params.push_back(std::any_cast<function_parameter_variant>(visit(stuff)));
        }

        init_section init = std::any_cast<init_section>(visitInit_section(lfd->init_section()));
        then_section then = std::any_cast<then_section>(visitThen_section(lfd->then_section()));
        

        std::vector<ChipsParser::Named_outputContext*> old_ast_outputs = lfd->named_output();
        std::vector<function_output_variant> outputs;
        for (ChipsParser::Named_outputContext* stuff : old_ast_outputs)
        {
            outputs.push_back(std::any_cast<function_output_variant>(visit(stuff)));
        }

        return chips::logical_definition(identifier,params,init,then,outputs);
        //throw std::runtime_error("Unimplemented visit method LogicalDefintionContext");
    }

    std::any visitPhysicalDefinition(ChipsParser::PhysicalDefinitionContext *ctx) override
    {
        std::cout<<"visit physical definition"<<std::endl;
        ChipsParser::P_function_defContext* pfd = ctx->p_function_def();
        std::string identifier = pfd->IDENTIFIER()->getText();
        std::vector<ChipsParser::Pdf_parameter_declContext*> all_params = pfd->pdf_parameter_decl();
        std::vector<function_parameter_variant> params;
        std::vector<physical_parameter_variant> sensors;
        for(ChipsParser::Pdf_parameter_declContext* parameter : all_params){
            std::string pname = parameter->IDENTIFIER()->getText();
            if (ChipsParser::SensorParameterTypeContext* stuff = dynamic_cast<ChipsParser::SensorParameterTypeContext*>(parameter->pdf_parameter_type()); stuff != nullptr)
            {
                dataflow_type dft = std::any_cast<dataflow_type>(visit(stuff));
                
                #define TRY_ADD_SENSOR(DFK,DFT)  \
                if(dft == DFT){\
                    dataflow_declaration<DFT,statement_env::DEFINITION> declaration(pname);\
                    declaration.get_variable().set_declaration(&declaration);                    \
                    function_parameter<DFK,DFT> new_ast_param(pname,declaration);\
                    sensors.push_back(&new_ast_param);\
                    continue;\
                }
                
                TRY_ADD_SENSOR(dataflow_kind::PHYSICAL,dataflow_type::INT)
                TRY_ADD_SENSOR(dataflow_kind::PHYSICAL,dataflow_type::FLOAT)
                TRY_ADD_SENSOR(dataflow_kind::PHYSICAL,dataflow_type::BOOL)
                #undef TRY_ADD_SENSOR
                std::cerr<<"Unknown parameter type in the PhysicalDefinitionContext"<<std::endl;
            }
            if (ChipsParser::FunctionParameterTypeContext *stuff = dynamic_cast<ChipsParser::FunctionParameterTypeContext *>(parameter->pdf_parameter_type()); stuff != nullptr)
            {
                dataflow_type dft = std::any_cast<dataflow_type>(visit(stuff));
                
                #define TRY_ADD_PARAM(DFK,DFT)  \
                if(dft == DFT){\
                    dataflow_declaration<DFT,statement_env::DEFINITION> declaration(pname);\
                    declaration.get_variable().set_declaration(&declaration);                    \
                    function_parameter<DFK,DFT> new_ast_param(pname,declaration);\
                    params.push_back(&new_ast_param);\
                    continue;\
                }
                
                TRY_ADD_PARAM(dataflow_kind::LOGICAL,dataflow_type::INT)
                TRY_ADD_PARAM(dataflow_kind::LOGICAL,dataflow_type::FLOAT)
                TRY_ADD_PARAM(dataflow_kind::LOGICAL,dataflow_type::BOOL)
                #undef TRY_ADD_PARAM
                std::cerr<<"Unknown parameter type in the PhysicalDefinitionContext"<<std::endl;
            }
            std::cerr<<"Unknown parameter super type in the PhysicalDefinitionContext"<<std::endl;
        }

        with_section with = std::any_cast<with_section>(visitWith_section(pfd->with_section()));
        init_section init = std::any_cast<init_section>(visitInit_section(pfd->init_section()));
        then_section then = std::any_cast<then_section>(visitThen_section(pfd->then_section()));
        

        std::vector<function_output_variant> outputs;
        std::vector<physical_output_variant> actuators;
        for(ChipsParser::P_named_outputContext* output : pfd->p_named_output()){
            
            if (ChipsParser::FunctionOutputContext* stuff = dynamic_cast<ChipsParser::FunctionOutputContext*>(output); stuff != nullptr){
                std::string oname = stuff->named_output()->IDENTIFIER()->getText();
                rvalue_variant<expression_env::PRIMITIVE> rval 
                    = std::any_cast<rvalue_variant<expression_env::PRIMITIVE>>(visit(stuff->named_output()->expr(0)));
                try{
                    function_output<dataflow_kind::LOGICAL, dataflow_type::INT> 
                        final_output(oname,std::get<rvalue<dataflow_type::INT,expression_env::PRIMITIVE>*>(rval));
                    outputs.push_back(&final_output);
                    continue;
                }catch(const std::bad_variant_access& e){
                    std::cout<<"not an int rvalue";
                }
                try{
                    function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT> 
                        final_output(oname,std::get<rvalue<dataflow_type::FLOAT,expression_env::PRIMITIVE>*>(rval));
                    outputs.push_back(&final_output);
                    continue;
                }catch(const std::bad_variant_access& e){
                    std::cout<<"not a float rvalue";
                }
                try{
                    function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL> 
                        final_output(oname,std::get<rvalue<dataflow_type::BOOL,expression_env::PRIMITIVE>*>(rval));
                    outputs.push_back(&final_output);
                    continue;
                }catch(const std::bad_variant_access& e){
                    std::cout<<"not a bool rvalue";
                }
                std::cerr<<"Unknown output type in the PhysicalDefinitionContext"<<std::endl;
            }
            if (ChipsParser::ActuatorOutputContext* stuff = dynamic_cast<ChipsParser::ActuatorOutputContext*>(output); stuff != nullptr)
            {
                std::string oname = stuff->IDENTIFIER()->getText();
                rvalue_variant<expression_env::PRIMITIVE> rval = std::any_cast<rvalue_variant<expression_env::PRIMITIVE>>(visit(stuff->expr(0)));
                try{
                    function_output<dataflow_kind::PHYSICAL, dataflow_type::INT> 
                        final_output(oname,std::get<rvalue<dataflow_type::INT,expression_env::PRIMITIVE>*>(rval));
                    actuators.push_back(&final_output);
                    continue;
                }catch(const std::bad_variant_access& e){
                    std::cout<<"not an int rvalue";
                }
                try{
                    function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT> 
                        final_output(oname,std::get<rvalue<dataflow_type::FLOAT,expression_env::PRIMITIVE>*>(rval));
                    actuators.push_back(&final_output);
                    continue;
                }catch(const std::bad_variant_access& e){
                    std::cout<<"not a float rvalue";
                }
                try{
                    function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL> 
                        final_output(oname,std::get<rvalue<dataflow_type::BOOL,expression_env::PRIMITIVE>*>(rval));
                    actuators.push_back(&final_output);
                    continue;
                }catch(const std::bad_variant_access& e){
                    std::cout<<"not a bool rvalue";
                }
                std::cerr<<"Unknown output type in the PhysicalDefinitionContext"<<std::endl;
            }
            std::cerr<<"Unknown output super type in the PhysicalDefinitionContext"<<std::endl;
        }


        return chips::physical_definition(identifier,params,init,then,outputs,with,sensors,actuators);
        //throw std::runtime_error("Unimplemented visit method PhysicalDefinitionContext");
    }

    std::any visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Collective_op_defContext");
    }

    std::any visitDefaultOutput(ChipsParser::DefaultOutputContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method DefaultOutputContext");
    }

    std::any visitChanneledOutput(ChipsParser::ChanneledOutputContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method ChanneledOutputContext");
    }

    std::any visitL_function_def(ChipsParser::L_function_defContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method L_function_defContext");
    }

    std::any visitP_function_def(ChipsParser::P_function_defContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method P_function_defContext");
    }

    std::any visitC_signature(ChipsParser::C_signatureContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method C_signatureContext");
    }

    std::any visitC_keywords(ChipsParser::C_keywordsContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method C_keywordsContext");
    }

    std::any visitWith_section(ChipsParser::With_sectionContext *ctx) override
    {
        std::cout<<"visiting With"<<std::endl;
        with_section with;
        for(ChipsParser::With_statementContext* stt : ctx->with_statement()){
            std::any followup = visit(stt);
            try{
                node_element_declaration<node_element::CHANNEL> new_ast_stt = std::any_cast<node_element_declaration<node_element::CHANNEL>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            }catch(const std::bad_any_cast& e){
                std::cout<<"not a channel declaration"<<std::endl;
            }
            try{
                node_element_declaration<node_element::CONTEXTUAL_INT> new_ast_stt = std::any_cast<node_element_declaration<node_element::CONTEXTUAL_INT>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            }catch(const std::bad_any_cast& e){
                std::cout<<"not a contextual int declaration"<<std::endl;
            }
            try{
                node_element_declaration<node_element::CONTEXTUAL_FLOAT> new_ast_stt = std::any_cast<node_element_declaration<node_element::CONTEXTUAL_FLOAT>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            }catch(const std::bad_any_cast& e){
                std::cout<<"not a contextual float declaration"<<std::endl;
            }
            try{
                node_element_declaration<node_element::CONTEXTUAL_BOOL> new_ast_stt = std::any_cast<node_element_declaration<node_element::CONTEXTUAL_BOOL>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            }catch(const std::bad_any_cast& e){
                std::cout<<"not a contextual bool declaration"<<std::endl;
            }

            // using node_statement_variant = std::variant<node_statement<recurring_statement::IF>*,node_statement<recurring_statement::FOREACH>*,node_element_declaration<node_element::CHANNEL>*,node_element_declaration<node_element::CONTEXTUAL_INT>*,node_element_declaration<node_element::CONTEXTUAL_FLOAT>*,node_element_declaration<node_element::CONTEXTUAL_BOOL>*,node_statement<recurring_statement::DECLARATION>*,node_statement<recurring_statement::ASSIGNMENT>*>;
            
            try {
                // must try this one before the if statement because 
                // "if else" derives from "if" statement
                if_else_statement<statement_env::NODE> new_ast_stt = 
                std::any_cast<if_else_statement<statement_env::NODE>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            } catch (const std::bad_any_cast& e){
                std::cout<<"not an if else statement"<<std::endl;
            }

            try {
                if_statement<statement_env::NODE> new_ast_stt = 
                std::any_cast<if_statement<statement_env::NODE>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            } catch (const std::bad_any_cast& e){
                std::cout<<"not an if statement"<<std::endl;
            }

            try {
                foreach_statement<statement_env::NODE,dataflow_type::INT> new_ast_stt = 
                std::any_cast<foreach_statement<statement_env::NODE,dataflow_type::INT>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            } catch (const std::bad_any_cast& e){
                std::cout<<"not a foreach int statement"<<std::endl;
            }

            try {
                foreach_statement<statement_env::NODE,dataflow_type::FLOAT> new_ast_stt = 
                std::any_cast<foreach_statement<statement_env::NODE,dataflow_type::FLOAT>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            } catch (const std::bad_any_cast& e){
                std::cout<<"not a foreach float statement"<<std::endl;
            }

            try {
                foreach_statement<statement_env::NODE,dataflow_type::BOOL> new_ast_stt = 
                std::any_cast<foreach_statement<statement_env::NODE,dataflow_type::BOOL>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            } catch (const std::bad_any_cast& e){
                std::cout<<"not a foreach bool statement"<<std::endl;
            }

            try {
                dataflow_declaration<dataflow_type::INT,statement_env::NODE> new_ast_stt = 
                std::any_cast<dataflow_declaration<dataflow_type::INT,statement_env::NODE>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            } catch (const std::bad_any_cast& e){
                std::cout<<"not a int declaration statement"<<std::endl;
            }

            try {
                dataflow_declaration<dataflow_type::FLOAT,statement_env::NODE> new_ast_stt = 
                std::any_cast<dataflow_declaration<dataflow_type::FLOAT,statement_env::NODE>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            } catch (const std::bad_any_cast& e){
                std::cout<<"not a float declaration statement"<<std::endl;
            }

            try {
                dataflow_declaration<dataflow_type::BOOL,statement_env::NODE> new_ast_stt = 
                std::any_cast<dataflow_declaration<dataflow_type::BOOL,statement_env::NODE>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            } catch (const std::bad_any_cast& e){
                std::cout<<"not a bool declaration statement"<<std::endl;
            }

            try {
                dataflow_assignment<dataflow_type::INT, statement_env::NODE> new_ast_stt = 
                std::any_cast<dataflow_assignment<dataflow_type::INT, statement_env::NODE>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            } catch (const std::bad_any_cast& e){
                std::cout<<"not an int assignement statement"<<std::endl;
            }
            try {
                dataflow_assignment<dataflow_type::FLOAT, statement_env::NODE> new_ast_stt = 
                std::any_cast<dataflow_assignment<dataflow_type::FLOAT, statement_env::NODE>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            } catch (const std::bad_any_cast& e){
                std::cout<<"not a float assignment statement"<<std::endl;
            }
            try {
                dataflow_assignment<dataflow_type::BOOL, statement_env::NODE> new_ast_stt = 
                std::any_cast<dataflow_assignment<dataflow_type::BOOL, statement_env::NODE>>(followup);
                with.add_statement(&new_ast_stt);
                continue;
            } catch (const std::bad_any_cast& e){
                std::cout<<"not a bool assignment statement"<<std::endl;
            }

            throw std::runtime_error("Unknown kind of statement in with section");
        }
        return with;
        //throw std::runtime_error("Unimplemented visit method With_sectionContext");
    }

    std::any visitChannelDeclaration(ChipsParser::ChannelDeclarationContext *ctx) override
    {
        std::cout<<"Visiting Channel declaration"<<std::endl;
        return node_element_declaration<node_element::CHANNEL>(ctx->IDENTIFIER(0)->getText(),ctx->IDENTIFIER(1)->getText());
        //throw std::runtime_error("Unimplemented visit method ChannelDeclarationContext");
    }

    std::any visitContextualDeclaration(ChipsParser::ContextualDeclarationContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method ContextualDeclarationContext");
    }

    std::any visitWithRegularStatement(ChipsParser::WithRegularStatementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method WithRegularStatementContext");
    }

    std::any visitInit_section(ChipsParser::Init_sectionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Init_sectionContext");
    }

    std::any visitThen_section(ChipsParser::Then_sectionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Then_sectionContext");
    }

    std::any visitVar(ChipsParser::VarContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method VarContext");
    }

    std::any visitVarContext(ChipsParser::VarContextContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method VarContextContext");
    }

    std::any visitCStoplessExpression(ChipsParser::CStoplessExpressionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CStoplessExpressionContext");
    }

    std::any visitStop(ChipsParser::StopContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method StopContext");
    }

    std::any visitCLT(ChipsParser::CLTContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CLTContext");
    }

    std::any visitCGT(ChipsParser::CGTContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CGTContext");
    }

    std::any visitCLEQ(ChipsParser::CLEQContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CLEQContext");
    }

    std::any visitCGEQ(ChipsParser::CGEQContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CGEQContext");
    }

    std::any visitCNEQ(ChipsParser::CNEQContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CNEQContext");
    }

    std::any visitCEQ(ChipsParser::CEQContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CEQContext");
    }

    std::any visitCAND(ChipsParser::CANDContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CANDContext");
    }

    std::any visitCOR(ChipsParser::CORContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CORContext");
    }

    std::any visitPassCExpr0(ChipsParser::PassCExpr0Context *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method PassCExpr0Context");
    }

    std::any visitCPLUS(ChipsParser::CPLUSContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CPLUSContext");
    }

    std::any visitCSUB(ChipsParser::CSUBContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CSUBContext");
    }

    std::any visitCNegate(ChipsParser::CNegateContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CNegateContext");
    }

    std::any visitPassCExpr1(ChipsParser::PassCExpr1Context *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method PassCExpr1Context");
    }

    std::any visitCMULT(ChipsParser::CMULTContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CMULTContext");
    }

    std::any visitCDIV(ChipsParser::CDIVContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CDIVContext");
    }

    std::any visitCMOD(ChipsParser::CMODContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CMODContext");
    }

    std::any visitCNOT(ChipsParser::CNOTContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CNOTContext");
    }

    std::any visitPassCExpr2(ChipsParser::PassCExpr2Context *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method PassCExpr2Context");
    }

    std::any visitCVariableExpression(ChipsParser::CVariableExpressionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CVariableExpressionContext");
    }

    std::any visitCINT(ChipsParser::CINTContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CINTContext");
    }

    std::any visitCFLOAT(ChipsParser::CFLOATContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CFLOATContext");
    }

    std::any visitCBOOL(ChipsParser::CBOOLContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CBOOLContext");
    }

    std::any visitINPUT(ChipsParser::INPUTContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method INPUTContext");
    }

    std::any visitCtxVariableExpression(ChipsParser::CtxVariableExpressionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CtxVariableExpressionContext");
    }

    std::any visitChanneledAccuExpression(ChipsParser::ChanneledAccuExpressionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method ChanneledAccuExpressionContext");
    }

    std::any visitFunctionCall(ChipsParser::FunctionCallContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method FunctionCallContext");
    }

    std::any visitCParenthesis(ChipsParser::CParenthesisContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CParenthesisContext");
    }

    std::any visitCCastAs(ChipsParser::CCastAsContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CCastAsContext");
    }

    std::any visitC_cast(ChipsParser::C_castContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method C_castContext");
    }

    std::any visitC_suffixes(ChipsParser::C_suffixesContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method C_suffixesContext");
    }

    std::any visitSSuffixableVariableExpression(ChipsParser::SSuffixableVariableExpressionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method SSuffixableVariableExpressionContext");
    }

    std::any visitSSuffixableFunctionCallExpression(ChipsParser::SSuffixableFunctionCallExpressionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method SSuffixableFunctionCallExpressionContext");
    }

    std::any visitSSuffixableBlockOutputExpression(ChipsParser::SSuffixableBlockOutputExpressionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method SSuffixableBlockOutputExpressionContext");
    }

    std::any visitBlock(ChipsParser::BlockContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method BlockContext");
    }

    std::any visitLoop_in(ChipsParser::Loop_inContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Loop_inContext");
    }

    std::any visitLoop_statement(ChipsParser::Loop_statementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Loop_statementContext");
    }

    std::any visitC_loop_statement(ChipsParser::C_loop_statementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method C_loop_statementContext");
    }

    std::any visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method S_loop_statementContext");
    }

    std::any visitIf_else_statement(ChipsParser::If_else_statementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method If_else_statementContext");
    }

    std::any visitS_if_else_statement(ChipsParser::S_if_else_statementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method S_if_else_statementContext");
    }

    std::any visitC_if_else_statement(ChipsParser::C_if_else_statementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method C_if_else_statementContext");
    }

    std::any visitIf_statement(ChipsParser::If_statementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method If_statementContext");
    }

    std::any visitS_if_statement(ChipsParser::S_if_statementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method S_if_statementContext");
    }

    std::any visitC_if_statement(ChipsParser::C_if_statementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method C_if_statementContext");
    }

    std::any visitStatementAssignment(ChipsParser::StatementAssignmentContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method StatementAssignmentContext");
    }

    std::any visitStatementContextualAssignment(ChipsParser::StatementContextualAssignmentContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method StatementContextualAssignmentContext");
    }

    std::any visitStatementLoop(ChipsParser::StatementLoopContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method StatementLoopContext");
    }

    std::any visitStatementIfElse(ChipsParser::StatementIfElseContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method StatementIfElseContext");
    }

    std::any visitStatementIf(ChipsParser::StatementIfContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method StatementIfContext");
    }

    std::any visitObjectDeclaration(ChipsParser::ObjectDeclarationContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method ObjectDeclarationContext");
    }

    std::any visitFeedingStatement(ChipsParser::FeedingStatementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method FeedingStatementContext");
    }

    std::any visitLinkingStatement(ChipsParser::LinkingStatementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method LinkingStatementContext");
    }

    std::any visitImplementationStatement(ChipsParser::ImplementationStatementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method ImplementationStatementContext");
    }

    std::any visitSLoopStatement(ChipsParser::SLoopStatementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method SLoopStatementContext");
    }

    std::any visitSIfElseStatement(ChipsParser::SIfElseStatementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method SIfElseStatementContext");
    }

    std::any visitSIfStatement(ChipsParser::SIfStatementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method SIfStatementContext");
    }

    std::any visitRegularStatement(ChipsParser::RegularStatementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method RegularStatementContext");
    }

    std::any visitSBlockOutputExpression(ChipsParser::SBlockOutputExpressionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method SBlockOutputExpressionContext");
    }

    std::any visitSCollectiveCastExpression(ChipsParser::SCollectiveCastExpressionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method SCollectiveCastExpressionContext");
    }

    std::any visitSRegularExpression(ChipsParser::SRegularExpressionContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method SRegularExpressionContext");
    }

    std::any visitCollective_operation(ChipsParser::Collective_operationContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Collective_operationContext");
    }

    std::any visitCollectiveVariableDeclaration(ChipsParser::CollectiveVariableDeclarationContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CollectiveVariableDeclarationContext" );
    }

    std::any visitCollectiveAssignment(ChipsParser::CollectiveAssignmentContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CollectiveAssignmentContext");
    }

    std::any visitContextualAssignment(ChipsParser::ContextualAssignmentContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method ContextualAssignmentContext");
    }

    std::any visitCollectiveLoopStatement(ChipsParser::CollectiveLoopStatementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CollectiveLoopStatementContext");
    }

    std::any visitCollectiveIfElseStatement(ChipsParser::CollectiveIfElseStatementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CollectiveIfElseStatementContext");
    }

    std::any visitCollectiveIfStatement(ChipsParser::CollectiveIfStatementContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method CollectiveIfStatementContext");
    }

    std::any visitNamed_output(ChipsParser::Named_outputContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Named_outputContext");
    }

    std::any visitActuatorOutput(ChipsParser::ActuatorOutputContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method ActuatorOutputContext");
    }

    std::any visitFunctionOutput(ChipsParser::FunctionOutputContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method FunctionOutputContext");
    }

    std::any visitDf_parameter_decl(ChipsParser::Df_parameter_declContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Df_parameter_declContext");
    }

    std::any visitFunctionParameterType(ChipsParser::FunctionParameterTypeContext *ctx) override
    {
        std::cout<<"visit function parameter type"<<std::endl;
        ChipsParser::Df_typeContext* dft = ctx->df_type();
        
        if (ChipsParser::IntTypeContext* stuff = dynamic_cast<ChipsParser::IntTypeContext*>(dft); stuff != nullptr)
        {
            return visitIntType(stuff);
        }
        if (ChipsParser::FloatTypeContext* stuff = dynamic_cast<ChipsParser::FloatTypeContext*>(dft); stuff != nullptr)
        {
            return visitFloatType(stuff);
        }
        if (ChipsParser::BoolTypeContext* stuff = dynamic_cast<ChipsParser::BoolTypeContext*>(dft); stuff != nullptr)
        {
            return visitBoolType(stuff);
        }
        throw std::runtime_error("unrecognized parameter type in visit method FunctionParameterContext");
    }

    std::any visitSensorParameterType(ChipsParser::SensorParameterTypeContext *ctx) override
    {
        std::cout<<"visit sensor parameter type"<<std::endl;
        ChipsParser::Df_typeContext* dft = ctx->df_type();
        
        if (ChipsParser::IntTypeContext* stuff = dynamic_cast<ChipsParser::IntTypeContext*>(dft); stuff != nullptr)
        {
            return visitIntType(stuff);
        }
        if (ChipsParser::FloatTypeContext* stuff = dynamic_cast<ChipsParser::FloatTypeContext*>(dft); stuff != nullptr)
        {
            return visitFloatType(stuff);
        }
        if (ChipsParser::BoolTypeContext* stuff = dynamic_cast<ChipsParser::BoolTypeContext*>(dft); stuff != nullptr)
        {
            return visitBoolType(stuff);
        }
        
        throw std::runtime_error("unrecognized parameter type in visit method SensorParameterContext");
    }

    std::any visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Pdf_parameter_declContext");
    }

    std::any visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Cdf_defaulted_declContext");
    }

    std::any visitCdf_full_declaration(ChipsParser::Cdf_full_declarationContext *ctx) override
    {
        throw std::runtime_error("Unimplemented visit method Cdf_full_declarationContext");
    }

    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////

    // expr

    std::any visitFunction(ChipsParser::FunctionContext *ctx) override
    {
        std::string fname = ctx->IDENTIFIER()->getText();
        std::cout << "function_visited, symbol: " << fname << " ";
        if (fname.compare("is_fresh") == 0)
        {
            return std::make_shared<direct<dataflow_type::BOOL, expression_env::PRIMITIVE>>(false);
        }
        if (fname.compare("range") == 0)
            return std::make_shared<direct<dataflow_type::INT, expression_env::PRIMITIVE>>(0);
        if (fname.compare("zeros") == 0)
            return std::make_shared<direct<dataflow_type::INT, expression_env::PRIMITIVE>>(0);
        throw std::runtime_error("could not recognize the function" + fname);
    }

    std::any visitLT(ChipsParser::LTContext *ctx) override
    {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::LTBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "LT");
    }

    std::any visitLEQ(ChipsParser::LEQContext *ctx) override
    {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::LEQBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "LEQ");
    }

    std::any visitGT(ChipsParser::GTContext *ctx) override
    {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::GTBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "GT");
    }

    std::any visitGEQ(ChipsParser::GEQContext *ctx) override
    {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::GEQBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "GEQ");
    }

    std::any visitEQ(ChipsParser::EQContext *ctx) override
    {
        return ast_builder_detail::dispatch_binary<ast_builder_detail::EQBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "EQ");
    }

    std::any visitNEQ(ChipsParser::NEQContext *ctx) override
    {
        return ast_builder_detail::dispatch_binary<ast_builder_detail::NEQBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "NEQ");
    }

    std::any visitAND(ChipsParser::ANDContext *ctx) override
    {
        return ast_builder_detail::dispatch_boolean_binary<ast_builder_detail::ANDBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "AND");
    }

    std::any visitOR(ChipsParser::ORContext *ctx) override
    {
        return ast_builder_detail::dispatch_boolean_binary<ast_builder_detail::ORBuilder>(
            visit(ctx->expr0()), visit(ctx->expr()), "OR");
    }

    std::any visitPLUS(ChipsParser::PLUSContext *ctx) override
    {
        // std::cout << "visitPLUS()" << std::endl;
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::PlusBuilder>(
            visit(ctx->expr1()), visit(ctx->expr0()), "PLUS");
    }

    std::any visitSUB(ChipsParser::SUBContext *ctx) override
    {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::SubBuilder>(
            visit(ctx->expr1()), visit(ctx->expr0()), "SUB");
    }

    std::any visitNegate(ChipsParser::NegateContext *ctx) override
    {
        return ast_builder_detail::dispatch_numeric_unary<ast_builder_detail::NegateBuilder>(
            visit(ctx->expr1()), "Negate");
    }

    std::any visitMULT(ChipsParser::MULTContext *ctx) override
    {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::MultBuilder>(
            visit(ctx->expr2()), visit(ctx->expr1()), "MULT");
    }

    std::any visitDIV(ChipsParser::DIVContext *ctx) override
    {
        return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::DivBuilder>(
            visit(ctx->expr2()), visit(ctx->expr1()), "DIV");
    }

    std::any visitMOD(ChipsParser::MODContext *ctx) override
    {

        auto left_prim = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr2()));
        auto right_prim = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(visit(ctx->expr1()));
        if (left_prim && right_prim)
        {
            return ast_builder_detail::ModBuilder<dataflow_type::INT, expression_env::PRIMITIVE>::build(left_prim, right_prim);
        }

        auto left_collect = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(visit(ctx->expr2()));
        auto right_collect = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(visit(ctx->expr1()));
        if (left_collect && right_collect)
        {
            return ast_builder_detail::ModBuilder<dataflow_type::INT, expression_env::COLLECTIVE>::build(left_collect, right_collect);
        }

        auto left_system = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(visit(ctx->expr2()));
        auto right_system = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(visit(ctx->expr1()));
        if (left_system && right_system)
        {
            return ast_builder_detail::ModBuilder<dataflow_type::INT, expression_env::SYSTEM>::build(left_system, right_system);
        }

        throw std::runtime_error("MOD : opérandes doivent être des entiers (INT)");
    }

    std::any visitNOT(ChipsParser::NOTContext *ctx) override
    {
        return ast_builder_detail::dispatch_boolean_unary<ast_builder_detail::NOTBuilder>(
            visit(ctx->expr2()), "NOT");
    }

    // atom
    std::any visitIntLiteral(ChipsParser::IntLiteralContext *ctx) override
    {
        // std::cout << "visitIntLit()" << std::endl;
        return std::make_shared<direct<dataflow_type::INT, expression_env::PRIMITIVE>>(std::stoll(ctx->INT()->getText()));
    }

    std::any visitFloatLiteral(ChipsParser::FloatLiteralContext *ctx) override
    {
        // std::cout << "visitFloatLit()" << std::endl;
        return std::make_shared<direct<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(std::stod(ctx->FLOAT()->getText()));
    }

    std::any visitBoolLiteral(ChipsParser::BoolLiteralContext *ctx) override
    {
        std::string text = ctx->BOOL()->getText();
        bool value = (text == "true");
        return std::make_shared<direct<dataflow_type::BOOL, expression_env::PRIMITIVE>>(value);
    }

    std::any visitParens(ChipsParser::ParensContext* ctx) override {
        return visit(ctx->expr());
    }

    std::any visitCastAs(ChipsParser::CastAsContext *ctx) override
    {
        // std::cout << "visitCastAs()" << std::endl;
        return visit(ctx->cast());
    }

    std::any handle_cast(dataflow_type target, std::any operand_any)
    {
        // PRIMITIVE
        switch (target)
        {
        case dataflow_type::INT:
            if (auto src = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(operand_any))
                return std::make_shared<cast_as<dataflow_type::INT, expression_env::PRIMITIVE>>(
                    std::reinterpret_pointer_cast<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>>(src));
            if (auto src = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(operand_any))
                return std::make_shared<cast_as<dataflow_type::INT, expression_env::PRIMITIVE>>(
                    std::reinterpret_pointer_cast<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>>(src));
            break;
        case dataflow_type::FLOAT:
            if (auto src = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(operand_any))
                return std::make_shared<cast_as<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(
                    std::reinterpret_pointer_cast<rvalue<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(src));
            if (auto src = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(operand_any))
                return std::make_shared<cast_as<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(
                    std::reinterpret_pointer_cast<rvalue<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(src));
            break;
        default:
            break;
        }
        // COLLECTIVE
        switch (target)
        {
        case dataflow_type::INT:
            if (auto src = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::COLLECTIVE>(operand_any))
                return std::make_shared<cast_as<dataflow_type::INT, expression_env::COLLECTIVE>>(
                    std::reinterpret_pointer_cast<rvalue<dataflow_type::INT, expression_env::COLLECTIVE>>(src));
            if (auto src = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(operand_any))
                return std::make_shared<cast_as<dataflow_type::INT, expression_env::COLLECTIVE>>(
                    std::reinterpret_pointer_cast<rvalue<dataflow_type::INT, expression_env::COLLECTIVE>>(src));
            break;
        case dataflow_type::FLOAT:
            if (auto src = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(operand_any))
                return std::make_shared<cast_as<dataflow_type::FLOAT, expression_env::COLLECTIVE>>(
                    std::reinterpret_pointer_cast<rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>>(src));
            if (auto src = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::COLLECTIVE>(operand_any))
                return std::make_shared<cast_as<dataflow_type::FLOAT, expression_env::COLLECTIVE>>(
                    std::reinterpret_pointer_cast<rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>>(src));
            break;
        default:
            break;
        }
        // SYSTEM
        switch (target)
        {
        case dataflow_type::INT:
            if (auto src = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::SYSTEM>(operand_any))
                return std::make_shared<cast_as<dataflow_type::INT, expression_env::SYSTEM>>(
                    std::reinterpret_pointer_cast<rvalue<dataflow_type::INT, expression_env::SYSTEM>>(src));
            if (auto src = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(operand_any))
                return std::make_shared<cast_as<dataflow_type::INT, expression_env::SYSTEM>>(
                    std::reinterpret_pointer_cast<rvalue<dataflow_type::INT, expression_env::SYSTEM>>(src));
            break;
        case dataflow_type::FLOAT:
            if (auto src = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(operand_any))
                return std::make_shared<cast_as<dataflow_type::FLOAT, expression_env::SYSTEM>>(
                    std::reinterpret_pointer_cast<rvalue<dataflow_type::FLOAT, expression_env::SYSTEM>>(src));
            if (auto src = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::SYSTEM>(operand_any))
                return std::make_shared<cast_as<dataflow_type::FLOAT, expression_env::SYSTEM>>(
                    std::reinterpret_pointer_cast<rvalue<dataflow_type::FLOAT, expression_env::SYSTEM>>(src));
            break;
        default:
            break;
        }
        throw std::runtime_error("cast_as : seuls les casts numériques INT↔FLOAT sont supportés.");
    }

    std::any visitCast(ChipsParser::CastContext *ctx) override
    {
        // std::cout << "visitCast()" << std::endl;

        // Type
        dataflow_type target = std::any_cast<dataflow_type>(visit(ctx->df_type()));

        // Operande
        std::any operand_any = visit(ctx->expr());

        return handle_cast(target, operand_any);
    }

    // Type primitif
    std::any visitIntType(ChipsParser::IntTypeContext * /*ctx*/) override
    {
        return dataflow_type::INT;
    }

    std::any visitFloatType(ChipsParser::FloatTypeContext * /*ctx*/) override
    {
        return dataflow_type::FLOAT;
    }

    std::any visitBoolType(ChipsParser::BoolTypeContext * /*ctx*/) override
    {
        return dataflow_type::BOOL;
    }

    std::any visitSuffixes(ChipsParser::SuffixesContext* ctx) override {
        switch(current_env){
            case expression_env::PRIMITIVE: {
                std::vector<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>> dims;

                for(auto* expr : ctx->expr()){
                    std::any val = visit(expr);
                    auto node = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(val);
                    if(!node){
                        throw std::runtime_error(
                            "suffixes : l'expression d'indice doit être de type INT "
                            "(env PRIMITIVE).");
                    }
                    dims.push_back(*node);
                }
                return dims;
            }

            case expression_env::COLLECTIVE: {
                std::vector<rvalue<dataflow_type::INT, expression_env::COLLECTIVE>> dims;

                for(auto* expr : ctx->expr()){
                    std::any val = visit(expr);
                    auto node = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(val);
                    if(!node){
                         throw std::runtime_error(
                            "suffixes : l'expression d'indice doit être de type INT "
                            "(env COLLECTIVE).");
                    }
                    dims.push_back(*node);
                }
                return dims;
            }

            case expression_env::SYSTEM: {
                std::vector<rvalue<dataflow_type::INT, expression_env::SYSTEM>> dims;

                for(auto* expr : ctx->expr()){
                    std::any val = visit(expr);
                    auto node = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(val);
                    if(!node){
                         throw std::runtime_error(
                            "suffixes : l'expression d'indice doit être de type INT "
                            "(env SYSTEM).");
                    }
                    dims.push_back(*node);
                }
                return dims;
            }
        }
    }

    /**
     * STATEMENT
     */
    std::any handle_statement_declaration(dataflow_type type, std::any suffixes, std::string identifier){
        auto dims = std::any_cast<std::vector<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>>>(suffixes);
        switch(type){
            case dataflow_type::INT: {
                dataflow_primitive_variable<dataflow_type::INT> var_temp(identifier, nullptr);
                dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION> decl(var_temp);
                dataflow_primitive_variable<dataflow_type::INT> var(identifier, &decl, dims);
                decl.m_variable = var;
                return decl;
            }
            case dataflow_type::FLOAT: {
                dataflow_primitive_variable<dataflow_type::FLOAT> var_temp(identifier, nullptr);
                dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION> decl(var_temp);
                dataflow_primitive_variable<dataflow_type::FLOAT> var(identifier, &decl, dims);
                decl.m_variable = var;
                return decl;
            }
            case dataflow_type::BOOL: {
                dataflow_primitive_variable<dataflow_type::BOOL> var_temp(identifier, nullptr);
                dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION> decl(var_temp);
                dataflow_primitive_variable<dataflow_type::BOOL> var(identifier, &decl, dims);
                decl.m_variable = var;
                return decl;
            }
        }
    }

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
        auto dims = std::any_cast<std::vector<rvalue<dataflow_type::INT, expression_env::PRIMITIVE>>>(suffixes);
        switch(type){
            case dataflow_type::INT: {
                dataflow_primitive_variable<dataflow_type::INT> var_temp(identifier, nullptr);
                dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION> decl(var_temp);
                dataflow_primitive_variable<dataflow_type::INT> var(identifier, &decl, dims);
                decl.set_variable(var);
                if(!have_assign) return decl;
                variable_expression<dataflow_type::INT, expression_env::PRIMITIVE> left(&var);
                auto right = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(assign);
                dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION> assignment(&left, *right);
                return assignment;
            }
            case dataflow_type::FLOAT: {
                dataflow_primitive_variable<dataflow_type::FLOAT> var_temp(identifier, nullptr);
                dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION> decl(var_temp);
                dataflow_primitive_variable<dataflow_type::FLOAT> var(identifier, &decl, dims);
                decl.set_variable(var);
                if(!have_assign) return decl;
                variable_expression<dataflow_type::FLOAT, expression_env::PRIMITIVE> left(&var);
                auto right = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(assign);
                dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION> assignment(&left, *right);
                return assignment;
            }
            case dataflow_type::BOOL: {
                dataflow_primitive_variable<dataflow_type::BOOL> var_temp(identifier, nullptr);
                dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION> decl(var_temp);
                dataflow_primitive_variable<dataflow_type::BOOL> var(identifier, &decl, dims);
                decl.set_variable(var);
                if(!have_assign) return decl;
                variable_expression<dataflow_type::BOOL, expression_env::PRIMITIVE> left(&var);
                auto right = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(assign);
                dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION> assignment(&left, *right);
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
            auto decl = handle_statement_declaration(type_any, suffixes, var_name);
            if(!SymbolTable::getInstance().declareVariable(var_name, decl)){
                throw std::runtime_error("Redeclare a variable already declared");
            }
            return decl;
            // return handle_statement_declaration(type_any, suffixes, var_name);
        }else{
            std::cout << "ASSIGN REMPLI" << std::endl;
            // auto assignment = handle_statement_declaration(type_any, suffixes, var_name, assign, true);
            // if(!SymbolTable::getInstance().declareVariable(var_name, assignment)){
            //     throw std::runtime_error("Redeclare a variable already declared");
            // }
            // return assignment;
        }
        return std::any{};        
    }

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
    std::any visitPassExpr0(ChipsParser::PassExpr0Context *ctx) override
    {
        return visit(ctx->expr0());
    }

    std::any visitPassExpr1(ChipsParser::PassExpr1Context *ctx) override
    {
        return visit(ctx->expr1());
    }

    std::any visitPassExpr2(ChipsParser::PassExpr2Context *ctx) override
    {
        return visit(ctx->expr2());
    }

private:
    void print_any_type(const std::any &a)
    {
        std::cout << "Type: " << a.type().name();
        int status;
        char *demangled = abi::__cxa_demangle(a.type().name(), 0, 0, &status);
        if (status == 0 && demangled)
        {
            std::cout << " (" << demangled << ")";
            free(demangled);
        }
        std::cout << std::endl;
    }
};

#endif