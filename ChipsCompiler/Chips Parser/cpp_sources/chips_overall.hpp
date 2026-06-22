#ifndef OVERALL_USAGE_H
#define OVERALL_USAGE_H

#include "./chips_ast_classes.hpp"
#include <iostream>
#include <memory>
#include <vector>


class expression_node : public ast_node {
    public:
        virtual EXPRESSION_TYPE get_return_type() = 0;
        virtual bool have_implicit_cast() = 0;
};



class dataflow_type_node : public ast_node {
private:
    const DATAFLOW_TYPE type;
    std::unique_ptr<suffixes_node> suff;
public:

    dataflow_type_node (const DATAFLOW_TYPE type, std::unique_ptr<suffixes_node> suff)
        : type(type), suff(std::move(suff)) {}

    DATAFLOW_TYPE get_type() { return type; }
    suffixes_node* get_suffixes() { return suff.get(); }

    void accept(chips_visitor& visitor);
    virtual void hello() override;
};

class physical_dataflow_parameter_type_node : public ast_node {
    private:
        bool is_sensor = false;
        std::unique_ptr<dataflow_type_node> type;
    public:
        physical_dataflow_parameter_type_node(std::unique_ptr<dataflow_type_node> type)
            : type(std::move(type)) {}

        physical_dataflow_parameter_type_node(bool is_sensor, std::unique_ptr<dataflow_type_node> type)
            : is_sensor(is_sensor), type(std::move(type)) {}

        dataflow_type_node* get_df_type() { return type.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }
        virtual void hello() override;
};

class expressions_node : public ast_node {
private:
    std::vector<std::unique_ptr<expression_node>> exprs;
    friend class output_node;
public:

    expressions_node() = default;

    explicit expressions_node(std::vector<std::unique_ptr<expression_node>>&& exprs) noexcept
        : exprs(std::move(exprs)) {}

    expressions_node(const expressions_node&) = delete;
    expressions_node& operator=(const expressions_node&) = delete;
    
    expressions_node(expressions_node&&) = default;
    expressions_node& operator=(expressions_node&&) = default;
        
    const std::vector<std::unique_ptr<expression_node>>& get_expressions() const { return exprs; }
    
    void append(std::unique_ptr<expression_node> expr){
        exprs.insert(exprs.begin(), std::move(expr));
    };
    
    void accept(chips_visitor& visitor);

    virtual void hello() override;
};

class dataflow_parameter_list_node : public ast_node {
    private:
        std::vector<std::unique_ptr<dataflow_parameter_decl_node>> df_param_decls;
    public:
        dataflow_parameter_list_node() = default;
    
        dataflow_parameter_list_node(std::vector<std::unique_ptr<dataflow_parameter_decl_node>>&& d) 
        : df_param_decls(std::move(d)) {}
        
        dataflow_parameter_list_node(const dataflow_parameter_list_node&) = delete;
        dataflow_parameter_list_node& operator=(const dataflow_parameter_list_node&) = delete;
        
        dataflow_parameter_list_node(dataflow_parameter_list_node&&) = default;
        dataflow_parameter_list_node& operator=(dataflow_parameter_list_node&&) = default;

        std::vector<std::unique_ptr<dataflow_parameter_decl_node>>& get_dataflow_parameter_decls() { return df_param_decls; }

        void append(std::unique_ptr<dataflow_parameter_decl_node> item) {
            df_param_decls.push_back(std::move(item));
        }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class physical_dataflow_parameter_list_node : public ast_node {
    private:
        std::vector<std::unique_ptr<physical_dataflow_parameter_decl_node>> pdf_param_decls;
    public:
        physical_dataflow_parameter_list_node() = default;

        physical_dataflow_parameter_list_node(std::vector<std::unique_ptr<physical_dataflow_parameter_decl_node>>&& d) 
        : pdf_param_decls(std::move(d)) {}

        physical_dataflow_parameter_list_node(const physical_dataflow_parameter_list_node&) = delete;
        physical_dataflow_parameter_list_node& operator=(const physical_dataflow_parameter_list_node&) = delete;
        
        physical_dataflow_parameter_list_node(physical_dataflow_parameter_list_node&&) = default;
        physical_dataflow_parameter_list_node& operator=(physical_dataflow_parameter_list_node&&) = default;
    

        std::vector<std::unique_ptr<physical_dataflow_parameter_decl_node>>& get_physical_dataflow_parameter_decls() { return pdf_param_decls; }

        void append(std::unique_ptr<physical_dataflow_parameter_decl_node> item) {
            pdf_param_decls.push_back(std::move(item));
        }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class dataflow_parameter_decls_node :  public ast_node {
    private:
        std::vector<std::unique_ptr<dataflow_parameter_decl_node>> df_param_decls;
    public:
        dataflow_parameter_decls_node() = default;
    
        explicit dataflow_parameter_decls_node(std::vector<std::unique_ptr<dataflow_parameter_decl_node>>&& decls) noexcept
            : df_param_decls(std::move(decls)) {}
        
        dataflow_parameter_decls_node(const dataflow_parameter_decls_node&) = delete;
        dataflow_parameter_decls_node& operator=(const dataflow_parameter_decls_node&) = delete;
    
        dataflow_parameter_decls_node(dataflow_parameter_decls_node&&) = default;
        dataflow_parameter_decls_node& operator=(dataflow_parameter_decls_node&&) = default;

        void append(std::unique_ptr<dataflow_parameter_decl_node> decl){
            df_param_decls.insert(df_param_decls.begin(), std::move(decl));
        };

        std::vector<std::unique_ptr<dataflow_parameter_decl_node>>& get_df_param_decls() { return df_param_decls; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class physical_dataflow_parameter_decls_node :  public ast_node {
    private:
        std::vector<std::unique_ptr<physical_dataflow_parameter_decl_node>> pdf_param_decls;
    public:
        physical_dataflow_parameter_decls_node() = default;

        explicit physical_dataflow_parameter_decls_node(
            std::vector<std::unique_ptr<physical_dataflow_parameter_decl_node>>&& items
        ) : pdf_param_decls(std::move(items)) {}

        physical_dataflow_parameter_decls_node(const physical_dataflow_parameter_decls_node&) = delete;
        physical_dataflow_parameter_decls_node& operator=(const physical_dataflow_parameter_decls_node&) = delete;
        
        physical_dataflow_parameter_decls_node(physical_dataflow_parameter_decls_node&&) = default;
        physical_dataflow_parameter_decls_node& operator=(physical_dataflow_parameter_decls_node&&) = default;

        void append(std::unique_ptr<physical_dataflow_parameter_decl_node> decl){
            pdf_param_decls.insert(pdf_param_decls.begin(), std::move(decl));
        };

        std::vector<std::unique_ptr<physical_dataflow_parameter_decl_node>>& get_pdf_param_decls() { return pdf_param_decls; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class dataflow_parameter_decl_node : public ast_node {
    private:
        std::unique_ptr<dataflow_type_node> type;
        std::string identifier;
        std::unique_ptr<rhs_assignment_node> assign;
    public:
        dataflow_parameter_decl_node(std::unique_ptr<dataflow_type_node> type, std::string identifier, std::unique_ptr<rhs_assignment_node> assign) :
            type(std::move(type)), identifier(identifier), assign(std::move(assign)) {}

        dataflow_type_node* get_df_type() { return type.get(); }
        std::string get_identifier() { return identifier; }
        rhs_assignment_node* get_rhs() { return assign.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class physical_dataflow_parameter_decl_node : public ast_node {
    private:
        std::unique_ptr<physical_dataflow_parameter_type_node> type;
        std::string identifier;
        std::unique_ptr<rhs_assignment_node> assign;
    public:
        physical_dataflow_parameter_decl_node(std::unique_ptr<physical_dataflow_parameter_type_node> type, std::string identifier, std::unique_ptr<rhs_assignment_node> assign) :
            type(std::move(type)), identifier(identifier), assign(std::move(assign)) {}

        physical_dataflow_parameter_type_node* get_df_type() { return type.get(); }
        std::string get_identifier() { return identifier; }
        rhs_assignment_node* get_rhs() { return assign.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

#endif