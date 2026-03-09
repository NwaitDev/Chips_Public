#ifndef __chips_variables__
#define __chips_variables__
#include "forward_declarations.hpp"


namespace chips {
    

    template<expression_env expenv> 
    class array : public ast_node{

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    template<expression_env expenv>
    class variable : public array<expenv>{};

    class primitive_variable : public variable<chips::expression_env::PRIMITIVE>{};

    template<dataflow_type dft> 
    class dataflow_primitive_variable : public primitive_variable  
    {
    private:
        dataflow_declaration<dft,statement_env::DEFINITION>& m_declaration;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    class node_variable : public variable<chips::expression_env::PRIMITIVE>{};

    template<dataflow_type dft> 
    class contextual_variable : public node_variable 
    {
    private:
        using node_element_declaration_type = typename DfTypeToContextualDeclType<dft>::type;
        node_element_declaration_type& m_declaration;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };

    class collective_variable : public variable<chips::expression_env::COLLECTIVE>{};
    
    template<dataflow_type dft> 
    class dataflow_collective_variable : public collective_variable
    {
    private:
        dataflow_declaration<dft,statement_env::COLLECTIVE>& m_declaration;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };


    class system_variable : public variable<chips::expression_env::SYSTEM>{};
    
    template<block_type bt> 
    class block_variable : public system_variable 
    {
    private:
        block_declaration<bt>& m_declaration;

        public:

            //void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };
    
    template<dataflow_type dft> 
    class dataflow_system_variable : public system_variable 
    {
    private:
        dataflow_declaration<dft,statement_env::SYSTEM>& m_declaration;

        public:

            // void accept(visitor& v) { v.visit(*this); }
            virtual void hello() override;
    };
    
}

#endif