#include "chips_ast_classes.hpp"


class chips::ast_node
{
private:
    int line = 0;
    int column = 0;

public:
    ~ast_node() = default;
    virtual void hello(){
        std::cout<<"hello!"<<std::endl;
    };

    virtual void accept(chips_visitor &visitor) = 0;

    int get_line() { return line; }
    int get_column() { return column; }
    void set_line(int l) { line = l; }
    void set_column(int c) { column = c; }
};