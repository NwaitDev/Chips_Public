#include "ASTBuilder.hpp"
#include "ast_lrxvalues.hpp"

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

std::any ASTBuilder::visitProgram(ChipsParser::ProgramContext *ctx)
{
    program_node prgm;
    std::cout << "visit program" << std::endl;
    for (ChipsParser::PreambleContext *pc : ctx->preamble())
    {

#define APPEND_CASTED_DEF(POTENTIAL, EXPENV)                                                          \
    if (POTENTIAL *stuff = dynamic_cast<POTENTIAL *>(pc); stuff != nullptr)                           \
    {                                                                                                 \
        current_env = EXPENV;                                                                         \
        std::any def = visit(stuff);                                                                  \
        if (auto *physical = std::any_cast<physical_definition>(&def))                                \
        {                                                                                             \
            prgm.get_preamble().add_definition(physical);                                             \
        }                                                                                             \
        else if (auto *logical = std::any_cast<logical_definition>(&def))                             \
        {                                                                                             \
            prgm.get_preamble().add_definition(logical);                                              \
        }                                                                                             \
        else                                                                                          \
        {                                                                                             \
            throw std::runtime_error(ast_builder_detail::type_name(def.type()) + " not implemented"); \
        }                                                                                             \
        continue;                                                                                     \
    }

        APPEND_CASTED_DEF(ChipsParser::ObjectDefinitionContext, expression_env::PRIMITIVE)
        APPEND_CASTED_DEF(ChipsParser::CollectiveOperationDefinitionContext, expression_env::COLLECTIVE)
        APPEND_CASTED_DEF(ChipsParser::ImplementationDefinitionContext, expression_env::PRIMITIVE)
        APPEND_CASTED_DEF(ChipsParser::FunctionDefinitionContext, expression_env::PRIMITIVE)

#undef APPEND_CASTED_DEF

        std::cerr << "Unknown definition type in the preamble section!\n";
    }

    std::cout << "nb statements in system section root level: "
              << ctx->system()->s_statement().size() << std::endl;

    current_env = expression_env::SYSTEM;
    for (ChipsParser::S_statementContext *ssc : ctx->system()->s_statement())
    {

#define SSTATEMENT_CAST(POTENTIAL, ERRMSG)                                                 \
    if (POTENTIAL *stuff = dynamic_cast<POTENTIAL *>(ssc); stuff != nullptr)               \
    {                                                                                      \
        std::any res = visit(stuff);                                                       \
        try                                                                                \
        {                                                                                  \
            prgm.get_system().add_statement(std::any_cast<system_statement_variant>(res)); \
        }                                                                                  \
        catch (std::bad_any_cast e)                                                        \
        {                                                                                  \
            std::cerr << ERRMSG << std::endl;                                              \
            throw e;                                                                       \
        }                                                                                  \
        continue;                                                                          \
    }

        SSTATEMENT_CAST(ChipsParser::ObjectDeclarationContext, "PBLM with ObjectDecl")
        SSTATEMENT_CAST(ChipsParser::FeedingStatementContext, "PBLM with feeding")
        SSTATEMENT_CAST(ChipsParser::LinkingStatementContext, "PBLM with linking")
        SSTATEMENT_CAST(ChipsParser::ImplementationStatementContext, "PBLM with implem")
        SSTATEMENT_CAST(ChipsParser::SLoopStatementContext, "PBLM with sloop")
        SSTATEMENT_CAST(ChipsParser::SIfElseStatementContext, "PBLM with sifelse")
        SSTATEMENT_CAST(ChipsParser::SIfStatementContext, "PBLM with sif")
#undef SSTATEMENT_CAST

        if (ChipsParser::RegularStatementContext *stt = dynamic_cast<ChipsParser::RegularStatementContext *>(ssc); stt != nullptr)
        {
            travel_recurrent_statement<statement_env::SYSTEM>(
                stt->statement(),
                static_cast<statement_fillable<statement_env::SYSTEM> *>(&prgm.m_system));
            continue;
        }

        std::cerr << "Unknown statement type in the system section root level!\n"
                  << "Rule index: " << ssc->getRuleIndex() << std::endl;
    }

    return prgm;
}

std::any ASTBuilder::visitObjectDefinition(ChipsParser::ObjectDefinitionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method ObjectDefinitionContext");
}

std::any ASTBuilder::visitCollectiveOperationDefinition(ChipsParser::CollectiveOperationDefinitionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CollectiveOperationDefinitionContext");
}

std::any ASTBuilder::visitImplementationDefinition(ChipsParser::ImplementationDefinitionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method ImplementationDefinitionContext");
}

std::any ASTBuilder::visitObject_def(ChipsParser::Object_defContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method Object_defContext");
}

std::any ASTBuilder::visitImplementation_def(ChipsParser::Implementation_defContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method Implementation_defContext");
}

std::any ASTBuilder::visitNode_mapping(ChipsParser::Node_mappingContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method Node_mappingContext");
}

std::any ASTBuilder::visitLogicalDefintion(ChipsParser::LogicalDefintionContext *ctx)
{

    ChipsParser::L_function_defContext *lfd = ctx->l_function_def();
    std::string identifier = lfd->IDENTIFIER()->getText();
    std::cout << "visit logical definition " << identifier << std::endl;

    // we enter in a new scope
    SymbolTable::getInstance().enterScope();

    std::vector<ChipsParser::Df_parameter_declContext *> old_ast_params = lfd->df_parameter_decl();
    std::vector<function_parameter_variant> params;
    for (ChipsParser::Df_parameter_declContext *stuff : old_ast_params)
    {
        std::cout << "visit function parameter logical" << std::endl;

        dataflow_type dft = std::any_cast<dataflow_type>(visit(stuff->df_type()));
        std::string identifier = stuff->IDENTIFIER()->getText();

#define TRY_ADD_PARAM(DFK, DFT)                                                                  \
    if (dft == DFT)                                                                              \
    {                                                                                            \
        dataflow_declaration<DFT, statement_env::DEFINITION> declaration(identifier);            \
        declaration.get_variable().set_declaration(&declaration);                                \
        function_parameter<DFK, DFT> new_ast_param(identifier, declaration);                     \
        if (!SymbolTable::getInstance().declareVariable(identifier, declaration.get_variable())) \
        {                                                                                        \
            throw std::runtime_error("'" + identifier + "' was already declarated before");      \
        }                                                                                        \
        params.push_back(&new_ast_param);                                                        \
        continue;                                                                                \
    }

        TRY_ADD_PARAM(dataflow_kind::LOGICAL, dataflow_type::INT)
        TRY_ADD_PARAM(dataflow_kind::LOGICAL, dataflow_type::FLOAT)
        TRY_ADD_PARAM(dataflow_kind::LOGICAL, dataflow_type::BOOL)
#undef TRY_ADD_PARAM
        // params.push_back(std::any_cast<function_parameter_variant>(visit(stuff)));
    }
    std::cout << "end push param" << std::endl;
    init_section init = std::any_cast<init_section>(visitInit_section(lfd->init_section()));
    then_section then = std::any_cast<then_section>(visitThen_section(lfd->then_section()));

    std::vector<ChipsParser::Named_outputContext *> old_ast_outputs = lfd->named_output();
    std::vector<function_output_variant> outputs;
    std::cout << "visiting output logical" << std::endl;
    for (ChipsParser::Named_outputContext *stuff : old_ast_outputs)
    {
        std::string identifier = stuff->IDENTIFIER()->getText();
        std::cout << "output logical " << identifier << std::endl;
        std::any exp = visit(stuff->expr(0));

        if (auto expr = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(exp))
        {
            auto out = std::make_shared<function_output<dataflow_kind::LOGICAL, dataflow_type::INT>>(
                make_function_output<dataflow_kind::LOGICAL, dataflow_type::INT>(identifier, expr));
            node_arena.push_back(out);
            outputs.push_back(out.get());
        }
        else if (auto expr = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(exp))
        {
            auto out = std::make_shared<function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>(
                make_function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>(identifier, expr));
            node_arena.push_back(out);
            outputs.push_back(out.get());
        }
        else if (auto expr = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(exp))
        {
            auto out = std::make_shared<function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>>(
                make_function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>(identifier, expr));
            node_arena.push_back(out);
            outputs.push_back(out.get());
        }
        else
        {
            throw std::runtime_error("Unknown type of expr in make_function_output " + ast_builder_detail::type_name(exp.type()));
        }
        continue;
    }

    chips::logical_definition logical(identifier, params, init, then, outputs);
    SymbolTable::getInstance().exitScope();
    SymbolTable::getInstance().declareFunctionLogical(identifier, logical);
    SymbolTable::getInstance().dump();
    std::cout << "END LOGICAL " << identifier << std::endl;
    return logical;
}

std::any ASTBuilder::visitPhysicalDefinition(ChipsParser::PhysicalDefinitionContext *ctx)
{

    ChipsParser::P_function_defContext *pfd = ctx->p_function_def();
    std::string identifier = pfd->IDENTIFIER()->getText();
    std::cout << "visit physical definition " << identifier << std::endl;
    std::vector<ChipsParser::Pdf_parameter_declContext *> all_params = pfd->pdf_parameter_decl();
    std::vector<function_parameter_variant> params;
    std::vector<physical_parameter_variant> sensors;
    // we enter in a new scope
    SymbolTable::getInstance().enterScope();
    for (ChipsParser::Pdf_parameter_declContext *parameter : all_params)
    {
        std::string pname = parameter->IDENTIFIER()->getText();
        if (ChipsParser::SensorParameterTypeContext *stuff = dynamic_cast<ChipsParser::SensorParameterTypeContext *>(parameter->pdf_parameter_type()); stuff != nullptr)
        {
            dataflow_type dft = std::any_cast<dataflow_type>(visit(stuff));

#define TRY_ADD_SENSOR(DFK, DFT)                                                             \
    if (dft == DFT)                                                                          \
    {                                                                                        \
        dataflow_declaration<DFT, statement_env::DEFINITION> declaration(pname);             \
        declaration.get_variable().set_declaration(&declaration);                            \
        function_parameter<DFK, DFT> new_ast_param(pname, declaration);                      \
        SymbolTable::getInstance().declareSensorVariable(pname, declaration.get_variable()); \
        sensors.push_back(&new_ast_param);                                                   \
        continue;                                                                            \
    }

            TRY_ADD_SENSOR(dataflow_kind::PHYSICAL, dataflow_type::INT)
            TRY_ADD_SENSOR(dataflow_kind::PHYSICAL, dataflow_type::FLOAT)
            TRY_ADD_SENSOR(dataflow_kind::PHYSICAL, dataflow_type::BOOL)
#undef TRY_ADD_SENSOR
            std::cerr << "Unknown parameter type in the PhysicalDefinitionContext" << std::endl;
        }
        if (ChipsParser::FunctionParameterTypeContext *stuff = dynamic_cast<ChipsParser::FunctionParameterTypeContext *>(parameter->pdf_parameter_type()); stuff != nullptr)
        {
            dataflow_type dft = std::any_cast<dataflow_type>(visit(stuff));

#define TRY_ADD_PARAM(DFK, DFT)                                                        \
    if (dft == DFT)                                                                    \
    {                                                                                  \
        dataflow_declaration<DFT, statement_env::DEFINITION> declaration(pname);       \
        declaration.get_variable().set_declaration(&declaration);                      \
        function_parameter<DFK, DFT> new_ast_param(pname, declaration);                \
        params.push_back(&new_ast_param);                                              \
        SymbolTable::getInstance().declareVariable(pname, declaration.get_variable()); \
        continue;                                                                      \
    }

            TRY_ADD_PARAM(dataflow_kind::LOGICAL, dataflow_type::INT)
            TRY_ADD_PARAM(dataflow_kind::LOGICAL, dataflow_type::FLOAT)
            TRY_ADD_PARAM(dataflow_kind::LOGICAL, dataflow_type::BOOL)
#undef TRY_ADD_PARAM
            std::cerr << "Unknown parameter type in the PhysicalDefinitionContext" << std::endl;
        }
        std::cerr << "Unknown parameter super type in the PhysicalDefinitionContext" << std::endl;
    }

    with_section with = std::any_cast<with_section>(visitWith_section(pfd->with_section()));
    init_section init = std::any_cast<init_section>(visitInit_section(pfd->init_section()));
    then_section then = std::any_cast<then_section>(visitThen_section(pfd->then_section()));

    std::vector<function_output_variant> outputs;
    std::vector<physical_output_variant> actuators;
    for (ChipsParser::P_named_outputContext *output : pfd->p_named_output())
    {

        if (ChipsParser::FunctionOutputContext *stuff = dynamic_cast<ChipsParser::FunctionOutputContext *>(output); stuff != nullptr)
        {
            std::string identifier = stuff->named_output()->IDENTIFIER()->getText();
            std::cout << "output " << identifier << std::endl;
            std::any exp = visit(stuff->named_output()->expr(0));

            if (auto expr = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(exp))
            {
                auto out = std::make_shared<function_output<dataflow_kind::LOGICAL, dataflow_type::INT>>(
                    make_function_output<dataflow_kind::LOGICAL, dataflow_type::INT>(identifier, expr));
                node_arena.push_back(out);
                outputs.push_back(out.get());
            }
            else if (auto expr = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(exp))
            {
                auto out = std::make_shared<function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>(
                    make_function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>(identifier, expr));
                node_arena.push_back(out);
                outputs.push_back(out.get());
            }
            else if (auto expr = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(exp))
            {
                auto out = std::make_shared<function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>>(
                    make_function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>(identifier, expr));
                node_arena.push_back(out);
                outputs.push_back(out.get());
            }
            else
            {
                throw std::runtime_error("Unknown type of expr in make_function_output " + ast_builder_detail::type_name(exp.type()));
            }
            continue;
        }
        if (ChipsParser::ActuatorOutputContext *stuff = dynamic_cast<ChipsParser::ActuatorOutputContext *>(output); stuff != nullptr)
        {
            std::string identifier = stuff->IDENTIFIER()->getText();
            std::cout << "output " << identifier << std::endl;
            std::any exp = visit(stuff->expr(0));

            if (auto expr = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(exp))
            {
                auto out = std::make_shared<function_output<dataflow_kind::PHYSICAL, dataflow_type::INT>>(
                    make_function_output<dataflow_kind::PHYSICAL, dataflow_type::INT>(identifier, expr));
                node_arena.push_back(out);
                actuators.push_back(out.get());
            }
            else if (auto expr = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(exp))
            {
                auto out = std::make_shared<function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>(
                    make_function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>(identifier, expr));
                node_arena.push_back(out);
                actuators.push_back(out.get());
            }
            else if (auto expr = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(exp))
            {
                auto out = std::make_shared<function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>(
                    make_function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL>(identifier, expr));
                node_arena.push_back(out);
                actuators.push_back(out.get());
            }
            else
            {
                throw std::runtime_error("Unknown type of expr in make_function_output " + ast_builder_detail::type_name(exp.type()));
            }
            continue;
        }
        std::cerr << "Unknown output super type in the PhysicalDefinitionContext" << std::endl;
    }
    std::cout << "return physical" << std::endl;
    chips::physical_definition physical(identifier, params, init, then, outputs, with, sensors, actuators);
    SymbolTable::getInstance().exitScope();
    SymbolTable::getInstance().declareFunctionPhysical(identifier, physical);
    SymbolTable::getInstance().dump();
    std::cout << "END PHYSICAL " << identifier << std::endl;
    return physical;
}

std::any ASTBuilder::visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method Collective_op_defContext");
}

std::any ASTBuilder::visitDefaultOutput(ChipsParser::DefaultOutputContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method DefaultOutputContext");
}

std::any ASTBuilder::visitChanneledOutput(ChipsParser::ChanneledOutputContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method ChanneledOutputContext");
}

std::any ASTBuilder::visitL_function_def(ChipsParser::L_function_defContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method L_function_defContext");
}

std::any ASTBuilder::visitP_function_def(ChipsParser::P_function_defContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method P_function_defContext");
}

std::any ASTBuilder::visitC_signature(ChipsParser::C_signatureContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method C_signatureContext");
}

std::any ASTBuilder::visitC_keywords(ChipsParser::C_keywordsContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method C_keywordsContext");
}

std::any ASTBuilder::visitWith_section(ChipsParser::With_sectionContext *ctx)
{
    std::cout << "visiting With" << std::endl;
    with_section with;
    for (ChipsParser::With_statementContext *stt : ctx->with_statement())
    {
        std::any followup = visit(stt);
        try
        {
            with.add_statement(ast_builder_detail::try_extract_node_specific_statement(followup));
            continue;
        }
        catch (const std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }

        try
        {
            with.add_statement(std::get<node_statement_variant>(ast_builder_detail::try_extract_node_recurring_statement(followup)));
            continue;
        }
        catch (const std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }
        throw std::runtime_error("Unknown kind of statement in with section");
    }
    return with;
}

std::any ASTBuilder::visitChannelDeclaration(ChipsParser::ChannelDeclarationContext *ctx)
{
    std::cout << "Visiting Channel declaration" << std::endl;
    return node_element_declaration<node_element::CHANNEL>(ctx->IDENTIFIER(0)->getText(), ctx->IDENTIFIER(1)->getText());
}

std::any ASTBuilder::handle_var(std::string identifier, std::any suffixes, bool is_contextual)
{
    std::cout << "visit var " << identifier << std::endl;
    std::optional<std::any> variable;

    if (!is_contextual)
    {
        variable = SymbolTable::getInstance().lookupVariable(identifier);
        if (!variable.has_value())
        {
            variable = SymbolTable::getInstance().lookupSensorVariable(identifier);
        }
    }
    else
    {
        variable = SymbolTable::getInstance().lookupContextualVariable(identifier);
    }

    if (!variable.has_value())
    {
        throw std::runtime_error("'" + identifier + "' was never declarated before");
    }

    std::cout << "handle var type: " << ast_builder_detail::type_name(variable.value().type()) << std::endl;

    std::cout << "before switch" << std::endl;
    switch (current_env)
    {
    case expression_env::PRIMITIVE:
    {
        auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(suffixes);
        if (!is_contextual)
            return tryAllTypes<expression_env::PRIMITIVE>(identifier, variable.value(), dims);
        return tryAllTypesContextual<expression_env::PRIMITIVE>(identifier, variable.value(), dims);
    }
    }
    std::cout << "after switch" << std::endl;
    throw std::runtime_error("handle_var: Unsupported environment " + expenv_to_string(current_env));
}

std::any ASTBuilder::handle_statement_assignment(std::string identifier, std::any suffixes, std::any assign, bool is_contextual)
{
    std::cout << "handle_statement_assignment" << std::endl;
    std::optional<std::any> variable;
    if (is_contextual)
    {
        variable = SymbolTable::getInstance().lookupContextualVariable(identifier);
    }
    else
    {
        variable = SymbolTable::getInstance().lookupVariable(identifier);
        // TODO: demander à Anna si un sensor peut etre un lvalue
    }

    if (!variable.has_value())
    {
        throw std::runtime_error("'" + identifier + "' was never declarated before");
    }
    auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(suffixes);
    auto var = (!is_contextual) ? tryAllTypes<expression_env::PRIMITIVE>(identifier, variable.value(), dims) : tryAllTypesContextual<expression_env::PRIMITIVE>(identifier, variable.value(), dims);

    std::cout << "Type var (handle assign) " << identifier << ": " << ast_builder_detail::type_name(var.type()) << std::endl;
    // try{
    //     auto exp = std::any_cast<dataflow_primitive_variable<dataflow_type::INT>>(variable.value());
    //     std::cout << "TYPE VALUE: " << ast_builder_detail::type_name(std::any{exp.get_declaration()}.type()) << std::endl;
    // }catch(const std::bad_any_cast& e){
    //     std::cout << "UP " << identifier << std::endl;
    //     std::cout << e.what() << std::endl;
    // }

    if (auto right = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(assign))
    {
        try
        {
            if (!is_contextual)
            {
                auto left = std::any_cast<std::shared_ptr<variable_expression<dataflow_type::INT, expression_env::PRIMITIVE>>>(var);
                node_arena.push_back(left);
                node_arena.push_back(right);
                dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION> assignment(left.get(), right.get());
                return assignment;
            }
            // auto var_ptr = std::any_cast<std::shared_ptr<contextual_variable<dataflow_type::INT>>>(var);
            // auto left = std::make_shared<variable_contextual_expression<dataflow_type::INT, expression_env::PRIMITIVE>>(var_ptr.get(), dims);
            auto left = std::any_cast<std::shared_ptr<variable_contextual_expression<dataflow_type::INT, expression_env::PRIMITIVE>>>(var);
            node_arena.push_back(left);
            node_arena.push_back(right);
            dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION> assignment(left.get(), right.get());
            return assignment;
        }
        catch (const std::bad_any_cast &e)
        {
            throw std::runtime_error("Erreur de cast dans la récupération du pointeur de variable INT depuis la SymbolTable");
        }
    }
    else if (auto right = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(assign))
    {
        try
        {
            if (!is_contextual)
            {
                auto left = std::any_cast<std::shared_ptr<variable_expression<dataflow_type::FLOAT, expression_env::PRIMITIVE>>>(var);
                node_arena.push_back(left);
                node_arena.push_back(right);
                dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION> assignment(left.get(), right.get());
                return assignment;
            }
            auto left = std::any_cast<std::shared_ptr<variable_contextual_expression<dataflow_type::FLOAT, expression_env::PRIMITIVE>>>(var);
            node_arena.push_back(left);
            node_arena.push_back(right);
            dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION> assignment(left.get(), right.get());
            return assignment;
        }
        catch (const std::bad_any_cast &e)
        {
            throw std::runtime_error("Erreur de cast dans la récupération du pointeur de variable FLOAT depuis la SymbolTable");
        }
    }
    else if (auto right = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(assign))
    {
        try
        {
            if (!is_contextual)
            {
                auto left = std::any_cast<std::shared_ptr<variable_expression<dataflow_type::BOOL, expression_env::PRIMITIVE>>>(var);
                node_arena.push_back(left);
                node_arena.push_back(right);
                dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION> assignment(left.get(), right.get());
                return assignment;
            }
            auto left = std::any_cast<std::shared_ptr<variable_contextual_expression<dataflow_type::BOOL, expression_env::PRIMITIVE>>>(var);
            node_arena.push_back(left);
            node_arena.push_back(right);
            dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION> assignment(left.get(), right.get());
            return assignment;
        }
        catch (const std::bad_any_cast &e)
        {
            throw std::runtime_error("Erreur de cast dans la récupération du pointeur de variable BOOL depuis la SymbolTable");
        }
    }

    return std::any{};
}

std::any ASTBuilder::handle_statement_declaration_contextual(dataflow_type type, std::any suffixes, std::string identifier, std::any assign)
{
    std::cout << "handle_statement_declaration_contextual " << dft_to_string(type) << std::endl;

    auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(suffixes);
    switch (type)
    {
    case dataflow_type::INT:
    {
        auto decl = std::make_shared<node_element_declaration<node_element::CONTEXTUAL_INT>>(
            contextual_variable<dataflow_type::INT>(identifier), identifier);
        auto var = std::make_shared<contextual_variable<dataflow_type::INT>>(
            identifier, decl.get(), dims);
        decl->set_variable(*var);
        node_arena.push_back(decl);
        node_arena.push_back(var);
        if (!assign.has_value())
        {
            if (!SymbolTable::getInstance().declareContextualVariable(identifier, var))
            {
                throw std::runtime_error("Redeclare a contextual variable already declared");
            }
            return *decl;
        }
        throw std::runtime_error("TODO: Implemented for declaration of an int contextual assignment");
    }
    case dataflow_type::FLOAT:
    {
        auto decl = std::make_shared<node_element_declaration<node_element::CONTEXTUAL_FLOAT>>(
            contextual_variable<dataflow_type::FLOAT>(identifier), identifier);
        auto var = std::make_shared<contextual_variable<dataflow_type::FLOAT>>(
            identifier, decl.get(), dims);
        decl->set_variable(*var);
        node_arena.push_back(decl);
        node_arena.push_back(var);
        if (!assign.has_value())
        {
            if (!SymbolTable::getInstance().declareContextualVariable(identifier, var))
            {
                throw std::runtime_error("Redeclare a contextual variable already declared");
            }
            return *decl;
        }
        throw std::runtime_error("TODO: Implemented for declaration of an float contextual assignment");
    }
    case dataflow_type::BOOL:
    {
        auto decl = std::make_shared<node_element_declaration<node_element::CONTEXTUAL_BOOL>>(
            contextual_variable<dataflow_type::BOOL>(identifier), identifier);
        auto var = std::make_shared<contextual_variable<dataflow_type::BOOL>>(
            identifier, decl.get(), dims);
        decl->set_variable(*var);
        node_arena.push_back(decl);
        node_arena.push_back(var);
        if (!assign.has_value())
        {
            if (!SymbolTable::getInstance().declareContextualVariable(identifier, var))
            {
                throw std::runtime_error("Redeclare a contextual variable already declared");
            }
            return *decl;
        }
        throw std::runtime_error("TODO: Implemented for declaration of an BOOL contextual assignment");
    }
    }
    throw std::runtime_error("Unknown type");
}

std::any ASTBuilder::visitContextualDeclaration(ChipsParser::ContextualDeclarationContext *ctx)
{
    std::cout << "visit contextual declaration" << std::endl;

    dataflow_type type = std::any_cast<dataflow_type>(visit(ctx->df_type()));
    std::any suffixes = visit(ctx->suffixes());
    std::string identifier = ctx->IDENTIFIER()->getText();
    std::any assign;

    if (ctx->expr())
    {
        assign = visit(ctx->expr());
    }
    return handle_statement_declaration_contextual(type, suffixes, identifier, assign);
}

std::any ASTBuilder::visitWithRegularStatement(ChipsParser::WithRegularStatementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method WithRegularStatementContext");
}

std::any ASTBuilder::visitInit_section(ChipsParser::Init_sectionContext *ctx)
{
    std::cout << "visiting Init" << std::endl;
    init_section init;
    for (ChipsParser::StatementContext *stt : ctx->statement())
    {
        try
        {
            std::any followup = visit(stt);

            // DECLARATIONS FEATURING AN ASSIGNMENT MUST BE DISTINGUISHED IN THE METAMODEL
            if (ChipsParser::StatementDeclarationContext *stuff = dynamic_cast<ChipsParser::StatementDeclarationContext *>(stt); (stuff != nullptr) && (stuff->expr() != nullptr))
            {
                if (dynamic_cast<ChipsParser::IntTypeContext *>(stuff->df_type()))
                {
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement(followup_pair.first)));
                    init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement(followup_pair.second)));
                }
                else if (dynamic_cast<ChipsParser::FloatTypeContext *>(stuff->df_type()))
                {
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement(followup_pair.first)));
                    init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement(followup_pair.second)));
                }
                else if (dynamic_cast<ChipsParser::BoolTypeContext *>(stuff->df_type()))
                {
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement(followup_pair.first)));
                    init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement(followup_pair.second)));
                }
                else
                {
                    throw std::runtime_error("unrecognized variable type");
                }
                continue;
            }
            else
            {
                init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement(followup)));
                continue;
            }
        }
        catch (const std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }
        throw std::runtime_error("Unknwon kind of statement in init section");
    }
    return init;
}

std::any ASTBuilder::visitThen_section(ChipsParser::Then_sectionContext *ctx)
{
    std::cout << "visiting Then" << std::endl;
    then_section then;

    for (ChipsParser::StatementContext *stt : ctx->statement())
    {
        std::cout << "statement of then section" << std::endl;
        std::any followup = visit(stt);

        try
        {
            then.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement(followup)));
            continue;
        }
        catch (const std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }
        throw std::runtime_error("Unknown kind of statement in then section");
    }
    std::cout << "end of statement of then section" << std::endl;
    return then;
}

template <dataflow_type DT, expression_env ENV, typename Dims>
std::any ASTBuilder::tryCastVar(const std::any &var, const Dims &dims)
{

    if (auto sptr = std::any_cast<std::shared_ptr<dataflow_primitive_variable<DT>>>(&var))
    {
        std::cout << "FIRST ANY CAST " << ast_builder_detail::type_name(std::any{sptr}.type()) << std::endl;
        if (*sptr)
            return std::make_shared<variable_expression<DT, ENV>>(sptr->get(), dims);
    }

    if (auto raw_ptr = std::any_cast<dataflow_primitive_variable<DT>>(&var))
    {
        std::cout << "SECOND ANY CAST" << std::endl;
        auto non_const_ptr = const_cast<dataflow_primitive_variable<DT> *>(raw_ptr);
        return std::make_shared<variable_expression<DT, ENV>>(non_const_ptr, dims);
    }

    return {};
}

template <dataflow_type DT, expression_env ENV, typename Dims>
std::any ASTBuilder::tryCastVarContextual(const std::any &var, const Dims &dims)
{

    if (auto sptr = std::any_cast<std::shared_ptr<contextual_variable<DT>>>(&var))
    {
        if (*sptr)
            return std::make_shared<variable_contextual_expression<DT, ENV>>(sptr->get(), dims);
    }

    if (auto raw_ptr = std::any_cast<contextual_variable<DT>>(&var))
    {
        auto non_const_ptr = const_cast<contextual_variable<DT> *>(raw_ptr);
        return std::make_shared<variable_contextual_expression<DT, ENV>>(non_const_ptr, dims);
    }

    return {};
}

template <expression_env ENV, typename Dims>
std::any ASTBuilder::tryAllTypes(const std::string &var_name, const std::any &var, const Dims &dims)
{
    std::cout << "before try all cast" << std::endl;
    if (auto r = tryCastVar<dataflow_type::INT, ENV>(var, dims); r.has_value())
        return r;
    if (auto r = tryCastVar<dataflow_type::FLOAT, ENV>(var, dims); r.has_value())
        return r;
    if (auto r = tryCastVar<dataflow_type::BOOL, ENV>(var, dims); r.has_value())
        return r;
    std::cout << "after try all cast" << std::endl;
    throw std::runtime_error(
        "visitVar: unknown dataflow type for variable '" + var_name + "' " + ast_builder_detail::type_name(var.type()));
}

template <expression_env ENV, typename Dims>
std::any ASTBuilder::tryAllTypesContextual(const std::string &var_name, const std::any &var, const Dims &dims)
{
    if (auto r = tryCastVarContextual<dataflow_type::INT, ENV>(var, dims); r.has_value())
        return r;
    if (auto r = tryCastVarContextual<dataflow_type::FLOAT, ENV>(var, dims); r.has_value())
        return r;
    if (auto r = tryCastVarContextual<dataflow_type::BOOL, ENV>(var, dims); r.has_value())
        return r;

    throw std::runtime_error(
        "visitVar: unknown dataflow type for contextual variable '" + var_name + "' " + ast_builder_detail::type_name(var.type()));
}

std::any ASTBuilder::visitVar(ChipsParser::VarContext *ctx)
{
    return handle_var(ctx->IDENTIFIER()->getText(),
                      visit(ctx->suffixes()),
                      false);
}

std::any ASTBuilder::visitVarContext(ChipsParser::VarContextContext *ctx)
{
    std::cout << "contextual ";
    return handle_var(ctx->IDENTIFIER()->getText(),
                      visit(ctx->suffixes()),
                      true);
}

std::any ASTBuilder::visitCStoplessExpression(ChipsParser::CStoplessExpressionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CStoplessExpressionContext");
}

std::any ASTBuilder::visitStop(ChipsParser::StopContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method StopContext");
}

std::any ASTBuilder::visitCLT(ChipsParser::CLTContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CLTContext");
}

std::any ASTBuilder::visitCGT(ChipsParser::CGTContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CGTContext");
}

std::any ASTBuilder::visitCLEQ(ChipsParser::CLEQContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CLEQContext");
}

std::any ASTBuilder::visitCGEQ(ChipsParser::CGEQContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CGEQContext");
}

std::any ASTBuilder::visitCNEQ(ChipsParser::CNEQContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CNEQContext");
}

std::any ASTBuilder::visitCEQ(ChipsParser::CEQContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CEQContext");
}

std::any ASTBuilder::visitCAND(ChipsParser::CANDContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CANDContext");
}

std::any ASTBuilder::visitCOR(ChipsParser::CORContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CORContext");
}

std::any ASTBuilder::visitPassCExpr0(ChipsParser::PassCExpr0Context *ctx)
{
    throw std::runtime_error("Unimplemented visit method PassCExpr0Context");
}

std::any ASTBuilder::visitCPLUS(ChipsParser::CPLUSContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CPLUSContext");
}

std::any ASTBuilder::visitCSUB(ChipsParser::CSUBContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CSUBContext");
}

std::any ASTBuilder::visitCNegate(ChipsParser::CNegateContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CNegateContext");
}

std::any ASTBuilder::visitPassCExpr1(ChipsParser::PassCExpr1Context *ctx)
{
    throw std::runtime_error("Unimplemented visit method PassCExpr1Context");
}

std::any ASTBuilder::visitCMULT(ChipsParser::CMULTContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CMULTContext");
}

std::any ASTBuilder::visitCDIV(ChipsParser::CDIVContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CDIVContext");
}

std::any ASTBuilder::visitCMOD(ChipsParser::CMODContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CMODContext");
}

std::any ASTBuilder::visitCNOT(ChipsParser::CNOTContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CNOTContext");
}

std::any ASTBuilder::visitPassCExpr2(ChipsParser::PassCExpr2Context *ctx)
{
    throw std::runtime_error("Unimplemented visit method PassCExpr2Context");
}

std::any ASTBuilder::visitCVariableExpression(ChipsParser::CVariableExpressionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CVariableExpressionContext");
}

std::any ASTBuilder::visitCINT(ChipsParser::CINTContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CINTContext");
}

std::any ASTBuilder::visitCFLOAT(ChipsParser::CFLOATContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CFLOATContext");
}

std::any ASTBuilder::visitCBOOL(ChipsParser::CBOOLContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CBOOLContext");
}

std::any ASTBuilder::visitINPUT(ChipsParser::INPUTContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method INPUTContext");
}

std::any ASTBuilder::visitCtxVariableExpression(ChipsParser::CtxVariableExpressionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CtxVariableExpressionContext");
}

std::any ASTBuilder::visitChanneledAccuExpression(ChipsParser::ChanneledAccuExpressionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method ChanneledAccuExpressionContext");
}

std::any ASTBuilder::visitFunctionCall(ChipsParser::FunctionCallContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method FunctionCallContext");
}

std::any ASTBuilder::visitCParenthesis(ChipsParser::CParenthesisContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CParenthesisContext");
}

std::any ASTBuilder::visitCCastAs(ChipsParser::CCastAsContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CCastAsContext");
}

std::any ASTBuilder::visitC_cast(ChipsParser::C_castContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method C_castContext");
}

std::any ASTBuilder::visitC_suffixes(ChipsParser::C_suffixesContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method C_suffixesContext");
}

std::any ASTBuilder::visitSSuffixableVariableExpression(ChipsParser::SSuffixableVariableExpressionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method SSuffixableVariableExpressionContext");
}

std::any ASTBuilder::visitSSuffixableFunctionCallExpression(ChipsParser::SSuffixableFunctionCallExpressionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method SSuffixableFunctionCallExpressionContext");
}

std::any ASTBuilder::visitSSuffixableBlockOutputExpression(ChipsParser::SSuffixableBlockOutputExpressionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method SSuffixableBlockOutputExpressionContext");
}

std::any ASTBuilder::visitBlock(ChipsParser::BlockContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method BlockContext");
}

std::any ASTBuilder::visitLoop_in(ChipsParser::Loop_inContext *ctx)
{
    std::cout << "visit loop in" << std::endl;
    std::string identifier = ctx->IDENTIFIER()->getText();
    switch (current_env)
    {
    case expression_env::PRIMITIVE:
        if (!ctx->expr().empty())
            return make_function<expression_env::PRIMITIVE>(identifier, ctx->expr());
        break;
    case expression_env::COLLECTIVE:
        if (!ctx->expr().empty())
            return make_function<expression_env::COLLECTIVE>(identifier, ctx->expr());
        break;
    case expression_env::SYSTEM:
        if (!ctx->expr().empty())
            return make_function<expression_env::SYSTEM>(identifier, ctx->expr());
        break;
    default:
        break;
    }

    throw std::runtime_error("Not implement for variable yet in loop_in context");
}

std::any ASTBuilder::visitLoop_statement(ChipsParser::Loop_statementContext *ctx)
{
    std::cout << "visit loop statement" << std::endl;

    // TODO bien faire le Scope avec SymbolTable
    SymbolTable::getInstance().enterScope();
    SymbolTable::getInstance().dump();

    std::string identifier = ctx->IDENTIFIER()->getText();

    std::cout << "Enter new Scope foreach " << identifier << std::endl;

    std::any loop_in = visit(ctx->loop_in());

    dataflow_type type = ast_builder_detail::get_dataflow_type<expression_env::PRIMITIVE>(loop_in);
    std::cout << dft_to_string(type) << std::endl;

    std::any iterator;
    switch (current_env)
    {
    case expression_env::PRIMITIVE:
        switch (type)
        {
        case dataflow_type::INT:
            iterator = handle_statement_declaration<expression_env::PRIMITIVE, dataflow_type::INT>(std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>(), identifier, std::any{});
        case dataflow_type::FLOAT:
            iterator = handle_statement_declaration<expression_env::PRIMITIVE, dataflow_type::FLOAT>(std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>(), identifier, std::any{});
        case dataflow_type::BOOL:
            iterator = handle_statement_declaration<expression_env::PRIMITIVE, dataflow_type::BOOL>(std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>(), identifier, std::any{});
        default:
            throw std::runtime_error("couldn't find type for the iterator in loop statement");
        }
    case expression_env::COLLECTIVE:
        switch (type)
        {
        case dataflow_type::INT:
            iterator = handle_statement_declaration<expression_env::COLLECTIVE, dataflow_type::INT>(std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>(), identifier, std::any{});
        case dataflow_type::FLOAT:
            iterator = handle_statement_declaration<expression_env::COLLECTIVE, dataflow_type::FLOAT>(std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>(), identifier, std::any{});
        case dataflow_type::BOOL:
            iterator = handle_statement_declaration<expression_env::COLLECTIVE, dataflow_type::BOOL>(std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>(), identifier, std::any{});
        default:
            throw std::runtime_error("couldn't find type for the iterator in loop statement");
        }
    case expression_env::SYSTEM:
        switch (type)
        {
        case dataflow_type::INT:
            iterator = handle_statement_declaration<expression_env::SYSTEM, dataflow_type::INT>(std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>(), identifier, std::any{});
        case dataflow_type::FLOAT:
            iterator = handle_statement_declaration<expression_env::SYSTEM, dataflow_type::FLOAT>(std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>(), identifier, std::any{});
        case dataflow_type::BOOL:
            iterator = handle_statement_declaration<expression_env::SYSTEM, dataflow_type::BOOL>(std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>(), identifier, std::any{});
        default:
            throw std::runtime_error("couldn't find type for the iterator in loop statement");
        }
    }

    switch (type)
    {
    case dataflow_type::INT:
    {
        auto iterable = make_primitive_iterable_variant_from_node(
            ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(loop_in));
        auto it = std::any_cast<dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>>(iterator);
        foreach_statement<statement_env::DEFINITION, dataflow_type::INT> foreach (it, iterable);
        std::any res = make_statement_foreach(foreach, ctx->statement());
        SymbolTable::getInstance().exitScope();
        std::cout << "Exit scope foreach" << std::endl;
        return res;
    }
    case dataflow_type::FLOAT:
    {
        break;
    }
    case dataflow_type::BOOL:
    {
        break;
    }
        throw std::runtime_error("Unknown kind of type for foreach statement");
    }

    // for(ChipsParser::StatementContext* stt : ctx->statement()){
    //     std::cout << "TODO statement loop" << std::endl;
    // }

    throw std::runtime_error("Error in method Loop_statementContext");
}

std::any ASTBuilder::visitC_loop_statement(ChipsParser::C_loop_statementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method C_loop_statementContext");
}

std::any ASTBuilder::visitS_loop_statement(ChipsParser::S_loop_statementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method S_loop_statementContext");
}

std::any ASTBuilder::visitIf_else_statement(ChipsParser::If_else_statementContext *ctx)
{
    std::cout << "visit if else statement" << std::endl;

    if_else_statement<statement_env::DEFINITION> if_else;

    // TODO: regarder les scopes avec SymbolTable

    visit(ctx->if_statement());

    SymbolTable::getInstance().enterScope();
    SymbolTable::getInstance().dump();

    for (ChipsParser::StatementContext *stt : ctx->statement())
    {
        std::any followup = visit(stt);

        try
        {
            if_else.m_else_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement(followup)));
            continue;
        }
        catch (const std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }
        throw std::runtime_error("Unknown kind of statement in else section");
    }

    SymbolTable::getInstance().exitScope();

    return if_else;
    // throw std::runtime_error("Unimplemented visit method If_else_statementContext");
}

std::any ASTBuilder::visitS_if_else_statement(ChipsParser::S_if_else_statementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method S_if_else_statementContext");
}

std::any ASTBuilder::visitC_if_else_statement(ChipsParser::C_if_else_statementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method C_if_else_statementContext");
}

std::any ASTBuilder::visitIf_statement(ChipsParser::If_statementContext *ctx)
{
    std::cout << "visit if statement" << std::endl;
    if_statement<statement_env::DEFINITION> if_stt;

    std::any val = visit(ctx->expr());
    auto node = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(val);
    if (!node)
    {
        throw std::runtime_error(
            "condition : l'expression doit être de type BOOL "
            "(env PRIMITIVE).");
    }

    node_arena.push_back(node);
    if_stt.m_condition = make_bool_rvalue_variant_from_node(node);

    std::cout << "statements if section" << std::endl;

    SymbolTable::getInstance().enterScope();
    SymbolTable::getInstance().dump();

    for (ChipsParser::StatementContext *stt : ctx->statement())
    {
        std::any followup = visit(stt);

        try
        {
            if_stt.m_if_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement(followup)));
            continue;
        }
        catch (const std::runtime_error &e)
        {
            std::cout << e.what() << std::endl;
        }
        throw std::runtime_error("Unknown kind of statement in if section");
    }

    SymbolTable::getInstance().exitScope();

    return if_stt;
}

std::any ASTBuilder::visitS_if_statement(ChipsParser::S_if_statementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method S_if_statementContext");
}

std::any ASTBuilder::visitC_if_statement(ChipsParser::C_if_statementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method C_if_statementContext");
}

std::any ASTBuilder::visitStatementAssignment(ChipsParser::StatementAssignmentContext *ctx)
{
    std::cout << "visit StatementAssignment" << std::endl;
    std::any suffixes = visit(ctx->suffixes());
    std::string var_name = ctx->IDENTIFIER()->getText();
    std::cout << "assign type var: " << ast_builder_detail::type_name(std::any{ctx->expr()}.type()) << std::endl;
    std::any assign = visit(ctx->expr());

    return handle_statement_assignment(var_name, suffixes, assign, false);
}

std::any ASTBuilder::visitStatementContextualAssignment(ChipsParser::StatementContextualAssignmentContext *ctx)
{
    std::cout << "visit StatementContextualAssignmentContext" << std::endl;

    std::any suffixes = visit(ctx->suffixes());
    std::string identifier = ctx->IDENTIFIER()->getText();
    std::any assign = visit(ctx->expr());

    return handle_statement_assignment(identifier, suffixes, assign, true);

    // throw std::runtime_error("Unimplemented visit method StatementContextualAssignmentContext");
}

std::any ASTBuilder::visitStatementLoop(ChipsParser::StatementLoopContext *ctx)
{
    return visit(ctx->loop_statement());
}

std::any ASTBuilder::visitStatementIfElse(ChipsParser::StatementIfElseContext *ctx)
{
    std::cout << "visit statement if else" << std::endl;
    return visit(ctx->if_else_statement());
    // throw std::runtime_error("Unimplemented visit method StatementIfElseContext");
}

std::any ASTBuilder::visitStatementIf(ChipsParser::StatementIfContext *ctx)
{
    std::cout << "visit statement if" << std::endl;
    return visit(ctx->if_statement());
    // throw std::runtime_error("Unimplemented visit method StatementIfContext");
}

std::any ASTBuilder::visitObjectDeclaration(ChipsParser::ObjectDeclarationContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method ObjectDeclarationContext");
}

std::any ASTBuilder::visitFeedingStatement(ChipsParser::FeedingStatementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method FeedingStatementContext");
}

std::any ASTBuilder::visitLinkingStatement(ChipsParser::LinkingStatementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method LinkingStatementContext");
}

std::any ASTBuilder::visitImplementationStatement(ChipsParser::ImplementationStatementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method ImplementationStatementContext");
}

std::any ASTBuilder::visitSLoopStatement(ChipsParser::SLoopStatementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method SLoopStatementContext");
}

std::any ASTBuilder::visitSIfElseStatement(ChipsParser::SIfElseStatementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method SIfElseStatementContext");
}

std::any ASTBuilder::visitSIfStatement(ChipsParser::SIfStatementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method SIfStatementContext");
}

std::any ASTBuilder::visitRegularStatement(ChipsParser::RegularStatementContext *ctx)
{
#define STATEMENT_CAST(POTENTIAL)                                                         \
    if (POTENTIAL *stuff = dynamic_cast<POTENTIAL *>(ctx->statement()); stuff != nullptr) \
        return visit(stuff);

    STATEMENT_CAST(ChipsParser::StatementDeclarationContext)
    STATEMENT_CAST(ChipsParser::StatementAssignmentContext)
    STATEMENT_CAST(ChipsParser::StatementContextualAssignmentContext)
    STATEMENT_CAST(ChipsParser::StatementLoopContext)
    STATEMENT_CAST(ChipsParser::StatementIfElseContext)
    STATEMENT_CAST(ChipsParser::StatementIfContext)
#undef STATEMENT_CAST
    throw std::runtime_error("Unrecognized statement kind while visiting RegularStatementContext");
}

std::any ASTBuilder::visitSBlockOutputExpression(ChipsParser::SBlockOutputExpressionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method SBlockOutputExpressionContext");
}

std::any ASTBuilder::visitSCollectiveCastExpression(ChipsParser::SCollectiveCastExpressionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method SCollectiveCastExpressionContext");
}

std::any ASTBuilder::visitSRegularExpression(ChipsParser::SRegularExpressionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method SRegularExpressionContext");
}

std::any ASTBuilder::visitCollective_operation(ChipsParser::Collective_operationContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method Collective_operationContext");
}

std::any ASTBuilder::visitCollectiveVariableDeclaration(ChipsParser::CollectiveVariableDeclarationContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CollectiveVariableDeclarationContext");
}

std::any ASTBuilder::visitCollectiveAssignment(ChipsParser::CollectiveAssignmentContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CollectiveAssignmentContext");
}

std::any ASTBuilder::visitContextualAssignment(ChipsParser::ContextualAssignmentContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method ContextualAssignmentContext");
}

std::any ASTBuilder::visitCollectiveLoopStatement(ChipsParser::CollectiveLoopStatementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CollectiveLoopStatementContext");
}

std::any ASTBuilder::visitCollectiveIfElseStatement(ChipsParser::CollectiveIfElseStatementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CollectiveIfElseStatementContext");
}

std::any ASTBuilder::visitCollectiveIfStatement(ChipsParser::CollectiveIfStatementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CollectiveIfStatementContext");
}

std::any ASTBuilder::visitNamed_output(ChipsParser::Named_outputContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method Named_outputContext");
}

std::any ASTBuilder::visitActuatorOutput(ChipsParser::ActuatorOutputContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method ActuatorOutputContext");
}

std::any ASTBuilder::visitFunctionOutput(ChipsParser::FunctionOutputContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method FunctionOutputContext");
}

std::any ASTBuilder::visitDf_parameter_decl(ChipsParser::Df_parameter_declContext *ctx)
{
    std::cout << "visit function parameter logical" << std::endl;

    dataflow_type dft = std::any_cast<dataflow_type>(visit(ctx->df_type()));
    std::string identifier = ctx->IDENTIFIER()->getText();

#define TRY_ADD_PARAM(DFK, DFT)                                                                  \
    if (dft == DFT)                                                                              \
    {                                                                                            \
        dataflow_declaration<DFT, statement_env::DEFINITION> declaration(identifier);            \
        declaration.get_variable().set_declaration(&declaration);                                \
        function_parameter<DFK, DFT> new_ast_param(identifier, declaration);                     \
        if (!SymbolTable::getInstance().declareVariable(identifier, declaration.get_variable())) \
        {                                                                                        \
            throw std::runtime_error("'" + identifier + "' was already declarated before");      \
        }                                                                                        \
        return new_ast_param;                                                                    \
    }

    TRY_ADD_PARAM(dataflow_kind::LOGICAL, dataflow_type::INT)
    TRY_ADD_PARAM(dataflow_kind::LOGICAL, dataflow_type::FLOAT)
    TRY_ADD_PARAM(dataflow_kind::LOGICAL, dataflow_type::BOOL)
#undef TRY_ADD_PARAM

    throw std::runtime_error("Unimplemented visit method Df_parameter_declContext");
}

std::any ASTBuilder::visit_dft(ChipsParser::Df_typeContext *dft)
{
    if (ChipsParser::IntTypeContext *stuff = dynamic_cast<ChipsParser::IntTypeContext *>(dft); stuff != nullptr)
    {
        return visitIntType(stuff);
    }
    if (ChipsParser::FloatTypeContext *stuff = dynamic_cast<ChipsParser::FloatTypeContext *>(dft); stuff != nullptr)
    {
        return visitFloatType(stuff);
    }
    if (ChipsParser::BoolTypeContext *stuff = dynamic_cast<ChipsParser::BoolTypeContext *>(dft); stuff != nullptr)
    {
        return visitBoolType(stuff);
    }
    throw std::runtime_error("unrecognized parameter type");
}

std::any ASTBuilder::visitFunctionParameterType(ChipsParser::FunctionParameterTypeContext *ctx)
{
    std::cout << "visit function parameter type" << std::endl;
    ChipsParser::Df_typeContext *dft = ctx->df_type();
    try
    {
        return visit_dft(dft);
    }
    catch (const std::runtime_error &e)
    {
        throw std::runtime_error("unrecognized parameter type in visit method FunctionParameterContext");
    }
}

std::any ASTBuilder::visitSensorParameterType(ChipsParser::SensorParameterTypeContext *ctx)
{
    std::cout << "visit sensor parameter type" << std::endl;
    ChipsParser::Df_typeContext *dft = ctx->df_type();
    try
    {
        return visit_dft(dft);
    }
    catch (const std::runtime_error &e)
    {
        throw std::runtime_error("unrecognized parameter type in visit method SensorParameterContext");
    }
}

std::any ASTBuilder::visitPdf_parameter_decl(ChipsParser::Pdf_parameter_declContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method Pdf_parameter_declContext");
}

std::any ASTBuilder::visitCdf_defaulted_decl(ChipsParser::Cdf_defaulted_declContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method Cdf_defaulted_declContext");
}

std::any ASTBuilder::visitCdf_full_declaration(ChipsParser::Cdf_full_declarationContext *ctx)
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

std::any ASTBuilder::visitFunction(ChipsParser::FunctionContext *ctx)
{
    std::string identifier = ctx->IDENTIFIER()->getText();
    switch (current_env)
    {
    case expression_env::PRIMITIVE:
        return make_function<expression_env::PRIMITIVE>(identifier, ctx->expr());
        break;
    case expression_env::COLLECTIVE:
        return make_function<expression_env::COLLECTIVE>(identifier, ctx->expr());
        break;
    case expression_env::SYSTEM:
        return make_function<expression_env::SYSTEM>(identifier, ctx->expr());
        break;
    default:
        break;
    }
    throw std::runtime_error("unknown function environment");
}

std::any ASTBuilder::visitLT(ChipsParser::LTContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::LTBuilder>(
        visit(ctx->expr0()), visit(ctx->expr()), "LT");
}

std::any ASTBuilder::visitLEQ(ChipsParser::LEQContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::LEQBuilder>(
        visit(ctx->expr0()), visit(ctx->expr()), "LEQ");
}

std::any ASTBuilder::visitGT(ChipsParser::GTContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::GTBuilder>(
        visit(ctx->expr0()), visit(ctx->expr()), "GT");
}

std::any ASTBuilder::visitGEQ(ChipsParser::GEQContext *ctx)
{
    std::cout << "visit >=" << std::endl;
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::GEQBuilder>(
        visit(ctx->expr0()), visit(ctx->expr()), "GEQ");
}

std::any ASTBuilder::visitEQ(ChipsParser::EQContext *ctx)
{
    std::cout << "visit ==" << std::endl;
    return ast_builder_detail::dispatch_binary<ast_builder_detail::EQBuilder>(
        visit(ctx->expr0()), visit(ctx->expr()), "EQ");
}

std::any ASTBuilder::visitNEQ(ChipsParser::NEQContext *ctx)
{
    return ast_builder_detail::dispatch_binary<ast_builder_detail::NEQBuilder>(
        visit(ctx->expr0()), visit(ctx->expr()), "NEQ");
}

std::any ASTBuilder::visitAND(ChipsParser::ANDContext *ctx)
{
    std::cout << "visit &&" << std::endl;
    return ast_builder_detail::dispatch_boolean_binary<ast_builder_detail::ANDBuilder>(
        visit(ctx->expr0()), visit(ctx->expr()), "AND");
}

std::any ASTBuilder::visitOR(ChipsParser::ORContext *ctx)
{
    return ast_builder_detail::dispatch_boolean_binary<ast_builder_detail::ORBuilder>(
        visit(ctx->expr0()), visit(ctx->expr()), "OR");
}

std::any ASTBuilder::visitPLUS(ChipsParser::PLUSContext *ctx)
{
    // std::cout << "visitPLUS()" << std::endl;
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::PlusBuilder>(
        visit(ctx->expr1()), visit(ctx->expr0()), "PLUS");
}

std::any ASTBuilder::visitSUB(ChipsParser::SUBContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::SubBuilder>(
        visit(ctx->expr1()), visit(ctx->expr0()), "SUB");
}

std::any ASTBuilder::visitNegate(ChipsParser::NegateContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_unary<ast_builder_detail::NegateBuilder>(
        visit(ctx->expr1()), "Negate");
}

std::any ASTBuilder::visitMULT(ChipsParser::MULTContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::MultBuilder>(
        visit(ctx->expr2()), visit(ctx->expr1()), "MULT");
}

std::any ASTBuilder::visitDIV(ChipsParser::DIVContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::DivBuilder>(
        visit(ctx->expr2()), visit(ctx->expr1()), "DIV");
}

std::any ASTBuilder::visitMOD(ChipsParser::MODContext *ctx)
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

std::any ASTBuilder::visitNOT(ChipsParser::NOTContext *ctx)
{
    std::cout << "visit not" << std::endl;
    return ast_builder_detail::dispatch_boolean_unary<ast_builder_detail::NOTBuilder>(
        visit(ctx->expr2()), "NOT");
}

// atom
std::any ASTBuilder::visitIntLiteral(ChipsParser::IntLiteralContext *ctx)
{
    std::cout << "visitIntLit()" << std::endl;
    switch (current_env)
    {
    case expression_env::PRIMITIVE:
        return std::make_shared<direct<dataflow_type::INT, expression_env::PRIMITIVE>>(std::stoll(ctx->INT()->getText()));
    case expression_env::COLLECTIVE:
        return std::make_shared<direct<dataflow_type::INT, expression_env::COLLECTIVE>>(std::stoll(ctx->INT()->getText()));
    case expression_env::SYSTEM:
        return std::make_shared<direct<dataflow_type::INT, expression_env::SYSTEM>>(std::stoll(ctx->INT()->getText()));
    default:
        throw std::runtime_error("Unknown expression environment in visitIntLiteral");
    }
}

std::any ASTBuilder::visitFloatLiteral(ChipsParser::FloatLiteralContext *ctx)
{
    std::cout << "visitFloatLit()" << std::endl;
    switch (current_env)
    {
    case expression_env::PRIMITIVE:
        return std::make_shared<direct<dataflow_type::FLOAT, expression_env::PRIMITIVE>>(std::stod(ctx->FLOAT()->getText()));
    case expression_env::COLLECTIVE:
        return std::make_shared<direct<dataflow_type::FLOAT, expression_env::COLLECTIVE>>(std::stod(ctx->FLOAT()->getText()));
    case expression_env::SYSTEM:
        return std::make_shared<direct<dataflow_type::FLOAT, expression_env::SYSTEM>>(std::stod(ctx->FLOAT()->getText()));
    default:
        throw std::runtime_error("Unknown expression environment in visitFloatLiteral");
    }
}

std::any ASTBuilder::visitBoolLiteral(ChipsParser::BoolLiteralContext *ctx)
{
    std::cout << "visitBoolLit()" << std::endl;
    std::string text = ctx->BOOL()->getText();
    bool value = (text == "true");
    switch (current_env)
    {
    case expression_env::PRIMITIVE:
        return std::make_shared<direct<dataflow_type::BOOL, expression_env::PRIMITIVE>>(value);
    case expression_env::COLLECTIVE:
        return std::make_shared<direct<dataflow_type::BOOL, expression_env::COLLECTIVE>>(value);
    case expression_env::SYSTEM:
        return std::make_shared<direct<dataflow_type::BOOL, expression_env::SYSTEM>>(value);
    default:
        throw std::runtime_error("Unknown expression environment in visitBoolLiteral");
    }
}

std::any ASTBuilder::visitParens(ChipsParser::ParensContext *ctx)
{
    return visit(ctx->expr());
}

std::any ASTBuilder::visitCastAs(ChipsParser::CastAsContext *ctx)
{
    // std::cout << "visitCastAs()" << std::endl;
    return visit(ctx->cast());
}

std::any ASTBuilder::handle_cast(dataflow_type target, std::any operand_any)
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

std::any ASTBuilder::visitCast(ChipsParser::CastContext *ctx)
{
    // std::cout << "visitCast()" << std::endl;

    // Type
    dataflow_type target = std::any_cast<dataflow_type>(visit(ctx->df_type()));

    // Operande
    std::any operand_any = visit(ctx->expr());

    return handle_cast(target, operand_any);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

// Type primitif
std::any ASTBuilder::visitIntType(ChipsParser::IntTypeContext * /*ctx*/)
{
    return dataflow_type::INT;
}

std::any ASTBuilder::visitFloatType(ChipsParser::FloatTypeContext * /*ctx*/)
{
    return dataflow_type::FLOAT;
}

std::any ASTBuilder::visitBoolType(ChipsParser::BoolTypeContext * /*ctx*/)
{
    return dataflow_type::BOOL;
}

template <dataflow_type dft, expression_env expenv>
primitive_iterable_variant<expenv> ASTBuilder::make_primitive_iterable_variant_from_node(
    const std::shared_ptr<rvalue<dft, expenv>> &node)
{

    auto ptr = node.get();

    if (auto p = dynamic_cast<function<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<function<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<function<dataflow_type::BOOL, expenv> *>(ptr))
        return p;
    rvalue_variant<expenv> rval = make_variant_from_node(node);
    return &rval;

    throw std::runtime_error("Unsopported type in make_primitive_iterable_variant_from_node");
}

template <expression_env expenv>
int_rvalue_expression_variant<expenv> ASTBuilder::make_int_rvalue_variant_from_node(
    const std::shared_ptr<rvalue<dataflow_type::INT, expenv>> &node)
{
    auto ptr = node.get();

    if (auto p = dynamic_cast<function<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<direct<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<plus<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<minus<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<mult<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<chips::div<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<mod<expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<cast_as<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<uminus_operator<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<variable_expression<dataflow_type::INT, expenv> *>(ptr))
        return p;

    throw std::runtime_error("Unsupported type in make_int_rvalue_variant_from_node");
}

template <expression_env expenv>
bool_rvalue_expression_variant<expenv> ASTBuilder::make_bool_rvalue_variant_from_node(
    const std::shared_ptr<rvalue<dataflow_type::BOOL, expenv>> &node)
{
    auto ptr = node.get();

    if (auto p = dynamic_cast<gt<expenv, dataflow_type::INT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<gt<expenv, dataflow_type::FLOAT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<lt<expenv, dataflow_type::INT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<lt<expenv, dataflow_type::FLOAT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<geq<expenv, dataflow_type::INT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<geq<expenv, dataflow_type::FLOAT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<leq<expenv, dataflow_type::INT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<leq<expenv, dataflow_type::FLOAT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<eq<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<eq<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<eq<dataflow_type::BOOL, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<neq<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<neq<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<neq<dataflow_type::BOOL, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<and_operator<expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<or_operator<expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<not_operator<expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<direct<dataflow_type::BOOL, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<variable_expression<dataflow_type::BOOL, expenv> *>(ptr))
        return p;

    throw std::runtime_error("Unsupported type in make_bool_rvalue_variant_from_node");
}

template <dataflow_type dft, expression_env expenv>
rvalue_variant<expenv> ASTBuilder::make_variant_from_node(
    const std::shared_ptr<rvalue<dft, expenv>> &node)
{
    auto ptr = node.get();

    if (auto p = dynamic_cast<function<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<function<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<function<dataflow_type::BOOL, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<direct<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<direct<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<direct<dataflow_type::BOOL, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<plus<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<plus<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<minus<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<minus<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<mult<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<mult<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<chips::div<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<chips::div<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<mod<expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<cast_as<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<cast_as<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<uminus_operator<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<uminus_operator<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<variable_expression<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<variable_expression<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<variable_expression<dataflow_type::BOOL, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<gt<expenv, dataflow_type::INT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<gt<expenv, dataflow_type::FLOAT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<lt<expenv, dataflow_type::INT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<lt<expenv, dataflow_type::FLOAT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<geq<expenv, dataflow_type::INT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<geq<expenv, dataflow_type::FLOAT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<leq<expenv, dataflow_type::INT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<leq<expenv, dataflow_type::FLOAT> *>(ptr))
        return p;
    if (auto p = dynamic_cast<eq<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<eq<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<eq<dataflow_type::BOOL, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<neq<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<neq<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<neq<dataflow_type::BOOL, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<and_operator<expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<or_operator<expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<not_operator<expenv> *>(ptr))
        return p;

    throw std::runtime_error("Unsupported type in make_variant_from_node");
}

std::any ASTBuilder::visitSuffixes(ChipsParser::SuffixesContext *ctx)
{
    switch (current_env)
    {
    case expression_env::PRIMITIVE:
        return extract_dimensions<expression_env::PRIMITIVE>(ctx);
    case expression_env::COLLECTIVE:
        return extract_dimensions<expression_env::COLLECTIVE>(ctx);
    case expression_env::SYSTEM:
        return extract_dimensions<expression_env::SYSTEM>(ctx);
    }
    throw std::runtime_error("VITAL, FAUT PAS OUBLIER LE CASE DEFAULT");
}

std::any ASTBuilder::visitStatementDeclaration(ChipsParser::StatementDeclarationContext *ctx)
{
    std::cout << "visit StatementDeclaration" << std::endl;

    dataflow_type type_any = std::any_cast<dataflow_type>(visit(ctx->df_type()));
    std::string var_name = ctx->IDENTIFIER()->getText();
    std::any assign;
    if (ctx->expr())
    {
        assign = visit(ctx->expr());
    }

#define RESWITCH(EXPENV)                                                                                                                                                                \
    std::vector<int_rvalue_expression_variant<EXPENV>> suffs = std::any_cast<std::vector<int_rvalue_expression_variant<EXPENV>>>(visit(ctx->suffixes()));                               \
    switch (type_any)                                                                                                                                                                   \
    {                                                                                                                                                                                   \
    case dataflow_type::INT:                                                                                                                                                            \
        return handle_statement_declaration<EXPENV, dataflow_type::INT>(std::any_cast<std::vector<int_rvalue_expression_variant<EXPENV>>>(visit(ctx->suffixes())), var_name, assign);   \
    case dataflow_type::FLOAT:                                                                                                                                                          \
        return handle_statement_declaration<EXPENV, dataflow_type::FLOAT>(std::any_cast<std::vector<int_rvalue_expression_variant<EXPENV>>>(visit(ctx->suffixes())), var_name, assign); \
    case dataflow_type::BOOL:                                                                                                                                                           \
        return handle_statement_declaration<EXPENV, dataflow_type::BOOL>(std::any_cast<std::vector<int_rvalue_expression_variant<EXPENV>>>(visit(ctx->suffixes())), var_name, assign);  \
    default:                                                                                                                                                                            \
        throw std::runtime_error("unknown type for variable declaration");                                                                                                              \
    }

    if (current_env == expression_env::PRIMITIVE)
    {
        RESWITCH(expression_env::PRIMITIVE)
    }
    else if (current_env == expression_env::SYSTEM)
    {
        RESWITCH(expression_env::SYSTEM)
    }
    else if (current_env == expression_env::SYSTEM)
    {
        RESWITCH(expression_env::COLLECTIVE)
    }
#undef RESWITCH
    throw std::runtime_error("Ooops, looks like the environment for this statement is not handled...");
}

// pass to children
std::any ASTBuilder::visitPassExpr0(ChipsParser::PassExpr0Context *ctx)
{
    return visit(ctx->expr0());
}

std::any ASTBuilder::visitPassExpr1(ChipsParser::PassExpr1Context *ctx)
{
    return visit(ctx->expr1());
}

std::any ASTBuilder::visitPassExpr2(ChipsParser::PassExpr2Context *ctx)
{
    return visit(ctx->expr2());
}
