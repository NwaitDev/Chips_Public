
#ifndef AST_H
#define AST_H





enum COMPILE_STATE {
    CONFIGURING,
    DEFINING,
    IN_PURE,
    IN_PHYSICAL,
    IN_VIRTUAL
};

enum DATAFLOW_TYPE{
    INT_DF,
    FLOAT_DF,
    BOOL_DF
};

enum FUNCTION_TYPE{
    VIRTUAL,
    PHYSICAL,
    PURE
};

enum EXPRESSION_TYPE{
    PLUS_EXP, // binary
    MINUS_EXP, // binary
    U_MINUS_EXP,  // unary
    TIMES_EXP, // binary
    DIV_EXP, // binary
    FCALL_EXP, // Fcall
    MOD_EXP, // binary
    AND_EXP, // binary
    OR_EXP, // binary
    EQ_EXP, // binary
    NEQ_EXP, // binary
    GT_EXP, // binary
    LT_EXP, // binary
    GEQ_EXP, // binary
    LEQ_EXP, // binary
    NOT_EXP, // unary
    IDENT_EXP, // Ident
    CAST_TO_INT_EXP, // unary
    CAST_TO_FLOAT_EXP, // unary
    CAST_TO_BOOL_EXP, // unary
    INT_EXP, // number literal
    FLOAT_EXP, // number literal
    BOOL_EXP, // number literal
    OBJ_PHY_ATTR_EXP, // (ref to json file)
    OBJ_VIRT_IN_EXP, // (ref to input/output of functional block)
    OBJ_VIRT_OUT_EXP // (ref to input/output of functional block)
};

enum STATEMENT_TYPE {
    INST_ST,
    ASSI_ST,
    IF_ST,
    IFELSE_ST,
    LOOP_ST,
    FCALL_ST
};

enum C_STATEMENT_TYPE {
    C_LOOP_ST,
    C_IF_ST,
    C_IFELSE_ST,
    C_INST_ST,
    C_FCT_PLUG_ST,
    C_LINK_ST,
    C_AT_ST,
    C_DF_INST_ST,
    C_DF_ASSI_ST,
    C_FCALL_ST
};



/*
    BASE AST NODE
*/
class ast_node {
private:
    int line = 0;
    int column = 0;
public:
    virtual ~ast_node() = default;
    //virtual void accept(chips_visitor& visitor) = 0;
    virtual void hello() = 0;
    
    int get_line() { return line; }
    int get_column() { return column; }
    void set_line(int l) { line = l; }
    void set_column(int c) { column = c; }
};


class chips_node; // PROGRAM BASE NODE

class chips_visitor {
    public:
        void visit(chips_node& chips);
};

/*
    GENERAL USAGE NODES
*/

class dataflow_declarations_node;

class dataflow_type_node;

class dataflow_declaration_node;

class expressions_node;


/*
    EXPRESSION NODES
*/

class expression_node;

class suffixable_node;

class binary_expression_node;

class unary_expression_node;

class number_literal_node;

class function_call_node;

class variable_node;

class object_virtual_output_node;

class object_physical_attribute_node;

class suffix_node;

class cast_node;

class suffixes_node;

class suffixised_node;


/*
    CONFIGURATION STATEMENTS NODES
*/

class c_statement_node;

class c_assignment_node;

class at_node;

class link_node;

class c_statements_node;

class c_loop_node;

class c_if_node;;

class c_if_else_node;



/*
        (NOT CONFIGURATION) STATEMENTS NODES
*/

class statement_node;

class statements_node;

class rhs_assignment_node;

class assignment_node;

class this_attribute_node;

class dataflow_full_declaration_node;

class function_call_statement_node;

class if_node;

class if_else_node;

class loop_node;





/*
    DECLARATION CTX ELEMENTS
*/

class preamble_node;

class preambles_node;

class import_node;

class signature_node;

class output_node;

class function_definition_node;


/*
    Configuration stuff
*/

class dimension_node;

class system_node;

class function_declaration_node;



#endif 
