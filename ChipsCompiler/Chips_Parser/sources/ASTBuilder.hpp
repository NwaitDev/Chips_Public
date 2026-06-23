#ifndef AST_BUILD_HPP
#define AST_BUILD_HPP

#include "chips_headers.hpp"
#include "ast_builder_details.hpp"
#include "utils.hpp"

#include <any>
#include <deque>
#include <stdexcept>
#include <typeinfo>

using namespace chips;

class ASTBuilder : public ChipsBaseVisitor
{
private:
    expression_env current_env = expression_env::PRIMITIVE;
    std::string fname_current;

    // Arène de noeuds alloués sur le tas dans le builder.
    // Les shared_ptr ici prolongent la durée de vie de tous les nœuds
    // intermédiaires (decl, var, left) dont d'autres nœuds gardent
    // des raw pointers. À vider explicitement si besoin de reset.
    std::vector<std::shared_ptr<ast_node>> node_arena;

    // Arène de valeurs non-ast_node (std::variant, statements, etc.)
    // nécessaires quand on doit conserver des pointeurs vers des objets
    // construits localement dans le builder.
    std::deque<std::any> value_arena;

    template<typename T>
    T* keep_value_alive(T value){
        value_arena.emplace_back(std::move(value));
        return std::any_cast<T>(&value_arena.back());
    }

    template<typename T>
    T* keep_any_object_alive(std::any& value){
        if(auto* obj = std::any_cast<T>(&value)){
            return keep_value_alive(*obj);
        }
        if(auto* ptr = std::any_cast<T*>(&value)){
            return *ptr;
        }
        return nullptr;
    }

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

    /**
     * @brief Fonction qui permet de récuperer une variable_expression à partir d'un 
     *        std::shared_ptr<dataflow_ENV_variable<DT>> ou dataflow_ENV_variable<DT> 
     *        où DT et ENV sont le dataflow_type et expression_env du template 
     * 
     * @param var  Variable qui contient le dataflow_ENV_variable dans un std::any
     * @param dims Représente l'index du tableau
     * 
     * @return std::shared_ptr<variable_expression<DT, ENV>>
     */
    template <dataflow_type DT, expression_env ENV, typename Dims>
    std::any tryCastVar(const std::any &var, const Dims &dims);

    /**
     * @brief Fonction qui permet de récuperer une variable_contextual_expression à partir d'un 
     *        std::shared_ptr<contextual_variable<DT>> ou contextual_variable<DT> 
     *        où DT et ENV sont le dataflow_type et expression_env du template 
     * 
     * @param var  Variable qui contient le dataflow_ENV_variable dans un std::any
     * @param dims Représente l'index du tableau
     * 
     * @return std::shared_ptr<variable_contextual_expression<DT, ENV>>
     */
    template <dataflow_type DT, expression_env ENV, typename Dims>
    std::any tryCastVarContextual(const std::any &var, const Dims &dims);

    /**
     * @brief Essaye de cast une variable avec tout les types possibles
     * 
     * @param var_name Nom de la variable
     * @param var      Valeur de la variable sous forme de std::any
     * @param dims     Représente l'index de la variable
     * 
     * @return Valeur de la fonction tryCastVar
     */
    template <expression_env ENV, typename Dims>
    std::any tryAllTypes(const std::string &var_name, const std::any &var, const Dims &dims);

    /**
     * @brief Essaye de cast une variable contextuelle avec tout les types possibles
     * 
     * @param var_name Nom de la variable
     * @param var      Valeur de la variable sous forme de std::any
     * @param dims     Représente l'index de la variable
     * 
     * @return Valeur de la fonction tryCastVarContextual
     */
    template <expression_env ENV, typename Dims>
    std::any tryAllTypesContextual(const std::string &var_name, const std::any &var, const Dims &dims);

    /**
     * @brief Permet de créer un dataflow_assignment<DT,ENV> où DT et ENV sont le dataflow_type et expression_env
     * 
     * @param identifier Nom de la variable a affecté
     * @param suffixes   Index du tableau de la variable
     * @param assign     Expression d'affectation
     * @param is_contextual Booléen pour savoir si l'affectation pour une variable contextuelle
     * 
     * @return dataflow_assignment<DT, ENV>
     */
    std::any handle_statement_assignment(std::string identifier, std::any suffixes, std::any assign, bool is_contextual);

    /**
     * @brief Permet de créer un dataflow_assignment<DT,ENV> où DT et ENV sont le dataflow_type et expression_env
     * 
     * @param identifier Nom de la variable a affecté
     * @param suffixes   Index du tableau de la variable
     * @param assign     Expression d'affectation
     * @param is_contextual Booléen pour savoir si l'affectation pour une variable contextuelle
     * 
     * @return dataflow_assignment<DT, ENV>
     */
    template<expression_env expenv, statement_env stenv>
    std::any handle_statement_assignment(std::string identifier, std::any suffixes, std::any assign, bool is_contextual){
        std::cout << "handle_statement_assignment " << expenv_to_string(expenv) << std::endl;
        std::optional<std::any> variable;
        if(is_contextual){
            variable = SymbolTable::getInstance().lookupContextualVariable(identifier);
        }else{
            variable = SymbolTable::getInstance().lookupVariable(identifier);
        }

        if(!variable.has_value()){
            throw std::runtime_error("'"+identifier+"' was never declarated before");
        }

        std::cout << "Type dynamique var: " << ast_builder_detail::type_name(variable.value().type()) << std::endl;


        auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expenv>>>(suffixes);
        std::any var = (!is_contextual) ? tryAllTypes<expenv>(identifier, variable.value(), dims)
                                   : tryAllTypesContextual<expenv>(identifier, variable.value(), dims);

        
        if(auto right = ast_builder_detail::try_extract<dataflow_type::INT, expenv>(assign)){
            try{
                if(!is_contextual){
                    auto left = std::any_cast<std::shared_ptr<variable_expression<dataflow_type::INT, expenv>>>(var);
                    node_arena.push_back(left);
                    node_arena.push_back(right);
                    dataflow_assignment<dataflow_type::INT,stenv> assignment(left.get(), right.get());
                    return assignment;
                }
                auto left = std::any_cast<std::shared_ptr<variable_contextual_expression<dataflow_type::INT, expenv>>>(var);
                node_arena.push_back(left);
                node_arena.push_back(right);
                dataflow_assignment<dataflow_type::INT,stenv> assignment(left.get(), right.get());
                return assignment;
            }catch(const std::bad_any_cast& e){
                throw std::runtime_error("Erreur any_cast lors de left value dans assignment");
            }
        }else if(auto right = ast_builder_detail::try_extract<dataflow_type::FLOAT, expenv>(assign)){
            try{
                if(!is_contextual){
                    auto left = std::any_cast<std::shared_ptr<variable_expression<dataflow_type::FLOAT, expenv>>>(var);
                    node_arena.push_back(left);
                    node_arena.push_back(right);
                    dataflow_assignment<dataflow_type::FLOAT,stenv> assignment(left.get(), right.get());
                    return assignment;
                }
                auto left = std::any_cast<std::shared_ptr<variable_contextual_expression<dataflow_type::FLOAT, expenv>>>(var);
                node_arena.push_back(left);
                node_arena.push_back(right);
                dataflow_assignment<dataflow_type::FLOAT,stenv> assignment(left.get(), right.get());
                return assignment;
            }catch(const std::bad_any_cast& e){
                throw std::runtime_error("Erreur any_cast lors de left value dans assignment");
            }
        }else if(auto right = ast_builder_detail::try_extract<dataflow_type::BOOL, expenv>(assign)){
            try{
                if(!is_contextual){
                    auto left = std::any_cast<std::shared_ptr<variable_expression<dataflow_type::BOOL, expenv>>>(var);
                    node_arena.push_back(left);
                    node_arena.push_back(right);
                    dataflow_assignment<dataflow_type::BOOL,stenv> assignment(left.get(), right.get());
                    return assignment;
                }
                auto left = std::any_cast<std::shared_ptr<variable_contextual_expression<dataflow_type::BOOL, expenv>>>(var);
                node_arena.push_back(left);
                node_arena.push_back(right);
                dataflow_assignment<dataflow_type::BOOL,stenv> assignment(left.get(), right.get());
                return assignment;
            }catch(const std::bad_any_cast& e){
                throw std::runtime_error("Erreur any_cast lors de left value dans assignment");
            }
        }
        throw std::runtime_error("error");
    }

    /**
     * @brief Permet de créer un node_element_declaration<NE> où NE est un node_element
     * 
     * @param type Dataflow_type de la déclaration
     * @param suffixes Taille du tableau
     * @param identifier Nom de la variable
     * @param assign Expression d'affectation
     */
    std::any handle_statement_declaration_contextual(dataflow_type type, std::any suffixes, std::string identifier, std::any assign);

    std::any visitContextualDeclaration(ChipsParser::ContextualDeclarationContext *ctx);

    std::any visitWithRegularStatement(ChipsParser::WithRegularStatementContext *ctx);

    std::any visitInit_section(ChipsParser::Init_sectionContext *ctx);

    std::any visitThen_section(ChipsParser::Then_sectionContext *ctx);

    std::any visitVar(ChipsParser::VarContext *ctx);

    std::any visitVarContext(ChipsParser::VarContextContext *ctx);

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

    std::any visitPassCExpr01(ChipsParser::PassCExpr01Context* ctx);

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

    /**
     * @brief Permet d'ajouter les statements à un foreach_statement
     * 
     * @param node Le foreach_statement
     * @param statement Le tableau contenant tous les instructions à l'intérieur du foreach
     * 
     * @return le paramètre node avec les instructions d'ajouter
     */
    template <dataflow_type dft, statement_env stenv>
    std::any make_statement_foreach(foreach_statement<stenv, dft> &node, std::vector<ChipsParser::StatementContext *> statement)
    {
        std::cout << "make statement of foreach" << std::endl;
        for (ChipsParser::StatementContext *stt : statement)
        {
            std::any followup = visit(stt);

            try{

                if (ChipsParser::StatementDeclarationContext *stuff = dynamic_cast<ChipsParser::StatementDeclarationContext *>(stt); (stuff != nullptr) && (stuff->expr() != nullptr)){
                    std::cout << "LA TRY EXTRACT RECCURING" << std::endl;
                    if (dynamic_cast<ChipsParser::IntTypeContext *>(stuff->df_type())){
                        using chiant = std::pair<
                            dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>,
                            dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION>>;
                        chiant followup_pair = std::any_cast<chiant>(followup);
                        node.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                        node.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                    }else if (dynamic_cast<ChipsParser::FloatTypeContext *>(stuff->df_type())){
                        using chiant = std::pair<
                            dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>,
                            dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION>>;
                        chiant followup_pair = std::any_cast<chiant>(followup);
                        node.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                        node.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                    }else if (dynamic_cast<ChipsParser::BoolTypeContext *>(stuff->df_type())){
                        using chiant = std::pair<
                            dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>,
                            dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION>>;
                        chiant followup_pair = std::any_cast<chiant>(followup);
                        node.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                        node.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                    }else{
                        throw std::runtime_error("unrecognized variable type");
                    }
                    continue;
                }else{
                    node.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup)));
                    continue;
                }
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        return node;
    }

    /**
     * @brief Permet d'ajouter les statements à un foreach_statement
     * 
     * @param node Le foreach_statement
     * @param statement Le tableau contenant tous les instructions à l'intérieur du foreach
     * 
     * @return le paramètre node avec les instructions d'ajouter
     */
    template <dataflow_type dft, statement_env stenv>
    std::any make_statement_foreach(foreach_statement<stenv, dft> &node, std::vector<ChipsParser::S_statementContext *> statement)
    {
        std::cout << "make statement of foreach" << std::endl;
        for (ChipsParser::S_statementContext *stt : statement)
        {
            std::any followup = visit(stt);

            try{

                if (ChipsParser::StatementDeclarationContext *stuff = dynamic_cast<ChipsParser::StatementDeclarationContext *>(stt); (stuff != nullptr) && (stuff->expr() != nullptr)){
                    std::cout << "LA TRY EXTRACT RECCURING" << std::endl;
                    if (dynamic_cast<ChipsParser::IntTypeContext *>(stuff->df_type())){
                        using chiant = std::pair<
                            dataflow_declaration<dataflow_type::INT, stenv>,
                            dataflow_assignment<dataflow_type::INT, stenv>>;
                        chiant followup_pair = std::any_cast<chiant>(followup);
                        node.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup_pair.first)));
                        node.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup_pair.second)));
                    }else if (dynamic_cast<ChipsParser::FloatTypeContext *>(stuff->df_type())){
                        using chiant = std::pair<
                            dataflow_declaration<dataflow_type::FLOAT, stenv>,
                            dataflow_assignment<dataflow_type::FLOAT, stenv>>;
                        chiant followup_pair = std::any_cast<chiant>(followup);
                        node.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup_pair.first)));
                        node.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup_pair.second)));
                    }else if (dynamic_cast<ChipsParser::BoolTypeContext *>(stuff->df_type())){
                        using chiant = std::pair<
                            dataflow_declaration<dataflow_type::BOOL, stenv>,
                            dataflow_assignment<dataflow_type::BOOL, stenv>>;
                        chiant followup_pair = std::any_cast<chiant>(followup);
                        node.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup_pair.first)));
                        node.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup_pair.second)));
                    }else{
                        throw std::runtime_error("unrecognized variable type");
                    }
                    continue;
                }else{
                    node.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup)));
                    continue;
                }
            }
            catch (const std::runtime_error &e)
            {
                std::cout << e.what() << std::endl;
            }
        }
        return node;
    }

    std::any visitLoop_statement(ChipsParser::Loop_statementContext *ctx);

    std::any visitC_loop_statement(ChipsParser::C_loop_statementContext *ctx);

    std::any visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx);

    std::any visitIf_else_statement(ChipsParser::If_else_statementContext *ctx);

    std::any visitS_if_else_statement(ChipsParser::S_if_else_statementContext *ctx);

    std::any visitC_if_else_statement(ChipsParser::C_if_else_statementContext *ctx);

    std::any visitIf_statement(ChipsParser::If_statementContext *ctx);

    std::any visitS_if_statement(ChipsParser::S_if_statementContext *ctx);

    std::any visitC_if_statement(ChipsParser::C_if_statementContext *ctx);

    std::any visitStatementAssignment(ChipsParser::StatementAssignmentContext *ctx);

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

    std::any visit_dft(ChipsParser::Df_typeContext *dft);

    std::any visitFunctionParameterType(ChipsParser::FunctionParameterTypeContext *ctx);

    std::any visitSensorParameterType(ChipsParser::SensorParameterTypeContext *ctx);

    std::any visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *ctx);

    std::any visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *ctx);

    std::any visitCdf_full_declaration(ChipsParser::Cdf_full_declarationContext *ctx);

    /**
     * @brief Permet de créer un function<DT, ENV> où DT et ENV sont le dataflow_type et expression_env
     *        Fonctions prises en compte :
     *          - int random()
     *          - int range(n)
     *          - int[] zeros(n)
     *          - int[] ones(n)
     *          - int max(m,n)
     *          - int min(m,n)
     *          - bool is_fresh()
     * 
     * @param fname Nom de la fonction
     * @param exprs Tableau des paramètres de la fonction
     * 
     * @return function<DT,ENV>
     */
    template<expression_env expenv>
    std::any make_function(const std::string& fname, std::vector<ChipsParser::C_exprContext*> exprs){
        std::cout << "make function symbol: " << fname << std::endl;

        if (fname.compare("random") == 0){
            return std::make_shared<function<dataflow_type::FLOAT, expenv>>(fname);
        }

        if (fname.compare("range") == 0 || fname.compare("zeros") == 0 || fname.compare("ones") == 0 ||
            fname.compare("max") == 0 || fname.compare("min") == 0){
            std::cout << "MAKE FUNCTION MINMAX exprs size: " << exprs.size() << std::endl;
            std::vector<rvalue_variant<expenv>> parameters;
            for (auto expr : exprs){
                std::any val = visit(expr);
                auto node = ast_builder_detail::try_extract<dataflow_type::INT, expenv>(val);
                if (!node)
                {
                    throw std::runtime_error(
                        "suffixes : l'expression d'indice doit être de type INT "
                        "(env PRIMITIVE).");
                }
                node_arena.push_back(node);
                parameters.push_back(make_variant_from_node(node));
            }
            return std::make_shared<function<dataflow_type::INT, expenv>>(fname, parameters);
        }

        if (fname.compare("is_fresh") == 0){
            // PRENDS UN DATAFLOW_PRIMITIVE_VARIABLE
            std::cerr << "WARNING : Recognized the function " + fname + " but it is not fully handled yet, currently replaced by a \"false\"" << std::endl;
            return std::make_shared<direct<dataflow_type::BOOL, expenv>>(false);
        }
        throw std::runtime_error("could not recognize the function" + fname);
    };

    /**
     * @brief Permet de créer un function<DT, ENV> où DT et ENV sont le dataflow_type et expression_env
     *        Fonctions prises en compte :
     *          - int random()
     *          - int range(n)
     *          - int[] zeros(n)
     *          - int[] ones(n)
     *          - int max(m,n)
     *          - int min(m,n)
     *          - bool is_fresh()
     * 
     * @param fname Nom de la fonction
     * @param exprs Tableau des paramètres de la fonction
     * 
     * @return function<DT,ENV>
     */
    template<expression_env expenv>
    std::any make_function(const std::string &fname, std::vector<ChipsParser::ExprContext *> exprs)
    {
        std::cout << "make function symbol: " << fname << std::endl;

        if (fname.compare("random") == 0)
        {
            return std::make_shared<function<dataflow_type::FLOAT, expenv>>(fname);
        }

        if (fname.compare("range") == 0 || fname.compare("zeros") == 0 || fname.compare("ones") == 0 ||
            fname.compare("max") == 0 || fname.compare("min") == 0)
        {
            std::vector<rvalue_variant<expenv>> parameters;
            for (auto expr : exprs)
            {
                std::any val = visit(expr);
                auto node = ast_builder_detail::try_extract<dataflow_type::INT, expenv>(val);
                if (!node)
                {
                    throw std::runtime_error(
                        "suffixes : l'expression d'indice doit être de type INT "
                        "(env PRIMITIVE).");
                }
                node_arena.push_back(node);
                parameters.push_back(make_variant_from_node(node));
            }
            return std::make_shared<function<dataflow_type::INT, expenv>>(fname, parameters);
        }

        if (fname.compare("is_fresh") == 0)
        {
            // PRENDS UN DATAFLOW_PRIMITIVE_VARIABLE
            std::cerr << "WARNING : Recognized the function " + fname + " but it is not fully handled yet, currently replaced by a \"false\"" << std::endl;
            return std::make_shared<direct<dataflow_type::BOOL, expenv>>(false);
        }
        throw std::runtime_error("could not recognize the function" + fname);
    }

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

    std::any visitParens(ChipsParser::ParensContext *ctx);

    std::any visitCastAs(ChipsParser::CastAsContext *ctx);

    std::any handle_cast(dataflow_type target, std::any operand_any);

    std::any visitCast(ChipsParser::CastContext *ctx);

    // Type primitif
    std::any visitIntType(ChipsParser::IntTypeContext * /*ctx*/);

    std::any visitFloatType(ChipsParser::FloatTypeContext * /*ctx*/);

    std::any visitBoolType(ChipsParser::BoolTypeContext * /*ctx*/);

    /**
     * @brief Transforme un std::shared_ptr<rvalue<DT,ENV>> en un primitive_iterable_variant<ENV>
     */
    template <dataflow_type dft, expression_env expenv>
    primitive_iterable_variant<expenv> make_primitive_iterable_variant_from_node(
        const std::shared_ptr<rvalue<dft, expenv>> &node);

    /**
     * @brief Transforme un std::shared_ptr<rvalue<INT,ENV>> en un int_rvalue_expression_variant<ENV>
     */
    template <expression_env expenv>
    int_rvalue_expression_variant<expenv> make_int_rvalue_variant_from_node(
        const std::shared_ptr<rvalue<dataflow_type::INT, expenv>> &node);

    /**
     * @brief Transforme un std::shared_ptr<rvalue<BOOL,ENV>> en un bool_rvalue_expression_variant<ENV>
     */
    template <expression_env expenv>
    bool_rvalue_expression_variant<expenv> make_bool_rvalue_variant_from_node(
        const std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> &node);

    /**
     * @brief Transforme un std::shared_ptr<rvalue<DT,ENV>> en un rvalue_variant<ENV>
     */
    template <dataflow_type dft, expression_env expenv>
    rvalue_variant<expenv> make_variant_from_node(
        const std::shared_ptr<rvalue<dft, expenv>> &node);

    /**
     * @brief Permet de récupérer un functional_block_variant à partir d'un std::shared_ptr<block_variable<BT>> ou 
     *        block_variable<BT> en affectant son index aussi
     * 
     * @param node Variable représentant le block_variable
     * @param dims Index du tableau
     */
    functional_block_variant make_functional_block_from_any(std::any& node, std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dims);

    std::any visitSuffixes(ChipsParser::SuffixesContext *ctx);

    /**
     * @brief Permet de récupérer les dimensions d'un tableau à partir d'un suffixes
     */
    template <expression_env expenv>
    std::vector<int_rvalue_expression_variant<expenv>> extract_dimensions(ChipsParser::SuffixesContext *ctx)
    {
        std::vector<int_rvalue_expression_variant<expenv>> dims;
        for (auto *expr : ctx->expr())
        {
            std::any val = visit(expr);
            auto node = ast_builder_detail::try_extract<dataflow_type::INT, expenv>(val);
            if (!node)
            {
                throw std::runtime_error(
                    "suffixes : l'expression d'indice doit être de type INT ");
            }
            node_arena.push_back(node);
            dims.push_back(make_int_rvalue_variant_from_node<expenv>(node));
        }
        return dims;
    }

    /**
     * @brief Permet de récupérer les dimensions d'un tableau collectif à partir d'un suffixes
     */
    std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> extract_dimensions_collective(ChipsParser::C_suffixesContext *ctx);

    template<dataflow_type dft, expression_env expenv>
    std::any handle_statement_declaration_foreach(std::string identifier){
        switch (current_env){
            case expression_env::PRIMITIVE:
                return handle_statement_declaration<expression_env::PRIMITIVE, dft>(std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>(), identifier, std::any{});
                break;
            case expression_env::COLLECTIVE:
                return handle_statement_declaration<expression_env::COLLECTIVE, dft>(std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>(), identifier, std::any{});
                break;
            case expression_env::SYSTEM:
                return handle_statement_declaration<expression_env::SYSTEM, dft>(std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>(), identifier, std::any{});
                break;
        }
        throw std::runtime_error("Unsupported environment");
    }

    // Helper to store a definition by value and return a pointer to it
    // This keeps the object alive in value_arena
    template<typename DefType>
    DefType* store_definition(DefType def) {
        value_arena.push_back(std::make_shared<DefType>(def));
        return std::any_cast<std::shared_ptr<DefType>&>(value_arena.back()).get();
    }

    /**
     * @brief Permet de créer un block_declaration<BT> où BT est un block_type
     * 
     * @param type Type de la variable declarée
     * @param suffixes Taille du tableau
     * @param identifier Nom de la variable
     */
    template<block_type bt>
    std::any handle_statement_declaration(
        std::string type,
        std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> suffixes,
        std::string identifier){

        std::cout << "handle_statement_declaration (bt)" << std::endl;
            
        if constexpr(bt == block_type::PHYSICAL){
            auto def = std::any_cast<physical_definition>(SymbolTable::getInstance().lookupNodeDefinition(type).value());

            auto decl = std::make_shared<block_declaration<block_type::PHYSICAL>>(identifier);
            auto var = std::make_shared<block_variable<block_type::PHYSICAL>>(identifier, decl.get(), suffixes);
            decl->set_variable(*var);
            decl->set_definition(store_definition(def));
            node_arena.push_back(decl);
            node_arena.push_back(var);

            if(!SymbolTable::getInstance().declareBlock(type, identifier, var)){
                throw std::runtime_error("'"+identifier+"' was already declarated before");
            }
            return *decl;
        }else if constexpr(bt == block_type::LOGICAL){
            auto def = std::any_cast<logical_definition>(SymbolTable::getInstance().lookupFunctionLogical(type).value());

            auto decl = std::make_shared<block_declaration<block_type::LOGICAL>>(identifier);
            auto var = std::make_shared<block_variable<block_type::LOGICAL>>(identifier, decl.get(), suffixes);
            decl->set_variable(*var);
            decl->set_definition(store_definition(def));
            node_arena.push_back(decl);
            node_arena.push_back(var);

            if(!SymbolTable::getInstance().declareBlock(type, identifier, var)){
                throw std::runtime_error("'"+identifier+"' was already declarated before");
            }
            return *decl;
        }else if constexpr(bt == block_type::OBJECT){
            auto def = std::any_cast<object_definition>(SymbolTable::getInstance().lookupNodeDefinition(type).value());

            auto decl = std::make_shared<block_declaration<block_type::OBJECT>>(identifier);
            auto var = std::make_shared<block_variable<block_type::OBJECT>>(identifier, decl.get(), suffixes);
            decl->set_variable(*var);
            decl->set_definition(store_definition(def));
            node_arena.push_back(decl);
            node_arena.push_back(var);

            if(!SymbolTable::getInstance().declareBlock(type, identifier, var)){
                throw std::runtime_error("'"+identifier+"' was already declarated before");
            }
            return *decl;
        }
        throw std::runtime_error("Unsupported block type");
        }

    /**
     * @brief Permet de créer un dataflow_declaration ou un std::pair{dataflow_declaration, dataflow_assignment}
     * 
     * @param suffixes Taille du tableau
     * @param identifier Nom de la variable
     * @param assign Expression d'affectation
     */
    template <expression_env expenv, dataflow_type dft>
    std::any handle_statement_declaration(
        std::vector<int_rvalue_expression_variant<expenv>> suffixes,
        std::string identifier,
        std::any assign)
    {
        std::cout << "handle_statement_declaration " << identifier << std::endl;
        auto decl = std::make_shared<typename DataflowVariableDeclarationAliasType<expenv, dft>::type>(
            typename DataflowVariableAliasType<expenv, dft>::type(identifier));
        auto var = std::make_shared<typename DataflowVariableAliasType<expenv, dft>::type>(
            identifier, decl.get(), suffixes);
        decl->set_variable(*var);
        node_arena.push_back(decl);
        node_arena.push_back(var);
        if (!assign.has_value())
        {
            // Stocke un shared_ptr dans la SymbolTable
            if (!SymbolTable::getInstance().declareVariable(identifier, var))
            {
                throw std::runtime_error("Redeclare a variable already declared 1 " + identifier);
            }
            return *decl;
        }
        //typename RvalueExpressionVariantTypeAlias<expenv,dft>::type assigned_expr = std::any_cast<typename RvalueExpressionVariantTypeAlias<expenv,dft>::type>(assign);
        auto left = std::make_shared<variable_expression<dft, expenv>>(var.get());
        auto right = ast_builder_detail::try_extract<dft, expenv>(assign);
        node_arena.push_back(std::static_pointer_cast<ast_node>(left));
        node_arena.push_back(right);
        if (!right)
            throw std::runtime_error("handle_statement_declaration INT: expression droite invalide");
        typename DataflowAssignmentAliasType<expenv, dft>::type assignment(left.get(), right.get());
        if (!SymbolTable::getInstance().declareVariable(identifier, var))
        {
            throw std::runtime_error("Redeclare a variable already declared 2 " + identifier);
        }
        std::cout << "return PAIR" << std::endl;
        return std::pair{*decl,assignment};
    }

    std::any visitStatementDeclaration(ChipsParser::StatementDeclarationContext *ctx);

    std::any visitPassExpr0(ChipsParser::PassExpr0Context *ctx);

    std::any visitPassExpr01(ChipsParser::PassExpr01Context* ctx);

    std::any visitPassExpr1(ChipsParser::PassExpr1Context *ctx);

    std::any visitPassExpr2(ChipsParser::PassExpr2Context *ctx);

    /**
     * FUNCTION HELPERS TO MAKE CLASSES
     */

    /**
     * @brief Permet de créer linking_statement
     */
    template<block_type lk, block_type st, typename Dims_link, typename Dims_sup>
    linking_statement make_linking_statement(std::any linkable_any, Dims_link dims_link, 
                                             std::any support_any, Dims_sup dims_sup){
        if constexpr(st == block_type::LOGICAL){
            throw std::runtime_error("Logical can't be support for link method");
        } else {
            auto linkable_var = std::any_cast<std::shared_ptr<block_variable<lk>>>(linkable_any);
            auto support_var = std::any_cast<std::shared_ptr<block_variable<st>>>(support_any);

            auto* linkable = keep_value_alive(system_variable_block_expression<lk>(linkable_var.get(), dims_link));
            auto* support = keep_value_alive(system_variable_block_expression<st>(support_var.get(), dims_sup));

            linking_statement linking(linkable, support);
            return linking;
        }
    }

    /**
     * @brief Permet de créer un function_output<DFK,DFT> où DFK et DFT sont le dataflow_kind et dataflow_type
     * 
     * @param identifier Nom de la fonction
     * @param expr Expression retouner par la fonction
     */
    template <dataflow_kind dfk, dataflow_type dft>
    function_output<dfk, dft> make_function_output(const std::string &identifier, std::shared_ptr<rvalue<dft, expression_env::PRIMITIVE>> &expr)
    {
        rvalue_variant<expression_env::PRIMITIVE> rval = make_variant_from_node(expr);

        function_output<dfk, dft>
            final_output(identifier, std::get<rvalue<dft, expression_env::PRIMITIVE> *>(rval));
        return final_output;
    }

    /**
     * @brief Permet de récupérer un variable_expression ou variable_contextual_expression
     * 
     * @param l_identifier Nom de la variable
     * @param suffixes Index du tableau
     * @param is_contextual Booléen pour savoir si on doit récuperer un contextuel ou non
     */
    std::any handle_var(std::string l_identifier, std::any suffixes, bool is_contextual);

    template <statement_env stenv>
    void travel_recurrent_statement(ChipsParser::StatementContext *stt, statement_fillable<stenv> *datastruct)
    {
        try
        {
            std::any followup = visit(stt);

            // DECLARATIONS FEATURING AN ASSIGNMENT MUST BE DISTINGUISHED IN THE METAMODEL
            if (ast_builder_detail::is_declaration_with_expression(stt))
            {
                ChipsParser::StatementDeclarationContext *decl = dynamic_cast<ChipsParser::StatementDeclarationContext *>(stt);
                if (dynamic_cast<ChipsParser::IntTypeContext *>(decl->df_type()))
                {
                    ast_builder_detail::get_typed_pair_of_decl_and_expr<stenv, dataflow_type::INT>(datastruct, followup);
                }
                else if (dynamic_cast<ChipsParser::FloatTypeContext *>(decl->df_type()))
                {
                    ast_builder_detail::get_typed_pair_of_decl_and_expr<stenv, dataflow_type::FLOAT>(datastruct, followup);
                }
                else if (dynamic_cast<ChipsParser::BoolTypeContext *>(decl->df_type()))
                {
                    ast_builder_detail::get_typed_pair_of_decl_and_expr<stenv, dataflow_type::BOOL>(datastruct, followup);
                }
                else
                {
                    throw std::runtime_error("unrecognized pair generating node type");
                }
            }
            else
            {
                static constexpr auto expenv = SttEnvToExpEnv<stenv>::value;
                using sttvarianttype = typename StatementVariantTypeAlias<expenv>::type;
                datastruct->add_statement(std::get<sttvarianttype>(ast_builder_detail::try_extract_recurring_statement<stenv>(followup)));
            }
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }

    /**
     * @brief Permet de savoir la valeur est un function_parameter
     */
    bool is_function_parameter(std::any& value);

    /**
     * @brief Permet de créer un channel_eater
     * 
     * @param variable Représente un block_variable
     * @param parameter_who_eat Représente un node_element_declaration<CHANNEL>
     * @param dims Index du tableau
     */
    channel_eater make_channel_eater(std::any& variable, std::any& parameter_who_eat, 
                                     std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dims);

    /**
     * @brief Permet de créer un channel_feeder
     * 
     * @param variable Représente un block_variable
     * @param parameter_who_eat Représente un node_element_declaration<CHANNEL>
     * @param dims Index du tableau
     */
    channel_feeder make_channel_feeder(std::any& variable, std::any& channel_who_feed,
                                     std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dims);

    /**
     * @brief Permet de récupérer le dataflow_type en fonction d'un objet qui à un dataflow_type en template
     */
    template<expression_env expenv>
    dataflow_type get_type_of_output(std::any& value){
        std::cout << "get_type_of_output: " << ast_builder_detail::type_name(value.type()) << std::endl;
        if constexpr(expenv == expression_env::COLLECTIVE){
            if(auto* output = std::any_cast<target_output>(&value)){
                const auto& expr0 = output->m_expressions.at(0);
                std::cout << "expr0: " << ast_builder_detail::type_name(std::any{expr0}.type()) << std::endl;
                if(std::holds_alternative<rvalue<dataflow_type::INT,expenv>*>(expr0)){
                    return dataflow_type::INT;
                }
                if(std::holds_alternative<rvalue<dataflow_type::FLOAT,expenv>*>(expr0)){
                    return dataflow_type::FLOAT;
                }
                if(std::holds_alternative<rvalue<dataflow_type::BOOL,expenv>*>(expr0)){
                    return dataflow_type::BOOL;
                }
            }
            if(auto* output = std::any_cast<default_output>(&value)){
                return ast_builder_detail::get_dataflow_type<expenv>(output->m_accumulator_expressions.at(0));
            }
        }
        throw std::runtime_error("The value is not a default or target output");
    };
};

#endif