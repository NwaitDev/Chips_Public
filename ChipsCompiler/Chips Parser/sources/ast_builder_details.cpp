#include "ast_builder_details.hpp"

#include "utils.hpp"

using namespace chips;

namespace ast_builder_detail
{

    std::string type_name(const std::type_info &ti)
    {
        int status;
        char *d = abi::__cxa_demangle(ti.name(), nullptr, nullptr, &status);
        std::string r = (status == 0 && d) ? d : ti.name();
        free(d);
        return r;
    }

    
    node_statement_variant try_extract_node_specific_statement(std::any statement)
    {
        if (auto p = std::any_cast<node_element_declaration<node_element::CHANNEL>*>(&statement))
        {
            return *p;
        }
        std::cout << "not a channel declaration" << std::endl;

        if (auto p = std::any_cast<node_element_declaration<node_element::CONTEXTUAL_INT>*>(&statement))
        {
            return *p;
        }
        std::cout << "not a contextual int declaration" << std::endl;

        if (auto p = std::any_cast<node_element_declaration<node_element::CONTEXTUAL_FLOAT>*>(&statement))
        {
            return *p;
        }
        std::cout << "not a contextual float declaration" << std::endl;

        if (auto p = std::any_cast<node_element_declaration<node_element::CONTEXTUAL_BOOL>*>(&statement))
        {
            return *p;
        }
        std::cout << "not a contextual bool declaration" << std::endl;

        throw std::runtime_error("failed to extract node specific statement");
    }

    statement_variant try_extract_node_recurring_statement(std::any statement)
    {
        try
        {
            // must try this one before the if statement because
            // "if else" derives from "if" statement
            if_else_statement<statement_env::NODE> new_ast_stt =
                std::any_cast<if_else_statement<statement_env::NODE>>(statement);
            return &new_ast_stt;
        }
        catch (const std::bad_any_cast &e)
        {
            std::cout << "not an if else statement" << std::endl;
        }

        try
        {
            if_statement<statement_env::NODE> new_ast_stt =
                std::any_cast<if_statement<statement_env::NODE>>(statement);
            return &new_ast_stt;
        }
        catch (const std::bad_any_cast &e)
        {
            std::cout << "not an if statement" << std::endl;
        }

        try
        {
            foreach_statement<statement_env::NODE, dataflow_type::INT> new_ast_stt =
                std::any_cast<foreach_statement<statement_env::NODE, dataflow_type::INT>>(statement);
            return &new_ast_stt;
        }
        catch (const std::bad_any_cast &e)
        {
            std::cout << "not a foreach int statement" << std::endl;
        }

        try
        {
            foreach_statement<statement_env::NODE, dataflow_type::FLOAT> new_ast_stt =
                std::any_cast<foreach_statement<statement_env::NODE, dataflow_type::FLOAT>>(statement);
            return &new_ast_stt;
        }
        catch (const std::bad_any_cast &e)
        {
            std::cout << "not a foreach float statement" << std::endl;
        }

        try
        {
            foreach_statement<statement_env::NODE, dataflow_type::BOOL> new_ast_stt =
                std::any_cast<foreach_statement<statement_env::NODE, dataflow_type::BOOL>>(statement);
            return &new_ast_stt;
        }
        catch (const std::bad_any_cast &e)
        {
            std::cout << "not a foreach bool statement" << std::endl;
        }

        try
        {
            dataflow_declaration<dataflow_type::INT, statement_env::NODE> new_ast_stt =
                std::any_cast<dataflow_declaration<dataflow_type::INT, statement_env::NODE>>(statement);
            return &new_ast_stt;
        }
        catch (const std::bad_any_cast &e)
        {
            std::cout << "not a int declaration statement" << std::endl;
        }

        try
        {
            dataflow_declaration<dataflow_type::FLOAT, statement_env::NODE> new_ast_stt =
                std::any_cast<dataflow_declaration<dataflow_type::FLOAT, statement_env::NODE>>(statement);
            return &new_ast_stt;
        }
        catch (const std::bad_any_cast &e)
        {
            std::cout << "not a float declaration statement" << std::endl;
        }

        try
        {
            dataflow_declaration<dataflow_type::BOOL, statement_env::NODE> new_ast_stt =
                std::any_cast<dataflow_declaration<dataflow_type::BOOL, statement_env::NODE>>(statement);
            return &new_ast_stt;
        }
        catch (const std::bad_any_cast &e)
        {
            std::cout << "not a bool declaration statement" << std::endl;
        }

        try
        {
            dataflow_assignment<dataflow_type::INT, statement_env::NODE> new_ast_stt =
                std::any_cast<dataflow_assignment<dataflow_type::INT, statement_env::NODE>>(statement);
            return &new_ast_stt;
        }
        catch (const std::bad_any_cast &e)
        {
            std::cout << "not an int assignement statement" << std::endl;
        }
        try
        {
            dataflow_assignment<dataflow_type::FLOAT, statement_env::NODE> new_ast_stt =
                std::any_cast<dataflow_assignment<dataflow_type::FLOAT, statement_env::NODE>>(statement);
            return &new_ast_stt;
        }
        catch (const std::bad_any_cast &e)
        {
            std::cout << "not a float assignment statement" << std::endl;
        }
        try
        {
            dataflow_assignment<dataflow_type::BOOL, statement_env::NODE> new_ast_stt =
                std::any_cast<dataflow_assignment<dataflow_type::BOOL, statement_env::NODE>>(statement);
            return &new_ast_stt;
        }
        catch (const std::bad_any_cast &e)
        {
            std::cout << "not a bool assignment statement" << std::endl;
        }

        throw std::runtime_error("failed to extract node recurring statement "+type_name(statement.type()));
    }

     bool is_declaration_with_expression(antlr4::ParserRuleContext *ctx){
        if (ChipsParser::StatementDeclarationContext *stuff = dynamic_cast<ChipsParser::StatementDeclarationContext *>(ctx))
            if (stuff->expr() != nullptr)
                return true;
        
        return false;
    }


    std::shared_ptr<ast_node> extract_as_node(const std::any &a){
        // std::cout << "extract_as_node()" << std::endl;
        if (!a.has_value())
            return nullptr;

#define TRY_UPCAST(DFT, EXPENV)               \
    if (auto p = try_extract<DFT, EXPENV>(a)) \
        return std::static_pointer_cast<ast_node>(p);

        TRY_UPCAST(dataflow_type::INT, expression_env::PRIMITIVE)
        TRY_UPCAST(dataflow_type::FLOAT, expression_env::PRIMITIVE)
        TRY_UPCAST(dataflow_type::BOOL, expression_env::PRIMITIVE)
        TRY_UPCAST(dataflow_type::INT, expression_env::COLLECTIVE)
        TRY_UPCAST(dataflow_type::FLOAT, expression_env::COLLECTIVE)
        TRY_UPCAST(dataflow_type::BOOL, expression_env::COLLECTIVE)
        TRY_UPCAST(dataflow_type::INT, expression_env::SYSTEM)
        TRY_UPCAST(dataflow_type::FLOAT, expression_env::SYSTEM)
        TRY_UPCAST(dataflow_type::BOOL, expression_env::SYSTEM)

#undef TRY_UPCAST

        // dataflow_declaration DEFINITION
        if (auto *p = std::any_cast<dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION>>(&a))
            return std::shared_ptr<ast_node>(
                const_cast<dataflow_declaration<dataflow_type::INT, statement_env::DEFINITION> *>(p),
                [](ast_node *) {});
        if (auto *p = std::any_cast<dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION>>(&a))
            return std::shared_ptr<ast_node>(
                const_cast<dataflow_declaration<dataflow_type::FLOAT, statement_env::DEFINITION> *>(p),
                [](ast_node *) {});
        if (auto *p = std::any_cast<dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION>>(&a))
            return std::shared_ptr<ast_node>(
                const_cast<dataflow_declaration<dataflow_type::BOOL, statement_env::DEFINITION> *>(p),
                [](ast_node *) {});
        if (auto *p = std::any_cast<dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION>>(&a))
            return std::shared_ptr<ast_node>(
                const_cast<dataflow_assignment<dataflow_type::INT, statement_env::DEFINITION> *>(p),
                [](ast_node *) {});
        if (auto *p = std::any_cast<dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION>>(&a))
            return std::shared_ptr<ast_node>(
                const_cast<dataflow_assignment<dataflow_type::FLOAT, statement_env::DEFINITION> *>(p),
                [](ast_node *) {});
        if (auto *p = std::any_cast<dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION>>(&a))
            return std::shared_ptr<ast_node>(
                const_cast<dataflow_assignment<dataflow_type::BOOL, statement_env::DEFINITION> *>(p),
                [](ast_node *) {});

        std::cout << "extract as node type reel: " << type_name(a.type()) << std::endl;

        throw std::runtime_error(
            "extract_as_node : type inconnu dans le std::any : " + type_name(a.type()) + ". Ajouter la combinaison dans extract_as_node si un nouveau "
                                                                                         "visiteur produit ce type (sauf BOOL et SYSTEM, voir commentaire).");
    }

} // namespace ast_builder_detail