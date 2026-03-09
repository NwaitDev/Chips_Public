#ifndef __chips_base__
#define __chips_base__

#include "metamodel_enums.hpp"

namespace chips{

    class visitor;
    class ast_node{
        private:
            int line;
            int column;

    public:
        virtual ~ast_node() = default;

        virtual void hello() {};
        // virtual void accept(visitor& v) { v.visit(*this); }

        int get_line() { return line; }
        int get_column() { return column; }
        void set_line(int l) { line = l; }
        void set_column(int c) { column = c; }
    };
    class visitor{
    public:
        virtual ~visitor() = default;
        virtual void visit(ast_node& node) = 0;        
    };
    
}

#endif