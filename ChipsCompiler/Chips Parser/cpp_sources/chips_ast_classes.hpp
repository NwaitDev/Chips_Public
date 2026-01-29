
#ifndef AST_H
#define AST_H

class chips_visitor;
class ast_node;

enum COMPILE_STATE
{
    CONFIGURING,
    DEFINING,
    IN_PHYSICAL,
    IN_LOGICAL
};

enum DATAFLOW_TYPE
{
    INT_DF,
    FLOAT_DF,
    BOOL_DF
};

enum COLLECTIVE_KW
{
    SPREAD,
    COLLECT,
    INPUT,
    STOP
};

enum FUNCTION_TYPE
{
    LOGICAL,
    PHYSICAL
};

enum EXPRESSION_TYPE
{
    PLUS_EXP,          // binary
    MINUS_EXP,         // binary
    U_MINUS_EXP,       // unary
    TIMES_EXP,         // binary
    DIV_EXP,           // binary
    FCALL_EXP,         // Fcall
    MOD_EXP,           // binary
    AND_EXP,           // binary
    OR_EXP,            // binary
    EQ_EXP,            // binary
    NEQ_EXP,           // binary
    GT_EXP,            // binary
    LT_EXP,            // binary
    GEQ_EXP,           // binary
    LEQ_EXP,           // binary
    NOT_EXP,           // unary
    IDENT_EXP,         // Ident
    CAST_TO_INT_EXP,   // unary
    CAST_TO_FLOAT_EXP, // unary
    CAST_TO_BOOL_EXP,  // unary
    INT_EXP,           // number literal
    FLOAT_EXP,         // number literal
    BOOL_EXP,          // number literal
    OBJ_PHY_ATTR_EXP,  // (ref to json file)
    OBJ_VIRT_IN_EXP,   // (ref to input/output of functional block)
    OBJ_VIRT_OUT_EXP   // (ref to input/output of functional block)
};

enum STATEMENT_TYPE
{
    INST_ST,
    ASSI_ST,
    IF_ST,
    IFELSE_ST,
    LOOP_ST,
    FCALL_ST,
    S_LINK_ST,
    DF_INST_ST,
    DF_ASSIGN_ST,
    S_FUNC_BLOCK_INST_ST,
    S_EXPR_PLUG_ST,
    S_IMPLEMENTS_ST,
    C_FCT_PLUG_ST,
    C_DF_ASSI_ST
};

// enum S_STATEMENT_TYPE {
//     S_LOOP_ST,
//     S_IF_ST,
//     S_IFELSE_ST,
//     S_INST_ST,
//     S_LINK_ST,
//     S_DF_INST_ST,
//     S_DF_ASSIGN_ST,
//     S_FUNC_BLOCK_INST_ST,
//     S_EXPR_PLUG_ST,
//     S_IMPLEMENTS_ST
// };

// enum C_STATEMENT_TYPE {
//     C_LOOP_ST,
//     C_IF_ST,
//     C_IFELSE_ST,
//     C_INST_ST,
//     C_FCT_PLUG_ST,
//     C_DF_INST_ST,
//     C_DF_ASSI_ST,
//     C_FCALL_ST
// };

class chips_node; // PROGRAM BASE NODE

/*
    GENERAL USAGE NODES
*/

class dataflow_type_node;

// class dataflow_declaration_node;

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

class plugging_expr_node;

class object_virtual_output_node;

class object_physical_attribute_node;

class cast_node;

class suffixes_node;

class suffixised_node;

/*
    COLLECTIVE STATEMENTS NODES
*/

class c_statements_node;

class c_statement_node;

class c_loop_node;

class c_if_node;

class c_if_else_node;

class c_expressions_node;

/*
    CONFIGURATION STATEMENTS NODES
*/

class s_statements_node;

class s_statement_node;

class s_loop_node;

class s_if_node;

class s_if_else_node;

class link_node;

class implements_node;

class plugging_node;

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

class object_definition_node;

class function_definition_node;

class logical_function_definition_node;

class physical_function_definition_node;

class collective_operation_definition_node;

class implementation_definition_node;

class node_mappings_node;

class output_node;

class with_statements_node;

class with_statement_node;

class with_two_identifier_node;

class with_context_statement_node;

/*
    Configuration stuff
*/

class system_node;

class function_declaration_node;

/*
    OTHER CLASS (WE NEED TO REFACTOR CORRECTLY THIS)
*/

class c_optionnal_outputs_node;

class c_output_node;

class c_signature_node;

class c_keywords_node;

class spread_node;

class collect_node;

class with_section_node;

class init_section_node;

class then_section_node;

class paren_expression_node;

class c_cast_node;

class s_suffixable_node;

class block_node;

class named_outputs_node;

class named_output_node;

class physical_named_outputs_node;

class physical_named_output_node;

class actuator_node;

class dataflow_parameter_list_node;

class dataflow_parameter_decls_node;

class dataflow_parameter_decl_node;

class physical_dataflow_parameter_type_node;

class physical_dataflow_parameter_list_node;

class physical_dataflow_parameter_decls_node;

class physical_dataflow_parameter_decl_node;

class collective_dataflow_defaulted_decls_node;

class collective_dataflow_defaulted_decl_node;

class collective_dataflow_full_declaration_node;

class collective_rhs_assignment_node;

class c_variable_assignment_node;

class c_context_variable_assignment_node;

class functionnal_block_instanciation_node;

/*
    BASE AST NODE
*/
class ast_node
{
private:
    int line = 0;
    int column = 0;

public:
    virtual ~ast_node() = default;
    // virtual void accept(chips_visitor& visitor) = 0;
    virtual void hello() {}

    virtual void accept(chips_visitor &visitor) = 0;

    int get_line() { return line; }
    int get_column() { return column; }
    void set_line(int l) { line = l; }
    void set_column(int c) { column = c; }
};

class chips_visitor
{
public:
    virtual void visit(ast_node &node) = 0;

    // === PROGRAM & CONTEXT ===
    virtual void visit(chips_node &chips) = 0;
    virtual void visit(preambles_node &preambles) = 0;
    virtual void visit(preamble_node &preamble) = 0;
    virtual void visit(system_node &system) = 0;

    // === SYSTEM STATEMENTS ===
    virtual void visit(s_statements_node &sstatements) = 0;
    virtual void visit(const s_statements_node &sstatements) = 0;
    virtual void visit(s_statement_node &sstatement) = 0;

    // === S_STATEMENT subtypes ===
    virtual void visit(s_loop_node &sloop) = 0;
    virtual void visit(s_if_node &sif) = 0;
    virtual void visit(s_if_else_node &sifelse) = 0;
    virtual void visit(functionnal_block_instanciation_node &funcblock) = 0;
    virtual void visit(implements_node &impl) = 0;
    virtual void visit(link_node &link) = 0;
    virtual void visit(plugging_node &plug) = 0;

    // === 4. DECLARATION CONTEXT (preamble children) ===
    virtual void visit(object_definition_node& node) = 0;
    virtual void visit(function_definition_node& node) = 0;
    virtual void visit(logical_function_definition_node& node) = 0;
    virtual void visit(physical_function_definition_node& node) = 0;
    virtual void visit(collective_operation_definition_node& node) = 0;
    virtual void visit(implementation_definition_node& node) = 0;
    virtual void visit(node_mappings_node& node) = 0;
    virtual void visit(c_signature_node& node) = 0;
    virtual void visit(output_node& node) = 0;

    // === 5. WITH / SECTIONS ===
    virtual void visit(with_section_node& node) = 0;
    virtual void visit(with_statements_node& node) = 0;
    virtual void visit(with_statement_node& node) = 0;
    virtual void visit(with_two_identifier_node& node) = 0;
    virtual void visit(with_context_statement_node& node) = 0;
    virtual void visit(init_section_node& node) = 0;
    virtual void visit(then_section_node& node) = 0;

    virtual void visit(physical_named_outputs_node &chips) = 0;
    virtual void visit(physical_named_output_node &chips) = 0;
    virtual void visit(statement_node &node) = 0;

    // === 6. EXPRESSIONS ===
    virtual void visit(expression_node& node) = 0;
    virtual void visit(suffixable_node& node) = 0;
    virtual void visit(binary_expression_node& node) = 0;
    virtual void visit(unary_expression_node& node) = 0;
    virtual void visit(number_literal_node& node) = 0;
    virtual void visit(function_call_node& node) = 0;
    virtual void visit(variable_node& node) = 0;
    virtual void visit(object_virtual_output_node& node) = 0;
    virtual void visit(object_physical_attribute_node& node) = 0;
    virtual void visit(cast_node& node) = 0;
    virtual void visit(suffixes_node& node) = 0;
    virtual void visit(suffixised_node& node) = 0;
    virtual void visit(paren_expression_node& node) = 0;
};
class context_expression_node;

class collective_cast_node;

class collective_operation_node;

class integrated_function_node;

class context_decl_node;

class context_variable_assignment_node;

class variable_assignment_node;

#endif // ! AST_H
