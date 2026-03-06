#ifndef __chips_ast_base__
#define __chips_ast_base__

namespace chips{

    class visitor;
    class ast_node{
    public:
        void hello();
        void accept(visitor& v);
    };
    class visitor{
    public:
        void visit(ast_node &node);
    };
    
}

#endif