grammar Chips;

program 
//    : preambles system EOF
    : expr EOF
    ;

preambles
    : preamble preambles
    | NEWLINE
    ;

system
    : SYSTEM_KW L_CURL
        s_statements
      R_CURL
    | NEWLINE
    ;

preamble
    : object_def
    | function_def
    | collective_op_def
    | implementation_def
    ;

object_def
    : OBJECT_KW IDENTIFIER with_section
    ;

implementation_def
    : IMPLEMENTATION_KW IDENTIFIER COLUMN IDENTIFIER BY_KW IDENTIFIER L_CURL
        node_mappings
      R_CURL
    ;

node_mappings
    : HAVING_KW IDENTIFIER AS_KW IDENTIFIER SEMICOL node_mappings
    | NEWLINE
    ;

function_def
    : l_function_def
    | p_function_def
    ;

collective_op_def
    : c_signature L_CURL
        c_statements
      R_CURL
      ARROW TARGET_KW L_PARENTH c_list_expr R_PARENTH
      c_output
      c_optionnal_outputs
    ;

c_optionnal_outputs
    : c_output c_optionnal_outputs
    | NEWLINE
    ;

c_output
    : ARROW DEFAULT_KW L_PARENTH c_list_expr R_PARENTH
    | ARROW IDENTIFIER L_PARENTH c_list_expr R_PARENTH
    ;

l_function_def
    : LOGICAL_KW IDENTIFIER L_PARENTH df_parameter_list R_PARENTH
        init_section
        then_section
        named_outputs
    ;

p_function_def
    : PHYSICAL_KW IDENTIFIER L_PARENTH pdf_parameter_list R_PARENTH
        with_section
        init_section
        then_section
        p_named_outputs
    ;

c_signature
    : c_keywords L_PARENTH cdf_defaulted_decls R_PARENTH
        IDENTIFIER AMONG_KW IDENTIFIER
    ;

c_keywords
    : SPREAD_KW
    | COLLECT_KW
    ;

with_section
    : WITH_KW L_CURL
        with_statements
      R_CURL
    ;

with_statements
    : with_statement with_statements
    | NEWLINE
    ;

with_statement
    : IDENTIFIER IDENTIFIER SEMICOL
    | CTX_KW df_type IDENTIFIER may_assign SEMICOL
    | statement
    ;

init_section
    : INIT_KW L_CURL
        statements
      R_CURL
    ;

then_section
    : THEN_KW L_CURL
        statements
      R_CURL
    ;

list_expr
    : exprs
    | NEWLINE
    ;

c_list_expr
    : c_exprs
    | NEWLINE
    ;

exprs
    : expr
    | expr COMMA exprs
    ;

c_exprs
    : c_expr
    | c_expr COMMA c_exprs
    ;
 
expr
    : expr0 LT expr     # LT
    | expr0 GT expr     # GT
    | expr0 LEQ expr    # LEQ
    | expr0 GEQ expr    # GEQ
    | expr0 NEQ expr    # NEQ
    | expr0 EQ  expr    # EQ
    | expr0 AND expr    # AND
    | expr0 OR expr     # OR   
    | expr0             # PassExpr0
    ;

expr0
    : expr1 PLUS expr0      # PLUS
    | expr1 MINUS expr0     # SUB
    | MINUS expr1           # Negate
    | expr1                 # PassExpr1
    ;

expr1
    : expr2 TIMES expr1     # MULT
    | expr2 DIV expr1       # DIV
    | expr2 MOD expr1       # MOD
    | NOT expr2             # NNegateOT
    | expr2                 # PassExpr2
    ;

expr2
    : INT                                       # IntLiteral
    | FLOAT                                     # FloatLiteral
    | BOOL                                      # BoolLiteral
    | IDENTIFIER suffixes                       # Var
    | L_PARENTH expr R_PARENTH                  # Parens
    | CTX_KW PERIOD IDENTIFIER suffixes         # VarContext
    | IDENTIFIER L_PARENTH list_expr R_PARENTH  # Function
    | cast                                      # Casting
    ;

cast    
    : L_PARENTH df_type R_PARENTH expr
    ;

c_expr
    : c_stopless_expr
    | STOP_KW
    ;

c_stopless_expr 
    : c_stopless_expr0 LT c_stopless_expr
    | c_stopless_expr0 GT c_stopless_expr
    | c_stopless_expr0 LEQ c_stopless_expr
    | c_stopless_expr0 GEQ c_stopless_expr
    | c_stopless_expr0 NEQ c_stopless_expr
    | c_stopless_expr0 EQ c_stopless_expr
    | c_stopless_expr0 AND c_stopless_expr
    | c_stopless_expr0 OR c_stopless_expr
    | c_stopless_expr0
    ;

c_stopless_expr0
    : c_stopless_expr1 PLUS c_stopless_expr0
    | c_stopless_expr1 MINUS c_stopless_expr0
    | MINUS c_stopless_expr0
    | c_stopless_expr1
    ;

c_stopless_expr1
    : c_stopless_expr2 TIMES c_stopless_expr1
    | c_stopless_expr2 DIV c_stopless_expr1
    | c_stopless_expr2 MOD c_stopless_expr1
    | NOT c_stopless_expr1
    | c_stopless_expr2
    ;

c_stopless_expr2
    : IDENTIFIER c_suffixes
    | INT
    | FLOAT
    | BOOL
    | INPUT_KW
    | CTX_KW PERIOD IDENTIFIER c_suffixes
    | IDENTIFIER L_PARENTH list_expr R_PARENTH
    | L_PARENTH c_stopless_expr R_PARENTH
    | c_cast
    ;

c_cast
    : L_PARENTH df_type R_PARENTH c_stopless_expr
    ;


suffixes
    : (L_SQUA expr R_SQUA)*
    ;

c_suffixes
    : (L_SQUA c_stopless_expr R_SQUA)*
    ;

// suffixes
//    : L_SQUA expr R_SQUA suffixes
//    | NEWLINE
//    ;

//c_suffixes
//    : L_SQUA c_stopless_expr R_SQUA c_suffixes
//    | NEWLINE
//    ;

s_suffixable_expr
    : IDENTIFIER
    | block PERIOD IDENTIFIER
    | IDENTIFIER L_PARENTH list_expr R_PARENTH
    ;

block   
    : IDENTIFIER suffixes
    ;

loop_in
    : IDENTIFIER
    | IDENTIFIER L_PARENTH list_expr R_PARENTH
    ;

loop_statement
    : FOREACH_KW IDENTIFIER IN_KW loop_in L_CURL
        statements
      R_CURL
    ;

c_loop_statement
    : FOREACH_KW IDENTIFIER IN_KW loop_in L_CURL
        c_statements
      R_CURL
    ;

s_loop_statement
    : FOREACH_KW IDENTIFIER IN_KW s_suffixable_expr L_CURL
        s_statements
      R_CURL
    ;

if_else_statement
    : if_statement
      ELSE_KW L_CURL
        statements
      R_CURL
    ;

s_if_else_statement
    : s_if_statement
      ELSE_KW L_CURL
        s_statements
      R_CURL
    ;

c_if_else_statement
    : c_if_statement
      ELSE_KW L_CURL
        c_statements
      R_CURL
    ;

if_statement
    : IF_KW L_PARENTH expr R_PARENTH L_CURL
        statements
      R_CURL
    ;

s_if_statement
    : IF_KW L_PARENTH expr R_PARENTH L_CURL
        s_statements
      R_CURL
    ;

c_if_statement
    : IF_KW L_PARENTH c_expr R_PARENTH L_CURL
        c_statements
      R_CURL
    ;

statements
    : statement statements
    | loop_statement statements
    | if_else_statement statements
    | if_statement statements
    | NEWLINE
    ;

s_statements
    : s_statement s_statements
    | s_loop_statement s_statements
    | s_if_else_statement s_statements
    | s_if_statement s_statements
    | NEWLINE
    ;

statement
    : df_type IDENTIFIER may_assign SEMICOL
    | IDENTIFIER suffixes ASSIGN expr SEMICOL
    | CTX_KW PERIOD IDENTIFIER suffixes ASSIGN expr SEMICOL
    ;

s_statement
    : IDENTIFIER suffixes IDENTIFIER SEMICOL
    | block PERIOD IDENTIFIER suffixes L_PARENTH s_expr R_PARENTH SEMICOL
    | LINK_KW IDENTIFIER suffixes TO_KW IDENTIFIER suffixes SEMICOL
    | IDENTIFIER suffixes IMPLEMENTATION_KW IDENTIFIER suffixes USING_KW IDENTIFIER SEMICOL
    | statement
    ;

s_expr
    : block PERIOD IDENTIFIER
    | collective_operation block PERIOD IDENTIFIER
    | expr
    ;

collective_operation
    : L_PARENTH IDENTIFIER R_PARENTH
    ;

c_statements
    : c_statement c_statements
    | c_loop_statement c_statements
    | c_if_else_statement c_statements
    | c_if_statement c_statements
    | NEWLINE
    ;

c_statement
    : cdf_full_declaration SEMICOL
    | IDENTIFIER c_suffixes ASSIGN c_expr SEMICOL
    | CTX_KW PERIOD IDENTIFIER c_suffixes ASSIGN c_expr SEMICOL
    ;

named_outputs
    : named_output named_outputs
    | NEWLINE
    ;

named_output
    : ARROW IDENTIFIER L_PARENTH list_expr R_PARENTH
    ;

p_named_outputs
    : p_named_output p_named_outputs
    | NEWLINE
    ;

p_named_output
    : ARROW ACTUATOR_KW IDENTIFIER L_PARENTH exprs R_PARENTH
    | named_output
    ;

df_parameter_list
    : df_parameter_decls
    | NEWLINE
    ;

df_parameter_decls
    : df_parameter_decl
    | df_parameter_decl COMMA df_parameter_decls
    | NEWLINE
    ;

df_parameter_decl
    : df_type IDENTIFIER may_assign
    ;

df_type
    : INT_KW suffixes
    | FLOAT_KW suffixes
    | BOOL_KW suffixes
    ;

pdf_parameter_type
    : df_type
    | SENSOR_KW df_type
    ;

pdf_parameter_list
    : pdf_parameter_decls
    | NEWLINE
    ;

pdf_parameter_decls
    : pdf_parameter_decl
    | pdf_parameter_decl COMMA pdf_parameter_decls
    | NEWLINE
    ;

pdf_parameter_decl
    : pdf_parameter_type IDENTIFIER may_assign
    ;

cdf_defaulted_decls
    : cdf_defaulted_decl
    | cdf_defaulted_decl COMMA cdf_defaulted_decls
    | NEWLINE
    ;

cdf_defaulted_decl
    : df_type IDENTIFIER ASSIGN c_expr
    ;

cdf_full_declaration
    : df_type IDENTIFIER c_may_assign
    ;

c_may_assign
    : ASSIGN c_expr
    | NEWLINE
    ;

may_assign
    : ASSIGN expr
    | NEWLINE
    ;




FLOAT               : '.' [0-9]+ | [0-9]+ '.' [0-9]* ;
INT                 : [0-9]+ ;
BOOL                : 'true' | 'false';
IDENTIFIER          : [a-zA-Z][a-zA-Z0-9_]*;

INT_KW              : 'int';
FLOAT_KW            : 'flaot';
BOOL_KW             : 'bool';
LOGICAL_KW          : 'logical';
PHYSICAL_KW         : 'physical';
AS_KW               : 'as';
INIT_KW             : 'init';
THEN_KW             : 'then';
FOREACH_KW          : 'for';
IN_KW               : 'in';
IF_KW               : 'if';
ELSE_KW             : 'else';
TO_KW               : 'to';
SYSTEM_KW           : 'system' | 'SYSTEM';
LINK_KW             : 'link';
IMPLEMENTS_KW       : 'implements';
HAVING_KW           : 'having';
INPUT_KW            : 'input';
STOP_KW             : 'stop';
AMONG_KW            : 'among';
SPREAD_KW           : 'spread';
COLLECT_KW          : 'collect';
CTX_KW              : 'ctx';
OBJECT_KW           : 'object';
WITH_KW             : 'with';
IMPLEMENTATION_KW   : 'implementation';
BY_KW               : 'by';
TARGET_KW           : '@';
DEFAULT_KW          : 'default';
USING_KW            : 'using';
ACTUATOR_KW         : 'actuator';
SENSOR_KW           : 'sensor';
ARROW               : '->';
PLUS                : '+';
MINUS               : '-';
TIMES               : '*';
DIV                 : '/';
MOD                 : '%';
LT                  : '<';
GT                  : '>';
EQ                  : '==';
LEQ                 : '<=';
GEQ                 : '>=';
NEQ                 : '!=';
AND                 : '&&';
OR                  : '||';
NOT                 : '!';
ASSIGN              : '=';

COMMA               : ',';
SEMICOL             : ';';
L_PARENTH           : '(';
R_PARENTH           : ')';
L_CURL              : '{';
R_CURL              : '}';
L_SQUA              : '[';
R_SQUA              : ']';
COLUMN              : ':';
PERIOD              : '.';


NEWLINE : ('\r'? '\n')+ ;
WS          : [ \t\r]+ -> skip ;
COMMENT     : '//' ~[\r\n]* -> skip ;