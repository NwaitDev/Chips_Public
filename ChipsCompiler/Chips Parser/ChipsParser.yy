%require "3.0.4"
%skeleton "lalr1.cc"
%define api.value.type variant
%define api.token.constructor
%header
%locations
%parse-param { driver& drv}
%define parse.trace
%define parse.error detailed
%define parse.lac full


%code requires{
    // #include "cpp_sources/ChipsAST.hpp"
    #include "ChipsDriver.hpp"
}

%{
    #define YYDEBUG 1
    #include <iostream>
    #include <memory>
    #include "ChipsParser.hpp"
    
    // Give Flex the prototype of yylex we want ...
    # define YY_DECL yy::parser::symbol_type yylex ()
    // ... and declare it for the parser's sake.
    YY_DECL;
%}



/*defining the terminal tokens of the grammar*/
%token COMMA ARROW L_PARENTH R_PARENTH L_CURL R_CURL L_SQUA R_SQUA SEMICOL ASSIGN PLUS MINUS TIMES DIV MOD LT GT LEQ GEQ NEQ EQ NOT INT_KW FLOAT_KW BOOL_KW LOGICAL_KW PHYSICAL_KW AS_KW INIT_KW THEN_KW FOREACH_KW TO_KW IN_KW IF_KW ELSE_KW SYSTEM_KW LINK_KW PERIOD IMPLEMENTS_KW HAVING_KW INPUT_KW STOP_KW CHANNEL_KW CHANNELS_KW AMONG_KW SPREAD_KW COLLECT_KW SRC_CHAN_KW CTX_KW OBJECT_KW WITH_KW IMPLEMENTATION_KW BY_KW

%left PLUS MINUS
%left TIMES DIV


/*defining the variable tokens of the grammar*/
%token <int> INT
%token <double> FLOAT
%token <std::string> IDENTIFIER
%token <std::string> STR
%token <bool> BOOL


/*defining the non-terminal symbols of the grammar*/
// %type <std::unique_ptr<chips_node>> chips
// %type <std::unique_ptr<preambles_node>> preambles
// %type <std::unique_ptr<system_node>> system
// %type <std::unique_ptr<preamble_node>> preamble

%%

%start chips;
chips:
    preambles system
    ;
preambles:
    preamble preambles
    | /* EMPTY */
    ;
system:
    SYSTEM_KW  L_CURL 
        s_statements
    R_CURL
    | /* EMPTY */
    ;
preamble:
    object_def
    | function_def
    | collective_op_def
    | implementation_def
    ;
object_def:
    OBJECT_KW IDENTIFIER with_section
    ;
implementation_def:
    IMPLEMTATION_KW IDENTIFIER COLUMN IDENTIFIER BY_KW IDENTIFIER L_CURL
        node_mappings
    R_CURL
    ;
node_mappings:
    HAVING_KW IDENTIFIER AS_KW IDENTIFIER SEMICOL node_mappings
    | /* EMPTY */
    ;
function_def:
    l_function_def
    | p_function_def
    ;
collective_op_def:
    c_signature L_CURL
        c_statements
    R_CURL
    ARROW TARGET_KW L_PARENTH c_list_expr R_PARENTH
    c_output
    c_optionnal_outputs
    ;
c_optionnal_outputs:
    c_output c_optionnal_outputs
    | /* EMPTY */
    ;
c_output:
    ARROW DEFAULT_KW L_PARENTH c_list_expr R_PARENTH
    | ARROW IDENTIFIER L_PARENTH c_list_expr R_PARENTH
    ;
l_function_def:
    LOGICAL_KW IDENTIFIER L_PARENTH df_parameter_list R_PARENTH
    init_section
    then_section
    named_outputs
    ;
p_function_def:
    PHYSICAL_KW IDENTIFIER L_PARENTH pdf_parameter_list R_PARENTH
    with_section
    init_section
    then_section
    p_named_outputs
    ;
c_signature:
    c_keywords L_PARENTH cdf_defaulted_decls R_PARENTH 
      IDENTIFIER AMONG_KW IDENTIFIER
    ;
c_keywords:
    SPREAD_KW 
    | COLLECT_KW
    ;
with_section:
    WITH_KW L_CURL
        with_statements
    R_CURL
    ;
with_statements:
    with_statement with_statements
    | /* EMPTY */
    ;
with_statement:
    IDENTIFIER IDENTIFIER SEMICOL
    | CTX_KW df_decraration SEMICOL
    | statement
    ;
init_section:
    INIT_KW L_CURL 
        statements 
    R_CURL
    ;
then_section:
    THEN_KW L_CURL 
        statements 
    R_CURL
    ;
list_expr:
    exprs
    | /* EMPTY */
    ;
c_list_expr:
    c_exprs
    | /* EMPTY */
    ;
exprs:
    expr
    | expr COMMA exprs
    ;
c_exprs:
    c_exprc_expr
    | c_expr COMMA c_exprs
    ;
expr:
    expr0 LT expr
    | expr0 GT expr
    | expr0 LEQ expr
    | expr0 GEQ expr
    | expr0 NEQ expr
    | expr0 EQ expr
    | expr0
    ;
expr0:
    expr1 PLUS expr0
    | expr1 MINUS expr0
    | MINUS expr0
    | expr1
    ;
expr1: 
    expr2 TIMES expr1
    | expr2 DIV expr1
    | expr2 MOD expr1
    | expr2
    | NOT expr2
    ;
expr2: 
    IDENTIFIER suffixes
    | INT
    | FLOAT
    | BOOL
    | L_PARENTH expr R_PARENTH
    | cast
    ;
cast:
    L_PARENTH df_type R_PARENTH expr
    ;
c_expr:
    c_stopless_expr
    | STOP_KW
    ;
c_stopless_expr:
    c_stopless_expr0 LT c_stopless_expr
    | c_stopless_expr0 GT c_stopless_expr
    | c_stopless_expr0 LEQ c_stopless_expr
    | c_stopless_expr0 GEQ c_stopless_expr
    | c_stopless_expr0 NEQ c_stopless_expr
    | c_stopless_expr0 EQ c_stopless_expr
    | c_stopless_expr0
    ;
c_stopless_expr0:
    c_stopless_expr1 PLUS c_stopless_expr0
    | c_stopless_expr1 MINUS c_stopless_expr0
    | MINUS c_stopless_expr0
    | c_stopless_expr1
    ;
c_stopless_expr1: 
    c_stopless_expr2 TIMES c_stopless_expr1
    | c_stopless_expr2 DIV c_stopless_expr1
    | c_stopless_expr2 MOD c_stopless_expr1
    | c_stopless_expr2
    | NOT c_stopless_expr2
    ;
c_stopless_expr2: 
    IDENTIFIER c_suffixes
    | INT
    | FLOAT
    | BOOL
    | INPUT_KW
    | STOP_KW
    | expr
    | CTX_KW PERIOD IDENTIFIER c_suffixes
    | L_PARENTH c_stopless_expr R_PARENTH
    | cast
    ;
c_cast:
    L_PARENTH df_type R_PARENTH c_stopless_expr
    ;
suffixes:
    L_SQUA expr R_SQUA suffixes
    | /* EMPTY */
    ;
c_suffixes:
    L_SQUA c_stopless_expr R_SQUA c_suffixes
    | /* EMPTY */
    ;
s_suffixable_expr:
    IDENTIFIER
    | block PERIOD IDENTIFIER
    ;
block:
    IDENTIFIER suffixes
    ;
loop_statement:
    FOREACH_KW IDENTIFIER IN_KW IDENTIFIER L_CURL 
        statements 
    R_CURL
    ;
c_loop_statement:
    FOREACH_KW IDENTIFIER IN_KW IDENTIFIER L_CURL
        c_statements 
    R_CURL
    ;
s_loop_statement:
    FOREACH_KW IDENTIFIER IN_KW s_suffixable_expr L_CURL 
        s_statements 
    R_CURL
    ;
if_else_statement:
    if_statement 
    ELSE_KW L_CURL 
        statements 
    R_CURL
    ;
s_if_else_statement:
    s_if_statement 
    ELSE_KW L_CURL 
        s_statements 
    R_CURL
    ;
c_if_else_statement:
    c_if_statement
    ELSE_KW L_CURL 
        c_statements 
    R_CURL
    ;
if_statement: 
    IF_KW L_PARENTH expr R_PARENTH L_CURL 
        statements 
    R_CURL
    ;
s_if_statement: 
    IF_KW L_PARENTH expr R_PARENTH L_CURL 
        s_statements 
    R_CURL
    ;
c_if_statement: 
    IF_KW L_PARENTH expr R_PARENTH L_CURL 
        c_statements
    R_CURL
    ;
statements: 
    statement statements
    | loop_statement statements
    | if_else_statement statements
    | if_statement statements
    | /* EMPTY */
    ;
s_statements:
    s_statement s_statements
    | s_loop_statement s_statements
    | s_if_else_statement s_statements
    | s_if_statement s_statements
    | /* EMPTY */
    ;
statement:
    df_decraration SEMICOL
    | IDENTIFIER suffixes ASSIGN expr SEMICOL
    ;
s_statement:
    IDENTIFIER suffixes IDENTIFIER SEMICOL /* functionnal block instanciation */
    | block PERIOD IDENTIFIER suffixes L_PARENTH expr R_PARENTH SEMICOL /* plugging expr to block input */
    | LINK_KW IDENTIFIER TO_KW IDENTIFIER SEMICOL /* attaching logical process to a node */
    | df_decraration SEMICOL /* declaring a variable */
    | IDENTIFIER suffixes IMPLEMENTS_KW IDENTIFIER suffixes USING_KW IDENTIFIER SEMICOL
    | statement
    ;
c_statements:
    c_statement c_statements
    | c_loop_statement c_statements
    | c_if_else_statement c_statements
    | c_if_statement c_statements
    | /* EMPTY */
    ;
c_statement:
    cdf_full_declaration SEMICOL
    | IDENTIFIER suffixes ASSIGN c_expr SEMICOL
    | CTX_KW PERIOD IDENTIFIER c_suffixes ASSIGN c_expr SEMICOL
    ;
named_outputs:
    named_output named_outputs
    | /* EMPTY */
    ;
named_output:
    ARROW IDENTIFIER L_PARENTH list_expr R_PARENTH
    ;
p_named_outputs:
    p_named_output p_named_outputs
    | /* EMPTY */
    ;
p_named_output:
    ARROW ACTUATOR_KW IDENTIFIER L_PARENTH exprs R_PARENTH
    | named_output
    ;
c_named_outputs:
    c_named_output c_named_outputs
    | /* EMPTY */
    ;
df_parameter_list:
    df_parameter_decls
    | /* EMPTY */
    ;
df_parameter_decls:
    df_parameter_decl
    | df_parameter_decl COMMA df_parameter_decls
    ;
df_parameter_decl:
    df_type IDENTIFIER may_assign
    ;
df_type:
    INT_KW suffixes
    | FLOAT_KW suffixes
    | BOOL_KW suffixes
    ;
pdf_parameter_type:
    df_type
    | SENSOR_KW df_type
    ;
pdf_parameter_list:
    pdf_parameter_decls
    | /* EMPTY */
    ;
pdf_parameter_decls:
    pdf_parameter_decl
    | pdf_parameter_decl COMMA pdf_declaration_decls
    ;
pdf_parameter_decl:
    pdf_parameter_type IDENTIFIER may_assign
    ;
cdf_defaulted_decls:
    cdf_defaulted_decl
    | cdf_defaulted_decl COMMA cdf_defaulted_decls
    ;
cdf_defaulted_decl:
    df_type IDENTIFIER ASSIGN c_expr
    ;
df_decraration:
    df_type IDENTIFIER may_assign
    ;
cdf_full_declaration:
    df_type IDENTIFIER c_may_assign
    ;
c_may_assign:
    ASSIGN c_expr
    | /* EMPTY */
    ;
may_assign:
    ASSIGN expr
    | /* EMPTY */
    ;
%%

int main(int argc, char *argv[])
{
    if(argc != 2){
        std::cout << "Usage: ./chipsc <file.chips>\n";
        return -1;
    }
	driver drv;
	return drv.parse(std::string(argv[1]));
}


void yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}