#ifndef CHIPS_OVERALL_COLLECTIVE_HPP
#define CHIPS_OVERALL_COLLECTIVE_HPP

//#include "./ChipsADS.hpp"
#include "./chips_ast_classes.hpp"
#include <memory>
#include <string>
#include <utility>
#include <iostream>
#include <optional>

class c_signature_node : public ast_node {
    private:
        std::unique_ptr<c_keywords_node> keywords;
        std::unique_ptr<collective_dataflow_defaulted_decls_node> cdf_defaulted_decls;
        std::string ident1;
        std::string ident2;

    public:
        c_signature_node(std::unique_ptr<c_keywords_node> keywords, std::unique_ptr<collective_dataflow_defaulted_decls_node> cdf_defaulted_decls,
                         std::string ident1, std::string ident2)
                         : keywords(std::move(keywords)), cdf_defaulted_decls(std::move(cdf_defaulted_decls)), ident1(ident1), ident2(ident2) {}

        c_keywords_node* get_keywords() { return keywords.get(); }
        collective_dataflow_defaulted_decls_node* get_collective_dataflow_defaulted_decls() { return cdf_defaulted_decls.get(); }
        std::string get_ident1() { return ident1; }
        std::string get_ident2() { return ident2; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class c_keywords_node : public ast_node {        
    public:
        void accept(chips_visitor& visitor) { visitor.visit(*this); }
};

class spread_node : public c_keywords_node {
    private:
        static constexpr COLLECTIVE_KW kw = SPREAD;

    public:
        spread_node() = default;

        constexpr COLLECTIVE_KW get_keyword() { return kw; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class collect_node : public c_keywords_node {
    private:
        static constexpr COLLECTIVE_KW kw = COLLECT;

    public:
        collect_node() = default;

        constexpr COLLECTIVE_KW get_keyword() { return kw; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class collective_dataflow_defaulted_decls_node : public ast_node {
    private:
        std::vector<std::unique_ptr<collective_dataflow_defaulted_decl_node>> cdf_defaulted_decls;

    public:
        collective_dataflow_defaulted_decls_node() = default;

        explicit collective_dataflow_defaulted_decls_node(
            std::vector<std::unique_ptr<collective_dataflow_defaulted_decl_node>>&& items
        ) : cdf_defaulted_decls(std::move(items)) {}

        collective_dataflow_defaulted_decls_node(const collective_dataflow_defaulted_decls_node&) = delete;
        collective_dataflow_defaulted_decls_node& operator=(const collective_dataflow_defaulted_decls_node&) = delete;

        collective_dataflow_defaulted_decls_node(collective_dataflow_defaulted_decls_node&&) = default;
        collective_dataflow_defaulted_decls_node& operator=(collective_dataflow_defaulted_decls_node&&) = default;

        void append(std::unique_ptr<collective_dataflow_defaulted_decl_node> decl){
            cdf_defaulted_decls.insert(cdf_defaulted_decls.begin(), std::move(decl));
        }

        std::vector<std::unique_ptr<collective_dataflow_defaulted_decl_node>>& get_cdf_defaulted_decls() { return cdf_defaulted_decls; }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
 
};

class collective_dataflow_defaulted_decl_node : public ast_node {
    private:
        std::unique_ptr<dataflow_type_node> type;
        std::string identifier;
        std::unique_ptr<expression_node> expr;

    public:
        collective_dataflow_defaulted_decl_node(std::unique_ptr<dataflow_type_node> type, std::string identifier, std::unique_ptr<expression_node> expr)
            : type(std::move(type)), identifier(identifier), expr(std::move(expr)) {}

        dataflow_type_node* get_df_type() { return type.get(); }
        std::string get_identifier() { return identifier; }
        expression_node* get_expression() { return expr.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class c_statement_node : public ast_node {
    public:
        virtual STATEMENT_TYPE get_type() = 0;
};

class c_statements_node : public ast_node {
    private:
        std::vector<std::unique_ptr<c_statement_node>> statements;

    public:
        c_statements_node() = default;

        explicit c_statements_node(std::vector<std::unique_ptr<c_statement_node>> statements)
            : statements(std::move(statements)) {}

        c_statements_node(const c_statements_node&) = delete;
        c_statements_node& operator=(const c_statements_node&) = delete;

        c_statements_node(c_statements_node&&) = default;
        c_statements_node& operator=(c_statements_node&&) = default;

        std::vector<std::unique_ptr<c_statement_node>>& get_statements() { return statements; }

        void append(std::unique_ptr<c_statement_node> sttmt){
            statements.insert(statements.begin(), std::move(sttmt));
        }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class c_output_node : public ast_node {
    private:
        std::optional<std::string> identifier;
        std::unique_ptr<c_expressions_node> exprs;

    public:
        c_output_node(std::unique_ptr<c_expressions_node> exprs)
            : exprs(std::move(exprs)) {}

        c_output_node(std::string identifier, std::unique_ptr<c_expressions_node> exprs)
            : identifier(identifier), exprs(std::move(exprs)) {}

        std::string get_identifier() { return identifier.value_or("default"); }
        c_expressions_node* get_expressions() { return exprs.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class c_optionnal_outputs_node : public ast_node {
    private:
        std::vector<std::unique_ptr<c_output_node>> outputs;

    public:
        c_optionnal_outputs_node() = default;

        std::vector<std::unique_ptr<c_output_node>>& get_outputs() { return outputs; }

        void append(std::unique_ptr<c_output_node> output){
            outputs.insert(outputs.begin(), std::move(output));
        }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class c_loop_node : public c_statement_node {
    private:
        STATEMENT_TYPE type = LOOP_ST;
        std::string ident1;
        std::unique_ptr<expression_node> loop_expr;
        std::unique_ptr<c_statements_node> stts;

    public:
        c_loop_node(std::string ident1, std::unique_ptr<expression_node> loop_expr, std::unique_ptr<c_statements_node> stts)
            : ident1(ident1), loop_expr(std::move(loop_expr)), stts(std::move(stts)) {}

        STATEMENT_TYPE get_type() override { return type; }
        std::string get_ident1() { return ident1; }
        expression_node* get_loop_expr() { return loop_expr.get(); }
        c_statements_node* get_statements() { return stts.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class c_if_node : public c_statement_node {
    private:
        STATEMENT_TYPE type = IF_ST;
        std::unique_ptr<expression_node> cond;
        std::unique_ptr<c_statements_node> stts;

    public:
        c_if_node(std::unique_ptr<expression_node> cond, std::unique_ptr<c_statements_node> stts)
            : cond(std::move(cond)), stts(std::move(stts)) {}

        STATEMENT_TYPE get_type() override { return type; }
        expression_node* get_condition() { return cond.get(); }
        c_statements_node* get_statements() { return stts.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class c_if_else_node : public c_statement_node {
    private:
        STATEMENT_TYPE type = IFELSE_ST;
        std::unique_ptr<c_if_node> ifnode;
        std::unique_ptr<c_statements_node> elsestts;

    public:
        c_if_else_node(std::unique_ptr<c_if_node> ifnode, std::unique_ptr<c_statements_node> elsestts)
            : ifnode(std::move(ifnode)), elsestts(std::move(elsestts)) {}

        STATEMENT_TYPE get_type() override { return type; }
        c_if_node* get_if_node() { return ifnode.get(); }
        c_statements_node* get_else_node() { return elsestts.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;

};

class c_expressions_node : public ast_node {
    private:
        std::vector<std::unique_ptr<expression_node>> exprs;

    public:
        c_expressions_node() = default;

        explicit c_expressions_node(std::vector<std::unique_ptr<expression_node>>&& exprs) noexcept
            : exprs(std::move(exprs)) {}

        c_expressions_node(const c_expressions_node&) = delete;
        c_expressions_node& operator=(const c_expressions_node&) = delete;

        c_expressions_node(c_expressions_node&&) = default;
        c_expressions_node& operator=(c_expressions_node&&) = default;

        const std::vector<std::unique_ptr<expression_node>>& get_expressions() const { return exprs; }

        void append(std::unique_ptr<expression_node> expr){
            exprs.insert(exprs.begin(), std::move(expr));
        }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};



class collective_dataflow_full_declaration_node : public c_statement_node {
    private:
        STATEMENT_TYPE s_type = DF_ASSIGN_ST;
        std::unique_ptr<dataflow_type_node> type;
        std::string identifier;
        std::unique_ptr<collective_rhs_assignment_node> rhs;

    public:
        collective_dataflow_full_declaration_node(std::unique_ptr<dataflow_type_node> type, std::string identifier, std::unique_ptr<collective_rhs_assignment_node> rhs)
            : type(std::move(type)), identifier(identifier), rhs(std::move(rhs)) {}

        STATEMENT_TYPE get_type() override { return s_type; }
        dataflow_type_node* get_df_type() { return type.get(); }
        std::string get_identifier() { return identifier; }
        collective_rhs_assignment_node* get_rhs() { return rhs.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class collective_rhs_assignment_node : public ast_node {
    private:
        std::unique_ptr<expression_node> expr;

    public:
        collective_rhs_assignment_node() = default;

        collective_rhs_assignment_node(std::unique_ptr<expression_node> expr)
            : expr(std::move(expr)) {}

        expression_node* get_expression() { return expr.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;

};

class c_variable_assignment_node : public c_statement_node {
    private:
        STATEMENT_TYPE type = ASSI_ST;
        std::string identifier;
        std::unique_ptr<suffixes_node> suff;
        std::unique_ptr<expression_node> expr;

    public:
        c_variable_assignment_node(std::string identifier, std::unique_ptr<suffixes_node> suff, std::unique_ptr<expression_node> expr)
            : identifier(identifier), suff(std::move(suff)), expr(std::move(expr)) {}

        STATEMENT_TYPE get_type() override { return type; }
        std::string get_identifier() { return identifier; }
        suffixes_node* get_suffixes() { return suff.get(); }
        expression_node* get_expression() { return expr.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;
};

class c_context_variable_assignment_node : public c_statement_node {
    private:
        STATEMENT_TYPE type = ASSI_ST;
        std::string identifier;
        std::unique_ptr<suffixes_node> suff;
        std::unique_ptr<expression_node> expr;

    public:
        c_context_variable_assignment_node(std::string identifier, std::unique_ptr<suffixes_node> suff, std::unique_ptr<expression_node> expr)
            : identifier(identifier), suff(std::move(suff)), expr(std::move(expr)) {}

        STATEMENT_TYPE get_type() override { return type; }
        std::string get_identifier() { return identifier; }
        suffixes_node* get_suffixes() { return suff.get(); }
        expression_node* get_expression() { return expr.get(); }

        void accept(chips_visitor& visitor) { visitor.visit(*this); }

        virtual void hello() override;

};



#endif