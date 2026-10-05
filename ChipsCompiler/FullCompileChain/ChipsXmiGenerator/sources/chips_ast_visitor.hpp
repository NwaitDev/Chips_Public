#include "ast_node_definitions.hpp"

using namespace chips;

class chips_ast_visitor {

    void visit(with_section);

    void visit(init_section);

    void visit(then_section);
	
	void visit(collectiveops_section);
    
	void visit(accumulator_definition);

	void visit(object_definition);
	
	void visit(logical_definition);

    void visit(physical_definition);
 
 
    void visit(channeled_output);
 
    void visit(default_output);
 
    void visit(target_output);

    void visit(collective_function_definition);

    template<dataflow_kind dfk, dataflow_type dft>
    void visit(function_parameter<dfk,dft>);
    
    template<dataflow_type dft>
    void visit(collective_parameter<dft>);
    
    template<dataflow_kind dfk, dataflow_type dft>
    void visit(function_output<dfk,dft>);

    void visit(system_variable_block_expression<block_type::LOGICAL>);
 
    void visit(system_variable_block_expression<block_type::PHYSICAL>);
 
	void visit(system_variable_block_expression<block_type::OBJECT>);

    template<dataflow_kind dfk, dataflow_type dft>
    void visit(eater<dfk,dft>);

    template<dataflow_kind dfk, dataflow_type dft>
    void visit(feeder_block_expression<dfk,dft>);

    void visit(channel_eater);
 
    void visit(channel_feeder);

    template<dataflow_kind dfk, dataflow_type dft>
    void visit(collective_cast<dfk,dft>);

    template<dataflow_type dft, expression_env expenv> 
	void visit(direct<dft,expenv>);

    template<dataflow_type dft, expression_env expenv> 
	void visit(class function<dft,expenv>);

    
    template <dataflow_type dft, expression_env expenv>
    void visit(plus<dft,expenv>);

    /**
    * Concrete class
    * Node of the AST that represents - (minus) operator
    */
    template <dataflow_type dft, expression_env expenv>
    class minus : public rvalue<dft, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type m_left_operand;
        operand_type m_right_operand;

    public:
        minus(operand_type left_operand, operand_type right_operand)
            : m_left_operand((left_operand)), m_right_operand((right_operand)) {}

        operand_type get_lhs() const { return m_left_operand; }
        operand_type get_rhs() const { return m_right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented minus.accept(visitor&) error.");
        }
    };

    /**
    * Concrete class
    * Node of the AST that represents * (multiplication) operator
    */
    template <dataflow_type dft, expression_env expenv>
    class mult : public rvalue<dft, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type m_left_operand;
        operand_type m_right_operand;

    public:
        mult(operand_type left_operand, operand_type right_operand)
            : m_left_operand((left_operand)), m_right_operand((right_operand)) {}

        operand_type get_lhs() { return m_left_operand; }
        operand_type get_rhs() { return m_right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented mult.accept(visitor&) error.");
        }
    };

    /**
    * Concrete class
    * Node of the AST that represents / (division) operator
    */
    template <dataflow_type dft, expression_env expenv>
    class div : public rvalue<dft, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type m_left_operand;
        operand_type m_right_operand;

    public:
        div(operand_type left_operand, operand_type right_operand)
            : m_left_operand((left_operand)), m_right_operand((right_operand)) {}

        operand_type get_lhs() { return m_left_operand; }
        operand_type get_rhs() { return m_right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented div.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents % (modulo) operator
    */
    template <expression_env expenv>
    class mod : public rvalue<dataflow_type::INT, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dataflow_type::INT, expenv>::type;
        operand_type m_left_operand;
        operand_type m_right_operand;

    public:
        mod(operand_type left_operand, operand_type right_operand)
            : m_left_operand((left_operand)), m_right_operand((right_operand)) {}

        operand_type get_lhs() { return m_left_operand; }
        operand_type get_rhs() { return m_right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented mod.accept(visitor&) error.");
        }
    };

    /**
    * Concrete class
    * Node of the AST that represents the type casting operation
    */
    template <dataflow_type dft, expression_env expenv>
    class cast_as : public rvalue<dft, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type numeric;

    public:
        cast_as(operand_type numeric)
            : numeric((numeric)) {}

        operand_type get_cast() { return numeric; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented cast_as.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents > (greater than) operator
    */
    template <expression_env expenv, dataflow_type dft>
    class gt : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type m_left_operand;
        operand_type m_right_operand;

    public:
        gt(operand_type left_operand, operand_type right_operand)
            : m_left_operand((left_operand)), m_right_operand((right_operand)) {}

        operand_type get_lhs() { return m_left_operand; }
        operand_type get_rhs() { return m_right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented gt.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents < (lower than) operator
    */
    template <expression_env expenv, dataflow_type dft>
    class lt : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type left_operand;
        operand_type right_operand;

    public:
        lt(operand_type left_operand, operand_type right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        operand_type get_lhs() { return left_operand; }
        operand_type get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented lt.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents the >= (greater or equal) operator
    */
    template <expression_env expenv, dataflow_type dft>
    class geq : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type left_operand;
        operand_type right_operand;

    public:
        geq(operand_type left_operand, operand_type right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        operand_type get_lhs() { return left_operand; }
        operand_type get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented geq.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents <= (lower or equal) operator
    */
    template <expression_env expenv, dataflow_type dft>
    class leq : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type left_operand;
        operand_type right_operand;

    public:
        leq(operand_type left_operand, operand_type right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        operand_type get_lhs() { return left_operand; }
        operand_type get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented leq.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents || (or) operator
    */
    template <expression_env expenv>
    class or_operator : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> left_operand;
        rvalue<dataflow_type::BOOL, expenv> right_operand;

    public:
        or_operator(rvalue<dataflow_type::BOOL, expenv> left_operand, rvalue<dataflow_type::BOOL, expenv> right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        rvalue<dataflow_type::BOOL, expenv> *get_lhs() { return left_operand; }
        rvalue<dataflow_type::BOOL, expenv> *get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented or_operator.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents && (and) operator
    */
    template <expression_env expenv>
    class and_operator : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> left_operand;
        rvalue<dataflow_type::BOOL, expenv> right_operand;

    public:
        and_operator(rvalue<dataflow_type::BOOL, expenv> left_operand, rvalue<dataflow_type::BOOL, expenv> right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        rvalue<dataflow_type::BOOL, expenv> *get_lhs() { return left_operand; }
        rvalue<dataflow_type::BOOL, expenv> *get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented and_operator.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents ! (not) operator
    */
    template <expression_env expenv>
    class not_operator : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        rvalue<dataflow_type::BOOL, expenv> operand;

    public:
        not_operator(rvalue<dataflow_type::BOOL, expenv> operand)
            : operand(operand) {}

        rvalue<dataflow_type::BOOL, expenv> *get_lhs() { return operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented not_operator.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents the unary minus operator
    */
    template <dataflow_type dft, expression_env expenv>
    class uminus_operator : public rvalue<dft, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstNumericType<dft, expenv>::type;
        operand_type operand;

    public:
        uminus_operator(operand_type operand)
            : operand(operand) {}

        operand_type get_rhs() { return operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented uminus_operator.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents ==
    */
    template <dataflow_type dft, expression_env expenv>
    class eq : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type;
        operand_type left_operand;
        operand_type right_operand;

    public:
        eq(operand_type left_operand, operand_type right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        operand_type get_lhs() { return left_operand; }
        operand_type get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented eq.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents != (not equal) operator
    */
    template <dataflow_type dft, expression_env expenv>
    class neq : public rvalue<dataflow_type::BOOL, expenv>, public ast_node
    {
    private:
        using operand_type = typename ChipsOperandToAstType<dft, expenv>::type;
        operand_type left_operand;
        operand_type right_operand;

    public:
        neq(operand_type left_operand, operand_type right_operand)
            : left_operand((left_operand)), right_operand((right_operand)) {}

        operand_type get_lhs() { return left_operand; }
        operand_type get_rhs() { return right_operand; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented neq.accept(visitor&) error.");
        }

    };

    /**
    * Concrete class
    * Node of the AST that represents an expression
    * referencing a dataflow variable
    */
    template <dataflow_type dft, expression_env expenv>
    class variable_expression : public rvalue<dft, expenv>, public lvalue<dft, expenv>, public ast_node
    {
    private:
        variable<expenv> *m_variable;
        std::vector<int_rvalue_expression_variant<expenv>> m_index = {};

    public:
        variable_expression(variable<expenv> *variable, std::vector<int_rvalue_expression_variant<expenv>> index)
            : m_variable(variable), m_index(index) {}

        variable_expression(variable<expenv> *variable)
            : m_variable(variable) {}

        variable<expenv> *get_variable() { return m_variable; }
        std::vector<int_rvalue_expression_variant<expenv>>& get_index() { return m_index; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented variable_expression.accept(visitor&) error.");
        }

    };

    template <dataflow_type dft, expression_env expenv>
    class variable_contextual_expression : public variable_expression<dft, expenv>, public ast_node
    {
    public:
        variable_contextual_expression(variable<expenv> *variable, std::vector<int_rvalue_expression_variant<expenv>> index)
            : variable_expression<dft, expenv>(variable, index) {}

        variable_contextual_expression(variable<expenv> *variable)
            : variable_expression<dft, expenv>(variable) {}

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented variable_contextual_expression.accept(visitor&) error.");
        }
    };

    class input : public rvalue<dataflow_type::INT, expression_env::COLLECTIVE>,
          public rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>,
          public rvalue<dataflow_type::BOOL, expression_env::COLLECTIVE>,
          public ast_node {
        
    public:
        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented input.accept(visitor&) error.");
        }
    };

    class stop
        : public rvalue<dataflow_type::INT, expression_env::COLLECTIVE>,
          public rvalue<dataflow_type::FLOAT, expression_env::COLLECTIVE>,
          public rvalue<dataflow_type::BOOL, expression_env::COLLECTIVE>,
          public ast_node {

    public:
        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented stop.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the Chips AST that holds all the definitions
     * of Chips components (Logical, Physical and Objects)
     */
    class preamble_section_node : public ast_node
    {
        public:
        std::vector<definition_variant> m_definitions;

        preamble_section_node(int line, int column, const std::vector<definition_variant>& defs): 
        m_definitions(defs), ast_node(line, column){}

        inline std::vector<definition_variant>& get_definitions(){
            return m_definitions;
        }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented preamble_section_node.accept(visitor&) error.");
        }
        
    };

    /**
     * Concrete class
     * Node of the Chips AST that holds the description
     * of a complete system (an assembly of Chips components)
     */
    class system_section_node : public ast_node {
        public:
        std::vector<system_statement_variant> m_statements;

        system_section_node(int line, int column, const std::vector<system_statement_variant>& stts): 
        m_statements(stts), ast_node(line, column){}

        inline std::vector<system_statement_variant>& get_statements(){
            return m_statements;
        }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented system_section_node.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Root node for a Chips program in Chips AST
     */
    class program_node : public ast_node {
        public:
        std::string m_filename;
        preamble_section_node m_preamble;
        system_section_node m_system;

        program_node(int line, int column, const std::string& filename, preamble_section_node preamble, system_section_node system) :
        ast_node(line, column), m_filename(filename),m_preamble(preamble), m_system(system) {}

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented program_node.accept(visitor&) error.");
        }

        inline const preamble_section_node &get_preamble() {return m_preamble;};
        inline const system_section_node& get_system() {return m_system;};
    };

    /**
     * Abstract class
     * Node of the AST that represents a statement in any
     * Chips code environment.
     */
    template<statement_env stenv, recurring_statement recstt> class statement : public virtual ast_node {
        public:
        statement(int line, int column) : ast_node(line, column){}
    };

    
    // what is this?
    // template<recurring_statement recstt> 
    // class statement<statement_env::DEFINITION, recstt> : public statement<statement_env::NODE, recstt> {};
    
    /**
     * Concrete class
     * Node of the AST representing a dataflow declarations in any context.
     * Only treating generic dataflows, other kinds of variables
     * (functional blocks, nodes, channels and contextuals)
     * have their own dedicated nodes
     */
    template<dataflow_type dft, statement_env stenv> class dataflow_declaration : public statement<stenv, recurring_statement::DECLARATION> {
        public:
        using df_variable_type = typename SttEnvToVariableKind<dft, stenv>::type;
        df_variable_type m_variable;

        dataflow_declaration(df_variable_type variable) : 
        m_variable(variable) {};

        inline df_variable_type get_variable() { return m_variable; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented dataflow_declaration.accept(visitor&) error.");
        }
        
    };

    /**
     * Concrete class
     * Node of the AST representing a dataflow assignements in any context
     * Only treating generic dataflows, other kinds of variables
     * (functional blocks, nodes, channels and contextuals)
     * have their own dedicated nodes
     */
    template<dataflow_type dft, statement_env stenv> 
    class dataflow_assignment : public statement<stenv, recurring_statement::ASSIGNMENT> {
        public:
        static constexpr expression_env expr_env = SttEnvToExpEnv<stenv>::value;
        lvalue<dft, expr_env> *m_lvalue;
        rvalue<dft, expr_env> *m_rvalue;

        dataflow_assignment(lvalue<dft, expr_env> *lhs, rvalue<dft, expr_env> *rhs)
            : m_lvalue(lhs), m_rvalue(rhs) {}

        lvalue<dft, expr_env> *get_lhs() { return m_lvalue; }
        rvalue<dft, expr_env> *get_rhs() { return m_rvalue; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented dataflow_assignment.accept(visitor&) error.");
        }
        
    };

    /**
     * Concrete class
     * Node of the AST that represents the ordered list of the statements
     * that compose the code executed when the condition of an if_statement
     * is evaluated as true
     */
    template<statement_env stenv> 
    class if_section : public ast_node {
        public:
        using statement_type = typename SttEnvToSttVariant<stenv>::type;
        std::vector<statement_type> m_if_statements;
        
        if_section(int line, int column, const std::vector<statement_type>& stts):
        ast_node(line, column), m_if_statements(stts){};

        std::vector<statement_type>& get_statements() { return m_if_statements; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented if_section.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents the ordered list of the statements
     * that compose the code executed when the condition of an if_else_statement
     * is evaluated as false
     */
    template<statement_env stenv> 
    class else_section : public ast_node {
        public:
        using statement_type = typename SttEnvToSttVariant<stenv>::type;
        std::vector<statement_type> m_else_statements;

        else_section(int line, int column, const std::vector<statement_type>& stts):
        ast_node(line, column), m_else_statements(stts){};

        std::vector<statement_type>& get_statements() { return m_else_statements; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented else_section.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents an if statement.
     * if (bool rvalue) { if_section }
     */
    template<statement_env stenv>
    class if_statement : public statement<stenv, recurring_statement::IF> {
        public:
        static constexpr expression_env expr_env = SttEnvToExpEnv<stenv>::value;
        bool_rvalue_expression_variant<expr_env> m_condition;
        if_section<stenv> m_if_section;

        if_statement(int line, int column, bool_rvalue_expression_variant<expr_env> condition, if_section<stenv> if_sec) :
        statement<stenv, recurring_statement::IF>(line, column), m_condition(condition), m_if_section(if_sec) {}

        bool_rvalue_expression_variant<expr_env>& get_condition(){ return m_condition; }
        if_section<stenv>& get_if_section() { return m_if_section; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented if_statement.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents an if_else statement
     * if (bool rvalue) { if_section } else { else_section }
     */
    template<statement_env stenv>
    class if_else_statement : public if_statement<stenv> {
        public:
        static constexpr expression_env expr_env = SttEnvToExpEnv<stenv>::value;
        else_section<stenv> m_else_section;

        if_else_statement(int line, int column, bool_rvalue_expression_variant<expr_env> condition,
                           if_section<stenv> if_sec, else_section<stenv> else_sec) :
        if_statement<stenv>(line, column, condition, if_sec), m_else_section(else_sec) {}

        else_section<stenv>& get_else_section() { return m_else_section; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented if_else_statement.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents a foreach statement
     * for iterator in iterable { statements }
     * Generic version only suitable for iterating over dataflow
     * variables
     */
    template<statement_env stenv, dataflow_type dft>
    class foreach_statement : public statement<stenv, recurring_statement::FOREACH> {
        public:
        using statement_type = typename SttEnvToSttVariant<stenv>::type;
        static constexpr expression_env expenv = SttEnvToExpEnv<stenv>::value;
        dataflow_declaration<dft, stenv> m_iterator;
        primitive_iterable_variant<expenv> m_iterable_expr;
        std::vector<statement_type> m_statements;

        foreach_statement(int line, int column, dataflow_declaration<dft, stenv> iterator,
                           primitive_iterable_variant<expenv> iterable_expr, const std::vector<statement_type>& stts) :
        statement<stenv, recurring_statement::FOREACH>(line, column), m_iterator(iterator), m_iterable_expr(iterable_expr), m_statements(stts) {}

        dataflow_declaration<dft, stenv>& get_iterator() { return m_iterator; }
        primitive_iterable_variant<expenv>& get_iterable() { return m_iterable_expr; }
        std::vector<statement_type>& get_statements() { return m_statements; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented foreach_statement.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents a foreach statement
     * for iterator in iterable { statements }
     * System specific version only suitable for iterating
     * over components variables (logical, physical or objects)
     */
    template<block_type bt>
    class block_foreach_statement : public statement<statement_env::SYSTEM, recurring_statement::FOREACH> {
        public:
        block_declaration<bt> m_iterator;
        system_variable_block_expression<bt> m_iterable_expression;
        std::vector<system_statement_variant> m_statements;

        block_foreach_statement(int line, int column, block_declaration<bt> iterator,
                                 system_variable_block_expression<bt> iterable_expression, const std::vector<system_statement_variant>& stts) :
        statement<statement_env::SYSTEM, recurring_statement::FOREACH>(line, column), m_iterator(iterator), m_iterable_expression(iterable_expression), m_statements(stts) {}

        block_declaration<bt>& get_iterator() { return m_iterator; }
        system_variable_block_expression<bt>& get_iterable() { return m_iterable_expression; }
        std::vector<system_statement_variant>& get_statements() { return m_statements; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented block_foreach_statement.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents the declaration
     * of a component variable (object, physical or logical)
     */
    template<block_type bt>
    class block_declaration : public statement<statement_env::SYSTEM, recurring_statement::DECLARATION> {
        public:
        using block_definition_t = typename BlockTypeToBlockDef<bt>::type;
        using block_variable_t = typename BlockTypeToBlockVariable<bt>::type;

        block_definition_t* m_defintion;
        block_variable_t m_variable;

        block_declaration(int line, int column, block_definition_t* definition, block_variable_t variable) :
        statement<statement_env::SYSTEM, recurring_statement::DECLARATION>(line, column), m_defintion(definition), m_variable(variable) {}

        void set_variable(block_variable_t var) { m_variable = var; }
        void set_definition(block_definition_t* def) { m_defintion = def; }
        block_variable_t get_variable() { return m_variable; }
        block_definition_t* get_definition() { return m_defintion; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented block_declaration.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents the connection of
     * a channel output of a component to a channel input
     * of another component.
     * Such statement should assert that :
     * - channel types are compatibles
     * - connected channels inputs and outputs are not already
     *   connected
     */
    class channel_plugging : public statement<statement_env::SYSTEM, recurring_statement::PLUGGING> {
        public:
        channel_eater* m_eater;
        channel_feeder* m_feeder;

        channel_plugging(int line, int column, channel_eater* eat, channel_feeder* feed) :
        ast_node(line, column),
        statement<statement_env::SYSTEM, recurring_statement::PLUGGING>(line, column), m_eater(eat), m_feeder(feed) {}

        void set_eater(channel_eater* eat) { m_eater = eat; }
        channel_eater* get_eater() { return m_eater; }

        void set_feeder(channel_feeder* feed) { m_feeder = feed; }
        channel_feeder* get_feeder() { return m_feeder; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented channel_plugging.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents the connection of
     * a component dataflow output to a component dataflow
     * parameter.
     * Such statement should assert that
     * connected inputs and outputs are not already connected
     * (unless a collective_cast node is used)
     */
    template<dataflow_kind dfk, dataflow_type dft>
    class feeding_statement : public statement<statement_env::SYSTEM, recurring_statement::FEEDING> {
        public:
        eater<dfk, dft> m_eater;
        feeder<dfk, dft>* m_feeder = nullptr;

        feeding_statement(int line, int column, eater<dfk, dft> eat, feeder<dfk, dft>* feed) :
        statement<statement_env::SYSTEM, recurring_statement::FEEDING>(line, column), m_eater(eat), m_feeder(feed) {}

        eater<dfk, dft>& get_eater() { return m_eater; }
        feeder<dfk, dft>* get_feeder() { return m_feeder; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented feeding_statement.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents the physical
     * dependency of two objects or of a node to a physical block
     * using the following syntax :
     * link linkable to support;
     */
    class linking_statement : public statement<statement_env::SYSTEM, recurring_statement::LINKING> {
        public:
        linkable* m_linked_component;
        support* m_support_node;

        linking_statement(int line, int column, linkable* linked_component, support* support_node) :
        ast_node(line, column), statement<statement_env::SYSTEM, recurring_statement::LINKING>(line, column), m_linked_component(linked_component), m_support_node(support_node) {}

        linkable* get_linkable() { return m_linked_component; }
        support* get_support() { return m_support_node; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented linking_statement.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents the declaration
     * of a contextual or of a channel in a with section
     */
    template<node_element ne>
    class node_element_declaration : public statement<statement_env::NODE, recurring_statement::DECLARATION> {
        public:
        using node_variable_t = typename NodeElemToNodeVariable<ne>::type;
        node_variable_t m_variable_type;
        std::string m_declared_name;

        node_element_declaration(int line, int column, node_variable_t type, std::string vname) :
        statement<statement_env::NODE, recurring_statement::DECLARATION>(line, column), m_variable_type(type), m_declared_name(vname) {}

        node_variable_t get_variable() { return m_variable_type; }

        std::string get_name() { return m_declared_name; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented node_element_declaration.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents an array of elements
     * that can be instanciated in the parametering 
     * expression environment
     */
    template<expression_env expenv> 
    class array : public ast_node {
        public:
        std::vector<int_rvalue_expression_variant<expenv>> m_dimensions;

        inline std::vector<int_rvalue_expression_variant<expenv>>& get_dimensions() { return m_dimensions; }

        array(int line,  int column, const std::vector<int_rvalue_expression_variant<expenv>>& vec):
        ast_node(line, column), m_dimensions(vec){}

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented array.accept(visitor&) error.");
        }
    };

    /**
     * Abstract class
     * Node of the AST that represents a variable of any kind.
     * In chips, each variable is considered as a (dynamic) array.
     * By default, variables are arrays of dimension 1.
     * When declared with a [integer expression]+ suffix,
     * it is of the given dimension(s).
     */
    template<expression_env expenv> 
    class variable : public array<expenv> {
        public:
        std::string m_name;

        variable(int line, int column, const std::string& name):
        array<expenv>(line,column,
            std::vector<int_rvalue_expression_variant<expenv>>(direct<dataflow_type::INT, expenv>(1))
        ), m_name(name) {};

        variable(int line, int column, const std::string& name, std::vector<int_rvalue_expression_variant<expenv>> dims) :
        array<expenv>(line,column,dims), m_name(name) {};

        inline const std::string& get_name() {return m_name;}

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented array.accept(visitor&) error.");
        }
    };

    /**
     * Abstract class
     * Node of the AST that represents a variable that
     * is manipulated inside a functional block or to
     * initialize other variables in nodes
     * (with/init/then sections)
     * A variable of this kind is NOT contextual
     */
    class primitive_variable : public variable<chips::expression_env::PRIMITIVE>
    {
        public:
            primitive_variable(int line, int column, const std::string& name, std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims)
                : variable(line,column,name,dims){}
    };

    /**
     * Concrete class
     * Node of the AST that represents a variable that
     * is manipulated inside a functional block or to
     * initialize other variables in nodes
     * (it is currently the only specialization of
     * the primitive_variable class)
     */
    template<dataflow_type dft> 
    class dataflow_primitive_variable : public primitive_variable {
        public:
        dataflow_declaration<dft, statement_env::DEFINITION>* m_declaration = nullptr;

        dataflow_primitive_variable(int line, int column, const std::string& name,
                                     std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims) :
        primitive_variable(line, column, name, dims) {}

        dataflow_primitive_variable(int line, int column, const std::string& name,
                                     dataflow_declaration<dft, statement_env::DEFINITION>* decl,
                                     std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims) :
        primitive_variable(line, column, name, dims), m_declaration(decl) {}

        inline void set_declaration(dataflow_declaration<dft, statement_env::DEFINITION>* decl_ptr) { m_declaration = decl_ptr; }
        inline dataflow_declaration<dft, statement_env::DEFINITION>* get_declaration() { return m_declaration; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented dataflow_primitive_variable.accept(visitor&) error.");
        }
    };

    /**
     * Abstract class
     * Node of the AST that represents the kind of 
     * variables that can only be specified inside
     * the with section of a Node (i.e. Physical or Object)
     */
    class node_variable : public variable<expression_env::PRIMITIVE> {
        public:
        node_variable(int line, int column, const std::string& name,
                      std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims) :
        variable(line, column, name, dims) {}

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented node_variable.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents a contextual
     * variable.
     */
    template<dataflow_type dft> 
    class contextual_variable : public node_variable {
        public:
        using node_element_declaration_type = typename DfTypeToContextualDeclType<dft>::type;
        node_element_declaration_type* m_declaration = nullptr;

        contextual_variable(int line, int column, const std::string& identifier,
                             std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims) :
        node_variable(line, column, identifier, dims) {}

        contextual_variable(int line, int column, const std::string& identifier,
                             node_element_declaration_type* decl,
                             std::vector<int_rvalue_expression_variant<expression_env::PRIMITIVE>> dims) :
        node_variable(line, column, identifier, dims), m_declaration(decl) {}

        inline void set_declaration(node_element_declaration_type* decl_ptr) { m_declaration = decl_ptr; }
        inline node_element_declaration_type* get_declaration() { return m_declaration; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented contextual_variable.accept(visitor&) error.");
        }
    };

    /**
     * Abstract class
     * Node of the AST that represents a variable that
     * is used in the body/parameters or outputs of a 
     * collective primitive.
     */
    class collective_variable : public variable<expression_env::COLLECTIVE> {
        public:
        collective_variable(int line, int column, const std::string& name,
                             std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> dims) :
        variable(line, column, name, dims) {}

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented collective_variable.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents a variable that
     * is used in the body/parameters or outputs of a 
     * collective primitive. 
     * (it is currently the only specialization of
     * the collective_variable class)
     */
    template<dataflow_type dft> 
    class dataflow_collective_variable : public collective_variable {
        public:
        dataflow_declaration<dft, statement_env::COLLECTIVE>* m_declaration = nullptr;

        dataflow_collective_variable(int line, int column, const std::string& name,
                                      std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> dims) :
        collective_variable(line, column, name, dims) {}

        dataflow_collective_variable(int line, int column, const std::string& name,
                                      dataflow_declaration<dft, statement_env::COLLECTIVE>* decl,
                                      std::vector<int_rvalue_expression_variant<expression_env::COLLECTIVE>> dims) :
        collective_variable(line, column, name, dims), m_declaration(decl) {}

        inline void set_declaration(dataflow_declaration<dft, statement_env::COLLECTIVE>* decl_ptr) { m_declaration = decl_ptr; }
        inline dataflow_declaration<dft, statement_env::COLLECTIVE>* get_declaration() { return m_declaration; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented dataflow_collective_variable.accept(visitor&) error.");
        }
    };

    /**
     * Abstract class
     * Node of the AST that represents a variable
     * that can be used in the system section.
     */
    class system_variable : public variable<expression_env::SYSTEM> {
        public:
        system_variable(int line, int column, const std::string& name,
                         std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dims) :
        variable(line, column, name, dims) {}

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented system_variable.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents a component
     * of the model that was instantiated from a
     * former definition (Object/Logical/physical)
     */
    template<block_type bt> 
    class block_variable : public system_variable {
        public:
        block_declaration<bt>* m_declaration = nullptr;

        block_variable(int line, int column, const std::string& name,
                       std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dims) :
        system_variable(line, column, name, dims) {}

        block_variable(int line, int column, const std::string& name,
                       block_declaration<bt>* declaration,
                       std::vector<int_rvalue_expression_variant<expression_env::SYSTEM>> dims) :
        system_variable(line, column, name, dims), m_declaration(declaration) {}

        block_declaration<bt>* get_declaration() { return m_declaration; }

        inline void accept(visitor &v) { 
            throw std::runtime_error("unimplemented block_variable.accept(visitor&) error.");
        }
    };

    /**
     * Concrete class
     * Node of the AST that represents a variable holding 
     * an int/float/bool when used in an arithmetic/logical
     * expression of the system section. 
     * When used as the input of a component, it represents
     * a constant input dataflow of the value it contains
     * at compile time.
     */
    template<dataflow_type dft> 
    void visit(dataflow_system_variable<dft> system_dft_var);
};