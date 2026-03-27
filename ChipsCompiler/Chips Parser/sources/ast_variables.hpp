#ifndef __chips_variables__
#define __chips_variables__


namespace chips {
    

    /**
     * Concrete class
     * Node of the AST that represents an array of elements
     * that can be instanciated in the parametering 
     * expression environment
     */
    template<expression_env expenv> 
    class array : public ast_node {
        public:
        std::vector<rvalue<dataflow_type::INT,expenv>> m_dimensions;

        array() = default;

        array(std::vector<rvalue<dataflow_type::INT,expenv>> dim)
            : m_dimensions(dim){}

        std::vector<rvalue<dataflow_type::INT,expenv>> get_dimensions() { return m_dimensions; }
        
        
        void accept(visitor& v) { v.visit(*this); }
        virtual void hello() override;// override {std::cout<<"hello"<<std::endl;}
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
    class variable : public array<expenv>{
        public:
            std::string name;

            variable(std::string name, std::vector<rvalue<dataflow_type::INT,expenv>> dim) 
                : array<expenv>(dim), name(name){}

            variable(std::string name) : array<expenv>(), name(name){}

            std::string get_name() { return name; }
    };

    /**
     * Abstract class
     * Node of the AST that represents a variable that
     * is manipulated inside a functional block or to
     * initialize other variables in nodes
     * (with/init/then sections)
     * A variable of this kind is NOT contextual
     */
    class primitive_variable : public variable<chips::expression_env::PRIMITIVE>{
        public:
            primitive_variable(std::string name,std::vector<rvalue<dataflow_type::INT,expression_env::PRIMITIVE>> dim)
                : variable(name, dim){}

            primitive_variable(std::string name)
                : variable(name){}
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
    class dataflow_primitive_variable : public primitive_variable  
    {
        public:
        dataflow_declaration<dft,statement_env::DEFINITION>* m_declaration;
        
        dataflow_primitive_variable(std::string name, dataflow_declaration<dft,statement_env::DEFINITION>* declaration)
            : primitive_variable(name), m_declaration(declaration){}

        dataflow_primitive_variable(std::string name, dataflow_declaration<dft,statement_env::DEFINITION>* declaration,
                                    std::vector<rvalue<dataflow_type::INT,expression_env::PRIMITIVE>> dim)
            : primitive_variable(name, dim), m_declaration(declaration){}
        
        virtual void hello() override;
    };

    /**
     * Abstract class
     * Node of the AST that represents the kind of 
     * variables that can only be specified inside
     * the with section of a Node (i.e. Physical or Object)
     */
    class node_variable : public variable<chips::expression_env::PRIMITIVE>{
        
    };

    /**
     * Concrete class
     * Node of the AST that represents a contextual
     * variable.
     */
    template<dataflow_type dft> 
    class contextual_variable : public node_variable 
    {
        using node_element_declaration_type = typename DfTypeToContextualDeclType<dft>::type;
        node_element_declaration_type* m_declaration;
        void hello();
    };

    /**
     * Abstract class
     * Node of the AST that represents a variable that
     * is used in the body/parameters or outputs of a 
     * collective primitive.
     */
    class collective_variable : public variable<chips::expression_env::COLLECTIVE>{};
    
    /**
     * Concrete class
     * Node of the AST that represents a variable that
     * is used in the body/parameters or outputs of a 
     * collective primitive. 
     * (it is currently the only specialization of
     * the collective_variable class)
     */
    template<dataflow_type dft> 
    class dataflow_collective_variable : public collective_variable
    {
        dataflow_declaration<dft,statement_env::COLLECTIVE>* m_declaration;
        void hello();
    };


    /**
     * Abstract class
     * Node of the AST that represents a variable
     * that can be used in the system section.
     */
    class system_variable : public variable<chips::expression_env::SYSTEM>{};
    
    /**
     * Concrete class
     * Node of the AST that represents a component
     * of the model that was instantiated from a
     * former definition (Object/Logical/physical)
     */
    template<block_type bt> 
    class block_variable : public system_variable 
    {
        block_declaration<bt>* m_declaration;
        void hello();
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
    class dataflow_system_variable : public system_variable 
    {
        dataflow_declaration<dft,statement_env::SYSTEM>* m_declaration;
        void hello();

    };
    
}

#endif