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

        std::cout << "prezamble size: " << prgm.get_preamble().get_definitions().size() << std::endl;

#define APPEND_CASTED_DEF(POTENTIAL, EXPENV)                                                          \
    if (POTENTIAL *stuff = dynamic_cast<POTENTIAL *>(pc); stuff != nullptr)                           \
    {                                                                                                 \
        current_env = EXPENV;                                                                         \
        std::any def = visit(stuff);                                                                  \
        if (auto **physical = std::any_cast<physical_definition *>(&def))                             \
        {                                                                                              \
            prgm.get_preamble().add_definition(*physical);                                             \
        }                                                                                              \
        else if (auto *physical = std::any_cast<physical_definition>(&def))                            \
        {                                                                                             \
            auto owned = std::make_shared<physical_definition>(*physical);                             \
            node_arena.push_back(owned);                                                               \
            prgm.get_preamble().add_definition(owned.get());                                           \
        }                                                                                             \
        else if (auto **logical = std::any_cast<logical_definition *>(&def))                           \
        {                                                                                              \
            prgm.get_preamble().add_definition(*logical);                                              \
        }                                                                                              \
        else if (auto *logical = std::any_cast<logical_definition>(&def))                             \
        {                                                                                             \
            auto owned = std::make_shared<logical_definition>(*logical);                               \
            node_arena.push_back(owned);                                                               \
            prgm.get_preamble().add_definition(owned.get());                                           \
        } else if (auto **object = std::any_cast<object_definition *>(&def)) {                        \
            prgm.get_preamble().add_definition(*object);                                               \
        } else if (auto *object = std::any_cast<object_definition>(&def)) {                           \
            auto owned = std::make_shared<object_definition>(*object);                                 \
            node_arena.push_back(owned);                                                               \
            prgm.get_preamble().add_definition(owned.get());                                           \
        } else if (auto **collective = std::any_cast<collective_function_definition *>(&def)) {       \
            prgm.get_preamble().add_definition(*collective);                                           \
        } else if (auto *collective = std::any_cast<collective_function_definition>(&def)) {          \
            auto owned = std::make_shared<collective_function_definition>(*collective);                \
            node_arena.push_back(owned);                                                               \
            prgm.get_preamble().add_definition(owned.get());                                           \
        }\
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

    std::cout << "nb preamble in total: " << prgm.get_preamble().get_definitions().size() << std::endl;

    if(ctx->system() == nullptr) return prgm;

    std::cout << "nb statements in system section root level: "
              << ctx->system()->s_statement().size() << std::endl;

    current_env = expression_env::SYSTEM;
    for (ChipsParser::S_statementContext *ssc : ctx->system()->s_statement())
    {

#define SSTATEMENT_CAST(POTENTIAL, ERRMSG)                                                 \
    if (POTENTIAL *stuff = dynamic_cast<POTENTIAL *>(ssc); stuff != nullptr)               \
    {                                                                                      \
        std::any res = visit(stuff);                                                       \
        if(auto* block = keep_any_object_alive<block_declaration<block_type::PHYSICAL>>(res)){\
            prgm.get_system().add_statement(block); \
        }else if(auto* block = keep_any_object_alive<block_declaration<block_type::LOGICAL>>(res)){\
            prgm.get_system().add_statement(block);\
        }else if(auto* block = keep_any_object_alive<block_declaration<block_type::OBJECT>>(res)){\
            prgm.get_system().add_statement(block);\
        }else if(auto* linking = keep_any_object_alive<linking_statement>(res)){\
            prgm.get_system().add_statement(linking);\
        }else if(auto* sloop = keep_any_object_alive<foreach_statement<statement_env::SYSTEM, dataflow_type::INT>>(res)){\
            prgm.get_system().add_statement(sloop);\
        }else if(auto* sloop = keep_any_object_alive<foreach_statement<statement_env::SYSTEM, dataflow_type::FLOAT>>(res)){\
            prgm.get_system().add_statement(sloop);\
        }else if(auto* sloop = keep_any_object_alive<foreach_statement<statement_env::SYSTEM, dataflow_type::BOOL>>(res)){\
            prgm.get_system().add_statement(sloop);\
        }else if(auto* feeding = keep_any_object_alive<feeding_statement<dataflow_kind::LOGICAL, dataflow_type::INT>>(res)){\
            prgm.get_system().add_statement(feeding);\
        }else if(auto* feeding = keep_any_object_alive<feeding_statement<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>(res)){\
            prgm.get_system().add_statement(feeding);\
        }else if(auto* feeding = keep_any_object_alive<feeding_statement<dataflow_kind::LOGICAL, dataflow_type::BOOL>>(res)){\
            prgm.get_system().add_statement(feeding);\
        }else if(auto* feeding = keep_any_object_alive<feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::INT>>(res)){\
            prgm.get_system().add_statement(feeding);\
        }else if(auto* feeding = keep_any_object_alive<feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>(res)){\
            prgm.get_system().add_statement(feeding);\
        }else if(auto* feeding = keep_any_object_alive<feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>(res)){\
            prgm.get_system().add_statement(feeding);\
        }else{\
            throw std::runtime_error(ERRMSG);\
        }\
        continue;\
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
            std::cout << "travel regular stt ctx" << std::endl;
            travel_recurrent_statement<statement_env::SYSTEM>(
                stt->statement(),
                static_cast<statement_fillable<statement_env::SYSTEM> *>(&prgm.m_system));
            continue;
        }

        throw std::runtime_error("Unknown statement type in the system section root level!\n"
                                 "Rule index: "+ssc->getRuleIndex());
    }

    return prgm;
}

std::any ASTBuilder::visitObjectDefinition(ChipsParser::ObjectDefinitionContext *ctx)
{
    return visit(ctx->object_def());
}

std::any ASTBuilder::visitCollectiveOperationDefinition(ChipsParser::CollectiveOperationDefinitionContext *ctx)
{
    return visit(ctx->collective_op_def());
}

std::any ASTBuilder::visitImplementationDefinition(ChipsParser::ImplementationDefinitionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method ImplementationDefinitionContext");
}

std::any ASTBuilder::visitObject_def(ChipsParser::Object_defContext *ctx)
{
    std::string identifier = ctx->IDENTIFIER()->getText();

    std::cout << "visit object " << identifier << std::endl;
    fname_current = identifier;

    SymbolTable::getInstance().enterScope();

    with_section with = std::any_cast<with_section>(visit(ctx->with_section()));

    auto object = std::make_shared<object_definition>(identifier, with);
    node_arena.push_back(object);

    SymbolTable::getInstance().exitScope();
    if(SymbolTable::getInstance().lookupNodeDefinition(identifier).has_value()){
        throw std::runtime_error("'"+identifier+"' was already defined before");
    }
    if(!SymbolTable::getInstance().declareObject(identifier, *object)){
        throw std::runtime_error("'"+identifier+"' was already defined before");
    }

    return object.get();
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
    std::string fname = lfd->IDENTIFIER()->getText();
    std::cout << "visit logical definition " << fname << std::endl;
    fname_current = fname;

    // we enter in a new scope
    SymbolTable::getInstance().enterScope();

    std::vector<ChipsParser::Df_parameter_declContext *> old_ast_params = lfd->df_parameter_decl();
    std::vector<function_parameter_variant> params;
    for (ChipsParser::Df_parameter_declContext *stuff : old_ast_params)
    {
        std::cout << "visit function parameter logical" << std::endl;

        dataflow_type dft = std::any_cast<dataflow_type>(visit(stuff->df_type()));
        std::string identifier = stuff->IDENTIFIER()->getText();
        std::optional<std::any> expr;
        if(stuff->expr()) expr = visit(stuff->expr());
        auto param_dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(visit(stuff->suffixes()));

#define TRY_ADD_PARAM(DFK, DFT)                                                                  \
    if (dft == DFT)                                                                              \
    {                                                                                            \
        dataflow_declaration<DFT, statement_env::DEFINITION> declaration(identifier);            \
        auto declared_var = declaration.get_variable();                                           \
        declared_var.set_declaration(&declaration);                                               \
        declared_var.set_dimensions(param_dims);                                                  \
        declaration.set_variable(declared_var);                                                   \
        std::shared_ptr<function_parameter<DFK,DFT>> new_ast_param;\
        if(expr.has_value()){\
            auto exp = ast_builder_detail::try_extract<DFT,expression_env::PRIMITIVE>(expr.value());\
            if(!exp){\
                throw std::runtime_error("Invalid default value type for parameter '" + identifier + "'");\
            }\
            node_arena.push_back(std::static_pointer_cast<ast_node>(exp));\
            new_ast_param = std::make_shared<function_parameter<DFK, DFT>>(identifier, declaration, make_variant_from_node(exp));\
        }else{\
            new_ast_param = std::make_shared<function_parameter<DFK, DFT>>(identifier, declaration);\
        }\
        node_arena.push_back(new_ast_param);                                                     \
        if (!SymbolTable::getInstance().declareVariable(identifier, declaration.get_variable())) \
        {                                                                                        \
            throw std::runtime_error("The parameter '" + identifier + "' of the function '"+fname_current+"'was already declarated before here");      \
        }                                                                                        \
        SymbolTable::getInstance().declareFunctionParameter(fname_current, identifier, *new_ast_param);\
        params.push_back(new_ast_param.get());                                                   \
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
            node_arena.push_back(std::static_pointer_cast<ast_node>(expr));
            auto out = std::make_shared<function_output<dataflow_kind::LOGICAL, dataflow_type::INT>>(
                make_function_output<dataflow_kind::LOGICAL, dataflow_type::INT>(identifier, expr));
            node_arena.push_back(out);
            outputs.push_back(out.get());
            if(!SymbolTable::getInstance().declareFunctionOutput(fname_current, identifier, out)){
                throw std::runtime_error("'"+identifier+"' was already defined before");
            }
        }
        else if (auto expr = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(exp))
        {
            node_arena.push_back(std::static_pointer_cast<ast_node>(expr));
            auto out = std::make_shared<function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>(
                make_function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>(identifier, expr));
            node_arena.push_back(out);
            outputs.push_back(out.get());
            if(!SymbolTable::getInstance().declareFunctionOutput(fname_current, identifier, out)){
                throw std::runtime_error("'"+identifier+"' was already defined before");
            }
        }
        else if (auto expr = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(exp))
        {
            node_arena.push_back(std::static_pointer_cast<ast_node>(expr));
            auto out = std::make_shared<function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>>(
                make_function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>(identifier, expr));
            node_arena.push_back(out);
            outputs.push_back(out.get());
            if(!SymbolTable::getInstance().declareFunctionOutput(fname_current, identifier, out)){
                throw std::runtime_error("'"+identifier+"' was already defined before");
            }
        }
        else
        {
            throw std::runtime_error("Unknown type of expr in make_function_output " + ast_builder_detail::type_name(exp.type()));
        }
        continue;
    }

    auto logical = std::make_shared<chips::logical_definition>(fname, params, init, then, outputs);
    node_arena.push_back(logical);
    SymbolTable::getInstance().exitScope();
    if(SymbolTable::getInstance().lookupNodeDefinition(fname).has_value()){
        throw std::runtime_error("'"+fname+"' was already defined before");
    }
    SymbolTable::getInstance().declareFunctionLogical(fname, *logical);
    SymbolTable::getInstance().dump();
    std::cout << "END LOGICAL " << fname << std::endl;
    return logical.get();
}

std::any ASTBuilder::visitPhysicalDefinition(ChipsParser::PhysicalDefinitionContext *ctx)
{
    ChipsParser::P_function_defContext *pfd = ctx->p_function_def();
    std::string fname = pfd->IDENTIFIER()->getText();
    std::cout << "visit physical definition " << fname << std::endl;
    fname_current = fname;
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
            std::optional<std::any> expr;
            if(parameter->expr()){
                expr = visit(parameter->expr());
            }
            auto param_dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(visit(stuff->suffixes()));

#define TRY_ADD_SENSOR(DFK, DFT)                                                             \
    if (dft == DFT)                                                                          \
    {                                                                                        \
        dataflow_declaration<DFT, statement_env::DEFINITION> declaration(pname);             \
        auto declared_var = declaration.get_variable();                                       \
        declared_var.set_declaration(&declaration);                                           \
        declared_var.set_dimensions(param_dims);                                              \
        declaration.set_variable(declared_var);                                               \
        std::shared_ptr<function_parameter<DFK,DFT>> new_ast_param;                         \
        if(expr.has_value()){                                                                \
            auto exp = ast_builder_detail::try_extract<DFT,expression_env::PRIMITIVE>(expr.value());\
            if(!exp){                                                                        \
                throw std::runtime_error("Invalid default value type for sensor parameter '" + pname + "'");\
            }                                                                                \
            node_arena.push_back(std::static_pointer_cast<ast_node>(exp));                  \
            new_ast_param = std::make_shared<function_parameter<DFK, DFT>>(pname, declaration, make_variant_from_node(exp));\
        }else{                                                                               \
            new_ast_param = std::make_shared<function_parameter<DFK, DFT>>(pname, declaration);\
        }                                                                                    \
        node_arena.push_back(new_ast_param);                                                  \
        SymbolTable::getInstance().declareSensorVariable(pname, declaration.get_variable()); \
        SymbolTable::getInstance().declareFunctionParameter(fname_current, pname, *new_ast_param);\
        sensors.push_back(new_ast_param.get());                                              \
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
            std::optional<std::any> expr;
            if(parameter->expr()){
                std::cout << "DEFAULT VALUE" << std::endl;
                expr = visit(parameter->expr());
            } 
            auto param_dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(visit(stuff->suffixes()));
            

#define TRY_ADD_PARAM(DFK, DFT)                                                        \
    if (dft == DFT)                                                                    \
    {                                                                                  \
        dataflow_declaration<DFT, statement_env::DEFINITION> declaration(pname);       \
        auto declared_var = declaration.get_variable();                                 \
        declared_var.set_declaration(&declaration);                                     \
        declared_var.set_dimensions(param_dims);                                        \
        declaration.set_variable(declared_var);                                         \
        std::shared_ptr<function_parameter<DFK,DFT>> new_ast_param;\
        if(expr.has_value()){\
            auto exp = ast_builder_detail::try_extract<DFT,expression_env::PRIMITIVE>(expr.value());\
            if(!exp){\
                throw std::runtime_error("Invalid default value type for parameter '" + pname + "'");\
            }\
            node_arena.push_back(std::static_pointer_cast<ast_node>(exp));\
            new_ast_param = std::make_shared<function_parameter<DFK, DFT>>(pname, declaration, make_variant_from_node(exp));\
        }else{\
            new_ast_param = std::make_shared<function_parameter<DFK, DFT>>(pname, declaration);\
        }\
        node_arena.push_back(new_ast_param);                                           \
        params.push_back(new_ast_param.get());                                         \
        SymbolTable::getInstance().declareVariable(pname, declaration.get_variable()); \
        SymbolTable::getInstance().declareFunctionParameter(fname_current, pname, *new_ast_param);\
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
                node_arena.push_back(std::static_pointer_cast<ast_node>(expr));
                auto out = std::make_shared<function_output<dataflow_kind::LOGICAL, dataflow_type::INT>>(
                    make_function_output<dataflow_kind::LOGICAL, dataflow_type::INT>(identifier, expr));
                node_arena.push_back(out);
                outputs.push_back(out.get());
                if(!SymbolTable::getInstance().declareFunctionOutput(fname, identifier, out)){
                    throw std::runtime_error("'"+identifier+"' was already defined before");
                }
            }
            else if (auto expr = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(exp))
            {
                node_arena.push_back(std::static_pointer_cast<ast_node>(expr));
                auto out = std::make_shared<function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>(
                    make_function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>(identifier, expr));
                node_arena.push_back(out);
                outputs.push_back(out.get());
                if(!SymbolTable::getInstance().declareFunctionOutput(fname, identifier, out)){
                    throw std::runtime_error("'"+identifier+"' was already defined before");
                }
            }
            else if (auto expr = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(exp))
            {
                node_arena.push_back(std::static_pointer_cast<ast_node>(expr));
                auto out = std::make_shared<function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>>(
                    make_function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>(identifier, expr));
                node_arena.push_back(out);
                outputs.push_back(out.get());
                if(!SymbolTable::getInstance().declareFunctionOutput(fname, identifier, out)){
                    throw std::runtime_error("'"+identifier+"' was already defined before");
                }
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
            std::cout << "output actuator " << identifier << std::endl;
            std::any exp = visit(stuff->expr(0));

            if (auto expr = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::PRIMITIVE>(exp))
            {
                node_arena.push_back(std::static_pointer_cast<ast_node>(expr));
                auto out = std::make_shared<function_output<dataflow_kind::PHYSICAL, dataflow_type::INT>>(
                    make_function_output<dataflow_kind::PHYSICAL, dataflow_type::INT>(identifier, expr));
                node_arena.push_back(out);
                actuators.push_back(out.get());
                if(!SymbolTable::getInstance().declareFunctionOutput(fname, identifier, out)){
                    throw std::runtime_error("'"+identifier+"' was already defined before");
                }
            }
            else if (auto expr = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::PRIMITIVE>(exp))
            {
                node_arena.push_back(std::static_pointer_cast<ast_node>(expr));
                auto out = std::make_shared<function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>(
                    make_function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>(identifier, expr));
                node_arena.push_back(out);
                actuators.push_back(out.get());
                if(!SymbolTable::getInstance().declareFunctionOutput(fname, identifier, out)){
                    throw std::runtime_error("'"+identifier+"' was already defined before");
                }
            }
            else if (auto expr = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::PRIMITIVE>(exp))
            {
                node_arena.push_back(std::static_pointer_cast<ast_node>(expr));
                auto out = std::make_shared<function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>(
                    make_function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL>(identifier, expr));
                node_arena.push_back(out);
                actuators.push_back(out.get());
                if(!SymbolTable::getInstance().declareFunctionOutput(fname, identifier, out)){
                    throw std::runtime_error("'"+identifier+"' was already defined before");
                }
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
    auto physical = std::make_shared<chips::physical_definition>(fname, params, init, then, outputs, with, sensors, actuators);
    node_arena.push_back(physical);
    SymbolTable::getInstance().exitScope();
    if(SymbolTable::getInstance().lookupFunctionLogical(fname).has_value()){
        throw std::runtime_error("'"+fname+"' was already defined before");
    }
    if(!SymbolTable::getInstance().declareFunctionPhysical(fname, *physical)){
        throw std::runtime_error("'"+fname+"' was already defined before");
    }
    SymbolTable::getInstance().dump();
    std::cout << "END PHYSICAL " << fname << std::endl;
    return physical.get();
}

std::any ASTBuilder::visitCollective_op_def(ChipsParser::Collective_op_defContext *ctx)
{
    std::cout << "visit Collective op definition" << std::endl;

    SymbolTable::getInstance().enterScope();

    ChipsParser::C_signatureContext* sign = ctx->c_signature();

    std::string keyword = std::any_cast<std::string>(visit(sign->c_keywords()));
    
    collective_function_type type = (keyword == "collect") ? collective_function_type::COLLECT
                                                           : collective_function_type::SPREAD; 

    std::string fname = sign->IDENTIFIER(0)->getText();
    std::string among = sign->IDENTIFIER(1)->getText();

    fname_current = fname;

    std::optional<std::any> support = SymbolTable::getInstance().lookupNodeDefinition(among);

    if(!support.has_value()){
        throw std::runtime_error("'"+among+"' was never defined before");
    }

    node_definition* node_support = nullptr;
    std::shared_ptr<ast_node> owned_support;

    if(auto* node = std::any_cast<physical_definition>(&support.value())){
        owned_support = std::make_shared<physical_definition>(*node);
    }else if(auto* node = std::any_cast<object_definition>(&support.value())){
        owned_support = std::make_shared<object_definition>(*node);
    }

    if(!owned_support){
        throw std::runtime_error("Collective function support '" + among + "' must be a physical or object definition");
    }

    node_arena.push_back(owned_support);
    node_support = dynamic_cast<node_definition*>(owned_support.get());

    if(!node_support){
        throw std::runtime_error("Failed to resolve a stable support node for collective function '" + fname + "'");
    }

    std::cout << "AVANT DECL CONTEXT SUPPORT" << std::endl;

    // Ajouter les contextuel de la fonction support à la table des symboles
    for(auto stt : node_support->get_with_section().get_statements()){

        if(auto n = std::get_if<node_element_declaration<node_element::CONTEXTUAL_INT>*>(&stt)){
            auto contex = *n;
            // std::cout << "name " << contex->get_name() << std::endl;
            SymbolTable::getInstance().declareContextualVariable(contex->get_name(), contex->get_variable());
            std::cout << "ctx int " << ast_builder_detail::type_name(std::any{n}.type()) << std::endl;
        }else if(auto n = std::get_if<node_element_declaration<node_element::CONTEXTUAL_FLOAT>*>(&stt)){
            auto contex = *n;
            // std::cout << contex->get_name() << std::endl;
            SymbolTable::getInstance().declareContextualVariable(contex->get_name(), contex->get_variable());
            std::cout << "ctx float " << ast_builder_detail::type_name(std::any{n}.type()) << std::endl;
        }else if(auto n = std::get_if<node_element_declaration<node_element::CONTEXTUAL_BOOL>*>(&stt)){
            auto contex = *n;
            // std::cout << contex->get_name() << std::endl;
            SymbolTable::getInstance().declareContextualVariable(contex->get_name(), contex->get_variable());
            std::cout << "ctx bool " << ast_builder_detail::type_name(std::any{n}.type()) << std::endl;
        }else if(auto n = std::get_if<node_element_declaration<node_element::CHANNEL>*>(&stt)){
            auto contex = *n;
            SymbolTable::getInstance().declareChannel(contex->get_name(), contex);
        }
        // throw std::runtime_error("not a contextual variable in with section of "+among);
    }

    
    std::cout << "APRES DECL CONTEXT SUPPORT" << std::endl;

    std::vector<ChipsParser::Cdf_defaulted_declContext*> all_params = sign->cdf_defaulted_decl();
    std::vector<collective_parameter_variant> params;

    for(ChipsParser::Cdf_defaulted_declContext* param : all_params){

        std::string pname = param->IDENTIFIER()->getText();
        dataflow_type dft = std::any_cast<dataflow_type>(visit(param->df_type()));
        std::any c_expr = visit(param->c_expr());
        auto param_dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(visit(param->suffixes()));

#define TRY_ADD_COLLECTIVE_PARAM(DFT) \
        if(dft == DFT){ \
            auto expr = ast_builder_detail::try_extract<DFT,expression_env::COLLECTIVE>(c_expr);\
            if(!expr){ \
                throw std::runtime_error("Invalid default value type for collective parameter '" + pname + "'"); \
            } \
            dataflow_declaration<DFT, statement_env::COLLECTIVE> declaration(pname); \
            auto declared_var = declaration.get_variable(); \
            declared_var.set_declaration(&declaration); \
            declared_var.set_dimensions(param_dims); \
            declaration.set_variable(declared_var); \
            node_arena.push_back(std::static_pointer_cast<ast_node>(expr)); \
            auto new_ast_param = std::make_shared<collective_parameter<DFT>>(pname, declaration, expr.get()); \
            node_arena.push_back(new_ast_param); \
            params.push_back(new_ast_param.get()); \
            if(!SymbolTable::getInstance().declareVariable(pname, declaration.get_variable())){ \
                throw std::runtime_error("'"+pname+"' was already declarated before"); \
            } \
            continue; \
        } \

        TRY_ADD_COLLECTIVE_PARAM(dataflow_type::INT)
        TRY_ADD_COLLECTIVE_PARAM(dataflow_type::FLOAT)
        TRY_ADD_COLLECTIVE_PARAM(dataflow_type::BOOL)
#undef TRY_ADD_COLLECTIVE_PARAM

    }

    SymbolTable::getInstance().dump();

    accumulator_definition accumulator(params);

    collectiveops_section stts;

    for(ChipsParser::C_statementContext* stt : ctx->c_statement()){
        std::any followup = visit(stt);

        std::cout << "TYPE STT COLLECTIVE: " << ast_builder_detail::type_name(std::any{stt}.type()) << std::endl;

        try{
            if(ChipsParser::CollectiveVariableDeclarationContext* stuff = dynamic_cast<ChipsParser::CollectiveVariableDeclarationContext*>(stt); (stuff != nullptr) && (stuff->cdf_full_declaration()->c_expr() != nullptr)){
                std::cout << "HEREEEE" << std::endl;
                if(dynamic_cast<ChipsParser::IntTypeContext*>(stuff->cdf_full_declaration()->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::INT, statement_env::COLLECTIVE>,
                        dataflow_assignment<dataflow_type::INT, statement_env::COLLECTIVE>>;

                    chiant followup_pair = std::any_cast<chiant>(followup);
                    stts.add_statement(std::get<collective_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::COLLECTIVE>(followup_pair.first)));
                    stts.add_statement(std::get<collective_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::COLLECTIVE>(followup_pair.second)));
                    
                }else if(dynamic_cast<ChipsParser::FloatTypeContext*>(stuff->cdf_full_declaration()->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::FLOAT, statement_env::COLLECTIVE>,
                        dataflow_assignment<dataflow_type::FLOAT, statement_env::COLLECTIVE>>;

                    chiant followup_pair = std::any_cast<chiant>(followup);
                    stts.add_statement(std::get<collective_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::COLLECTIVE>(followup_pair.first)));
                    stts.add_statement(std::get<collective_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::COLLECTIVE>(followup_pair.second)));
                }else if(dynamic_cast<ChipsParser::BoolTypeContext*>(stuff->cdf_full_declaration()->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::BOOL, statement_env::COLLECTIVE>,
                        dataflow_assignment<dataflow_type::BOOL, statement_env::COLLECTIVE>>;

                    chiant followup_pair = std::any_cast<chiant>(followup);
                    stts.add_statement(std::get<collective_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::COLLECTIVE>(followup_pair.first)));
                    stts.add_statement(std::get<collective_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::COLLECTIVE>(followup_pair.second)));
                }else{
                    throw std::runtime_error("unrecognized variable type");
                }
                continue;
            }else{
                stts.add_statement(std::get<collective_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::COLLECTIVE>(followup)));
                continue;
            }
        }catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        throw std::runtime_error("Unknown kind of statement in collective section");
    }

    std::vector<rvalue_variant<expression_env::COLLECTIVE>> target_output_exprs;

    for(auto* expr : ctx->c_expr()){

        std::any exp = visit(expr);

        if(auto node = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(exp)){
            node_arena.push_back(std::static_pointer_cast<ast_node>(node));
            target_output_exprs.push_back(make_variant_from_node<dataflow_type::INT, expression_env::COLLECTIVE>(node));
        }else if(auto node = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::COLLECTIVE>(exp)){
            node_arena.push_back(std::static_pointer_cast<ast_node>(node));
            target_output_exprs.push_back(make_variant_from_node<dataflow_type::FLOAT, expression_env::COLLECTIVE>(node));
        }else if(auto node = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::COLLECTIVE>(exp)){
            node_arena.push_back(std::static_pointer_cast<ast_node>(node));
            target_output_exprs.push_back(make_variant_from_node<dataflow_type::BOOL, expression_env::COLLECTIVE>(node));
        }

    }

    std::vector<rvalue_variant<expression_env::COLLECTIVE>> default_output_exprs;
    std::vector<channeled_output> channeled_outputs;

    for(ChipsParser::C_outputContext* output : ctx->c_output()){
        if(ChipsParser::DefaultOutputContext* stuff = dynamic_cast<ChipsParser::DefaultOutputContext*>(output); stuff != nullptr){
            if(!default_output_exprs.empty()){
                throw std::runtime_error("Only one default output is valid");
            }
            for(auto* expr : stuff->c_expr()){

                std::any exp = visit(expr);

                if(auto node = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(exp)){
                    node_arena.push_back(std::static_pointer_cast<ast_node>(node));
                    default_output_exprs.push_back(make_variant_from_node<dataflow_type::INT, expression_env::COLLECTIVE>(node));
                }else if(auto node = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::COLLECTIVE>(exp)){
                    node_arena.push_back(std::static_pointer_cast<ast_node>(node));
                    default_output_exprs.push_back(make_variant_from_node<dataflow_type::FLOAT, expression_env::COLLECTIVE>(node));
                }else if(auto node = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::COLLECTIVE>(exp)){
                    node_arena.push_back(std::static_pointer_cast<ast_node>(node));
                    default_output_exprs.push_back(make_variant_from_node<dataflow_type::BOOL, expression_env::COLLECTIVE>(node));
                }

            }
        }else if(ChipsParser::ChanneledOutputContext* stuff = dynamic_cast<ChipsParser::ChanneledOutputContext*>(output); stuff != nullptr){
            SymbolTable::getInstance().dump();

            std::vector<rvalue_variant<expression_env::COLLECTIVE>> exprs_output;

            for(ChipsParser::C_exprContext* expr : stuff->c_expr()){
                std::any exp = visit(expr);

                if(auto node = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(exp)){
                    node_arena.push_back(std::static_pointer_cast<ast_node>(node));
                    exprs_output.push_back(make_variant_from_node<dataflow_type::INT, expression_env::COLLECTIVE>(node));
                }else if(auto node = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::COLLECTIVE>(exp)){
                    node_arena.push_back(std::static_pointer_cast<ast_node>(node));
                    exprs_output.push_back(make_variant_from_node<dataflow_type::FLOAT, expression_env::COLLECTIVE>(node));
                }else if(auto node = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::COLLECTIVE>(exp)){
                    node_arena.push_back(std::static_pointer_cast<ast_node>(node));
                    exprs_output.push_back(make_variant_from_node<dataflow_type::BOOL, expression_env::COLLECTIVE>(node));
                }
            }

            std::optional<std::any> channel = SymbolTable::getInstance().lookupChannel(stuff->IDENTIFIER()->getText());

            if(!channel.has_value()){
                throw std::runtime_error("'"+stuff->IDENTIFIER()->getText()+"' was never declarated before");
            }

            auto chan = std::any_cast<node_element_declaration<node_element::CHANNEL>*>(channel.value());

            channeled_output channel_output(chan, exprs_output);

            channeled_outputs.push_back(channel_output);

            if(!SymbolTable::getInstance().declareFunctionOutput(fname_current, stuff->IDENTIFIER()->getText(), channel_output)){
                throw std::runtime_error("'"+stuff->IDENTIFIER()->getText()+"' was already declarated before");
            }

            // throw std::runtime_error("IMPLEMENTER POUR LES CHANNELS");
        }
    }

    target_output target(target_output_exprs);
    default_output default_o(default_output_exprs);

    if(!SymbolTable::getInstance().declareFunctionOutput(fname_current, "@", target)){
        throw std::runtime_error("'@' was already declarated before");
    }

    if(!SymbolTable::getInstance().declareFunctionOutput(fname_current, "default", default_o)){
        throw std::runtime_error("'default' was already declarated before");
    }

    SymbolTable::getInstance().exitScope();

    auto collective = std::make_shared<collective_function_definition>(fname,
                                                                       type,
                                                                       accumulator,
                                                                       node_support,
                                                                       stts,
                                                                       target,
                                                                       default_o,
                                                                       channeled_outputs);
    node_arena.push_back(collective);


    if(keyword == "collect"){
        if(!SymbolTable::getInstance().declareFunctionCollect(fname, *collective)){
            throw std::runtime_error("'"+fname+"' was already defined before");
        }
    }else if(keyword == "spread"){
        if(!SymbolTable::getInstance().declareFunctionSpread(fname, *collective)){
            throw std::runtime_error("'"+fname+"' was already defined before");
        }
    }else{
        throw std::runtime_error("The keyword of this collective function doesn't exist");
    }

    return collective.get();
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
    std::cout << "visit Csignature" << std::endl;

    std::string keyword = std::any_cast<std::string>(visit(ctx->c_keywords()));
    
    std::string fname = ctx->IDENTIFIER(0)->getText();
    std::string among = ctx->IDENTIFIER(1)->getText();


    throw std::runtime_error("Unimplemented visit method C_signatureContext");
}

std::any ASTBuilder::visitC_keywords(ChipsParser::C_keywordsContext *ctx)
{
    if(ctx->SPREAD_KW()) return ctx->SPREAD_KW()->getText();
    return ctx->COLLECT_KW()->getText();
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
    auto decl = std::make_shared<node_element_declaration<node_element::CHANNEL>>(
        ctx->IDENTIFIER(0)->getText(), ctx->IDENTIFIER(1)->getText());
    node_arena.push_back(decl);
    SymbolTable::getInstance().declareFunctionOutput(fname_current, ctx->IDENTIFIER(1)->getText(), decl);
    return decl.get();
}

std::any ASTBuilder::handle_var(std::string identifier, std::any suffixes, bool is_contextual)
{
    std::cout << "visit var " << identifier << std::endl;
    std::optional<std::any> variable;

    SymbolTable::getInstance().dump();

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

    switch (current_env)
    {
        case expression_env::PRIMITIVE:
        {
            auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>>(suffixes);
            if (!is_contextual)
                return tryAllTypes<expression_env::PRIMITIVE>(identifier, variable.value(), dims);
            return tryAllTypesContextual<expression_env::PRIMITIVE>(identifier, variable.value(), dims);
        }
        case expression_env::COLLECTIVE:{
            auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(suffixes);
            if(!is_contextual)
                return tryAllTypes<expression_env::COLLECTIVE>(identifier, variable.value(), dims);
            return tryAllTypesContextual<expression_env::COLLECTIVE>(identifier, variable.value(), dims);
        }
        case expression_env::SYSTEM:{
            auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(suffixes);
            if(!is_contextual)
                return tryAllTypes<expression_env::SYSTEM>(identifier, variable.value(), dims);
            throw std::runtime_error("Impossible to use a variable of nowhere");
        }
    }
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
            return decl.get();
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
            return decl.get();
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
            return decl.get();
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
                std::cout << "LA TRY EXTRACT RECCURING" << std::endl;
                if (dynamic_cast<ChipsParser::IntTypeContext *>(stuff->df_type()))
                {
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                    init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                }
                else if (dynamic_cast<ChipsParser::FloatTypeContext *>(stuff->df_type()))
                {
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                    init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                }
                else if (dynamic_cast<ChipsParser::BoolTypeContext *>(stuff->df_type()))
                {
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                    init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                }
                else
                {
                    throw std::runtime_error("unrecognized variable type");
                }
                continue;
            }
            else
            {
                std::cout << "ICI TRY EXTRACT RECCURING" << std::endl;
                init.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup)));
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

        try{

            if (ChipsParser::StatementDeclarationContext *stuff = dynamic_cast<ChipsParser::StatementDeclarationContext *>(stt); (stuff != nullptr) && (stuff->expr() != nullptr)){
                if (dynamic_cast<ChipsParser::IntTypeContext *>(stuff->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    then.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                    then.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                }else if (dynamic_cast<ChipsParser::FloatTypeContext *>(stuff->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    then.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                    then.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                }else if (dynamic_cast<ChipsParser::BoolTypeContext *>(stuff->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    then.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                    then.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                }else{
                    throw std::runtime_error("unrecognized variable type");
                }
                continue;
            }else{
                std::cout << "THEN TRY EXTRACT " << ast_builder_detail::type_name(followup.type()) << std::endl;
                then.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup)));
                continue;
            }
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
    if constexpr(ENV == expression_env::PRIMITIVE){
        if (auto sptr = std::any_cast<std::shared_ptr<dataflow_primitive_variable<DT>>>(&var))
        {
            std::cout << "FIRST ANY CAST " << ast_builder_detail::type_name(std::any{sptr}.type()) << sptr->get()->get_name() << std::endl;
            if (*sptr)
                return std::make_shared<variable_expression<DT, ENV>>(sptr->get(), dims);
        }

        if (auto raw_ptr = std::any_cast<dataflow_primitive_variable<DT>>(&var))
        {
            std::cout << "SECOND ANY CAST" << std::endl;
            auto owned_var = std::make_shared<dataflow_primitive_variable<DT>>(*raw_ptr);
            node_arena.push_back(std::static_pointer_cast<ast_node>(owned_var));
            return std::make_shared<variable_expression<DT, ENV>>(owned_var.get(), dims);
        }
    }else if constexpr(ENV == expression_env::COLLECTIVE){
        if (auto sptr = std::any_cast<std::shared_ptr<dataflow_collective_variable<DT>>>(&var))
        {
            std::cout << "FIRST ANY CAST " << ast_builder_detail::type_name(std::any{sptr}.type()) << std::endl;
            if (*sptr)
                return std::make_shared<variable_expression<DT, ENV>>(sptr->get(), dims);
        }

        if (auto raw_ptr = std::any_cast<dataflow_collective_variable<DT>>(&var))
        {
            std::cout << "SECOND ANY CAST" << std::endl;
            auto owned_var = std::make_shared<dataflow_collective_variable<DT>>(*raw_ptr);
            node_arena.push_back(std::static_pointer_cast<ast_node>(owned_var));
            return std::make_shared<variable_expression<DT, ENV>>(owned_var.get(), dims);
        }
    }else if constexpr(ENV == expression_env::SYSTEM){
        std::cout << ast_builder_detail::type_name(var.type()) << std::endl;
        if(auto sptr = std::any_cast<std::shared_ptr<dataflow_system_variable<DT>>>(&var)){
            if(*sptr)
                return std::make_shared<variable_expression<DT, ENV>>(sptr->get(), dims);
        }

        if(auto raw_ptr = std::any_cast<dataflow_system_variable<DT>>(&var)){
            auto owned_var = std::make_shared<dataflow_system_variable<DT>>(*raw_ptr);
            node_arena.push_back(std::static_pointer_cast<ast_node>(owned_var));
            return std::make_shared<variable_expression<DT, ENV>>(owned_var.get(), dims);
        }
    }else{
        throw std::runtime_error("Unsupported environment: "+expenv_to_string(ENV));
    }

    

    return {};
}

template <dataflow_type DT, expression_env ENV, typename Dims>
std::any ASTBuilder::tryCastVarContextual(const std::any &var, const Dims &dims)
{
    if constexpr(ENV == expression_env::PRIMITIVE){
        if (auto sptr = std::any_cast<std::shared_ptr<contextual_variable<DT>>>(&var))
        {
            if (*sptr)
                return std::make_shared<variable_contextual_expression<DT, ENV>>(sptr->get(), dims);
        }

        if (auto raw_ptr = std::any_cast<contextual_variable<DT>>(&var))
        {
            auto owned_var = std::make_shared<contextual_variable<DT>>(*raw_ptr);
            node_arena.push_back(std::static_pointer_cast<ast_node>(owned_var));
            return std::make_shared<variable_contextual_expression<DT, ENV>>(owned_var.get(), dims);
        }
    }else if constexpr(ENV == expression_env::COLLECTIVE){
        std::cout << ast_builder_detail::type_name(var.type()) << std::endl;
        if(auto sptr = std::any_cast<std::shared_ptr<contextual_variable<DT>>>(&var)){
            if(*sptr)
                return std::make_shared<variable_contextual_expression<DT, ENV>>(
                    reinterpret_cast<variable<ENV>*>(sptr->get()), dims);
        }
        if(auto raw_ptr = std::any_cast<contextual_variable<DT>>(&var)){
            auto owned_var = std::make_shared<contextual_variable<DT>>(*raw_ptr);
            node_arena.push_back(std::static_pointer_cast<ast_node>(owned_var));
            return std::make_shared<variable_contextual_expression<DT,ENV>>(
                reinterpret_cast<variable<ENV>*>(owned_var.get()), dims);
        }
    }else{
        throw std::runtime_error("JA");
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
    return visit(ctx->c_stopless_expr());
}

std::any ASTBuilder::visitStop(ChipsParser::StopContext *ctx)
{
    return std::make_shared<stop>();
}

std::any ASTBuilder::visitCLT(ChipsParser::CLTContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::LTBuilder>(
        visit(ctx->c_stopless_expr0()), visit(ctx->c_stopless_expr()), "LT");
}

std::any ASTBuilder::visitCGT(ChipsParser::CGTContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::GTBuilder>(
        visit(ctx->c_stopless_expr0()), visit(ctx->c_stopless_expr()), "GT");
}

std::any ASTBuilder::visitCLEQ(ChipsParser::CLEQContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::LEQBuilder>(
        visit(ctx->c_stopless_expr0()), visit(ctx->c_stopless_expr()), "LEQ");
}

std::any ASTBuilder::visitCGEQ(ChipsParser::CGEQContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::GEQBuilder>(
        visit(ctx->c_stopless_expr0()), visit(ctx->c_stopless_expr()), "GEQ");
}

std::any ASTBuilder::visitCNEQ(ChipsParser::CNEQContext *ctx)
{
    std::cout << "visit !=" << std::endl;
    return ast_builder_detail::dispatch_binary<
                ast_builder_detail::NEQBuilder>(
                    visit(ctx->c_stopless_expr0()), visit(ctx->c_stopless_expr()), "NEQ");
}

std::any ASTBuilder::visitCEQ(ChipsParser::CEQContext *ctx)
{
    std::cout << "visit ==" << std::endl;
    return ast_builder_detail::dispatch_binary<
                ast_builder_detail::EQBuilder>(
                    visit(ctx->c_stopless_expr0()), visit(ctx->c_stopless_expr()), "EQ");
}

std::any ASTBuilder::visitCAND(ChipsParser::CANDContext *ctx)
{
    std::cout << "visit &&" << std::endl;
    return ast_builder_detail::dispatch_boolean_binary<ast_builder_detail::ANDBuilder>(
        visit(ctx->c_stopless_expr0()), visit(ctx->c_stopless_expr()), "AND");
}

std::any ASTBuilder::visitCOR(ChipsParser::CORContext *ctx)
{
    return ast_builder_detail::dispatch_boolean_binary<ast_builder_detail::ORBuilder>(
        visit(ctx->c_stopless_expr0()), visit(ctx->c_stopless_expr()), "OR");
}

std::any ASTBuilder::visitPassCExpr0(ChipsParser::PassCExpr0Context *ctx)
{
    return visit(ctx->c_stopless_expr0());
}

std::any ASTBuilder::visitPassCExpr01(ChipsParser::PassCExpr01Context* ctx){
    return visit(ctx->c_stopless_expr01());
}

std::any ASTBuilder::visitCPLUS(ChipsParser::CPLUSContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::PlusBuilder>(
        visit(ctx->c_stopless_expr01()), visit(ctx->c_stopless_expr0()), "PLUS");
}

std::any ASTBuilder::visitCSUB(ChipsParser::CSUBContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::SubBuilder>(
        visit(ctx->c_stopless_expr01()), visit(ctx->c_stopless_expr0()), "SUB");
}

std::any ASTBuilder::visitCNegate(ChipsParser::CNegateContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_unary<ast_builder_detail::NegateBuilder>(
        visit(ctx->c_stopless_expr1()), "Negate");
}

std::any ASTBuilder::visitPassCExpr1(ChipsParser::PassCExpr1Context *ctx)
{
    return visit(ctx->c_stopless_expr1());
}

std::any ASTBuilder::visitCMULT(ChipsParser::CMULTContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::MultBuilder>(
        visit(ctx->c_stopless_expr2()), visit(ctx->c_stopless_expr1()), "MULT");
}

std::any ASTBuilder::visitCDIV(ChipsParser::CDIVContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::DivBuilder>(
        visit(ctx->c_stopless_expr2()), visit(ctx->c_stopless_expr1()), "DIV");
}

std::any ASTBuilder::visitCMOD(ChipsParser::CMODContext *ctx)
{
    auto left_collect = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(visit(ctx->c_stopless_expr2()));
    auto right_collect = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(visit(ctx->c_stopless_expr1()));
    if (left_collect && right_collect)
    {
        return ast_builder_detail::ModBuilder<dataflow_type::INT, expression_env::COLLECTIVE>::build(left_collect, right_collect);
    }
    throw std::runtime_error("Error with modulo");
}

std::any ASTBuilder::visitCNOT(ChipsParser::CNOTContext *ctx)
{
    std::cout << "visit not" << std::endl;
    return ast_builder_detail::dispatch_boolean_unary<ast_builder_detail::NOTBuilder>(
        visit(ctx->c_stopless_expr2()), "NOT");
}

std::any ASTBuilder::visitPassCExpr2(ChipsParser::PassCExpr2Context *ctx)
{
    return visit(ctx->c_stopless_expr2());
}

std::any ASTBuilder::visitCVariableExpression(ChipsParser::CVariableExpressionContext *ctx)
{
    return handle_var(
        ctx->IDENTIFIER()->getText(),
        visit(ctx->c_suffixes()),
        false);
}

std::any ASTBuilder::visitCINT(ChipsParser::CINTContext *ctx)
{
    std::cout << "visit CINT" << std::endl;
    return std::make_shared<direct<dataflow_type::INT, expression_env::COLLECTIVE>>(std::stoll(ctx->INT()->getText()));
}

std::any ASTBuilder::visitCFLOAT(ChipsParser::CFLOATContext *ctx)
{
    std::cout << "visit CFLOAT" << std::endl;
    return std::make_shared<direct<dataflow_type::FLOAT, expression_env::COLLECTIVE>>(std::stoll(ctx->FLOAT()->getText()));
}

std::any ASTBuilder::visitCBOOL(ChipsParser::CBOOLContext *ctx)
{
    std::cout << "visit CBOOL" << std::endl;
    return std::make_shared<direct<dataflow_type::BOOL, expression_env::COLLECTIVE>>(std::stoll(ctx->BOOL()->getText()));
}

std::any ASTBuilder::visitINPUT(ChipsParser::INPUTContext *ctx)
{
    return std::make_shared<input>();
}

std::any ASTBuilder::visitCtxVariableExpression(ChipsParser::CtxVariableExpressionContext *ctx)
{

    std::string identifier = ctx->IDENTIFIER()->getText();

    std::cout << "contextual var collect " << identifier << std::endl;

    SymbolTable::getInstance().dump();

    std::optional<std::any> variable = SymbolTable::getInstance().lookupContextualVariable(identifier);

    if(!variable.has_value()){
        throw std::runtime_error("'"+identifier+"' was never declarated before");
    }

    auto dims = extract_dimensions_collective(ctx->c_suffixes());
    return tryAllTypesContextual<expression_env::COLLECTIVE>(identifier, variable.value(), dims);
}

std::any ASTBuilder::visitChanneledAccuExpression(ChipsParser::ChanneledAccuExpressionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method ChanneledAccuExpressionContext");
}

std::any ASTBuilder::visitFunctionCall(ChipsParser::FunctionCallContext *ctx)
{
    std::string identifier = ctx->IDENTIFIER()->getText();
    std::cout << "visit function call " << identifier << std::endl;
    
    return make_function<expression_env::COLLECTIVE>(identifier, ctx->c_expr());
}

std::any ASTBuilder::visitCParenthesis(ChipsParser::CParenthesisContext *ctx)
{
    return visit(ctx->c_stopless_expr());
}

std::any ASTBuilder::visitCCastAs(ChipsParser::CCastAsContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method CCastAsContext");
}

std::any ASTBuilder::visitC_cast(ChipsParser::C_castContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method C_castContext");
}

std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> ASTBuilder::extract_dimensions_collective(ChipsParser::C_suffixesContext *ctx){
    std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> dims;
    for (auto *expr : ctx->c_stopless_expr())
    {
        std::any val = visit(expr);
        auto node = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::COLLECTIVE>(val);
        if (!node)
        {
            throw std::runtime_error(
                "suffixes : l'expression d'indice doit être de type INT ");
        }
        node_arena.push_back(node);
        dims.push_back(make_int_rvalue_variant_from_node<expression_env::COLLECTIVE>(node));
    }
    return dims;
}

std::any ASTBuilder::visitC_suffixes(ChipsParser::C_suffixesContext *ctx)
{
    return extract_dimensions_collective(ctx);
}

std::any ASTBuilder::visitSSuffixableVariableExpression(ChipsParser::SSuffixableVariableExpressionContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method SSuffixableVariableExpressionContext");
}

std::any ASTBuilder::visitSSuffixableFunctionCallExpression(ChipsParser::SSuffixableFunctionCallExpressionContext *ctx)
{
    std::cout << "visit s_suffixable_expr function" << std::endl;

    return make_function<expression_env::SYSTEM>(ctx->IDENTIFIER()->getText(), ctx->expr());
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
            break;
        case dataflow_type::FLOAT:
            iterator = handle_statement_declaration<expression_env::PRIMITIVE, dataflow_type::FLOAT>(std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>(), identifier, std::any{});
            break;
        case dataflow_type::BOOL:
            iterator = handle_statement_declaration<expression_env::PRIMITIVE, dataflow_type::BOOL>(std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>>(), identifier, std::any{});
            break;
        default:
            throw std::runtime_error("couldn't find type for the iterator in loop statement");
        }
        break;
    case expression_env::COLLECTIVE:
        switch (type)
        {
        case dataflow_type::INT:
            iterator = handle_statement_declaration<expression_env::COLLECTIVE, dataflow_type::INT>(std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>(), identifier, std::any{});
            break;
        case dataflow_type::FLOAT:
            iterator = handle_statement_declaration<expression_env::COLLECTIVE, dataflow_type::FLOAT>(std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>(), identifier, std::any{});
            break;
        case dataflow_type::BOOL:
            iterator = handle_statement_declaration<expression_env::COLLECTIVE, dataflow_type::BOOL>(std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>(), identifier, std::any{});
            break;
        default:
            throw std::runtime_error("couldn't find type for the iterator in loop statement");
        }
        break;
    case expression_env::SYSTEM:
        switch (type)
        {
        case dataflow_type::INT:
            iterator = handle_statement_declaration<expression_env::SYSTEM, dataflow_type::INT>(std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>(), identifier, std::any{});
            break;
        case dataflow_type::FLOAT:
            iterator = handle_statement_declaration<expression_env::SYSTEM, dataflow_type::FLOAT>(std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>(), identifier, std::any{});
            break;
        case dataflow_type::BOOL:
            iterator = handle_statement_declaration<expression_env::SYSTEM, dataflow_type::BOOL>(std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>(), identifier, std::any{});
            break;
        default:
            throw std::runtime_error("couldn't find type for the iterator in loop statement");
        }
        break;
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
    std::cout << "visit loop statement" << std::endl;

    SymbolTable::getInstance().enterScope();
    SymbolTable::getInstance().dump();

    std::string identifier = ctx->IDENTIFIER()->getText();

    std::cout << "ENter new Scope foreach " << identifier << std::endl;

    // throw std::runtime_error("ICI");

    std::any suffixable_expr = visit(ctx->s_suffixable_expr());
    dataflow_type type = ast_builder_detail::get_dataflow_type<expression_env::SYSTEM>(suffixable_expr);

    

    switch(type){
        case dataflow_type::INT:{
            std::any iterator = handle_statement_declaration_foreach<dataflow_type::INT, expression_env::SYSTEM>(identifier);
            auto iterable = make_primitive_iterable_variant_from_node(
                ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(suffixable_expr));
            auto it = std::any_cast<dataflow_declaration<dataflow_type::INT, statement_env::SYSTEM>>(iterator);
            foreach_statement<statement_env::SYSTEM, dataflow_type::INT> foreach(it, iterable);
            std::any res = make_statement_foreach(foreach, ctx->s_statement());
            SymbolTable::getInstance().exitScope();
            std::cout << "Exit scope foreach" << std::endl;
            return res;
        }
        case dataflow_type::FLOAT:
            break;
        case dataflow_type::BOOL:
            break;
    }

    throw std::runtime_error("Faut faire le reste mais ya pas dans l'exemple encore");
}

std::any ASTBuilder::visitIf_else_statement(ChipsParser::If_else_statementContext *ctx)
{
    std::cout << "visit if else statement" << std::endl;

    if_else_statement<statement_env::DEFINITION> if_else;

    // TODO: regarder les scopes avec SymbolTable

    std::any if_stt = visit(ctx->if_statement());
    if_else.m_if_section  = std::any_cast<if_statement<statement_env::DEFINITION>>(if_stt).m_if_section;
    if_else.m_condition   = std::any_cast<if_statement<statement_env::DEFINITION>>(if_stt).m_condition;


    SymbolTable::getInstance().enterScope();
    SymbolTable::getInstance().dump();

    for (ChipsParser::StatementContext *stt : ctx->statement())
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
                    if_else.m_else_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                    if_else.m_else_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                }
                else if (dynamic_cast<ChipsParser::FloatTypeContext *>(stuff->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    if_else.m_else_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                    if_else.m_else_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                }
                else if (dynamic_cast<ChipsParser::BoolTypeContext *>(stuff->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    if_else.m_else_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                    if_else.m_else_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                }
                else{
                    throw std::runtime_error("unrecognized variable type");
                }
                continue;
            }else{
                if_else.m_else_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup)));
                continue;
            }            
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
    std::cout << "visit if else collective statement" << std::endl;

    if_else_statement<statement_env::COLLECTIVE> if_else;

    std::any if_stt = visit(ctx->c_if_statement());

    if_else.m_if_section = std::any_cast<if_statement<statement_env::COLLECTIVE>>(if_stt).m_if_section;
    if_else.m_condition = std::any_cast<if_statement<statement_env::COLLECTIVE>>(if_stt).m_condition;

    SymbolTable::getInstance().enterScope();
    SymbolTable::getInstance().dump();

    for(ChipsParser::C_statementContext* stt : ctx->c_statement()){
        std::any followup = visit(stt);

        try{
            if(ChipsParser::Cdf_full_declarationContext* stuff = dynamic_cast<ChipsParser::Cdf_full_declarationContext*>(stt); (stuff != nullptr) && (stuff->c_expr() != nullptr)){
                if(dynamic_cast<ChipsParser::IntTypeContext*>(stuff->df_type())){
                    throw std::runtime_error("ouais");
                }else if(dynamic_cast<ChipsParser::FloatTypeContext*>(stuff->df_type())){
                    throw std::runtime_error("ouais ouais");
                }else if(dynamic_cast<ChipsParser::BoolTypeContext*>(stuff->df_type())){
                    throw std::runtime_error("ouais ouais oauis");
                }else{
                    throw std::runtime_error("unrecognized variable type");
                }
                continue;
            }else{
                if_else.m_else_section.add_statement(std::get<collective_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::COLLECTIVE>(followup)));
                continue;
            }
        }catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        throw std::runtime_error("Unknown kind of statement in else collective section");
    }

    SymbolTable::getInstance().exitScope();

    return if_else;
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

        try{

            if (ChipsParser::StatementDeclarationContext *stuff = dynamic_cast<ChipsParser::StatementDeclarationContext *>(stt); (stuff != nullptr) && (stuff->expr() != nullptr)){
                if (dynamic_cast<ChipsParser::IntTypeContext *>(stuff->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    if_stt.m_if_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                    if_stt.m_if_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                }
                else if (dynamic_cast<ChipsParser::FloatTypeContext *>(stuff->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    if_stt.m_if_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                    if_stt.m_if_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                }else if (dynamic_cast<ChipsParser::BoolTypeContext *>(stuff->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>,
                        dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    if_stt.m_if_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.first)));
                    if_stt.m_if_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup_pair.second)));
                }else{
                    throw std::runtime_error("unrecognized variable type");
                }
                continue;
            }else{
                if_stt.m_if_section.add_statement(std::get<primitive_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::DEFINITION>(followup)));
                continue;
            }            
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
    std::cout << "visit if system statement" << std::endl;

    if_statement<statement_env::SYSTEM> if_stt;

    std::any val = visit(ctx->expr());
    auto node = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::SYSTEM>(val);
    if(!node){
        throw std::runtime_error(
            "condition : l'expression doit être de type BOOL "
            "(env SYSTEM)");
    }

    node_arena.push_back(node);
    if_stt.m_condition = make_bool_rvalue_variant_from_node(node);

    std::cout << "statements if system section" << std::endl;

    SymbolTable::getInstance().enterScope();
    SymbolTable::getInstance().dump();

    for(ChipsParser::S_statementContext* stt : ctx->s_statement()){

        std::any followup = visit(stt);

        try{
            if(ChipsParser::StatementDeclarationContext* stuff = dynamic_cast<ChipsParser::StatementDeclarationContext*>(stt); (stuff != nullptr) && stuff->expr() != nullptr){
                if(dynamic_cast<ChipsParser::IntTypeContext*>(stuff->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::INT, statement_env::SYSTEM>,
                        dataflow_assignment<dataflow_type::INT, statement_env::SYSTEM>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    if_stt.m_if_section.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup_pair.first)));
                    if_stt.m_if_section.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup_pair.second)));
                }else if(dynamic_cast<ChipsParser::FloatTypeContext*>(stuff->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::FLOAT, statement_env::SYSTEM>,
                        dataflow_assignment<dataflow_type::FLOAT, statement_env::SYSTEM>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    if_stt.m_if_section.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup_pair.first)));
                    if_stt.m_if_section.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup_pair.second)));
                }else if(dynamic_cast<ChipsParser::BoolTypeContext*>(stuff->df_type())){
                    using chiant = std::pair<
                        dataflow_declaration<dataflow_type::BOOL, statement_env::SYSTEM>,
                        dataflow_assignment<dataflow_type::BOOL, statement_env::SYSTEM>>;
                    chiant followup_pair = std::any_cast<chiant>(followup);
                    if_stt.m_if_section.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup_pair.first)));
                    if_stt.m_if_section.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup_pair.second)));
                }else{
                    throw std::runtime_error("Unrecognized variable type");
                }
                continue;
            }else{
                if_stt.m_if_section.add_statement(std::get<system_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::SYSTEM>(followup)));
                continue;
            }
        }catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        throw std::runtime_error("Unknown kind of statement in if system section");
    }

    SymbolTable::getInstance().exitScope();

    return if_stt;
}

std::any ASTBuilder::visitC_if_statement(ChipsParser::C_if_statementContext *ctx)
{
    std::cout << "visit if collective statement" << std::endl;
    if_statement<statement_env::COLLECTIVE> if_stt;

    std::any val = visit(ctx->c_expr());
    auto node = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::COLLECTIVE>(val);
    if(!node){
        throw std::runtime_error(
            "condition: l'expression doit être de type BOOL "
            "(env COLLECTIVE)");
    }
    node_arena.push_back(node);
    if_stt.m_condition = make_bool_rvalue_variant_from_node<expression_env::COLLECTIVE>(node);

    std::cout << "statements if collective section" << std::endl;

    SymbolTable::getInstance().enterScope();
    SymbolTable::getInstance().dump();

    for(ChipsParser::C_statementContext* stt: ctx->c_statement()){
        std::any followup = visit(stt);

        try{
            if(ChipsParser::Cdf_full_declarationContext* stuff = dynamic_cast<ChipsParser::Cdf_full_declarationContext*>(stt); (stuff != nullptr) && (stuff->c_expr() != nullptr)){
                if(dynamic_cast<ChipsParser::IntTypeContext*>(stuff->df_type())){
                    throw std::runtime_error("ouais");
                }else if(dynamic_cast<ChipsParser::FloatTypeContext*>(stuff->df_type())){
                    throw std::runtime_error("ouais ouais");
                }else if(dynamic_cast<ChipsParser::BoolTypeContext*>(stuff->df_type())){
                    throw std::runtime_error("ouais ouais oauis");
                }else{
                    throw std::runtime_error("unrecognized variable type");
                }
                continue;
            }else{
                if_stt.m_if_section.add_statement(std::get<collective_statement_variant>(ast_builder_detail::try_extract_recurring_statement<statement_env::COLLECTIVE>(followup)));
                continue;
            }
        }catch(const std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
        throw std::runtime_error("Unknown kind of statement in if collective section");
    }

    SymbolTable::getInstance().exitScope();
    return if_stt;
}

std::any ASTBuilder::visitStatementAssignment(ChipsParser::StatementAssignmentContext *ctx)
{
    std::cout << "visit StatementAssignment" << std::endl;
    std::any suffixes = visit(ctx->suffixes());
    std::string var_name = ctx->IDENTIFIER()->getText();
    std::cout << "assign type var: " << ast_builder_detail::type_name(std::any{ctx->expr()}.type()) << std::endl;
    std::any assign = visit(ctx->expr());

    switch(current_env){
        case expression_env::PRIMITIVE: return handle_statement_assignment<expression_env::PRIMITIVE, statement_env::DEFINITION>(var_name, suffixes, assign, false);
        case expression_env::COLLECTIVE: return handle_statement_assignment<expression_env::COLLECTIVE, statement_env::COLLECTIVE>(var_name, suffixes, assign, false);
        case expression_env::SYSTEM: return handle_statement_assignment<expression_env::SYSTEM, statement_env::SYSTEM>(var_name, suffixes, assign, false);
    }
    throw std::runtime_error("Unsupported environment: "+expenv_to_string(current_env));
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
    std::string identifier = ctx->IDENTIFIER(1)->getText();

    std::cout << "visit object declaration " << identifier << std::endl;

    std::string type = ctx->IDENTIFIER(0)->getText();
    std::any suffixes = visit(ctx->suffixes());

    auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(suffixes);

    if(SymbolTable::getInstance().lookupFunctionLogical(type).has_value()){
        return handle_statement_declaration<block_type::LOGICAL>(type, dims, identifier);
    }else if(auto node = SymbolTable::getInstance().lookupNodeDefinition(type); node.has_value()){
        if(auto* n = std::any_cast<physical_definition>(&(node.value()))){
            return handle_statement_declaration<block_type::PHYSICAL>(type, dims, identifier);
        }
        return handle_statement_declaration<block_type::OBJECT>(type, dims, identifier);
    }else{
        throw std::runtime_error("'"+type+"' was never defined before");
    }

    throw std::runtime_error("Unimplemented visit method ObjectDeclarationContext");
}

std::any ASTBuilder::visitFeedingStatement(ChipsParser::FeedingStatementContext *ctx)
{

    std::string identifier = ctx->block()->IDENTIFIER()->getText();
    std::string function_parameter_id = ctx->IDENTIFIER()->getText();
    auto suffixes = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(visit(ctx->block()->suffixes()));

    bool is_function_param = true;

    std::optional<std::any> type = SymbolTable::getInstance().getTypeOfDeclaratedBlock(identifier);
    if(!type.has_value()){
        throw std::runtime_error("'"+identifier+"' was never declarated before");
    }

    std::optional<std::any> parameter_who_eat = SymbolTable::getInstance().lookupParameter(std::any_cast<std::string>(type.value()), function_parameter_id);

    if(!parameter_who_eat.has_value()){
        parameter_who_eat = SymbolTable::getInstance().lookupOutput(std::any_cast<std::string>(type.value()), function_parameter_id);
        if(!parameter_who_eat.has_value()){
            throw std::runtime_error("'"+function_parameter_id+"' was never defined before");
        }
        is_function_param = false;
    }

    std::cout << "visit feeding statement " << identifier << "." << function_parameter_id << std::endl;    

    std::optional<std::any> variable = SymbolTable::getInstance().lookupBlock(identifier);
    if(!variable.has_value()){
        throw std::runtime_error("'"+identifier+"' was never declarated before");
    }    

    
    std::cout << "Is function param " << (is_function_parameter(parameter_who_eat.value()) ? "param" : "non") << std::endl;

    if(is_function_param){
        std::any s_expr = visit(ctx->s_expr());
        
        std::cout << "type eater: " << ast_builder_detail::type_name(parameter_who_eat.value().type()) << std::endl;
        std::cout << "type s_expr: " << ast_builder_detail::type_name(s_expr.type()) << std::endl;
        
        functional_block_variant variable_expression = make_functional_block_from_any(variable.value(), suffixes);
        if(auto* parameter = keep_any_object_alive<function_parameter<dataflow_kind::LOGICAL, dataflow_type::INT>>(parameter_who_eat.value())){
            eater<dataflow_kind::LOGICAL, dataflow_type::INT> eat(variable_expression, parameter);
            if(auto* feed = keep_any_object_alive<collective_cast<dataflow_kind::LOGICAL, dataflow_type::INT>>(s_expr)){
                feeding_statement<dataflow_kind::LOGICAL, dataflow_type::INT> feeding_stt(eat, feed);
                return feeding_stt;
            }else if(auto* feed = keep_any_object_alive<feeder_block_expression<dataflow_kind::LOGICAL, dataflow_type::INT>>(s_expr)){
                feeding_statement<dataflow_kind::LOGICAL, dataflow_type::INT> feeding_stt(eat, feed);
                return feeding_stt;
            }else if(auto feed = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(s_expr)){
                if(feed){
                    value_arena.emplace_back(feed);
                    feeding_statement<dataflow_kind::LOGICAL, dataflow_type::INT> feeding_stt(eat, feed.get());
                    return feeding_stt;
                }
            }

        }else if(auto* parameter = keep_any_object_alive<function_parameter<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>(parameter_who_eat.value())){
            eater<dataflow_kind::LOGICAL, dataflow_type::FLOAT> eat(variable_expression, parameter);
            if(auto* feed = keep_any_object_alive<collective_cast<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>(s_expr)){
                feeding_statement<dataflow_kind::LOGICAL, dataflow_type::FLOAT> feeding_stt(eat, feed);
                return feeding_stt;
            }else if(auto* feed = keep_any_object_alive<feeder_block_expression<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>(s_expr)){
                feeding_statement<dataflow_kind::LOGICAL, dataflow_type::FLOAT> feeding_stt(eat, feed);
                return feeding_stt;
            }else if(auto feed = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::SYSTEM>(s_expr)){
                if(feed){
                    value_arena.emplace_back(feed);
                    feeding_statement<dataflow_kind::LOGICAL, dataflow_type::FLOAT> feeding_stt(eat, feed.get());
                    return feeding_stt;
                }
            }
        }else if(auto* parameter = keep_any_object_alive<function_parameter<dataflow_kind::LOGICAL, dataflow_type::BOOL>>(parameter_who_eat.value())){
            eater<dataflow_kind::LOGICAL, dataflow_type::BOOL> eat(variable_expression, parameter);
            if(auto* feed = keep_any_object_alive<collective_cast<dataflow_kind::LOGICAL, dataflow_type::BOOL>>(s_expr)){
                feeding_statement<dataflow_kind::LOGICAL, dataflow_type::BOOL> feeding_stt(eat, feed);
                return feeding_stt;
            }else if(auto* feed = keep_any_object_alive<feeder_block_expression<dataflow_kind::LOGICAL, dataflow_type::BOOL>>(s_expr)){
                feeding_statement<dataflow_kind::LOGICAL, dataflow_type::BOOL> feeding_stt(eat, feed);
                return feeding_stt;
            }else if(auto feed = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::SYSTEM>(s_expr)){
                if(feed){
                    value_arena.emplace_back(feed);
                    feeding_statement<dataflow_kind::LOGICAL, dataflow_type::BOOL> feeding_stt(eat, feed.get());
                    return feeding_stt;
                }
            }
        }else if(auto* parameter = keep_any_object_alive<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::INT>>(parameter_who_eat.value())){
            eater<dataflow_kind::PHYSICAL, dataflow_type::INT> eat(variable_expression, parameter);
            
            if(auto* feed = keep_any_object_alive<collective_cast<dataflow_kind::PHYSICAL, dataflow_type::INT>>(s_expr)){
                feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::INT> feeding_stt(eat, feed);
                return feeding_stt;
            }else if(auto* feed = keep_any_object_alive<feeder_block_expression<dataflow_kind::PHYSICAL, dataflow_type::INT>>(s_expr)){
                feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::INT> feeding_stt(eat, feed);
                return feeding_stt;
            }else if(auto feed = ast_builder_detail::try_extract<dataflow_type::INT, expression_env::SYSTEM>(s_expr)){
                std::runtime_error("Expression can't be the feeder of a feeding statement where eater is a physical parameter");
            }
        }else if(auto* parameter = keep_any_object_alive<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>(parameter_who_eat.value())){
            eater<dataflow_kind::PHYSICAL, dataflow_type::FLOAT> eat(variable_expression, parameter);
            if(auto* feed = keep_any_object_alive<collective_cast<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>(s_expr)){
                feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::FLOAT> feeding_stt(eat, feed);
                return feeding_stt;
            }else if(auto* feed = keep_any_object_alive<feeder_block_expression<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>(s_expr)){
                feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::FLOAT> feeding_stt(eat, feed);
                return feeding_stt;
            }else if(auto feed = ast_builder_detail::try_extract<dataflow_type::FLOAT, expression_env::SYSTEM>(s_expr)){
                std::runtime_error("Expression can't be the feeder of a feeding statement where eater is a physical parameter");
            }
        }else if(auto* parameter = keep_any_object_alive<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>(parameter_who_eat.value())){
            eater<dataflow_kind::PHYSICAL, dataflow_type::BOOL> eat(variable_expression, parameter);
            if(auto* feed = keep_any_object_alive<collective_cast<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>(s_expr)){
                feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::BOOL> feeding_stt(eat, feed);
                return feeding_stt;
            }else if(auto* feed = keep_any_object_alive<feeder_block_expression<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>(s_expr)){
                feeding_statement<dataflow_kind::PHYSICAL, dataflow_type::BOOL> feeding_stt(eat, feed);
                return feeding_stt;
            }else if(auto feed = ast_builder_detail::try_extract<dataflow_type::BOOL, expression_env::SYSTEM>(s_expr)){
                std::runtime_error("Expression can't be the feeder of a feeding statement where eater is a physical parameter");
            }
        }
    }else{
        auto eating_channel = std::any_cast<std::shared_ptr<node_element_declaration<node_element::CHANNEL>>>(parameter_who_eat.value()).get();
        
        std::cout << "type channel who eat: " << ast_builder_detail::type_name(std::any{eating_channel}.type()) << std::endl;

        channel_eater* eat = keep_value_alive(make_channel_eater(variable.value(), parameter_who_eat.value(), suffixes));


        if(auto* expr = dynamic_cast<ChipsParser::SBlockOutputExpressionContext*>(ctx->s_expr())){

            std::string variable_feeder_id = expr->block()->IDENTIFIER()->getText();
            auto suffixes_feeder = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(visit(expr->block()->suffixes()));
            std::string channel_feeder_id = expr->IDENTIFIER()->getText();

            std::optional<std::any> variable_feeder_opt = SymbolTable::getInstance().lookupBlock(variable_feeder_id);
            if(!variable_feeder_opt.has_value()){
                throw std::runtime_error("'"+variable_feeder_id+"' was never declarated before");
            }

            std::optional<std::any> type_feeder = SymbolTable::getInstance().getTypeOfDeclaratedBlock(identifier);
            if(!type_feeder.has_value()){
                throw std::runtime_error("'"+identifier+"' was never declarated before");
            }

            std::optional<std::any> channel_who_feed = SymbolTable::getInstance().lookupOutput(std::any_cast<std::string>(type_feeder.value()), channel_feeder_id);
            if(!channel_who_feed.has_value()){
                throw std::runtime_error("'"+channel_feeder_id+"' was never defined before");
            }

            channel_feeder* feed = keep_value_alive(make_channel_feeder(variable_feeder_opt.value(), channel_who_feed.value(), suffixes_feeder));

            channel_plugging plugging(eat, feed);
            return plugging;
        }else if(auto* expr = dynamic_cast<ChipsParser::SCollectiveCastExpressionContext*>(ctx->s_expr())){
            throw std::runtime_error("Le feeder du channel plugging est un SCollective cast");
        }else{
            throw std::runtime_error("The feeder of a channel plugging can be only a block which is phyisical or object");
        }
        throw std::runtime_error("CHANNEL A IMPLEMETER");
    }

    throw std::runtime_error("Unimplemented visit method FeedingStatementContext");
}

std::any ASTBuilder::visitLinkingStatement(ChipsParser::LinkingStatementContext *ctx)
{
    std::string linkable_id = ctx->IDENTIFIER(0)->getText();
    std::any suffixes_linkable = visit(ctx->suffixes(0));

    auto dims_link = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(suffixes_linkable);

    std::string support_id = ctx->IDENTIFIER(1)->getText();
    std::any suffixes_support = visit(ctx->suffixes(1));

    auto dims_support = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(suffixes_support);

    std::cout << "visit link " << linkable_id << " to " << support_id << std::endl;

    std::optional<std::any> linkable = SymbolTable::getInstance().lookupBlock(linkable_id);

    if(!linkable.has_value()){
        throw std::runtime_error("'"+linkable_id+"' was never declarated before");
    }

    std::optional<std::any> support = SymbolTable::getInstance().lookupBlock(support_id);

    if(!support.has_value()){
        throw std::runtime_error("'"+support_id+"' was never declarated before");
    }

    std::cout << "linkable type: " << ast_builder_detail::type_name(linkable.value().type()) << std::endl;
    std::cout << "support type: " << ast_builder_detail::type_name(support.value().type()) << std::endl;

    block_type linkable_bt = ast_builder_detail::get_block_type(linkable.value());
    block_type support_bt = ast_builder_detail::get_block_type(support.value());

    switch(linkable_bt){
        case block_type::LOGICAL:{
            switch(support_bt){
                case block_type::LOGICAL:
                    throw std::runtime_error("Logical can't be support for link method");
                case block_type::OBJECT:
                    return make_linking_statement<block_type::LOGICAL, block_type::OBJECT>(
                        linkable.value(), dims_link, support.value(), dims_support);
                case block_type::PHYSICAL:
                    std::cout << "ICI je crois" << std::endl;
                    return make_linking_statement<block_type::LOGICAL, block_type::PHYSICAL>(
                        linkable.value(), dims_link, support.value(), dims_support);
            }
        }
        case block_type::OBJECT:{
            switch(support_bt){
                case block_type::LOGICAL:
                    throw std::runtime_error("Logical can't be support for link method");
                case block_type::OBJECT:
                    return make_linking_statement<block_type::OBJECT, block_type::OBJECT>(
                        linkable.value(), dims_link, support.value(), dims_support);
                case block_type::PHYSICAL:
                    return make_linking_statement<block_type::OBJECT, block_type::PHYSICAL>(
                        linkable.value(), dims_link, support.value(), dims_support);
            }
        }
        case block_type::PHYSICAL:{
            switch(support_bt){
                case block_type::LOGICAL:
                    throw std::runtime_error("Logical can't be support for link method");
                case block_type::OBJECT:
                    return make_linking_statement<block_type::PHYSICAL, block_type::OBJECT>(
                        linkable.value(), dims_link, support.value(), dims_support);
                case block_type::PHYSICAL:
                    return make_linking_statement<block_type::PHYSICAL, block_type::PHYSICAL>(
                        linkable.value(), dims_link, support.value(), dims_support);
            }
        }
    }

    throw std::runtime_error("Unhandled block type combination in linking statement");
}

std::any ASTBuilder::visitImplementationStatement(ChipsParser::ImplementationStatementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method ImplementationStatementContext");
}

std::any ASTBuilder::visitSLoopStatement(ChipsParser::SLoopStatementContext *ctx)
{
    return visit(ctx->s_loop_statement());
}

std::any ASTBuilder::visitSIfElseStatement(ChipsParser::SIfElseStatementContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method SIfElseStatementContext");
}

std::any ASTBuilder::visitSIfStatement(ChipsParser::SIfStatementContext *ctx)
{
    return visit(ctx->s_if_statement());
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
    std::string identifier = ctx->block()->IDENTIFIER()->getText();
    auto suffixes = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(visit(ctx->block()->suffixes()));
    std::string function_output_id = ctx->IDENTIFIER()->getText();

    std::cout << "visit SBlock output expr " << identifier << std::endl;

    std::optional<std::any> feeder_who_eaten = SymbolTable::getInstance().lookupBlock(identifier);
    if(!feeder_who_eaten.has_value()){
        throw std::runtime_error("'"+identifier+"' was never declarated before");
    }

    std::optional<std::any> output_who_eaten = SymbolTable::getInstance().lookupOutput(SymbolTable::getInstance().getTypeOfDeclaratedBlock(identifier), function_output_id);
    if(!output_who_eaten.has_value()){
        throw std::runtime_error("'"+function_output_id+"' was never defined before");
    }

    functional_block_variant variable_expression = make_functional_block_from_any(feeder_who_eaten.value(), suffixes);

    try{
        if(auto output = std::any_cast<std::shared_ptr<function_output<dataflow_kind::LOGICAL, dataflow_type::INT>>>(output_who_eaten.value())){
            auto feeder_block = std::make_shared<feeder_block_expression<dataflow_kind::LOGICAL, dataflow_type::INT>>(variable_expression, output.get());
            node_arena.push_back(feeder_block);
            return *feeder_block;
        }
    }catch(const std::bad_any_cast& e){
        std::cout << "not logical int" << std::endl;
    }

    try{
        if(auto output = std::any_cast<std::shared_ptr<function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>>(output_who_eaten.value())){
            auto feeder_block = std::make_shared<feeder_block_expression<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>(variable_expression, output.get());
            node_arena.push_back(feeder_block);
            return *feeder_block;
        }
    }catch(const std::bad_any_cast& e){
        std::cout << "not logical float" << std::endl;
    }

    try{
        if(auto output = std::any_cast<std::shared_ptr<function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>>>(output_who_eaten.value())){
            auto feeder_block = std::make_shared<feeder_block_expression<dataflow_kind::LOGICAL, dataflow_type::BOOL>>(variable_expression, output.get());
            node_arena.push_back(feeder_block);
            return *feeder_block;
        }
    }catch(const std::bad_any_cast& e){
        std::cout << "not logical bool" << std::endl;
    }

    try{
        if(auto output = std::any_cast<std::shared_ptr<function_output<dataflow_kind::PHYSICAL, dataflow_type::INT>>>(output_who_eaten.value())){
            auto feeder_block = std::make_shared<feeder_block_expression<dataflow_kind::PHYSICAL, dataflow_type::INT>>(variable_expression, output.get());
            node_arena.push_back(feeder_block);
            return *feeder_block;
        }
    }catch(const std::bad_any_cast& e){
        std::cout << "not physical int" << std::endl;
    }

    try{
        if(auto output = std::any_cast<std::shared_ptr<function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>>(output_who_eaten.value())){
            auto feeder_block = std::make_shared<feeder_block_expression<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>(variable_expression, output.get());
            node_arena.push_back(feeder_block);
            return *feeder_block;
        }
    }catch(const std::bad_any_cast& e){
        std::cout << "not physical float" << std::endl;
    }

    try{
        if(auto output = std::any_cast<std::shared_ptr<function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>>(output_who_eaten.value())){
            
            auto feeder_block = std::make_shared<feeder_block_expression<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>(variable_expression, output.get());
            node_arena.push_back(feeder_block);
            return *feeder_block;
        }
    }catch(const std::bad_any_cast& e){
        std::cout << "not physical bool" << std::endl;
    }
        

    throw std::runtime_error("Unsupported type or kind");

    // throw std::runtime_error("Unimplemented visit method SBlockOutputExpressionContext");
}

functional_block_variant ASTBuilder::make_functional_block_from_any(std::any& node, std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dims){
    if(auto* p = std::any_cast<std::shared_ptr<block_variable<block_type::LOGICAL>>>(&node)){
        p->get()->set_dimensions(dims);
        return p->get();
    }
    if(auto* p = std::any_cast<block_variable<block_type::LOGICAL>>(&node)){
        p->set_dimensions(dims);
        return p;
    }
    if(auto* p = std::any_cast<std::shared_ptr<block_variable<block_type::PHYSICAL>>>(&node)){
        p->get()->set_dimensions(dims);
        return p->get();
    }
    if(auto* p = std::any_cast<block_variable<block_type::PHYSICAL>>(&node)){
        p->set_dimensions(dims);
        return p;
    }
    throw std::runtime_error("Unsopported type in make_functional_block_from_any");
}

std::any ASTBuilder::visitSCollectiveCastExpression(ChipsParser::SCollectiveCastExpressionContext *ctx)
{

    std::string identifier = ctx->block()->IDENTIFIER()->getText();

    std::cout << "visit collective cast expr " << identifier << std::endl;

    auto suffixes = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>>>(visit(ctx->block()->suffixes()));

    std::string function_output_id = ctx->IDENTIFIER()->getText();
    std::string collective_op = ctx->collective_operation()->IDENTIFIER()->getText();

    std::optional<std::any> collective = SymbolTable::getInstance().lookupFunctionSpread(collective_op);
    if(!collective.has_value()){
        collective = SymbolTable::getInstance().lookupFunctionCollect(collective_op);
    }

    if(!collective.has_value()){
        throw std::runtime_error("'"+collective_op+"' was never defined before");
    }

    std::optional<std::any> target_output_opt = SymbolTable::getInstance().lookupOutput(collective_op, "@");

    if(!target_output_opt.has_value()){
        throw std::runtime_error("'@' was never defined before");
    }

    auto collective_func_def = std::make_shared<collective_function_definition>(
        std::any_cast<collective_function_definition>(collective.value()));
    node_arena.push_back(collective_func_def);

    dataflow_type type_target_output = get_type_of_output<expression_env::COLLECTIVE>(target_output_opt.value());

    std::cout << "TYPE OF TARGET: " << dft_to_string(type_target_output) << std::endl;
    std::cout << "feeder who eaten " << identifier << "(" << SymbolTable::getInstance().getTypeOfDeclaratedBlock(identifier) << ")" << std::endl; 

    std::optional<std::any> feeder_who_eaten = SymbolTable::getInstance().lookupBlock(identifier);
    if(!feeder_who_eaten.has_value()){
        throw std::runtime_error("'"+identifier+"' was never declarated before");
    }

    std::optional<std::any> output_who_eaten = SymbolTable::getInstance().lookupOutput(SymbolTable::getInstance().getTypeOfDeclaratedBlock(identifier), function_output_id);
    if(!output_who_eaten.has_value()){
        throw std::runtime_error("'"+function_output_id+"' was never defined before");
    }

    functional_block_variant variable_expression = make_functional_block_from_any(feeder_who_eaten.value(), suffixes);

    std::cout << "bordel ce type: " << ast_builder_detail::type_name(output_who_eaten.value().type()) << std::endl;

    try{
        if(auto output = std::any_cast<std::shared_ptr<function_output<dataflow_kind::LOGICAL, dataflow_type::INT>>>(output_who_eaten.value())){
            auto feeder_block = std::make_shared<feeder_block_expression<dataflow_kind::LOGICAL, dataflow_type::INT>>(variable_expression, output.get());
            node_arena.push_back(feeder_block);
            // collective_cast<dataflow_kind::LOGICAL, dataflow_type::INT> collect_cast(collective_func_def.get(), *feeder_block);
            // return collect_cast;

            switch(type_target_output){
                case dataflow_type::INT:{
                    collective_cast<dataflow_kind::LOGICAL, dataflow_type::INT> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
                case dataflow_type::FLOAT:{
                    collective_cast<dataflow_kind::LOGICAL, dataflow_type::FLOAT> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
                case dataflow_type::BOOL:{
                    collective_cast<dataflow_kind::LOGICAL, dataflow_type::BOOL> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
            }

        }
    }catch(const std::bad_any_cast& e){
        std::cout << "not logical int" << std::endl;
    }

    try{
        if(auto output = std::any_cast<std::shared_ptr<function_output<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>>(output_who_eaten.value())){
            auto feeder_block = std::make_shared<feeder_block_expression<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>(variable_expression, output.get());
            node_arena.push_back(feeder_block);
            // collective_cast<dataflow_kind::LOGICAL, dataflow_type::FLOAT> collect_cast(collective_func_def.get(), *feeder_block);
            // return collect_cast;

            switch(type_target_output){
                case dataflow_type::INT:{
                    collective_cast<dataflow_kind::LOGICAL, dataflow_type::INT> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
                case dataflow_type::FLOAT:{
                    collective_cast<dataflow_kind::LOGICAL, dataflow_type::FLOAT> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
                case dataflow_type::BOOL:{
                    collective_cast<dataflow_kind::LOGICAL, dataflow_type::BOOL> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
            }
        }
    }catch(const std::bad_any_cast& e){
        std::cout << "not logical float" << std::endl;
    }

    try{
        if(auto output = std::any_cast<std::shared_ptr<function_output<dataflow_kind::LOGICAL, dataflow_type::BOOL>>>(output_who_eaten.value())){
            auto feeder_block = std::make_shared<feeder_block_expression<dataflow_kind::LOGICAL, dataflow_type::BOOL>>(variable_expression, output.get());
            node_arena.push_back(feeder_block);
            // collective_cast<dataflow_kind::LOGICAL, dataflow_type::BOOL> collect_cast(collective_func_def.get(), *feeder_block);
            // return collect_cast;

            switch(type_target_output){
                case dataflow_type::INT:{
                    collective_cast<dataflow_kind::LOGICAL, dataflow_type::INT> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
                case dataflow_type::FLOAT:{
                    collective_cast<dataflow_kind::LOGICAL, dataflow_type::FLOAT> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
                case dataflow_type::BOOL:{
                    collective_cast<dataflow_kind::LOGICAL, dataflow_type::BOOL> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
            }
        }
    }catch(const std::bad_any_cast& e){
        std::cout << "not logical bool" << std::endl;
    }

    try{
        if(auto output = std::any_cast<std::shared_ptr<function_output<dataflow_kind::PHYSICAL, dataflow_type::INT>>>(output_who_eaten.value())){
            auto feeder_block = std::make_shared<feeder_block_expression<dataflow_kind::PHYSICAL, dataflow_type::INT>>(variable_expression, output.get());
            node_arena.push_back(feeder_block);
            // collective_cast<dataflow_kind::PHYSICAL, dataflow_type::INT> collect_cast(collective_func_def.get(), *feeder_block);
            // return collect_cast;

            switch(type_target_output){
                case dataflow_type::INT:{
                    collective_cast<dataflow_kind::PHYSICAL, dataflow_type::INT> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
                case dataflow_type::FLOAT:{
                    collective_cast<dataflow_kind::PHYSICAL, dataflow_type::FLOAT> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
                case dataflow_type::BOOL:{
                    collective_cast<dataflow_kind::PHYSICAL, dataflow_type::BOOL> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
            }
        }
    }catch(const std::bad_any_cast& e){
        std::cout << "not physical int" << std::endl;
    }

    try{
        if(auto output = std::any_cast<std::shared_ptr<function_output<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>>(output_who_eaten.value())){
            auto feeder_block = std::make_shared<feeder_block_expression<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>(variable_expression, output.get());
            node_arena.push_back(feeder_block);
            // collective_cast<dataflow_kind::PHYSICAL, dataflow_type::FLOAT> collect_cast(collective_func_def.get(), *feeder_block);
            // return collect_cast;

            switch(type_target_output){
                case dataflow_type::INT:{
                    collective_cast<dataflow_kind::PHYSICAL, dataflow_type::INT> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
                case dataflow_type::FLOAT:{
                    collective_cast<dataflow_kind::PHYSICAL, dataflow_type::FLOAT> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
                case dataflow_type::BOOL:{
                    collective_cast<dataflow_kind::PHYSICAL, dataflow_type::BOOL> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
            }
        }
    }catch(const std::bad_any_cast& e){
        std::cout << "not physical float" << std::endl;
    }

    try{
        if(auto output = std::any_cast<std::shared_ptr<function_output<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>>(output_who_eaten.value())){
            
            auto feeder_block = std::make_shared<feeder_block_expression<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>(variable_expression, output.get());
            node_arena.push_back(feeder_block);
            // collective_cast<dataflow_kind::PHYSICAL, dataflow_type::BOOL> collect_cast(collective_func_def.get(), *feeder_block);
            // return collect_cast;

            switch(type_target_output){
                case dataflow_type::INT:{
                    collective_cast<dataflow_kind::PHYSICAL, dataflow_type::INT> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
                case dataflow_type::FLOAT:{
                    collective_cast<dataflow_kind::PHYSICAL, dataflow_type::FLOAT> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
                case dataflow_type::BOOL:{
                    collective_cast<dataflow_kind::PHYSICAL, dataflow_type::BOOL> collect_cast(collective_func_def.get(), *feeder_block);
                    return collect_cast;
                }
            }
        }
    }catch(const std::bad_any_cast& e){
        std::cout << "not physical bool" << std::endl;
    }
        

    throw std::runtime_error("Unsupported type or kind");
}

std::any ASTBuilder::visitSRegularExpression(ChipsParser::SRegularExpressionContext *ctx)
{
    return visit(ctx->expr());
}

std::any ASTBuilder::visitCollective_operation(ChipsParser::Collective_operationContext *ctx)
{
    throw std::runtime_error("Unimplemented visit method Collective_operationContext");
}

std::any ASTBuilder::visitCollectiveVariableDeclaration(ChipsParser::CollectiveVariableDeclarationContext *ctx)
{

    std::cout << "visit collective statement declaration" << std::endl;

    dataflow_type type = std::any_cast<dataflow_type>(visit(ctx->cdf_full_declaration()->df_type()));
    std::string var = ctx->cdf_full_declaration()->IDENTIFIER()->getText();
    std::any assign;

    if(ctx->cdf_full_declaration()->c_expr()){
        assign = visit(ctx->cdf_full_declaration()->c_expr());
    }

    auto dims = std::any_cast<std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>>>(visit(ctx->cdf_full_declaration()->suffixes()));

    switch(type){
        case dataflow_type::INT:
            return handle_statement_declaration<expression_env::COLLECTIVE, dataflow_type::INT>(dims, var, assign);
        case dataflow_type::FLOAT:
            return handle_statement_declaration<expression_env::COLLECTIVE, dataflow_type::FLOAT>(dims, var, assign);
        case dataflow_type::BOOL:
            return handle_statement_declaration<expression_env::COLLECTIVE, dataflow_type::BOOL>(dims, var, assign);
        default:
            throw std::runtime_error("unknown type for variable declaration");
    }
}

std::any ASTBuilder::visitCollectiveAssignment(ChipsParser::CollectiveAssignmentContext *ctx)
{
    std::cout << "visit collective assignment" << std::endl;

    std::string identifier = ctx->IDENTIFIER()->getText();
    std::any suffixes = visit(ctx->c_suffixes());

    std::any assign = visit(ctx->c_expr());

    return handle_statement_assignment<expression_env::COLLECTIVE, statement_env::COLLECTIVE>(identifier, suffixes, assign, false);

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
    std::cout << "visit statement if else" << std::endl;
    return visit(ctx->c_if_else_statement());
}

std::any ASTBuilder::visitCollectiveIfStatement(ChipsParser::CollectiveIfStatementContext *ctx)
{
    std::cout << "visit statement collective if" << std::endl;
    return visit(ctx->c_if_statement());
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
        visit(ctx->expr01()), visit(ctx->expr0()), "PLUS");
}

std::any ASTBuilder::visitSUB(ChipsParser::SUBContext *ctx)
{
    return ast_builder_detail::dispatch_numeric_binary<ast_builder_detail::SubBuilder>(
        visit(ctx->expr01()), visit(ctx->expr0()), "SUB");
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
    // Keep the owning handle alive in the builder so raw pointers returned
    // below remain valid for later XMI traversal.
    value_arena.emplace_back(node);

    auto ptr = node.get();

    if (auto p = dynamic_cast<function<dataflow_type::INT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<function<dataflow_type::FLOAT, expenv> *>(ptr))
        return p;
    if (auto p = dynamic_cast<function<dataflow_type::BOOL, expenv> *>(ptr))
        return p;
    rvalue_variant<expenv> rval = make_variant_from_node(node);
    return keep_value_alive(std::move(rval));

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
    if (auto p = dynamic_cast<input*>(ptr))
        return p;
    if (auto p = dynamic_cast<stop*>(ptr))
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
    if (auto p = dynamic_cast<input*>(ptr))
        return p;
    if (auto p = dynamic_cast<stop*>(ptr))
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
    if constexpr (expenv == expression_env::COLLECTIVE)
    {
        if (auto p = dynamic_cast<input *>(ptr))
            return static_cast<rvalue<dft, expenv> *>(p);
        if (auto p = dynamic_cast<stop *>(ptr))
            return static_cast<rvalue<dft, expenv> *>(p);
    }

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

std::any ASTBuilder::visitPassExpr01(ChipsParser::PassExpr01Context* ctx){
    return visit(ctx->expr01());
}

std::any ASTBuilder::visitPassExpr1(ChipsParser::PassExpr1Context *ctx)
{
    return visit(ctx->expr1());
}

std::any ASTBuilder::visitPassExpr2(ChipsParser::PassExpr2Context *ctx)
{
    return visit(ctx->expr2());
}

bool ASTBuilder::is_function_parameter(std::any& value){
        if(auto* p = std::any_cast<function_parameter<dataflow_kind::LOGICAL, dataflow_type::INT>>(&value))
            return true;
        if(auto* p = std::any_cast<function_parameter<dataflow_kind::LOGICAL, dataflow_type::FLOAT>>(&value))
            return true;
        if(auto* p = std::any_cast<function_parameter<dataflow_kind::LOGICAL, dataflow_type::BOOL>>(&value))
            return true;
        if(auto* p = std::any_cast<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::INT>>(&value))
            return true;
        if(auto* p = std::any_cast<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::FLOAT>>(&value))
            return true;
        if(auto* p = std::any_cast<function_parameter<dataflow_kind::PHYSICAL, dataflow_type::BOOL>>(&value))
            return true;    
        
        return false;
}

channel_eater ASTBuilder::make_channel_eater(std::any& variable, std::any& parameter_who_eat, std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dims){
    auto eating_channel = std::any_cast<std::shared_ptr<node_element_declaration<node_element::CHANNEL>>>(parameter_who_eat);

    if(auto block = std::any_cast<std::shared_ptr<block_variable<block_type::PHYSICAL>>>(variable)){
        auto var_expr = std::make_shared<system_variable_block_expression<block_type::PHYSICAL>>(block.get(), dims);
        node_arena.push_back(var_expr);  // Garde l'objet vivant
        channel_eater eat(var_expr.get(), eating_channel.get());
        return eat;
    }else if(auto block = std::any_cast<std::shared_ptr<block_variable<block_type::OBJECT>>>(variable)){
        auto var_expr = std::make_shared<system_variable_block_expression<block_type::OBJECT>>(block.get(), dims);
        node_arena.push_back(var_expr);  // Garde l'objet vivant
        channel_eater eat(var_expr.get(), eating_channel.get());
        return eat;
    }
    throw std::runtime_error("Channel eater can't be of type logical");
}

channel_feeder ASTBuilder::make_channel_feeder(std::any& variable, std::any& channel_who_feed, std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dims){
    auto feeding_channel = std::any_cast<std::shared_ptr<node_element_declaration<node_element::CHANNEL>>>(channel_who_feed);

    if(auto block = std::any_cast<std::shared_ptr<block_variable<block_type::PHYSICAL>>>(variable)){
        auto var_expr = std::make_shared<system_variable_block_expression<block_type::PHYSICAL>>(block.get(), dims);
        node_arena.push_back(var_expr);  // Garde l'objet vivant
        channel_feeder feed(var_expr.get(), feeding_channel.get());
        return feed;
    }else if(auto block = std::any_cast<std::shared_ptr<block_variable<block_type::OBJECT>>>(variable)){
        auto var_expr = std::make_shared<system_variable_block_expression<block_type::OBJECT>>(block.get(), dims);
        node_arena.push_back(var_expr);  // Garde l'objet vivant
        channel_feeder feed(var_expr.get(), feeding_channel.get());
        return feed;
    }
    throw std::runtime_error("Channel eater can't be of type logical");
}
