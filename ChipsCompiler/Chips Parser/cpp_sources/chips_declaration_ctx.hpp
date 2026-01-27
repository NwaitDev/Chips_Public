
#ifndef DECLARATION_CTX_H
#define DECLARATION_CTX_H

#include "./chips_ast_classes.hpp"
#include "./chips_expressions.hpp"
#include <iostream>
#include <memory>
#include <vector>

// TODO : refactor S_STATEMENT_TYPE functions


/*
    Declaration context stuff
*/

class preamble_node : public ast_node {
public:
    void accept(chips_visitor &visitor) override {
        visitor.visit(*this);
    }
};

class preambles_node : public ast_node {
private:
    std::vector<std::unique_ptr<preamble_node>> preambleList;
public:
    preambles_node() : preambleList(std::vector<std::unique_ptr<preamble_node>>()){}
    

    preambles_node(const std::unique_ptr<preambles_node> preambles) : preambleList(std::move(preambles->preambleList)){};

    void append(std::unique_ptr<preamble_node> preamble){
        preambleList.insert(preambleList.begin(), std::move(preamble));
    };

    const std::vector<std::unique_ptr<preamble_node>>& get_preamble_list() const { return preambleList; }

    void accept(chips_visitor& visitor);

    virtual void hello() override;
};

class object_definition_node : public preamble_node {
    private:
        std::string identifier;
        std::unique_ptr<with_section_node> with;

    public:
        object_definition_node(std::string identifier, std::unique_ptr<with_section_node> with)
            : identifier(identifier), with(std::move(with)) {}

        std::string get_identifier() { return identifier; }
        with_section_node* get_with() { return with.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};

class implementation_definition_node : public preamble_node {
    private:
        std::string ident1;
        std::string ident2;
        std::string ident3;
        std::unique_ptr<node_mappings_node> node;

    public:
        implementation_definition_node(std::string ident1, std::string ident2, std::string ident3, std::unique_ptr<node_mappings_node> node)
            : ident1(ident1), ident2(ident2), ident3(ident3), node(std::move(node)) {}

        std::string get_ident1() { return ident1; }
        std::string get_ident2() { return ident2; }
        std::string get_ident3() { return ident3; }
        node_mappings_node* get_node() { return node.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};

class node_mappings_node : public ast_node {
    private:
        std::string ident1;
        std::string ident2;
        std::unique_ptr<node_mappings_node> node;

    public:
        node_mappings_node() = default;

        node_mappings_node(std::string ident1, std::string ident2, std::unique_ptr<node_mappings_node> node)
            : ident1(ident1), ident2(ident2), node(std::move(node)) {}

        std::string get_ident1() { return ident1; }
        std::string get_ident2() { return ident2; }
        node_mappings_node* get_node() { return node.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};

class collective_operation_definition_node : public preamble_node {
    private:
        std::unique_ptr<c_signature_node> signature;
        std::unique_ptr<c_statements_node> statements;
        std::unique_ptr<c_expressions_node> exprs;
        std::unique_ptr<c_output_node> output;
        std::unique_ptr<c_optionnal_outputs_node> optionnal_output;

    public:
        collective_operation_definition_node(
            std::unique_ptr<c_signature_node> signature, std::unique_ptr<c_statements_node> statements, std::unique_ptr<c_expressions_node> exprs, 
            std::unique_ptr<c_output_node> output, std::unique_ptr<c_optionnal_outputs_node> optionnal_output)
            : signature(std::move(signature)), statements(std::move(statements)), exprs(std::move(exprs)),
            output(std::move(output)), optionnal_output(std::move(optionnal_output)) {}

        c_signature_node* get_signature() { return signature.get(); }
        c_statements_node* get_statements() { return statements.get(); }
        c_expressions_node* get_expressions() { return exprs.get(); }
        c_output_node* get_output() { return output.get(); }
        c_optionnal_outputs_node* get_optionnal_output() { return optionnal_output.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};

class output_node : public ast_node {
private:
    std::vector<std::unique_ptr<expression_node>> outputs;
public:
    output_node(){}

    output_node(std::unique_ptr<expressions_node> exprs)
    : outputs(std::move(exprs->exprs)) {}

    output_node(std::unique_ptr<output_node> out)
    : outputs(std::move(out->outputs)) {}

    virtual void hello() override;
};

class function_definition_node : public preamble_node {
    public:
        virtual ~function_definition_node() = default;
        virtual void hello() override = 0; 
};

class physical_function_definition_node : public function_definition_node {
private:
    static constexpr FUNCTION_TYPE type = PHYSICAL;
    std::string identifier;
    std::unique_ptr<physical_dataflow_parameter_decls_node> pdf_parameter_list;
    std::unique_ptr<with_section_node> with;
    std::unique_ptr<init_section_node> init;
    std::unique_ptr<then_section_node> then;
    std::unique_ptr<physical_named_outputs_node> outputs;
public:
    physical_function_definition_node(std::string identifier, std::unique_ptr<physical_dataflow_parameter_decls_node> pdf_parameter_list, std::unique_ptr<with_section_node> with, std::unique_ptr<init_section_node> init, std::unique_ptr<then_section_node> then, std::unique_ptr<physical_named_outputs_node> outputs) :
        identifier(identifier), pdf_parameter_list(std::move(pdf_parameter_list)), with(std::move(with)), init(std::move(init)), then(std::move(then)), outputs(std::move(outputs)) {}

    constexpr FUNCTION_TYPE get_type() { return type; }
    std::string get_identifier() { return identifier; }
    physical_dataflow_parameter_decls_node* get_pdf_parameter_list() { return pdf_parameter_list.get(); }
    with_section_node* get_with() { return with.get(); }
    init_section_node* get_init() { return init.get(); }
    then_section_node* get_then() { return then.get(); }
    physical_named_outputs_node* get_outputs() { return outputs.get(); }

    void accept(chips_visitor& visitor) {}
    virtual void hello() override;

};

class logical_function_definition_node : public function_definition_node {
private:
    static constexpr FUNCTION_TYPE type = LOGICAL;
    std::string identifier;
    std::unique_ptr<dataflow_parameter_decls_node> df_parameter_list;
    std::unique_ptr<init_section_node> init;
    std::unique_ptr<then_section_node> then;
    std::unique_ptr<named_outputs_node> outputs;
public:
    logical_function_definition_node(std::string identifier, std::unique_ptr<dataflow_parameter_decls_node> df_parameter_list, std::unique_ptr<init_section_node> init, std::unique_ptr<then_section_node> then, std::unique_ptr<named_outputs_node> outputs) :
        identifier(identifier), df_parameter_list(std::move(df_parameter_list)), init(std::move(init)), then(std::move(then)), outputs(std::move(outputs)) {}

    constexpr FUNCTION_TYPE get_type() { return type; }
    std::string get_identifier() const { return identifier; }
    dataflow_parameter_decls_node* get_df_parameter_list() { return df_parameter_list.get(); }
    init_section_node* get_init() { return init.get(); }
    then_section_node* get_then() { return then.get(); }
    named_outputs_node* get_outputs() { return outputs.get(); }
    
    void accept(chips_visitor& visitor) {}

    virtual void hello() override;
};

class with_section_node : public ast_node {
    private:
        std::unique_ptr<with_statements_node> sttms;
    public:
        with_section_node() = default;
        
        with_section_node(std::unique_ptr<with_statements_node> sttms) : sttms(std::move(sttms)) {}

        with_statements_node* get_statements() { return sttms.get(); }

        void accept(chips_visitor& visitor) {}
        virtual void hello() override;
};

class with_statements_node : public ast_node {
    private:
        std::vector<std::unique_ptr<statement_node>> sttms;
    public:
        with_statements_node() : sttms(std::vector<std::unique_ptr<statement_node>>()) {}

        const std::vector<std::unique_ptr<statement_node>>& get_statements() const { return sttms; }

        void append(std::unique_ptr<statement_node> sttm){
            sttms.insert(sttms.begin(), std::move(sttm));
        }

        void accept(chips_visitor& visitor) {}
        virtual void hello() override;
};

class with_statement_node : public statement_node {
};

class with_two_identifier_node : public with_statement_node {
    private:
        STATEMENT_TYPE type = INST_ST;
        std::string ident1;
        std::string ident2;
    public:
        S_STATEMENT_TYPE get_statement_type() const override { return S_INST_ST; }

        with_two_identifier_node(std::string ident1, std::string ident2) : ident1(ident1), ident2(ident2) {}

        STATEMENT_TYPE get_type() override { return type; }
        std::string get_ident1() { return ident1; }
        std::string get_ident2() { return ident2; }

        void accept(chips_visitor& visitor) {}
        virtual void hello() override;
};

class with_context_statement_node : public with_statement_node {
    private:
        STATEMENT_TYPE s_type = DF_ASSIGN_ST;
        std::unique_ptr<dataflow_type_node> type;
        std::string identifier;
        std::unique_ptr<rhs_assignment_node> rhs;
    public:
        with_context_statement_node(std::unique_ptr<dataflow_type_node> type, std::string identifier, std::unique_ptr<rhs_assignment_node> rhs) :
            type(std::move(type)), identifier(identifier), rhs(std::move(rhs)) {}

        STATEMENT_TYPE get_type() override { return s_type; }
        dataflow_type_node* get_df_type() { return type.get(); }
        std::string get_identifier() { return identifier; }
        rhs_assignment_node* get_rhs() { return rhs.get(); }

        void accept(chips_visitor& visitor) {}
        virtual void hello() override;
};

class init_section_node : public ast_node {
    private:
        std::unique_ptr<statements_node> statements;
    public:
        init_section_node() = default;

        init_section_node(std::unique_ptr<statements_node> statements) : statements(std::move(statements)) {}

        statements_node* get_statements() { return statements.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override; 
};

class then_section_node : public ast_node {
    private:
        std::unique_ptr<statements_node> statements;
    public:
        then_section_node() = default;
        
        then_section_node(std::unique_ptr<statements_node> statements) : statements(std::move(statements)) {}

        statements_node* get_statements() { return statements.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};

class physical_named_outputs_node : public ast_node {
    private:
        std::vector<std::unique_ptr<physical_named_output_node>> outputs;
    public:
        physical_named_outputs_node()= default;

        explicit physical_named_outputs_node(std::vector<std::unique_ptr<physical_named_output_node>>&& output) noexcept
        : outputs(std::move(output)) {}

        physical_named_outputs_node(const physical_named_outputs_node&) = delete;
        physical_named_outputs_node& operator=(const physical_named_outputs_node&) = delete;
        
        physical_named_outputs_node(physical_named_outputs_node&&) = default;
        physical_named_outputs_node& operator=(physical_named_outputs_node&&) = default;
    
        std::vector<std::unique_ptr<physical_named_output_node>>& get_outputs() { return outputs; }

        void append(std::unique_ptr<physical_named_output_node> output) {
            outputs.insert(outputs.begin(), std::move(output));
        }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};   

class named_outputs_node : public ast_node {
    private:
        std::vector<std::unique_ptr<named_output_node>> outputs;
    public:
        named_outputs_node() : outputs() {}

        named_outputs_node(const named_outputs_node&) = delete;
        named_outputs_node& operator=(const named_outputs_node&) = delete;
        
        named_outputs_node(named_outputs_node&&) = default;
        named_outputs_node& operator=(named_outputs_node&&) = default;

        std::vector<std::unique_ptr<named_output_node>>& get_outputs() { return outputs; }

        void append(std::unique_ptr<named_output_node> output) {
            outputs.insert(outputs.begin(), std::move(output));
        }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override; 
};

class physical_named_output_node : public ast_node {

};

class actuator_node : public physical_named_output_node {
    private:
        std::string identifier;
        std::unique_ptr<expressions_node> exprs;
    public:
        actuator_node(std::string identifier, std::unique_ptr<expressions_node> exprs) :
            identifier(identifier), exprs(std::move(exprs)) {}

        std::string get_identifier() { return identifier; }
        expressions_node* get_expressions() { return exprs.get(); }

        void accept(chips_visitor& visitor) {}
        virtual void hello() override;
};

class named_output_node : public physical_named_output_node {
    private:
        std::string identifier;
        std::unique_ptr<expressions_node> exprs;
    public:
        named_output_node(std::string identifier, std::unique_ptr<expressions_node> exprs) : identifier(identifier), exprs(std::move(exprs)) {}

        std::string get_identifier() { return identifier; }
        expressions_node* get_expressions() { return exprs.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};

#endif