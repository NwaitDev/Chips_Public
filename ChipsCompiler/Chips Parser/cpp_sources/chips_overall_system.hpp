#ifndef CHIPS_OVERALL_SYSYTEM_HPP
#define CHIPS_OVERALL_SYSYTEM_HPP

//#include "./ChipsADS.hpp"
#include "./chips_ast_classes.hpp"
#include <memory>
#include <string>
#include <utility>
#include <iostream>

class s_statement_node : public ast_node {
    public:
        virtual STATEMENT_TYPE get_type() = 0;
};

class s_statements_node : public ast_node {
    private:
        std::vector<std::unique_ptr<s_statement_node>> statements;

    public:
        s_statements_node() = default;

        explicit s_statements_node(std::vector<std::unique_ptr<s_statement_node>>&& sttmt) noexcept
            : statements(std::move(sttmt)) {}

        s_statements_node(const s_statements_node&) = delete;
        s_statements_node& operator=(const s_statements_node&) = delete;

        s_statements_node(s_statements_node&&) = default;
        s_statements_node& operator=(s_statements_node&&) = default;

        std::vector<std::unique_ptr<s_statement_node>>& get_statements() { return statements; }

        void append(std::unique_ptr<s_statement_node> sttmt){
            statements.insert(statements.begin(), std::move(sttmt));
        }

        void accept(chips_visitor& visitor){}

        virtual void hello() override;
};

class s_loop_node : public s_statement_node {
    private:
        STATEMENT_TYPE type = LOOP_ST;
        std::string ident1;
        std::unique_ptr<expression_node> loop_expr;
        std::unique_ptr<s_statements_node> stts;

    public:
        s_loop_node(std::string ident1, std::unique_ptr<expression_node> loop_expr, std::unique_ptr<s_statements_node> stts)
            : ident1(ident1), loop_expr(std::move(loop_expr)), stts(std::move(stts)) {}

        STATEMENT_TYPE get_type() override { return type; }
        std::string get_identifier() { return ident1; }
        expression_node* get_loop_expr() { return loop_expr.get();}
        s_statements_node* get_statements() { return stts.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};

class s_if_node : public s_statement_node {
    private:
        STATEMENT_TYPE type = IF_ST;
        std::unique_ptr<expression_node> cond;
        std::unique_ptr<s_statements_node> stts;

    public:
        s_if_node(std::unique_ptr<expression_node> cond, std::unique_ptr<s_statements_node> stts)
            : cond(std::move(cond)), stts(std::move(stts)) {}

        STATEMENT_TYPE get_type() override { return type; }
        expression_node* get_condition() { return cond.get(); }
        s_statements_node* get_statements() { return stts.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};

class s_if_else_node : public s_statement_node {
    private:
        STATEMENT_TYPE type = IFELSE_ST;
        std::unique_ptr<s_if_node> ifnode;
        std::unique_ptr<s_statements_node> elsestts;

    public:
        s_if_else_node(std::unique_ptr<s_if_node> ifnode, std::unique_ptr<s_statements_node> elsestts)
            : ifnode(std::move(ifnode)), elsestts(std::move(elsestts)) {}

        STATEMENT_TYPE get_type() override { return type; }
        s_if_node* get_if_node() { return ifnode.get(); }
        s_statements_node* get_else_node() { return elsestts.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};

class functionnal_block_instanciation_node : public s_statement_node {
    private:
        STATEMENT_TYPE type = S_FUNC_BLOCK_INST_ST;
        std::string ident1;
        std::unique_ptr<suffixes_node> suff;
        std::string ident2;

    public:
        functionnal_block_instanciation_node(std::string ident1, std::unique_ptr<suffixes_node> suff, std::string ident2)
            : ident1(ident1), suff(std::move(suff)), ident2(ident2) {}

        STATEMENT_TYPE get_type() override { return type; }
        std::string get_ident1() { return ident1; }
        suffixes_node* get_suffixes() { return suff.get(); }
        std::string get_ident2() { return ident2; }

        void accept(chips_visitor& visitor) {}
        virtual void hello() override;
};

class plugging_node : public s_statement_node {
    private:
        STATEMENT_TYPE type = S_EXPR_PLUG_ST;
        std::unique_ptr<block_node> block;
        std::string identifier;
        std::unique_ptr<suffixes_node> suff;
        std::unique_ptr<expression_node> expr;

    public:
        plugging_node(std::unique_ptr<block_node> block, std::string identifier, std::unique_ptr<suffixes_node> suff, std::unique_ptr<expression_node> expr)
            : block(std::move(block)), identifier(identifier), suff(std::move(suff)), expr(std::move(expr)) {}

        plugging_node(std::unique_ptr<block_node> block, std::string identifier)
            : block(std::move(block)), identifier(identifier) {}

        STATEMENT_TYPE get_type() override { return type; }
        block_node* get_block() { return block.get(); }
        std::string get_identifier() { return identifier; }
        suffixes_node* get_suffixes() { return suff.get(); }
        expression_node* get_expression() { return expr.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};

class link_node : public s_statement_node {
    private:
        STATEMENT_TYPE type = S_LINK_ST;
        std::string lk_src;
        std::unique_ptr<suffixes_node> suff_src;
        std::string lk_target;
        std::unique_ptr<suffixes_node> suff_target;

    public:
        link_node(std::string lk_src, std::unique_ptr<suffixes_node> suff_src, std::string lk_target, std::unique_ptr<suffixes_node> suff_target)
            : lk_src(lk_src), suff_src(std::move(suff_src)), lk_target(lk_target), suff_target(std::move(suff_target)) {}

        STATEMENT_TYPE get_type() override { return type; }
        std::string get_source() { return lk_src; }
        suffixes_node* get_suffixes_source() { return suff_src.get(); }
        std::string get_target() { return lk_target; }
        suffixes_node* get_suffixes_target() { return suff_target.get(); }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;
};

class implements_node : public s_statement_node {
    private:
        STATEMENT_TYPE type = S_IMPLEMENTS_ST;
        std::string ident1;
        std::unique_ptr<suffixes_node> suffixes1;
        std::string ident2;
        std::unique_ptr<suffixes_node> suffixes2;
        std::string ident3;

    public:
        implements_node(std::string ident1, std::unique_ptr<suffixes_node> suffixes1, std::string ident2, std::unique_ptr<suffixes_node> suffixes2, std::string ident3)
            : ident1(ident1), suffixes1(std::move(suffixes1)), ident2(ident2), suffixes2(std::move(suffixes2)), ident3(ident3) {}

        STATEMENT_TYPE get_type() override { return type; }
        std::string get_ident1() { return ident1; }
        suffixes_node* get_suffixes1() { return suffixes1.get(); }
        std::string get_ident2() { return ident2; }
        suffixes_node* get_suffixes2() { return suffixes2.get(); }
        std::string get_ident3() { return ident3; }

        void accept(chips_visitor& visitor) {}

        virtual void hello() override;

};

#endif 