#ifndef __chips_base__
#define __chips_base__

namespace chips{

    class visitor;
    class ast_node{
        private:
            int line;
            int column;

    public:
        // virtual void hello() = 0;
        // virtual void accept(visitor& v) = 0;

        int get_line() { return line; }
        int get_column() { return column; }
        void set_line(int l) { line = l; }
        void set_column(int c) { column = c; }
    };
    class visitor{
    public:
        virtual void visit(ast_node &node) = 0;
    };
    
}

#endif