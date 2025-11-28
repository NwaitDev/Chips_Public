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
%token COMMA ARROW L_PARENTH R_PARENTH L_CURL R_CURL L_SQUA R_SQUA SEMICOL ASSIGN PLUS MINUS TIMES DIV MOD LT GT LEQ GEQ NEQ EQ NOT INT_KW FLOAT_KW BOOL_KW PURE_KW LOGICAL_KW PHYSICAL_KW AS_KW INIT_KW THEN_KW FOREACH_KW TO_KW IN_KW IF_KW ELSE_KW SYSTEM_KW LINK_KW PERIOD IMPLEMENTED_BY_KW HAVING_KW INPUT_KW STOP_KW CHANNEL_KW CHANNELS_KW ONTO_KW AMONG_KW SPREAD_KW COLLECT_KW SRC_CHAN_KW CTX_KW

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
    ;
preamble:
    node_def
    | function_def
    ;
node_def:
    NODE_KW IDENTIFIER IMPLEMENTED_BY_KW STR L_CURL
        node_mappings
    R_CURL
    ;
node_mappings:
    node_mapping node_mappings
    | /* EMPTY */
    ;
node_mapping:
    HAVING_KW IDENTIFIER AS_KW IDENTIFIER SEMICOL
    ;
function_def:
    pure_function_def
    | o_function_def
    | c_function_def
    ;
pure_function_def:
    pure_signature output
    ;
o_function_def:
    l_function_def
    | p_function_def
    ;
c_function_def:
    c_signature L_CURL
        c_statements
    R_CURL
    ARROW TARGET_KW L_PARENTH c_expr R_PARENTH
    c_named_outputs
    ARROW DEFAULT_KW L_PARENTH c_expr R_PARENTH
    ;
l_function_def:
    l_signature 
    l_definition_body
    named_output
    named_outputs
    ;
p_function_def:
    p_signature
    channels_section
    p_definition_body
    p_named_output
    p_named_outputs
    ;
pure_signature:
    PURE_KW IDENTIFIER L_PARENTH df_parameter_list R_PARENTH
    ;
l_signature:
    LOGICAL_KW IDENTIFIER L_PARENTH df_parameter_list R_PARENTH
    ;
p_signature:
    PHYSICAL_KW IDENTIFIER L_PARENTH pdf_parameter_list R_PARENTH
    ;
c_signature:
    SPREAD_KW L_PARENTH cdf_defaulted_decls R_PARENTH 
    IDENTIFIER ONTO_KW IDENTIFIER
    | COLLECT_KW L_PARENTH cdf_defaulted_decls R_PARENTH 
      IDENTIFIER AMONG_KW IDENTIFIER
    ;
l_definition_body:
    INIT_KW L_CURL 
        statements 
    R_CURL THEN_KW L_CURL 
        statements 
    R_CURL
    ;
p_definition_body:
    INIT_KW L_CURL 
        p_statements 
    R_CURL THEN_KW L_CURL 
        statements 
    R_CURL
    ;
channels_section:
    CHANNELS_KW L_CURL
        channel_decraration
        channel_decrarations
    R_CURL
    ;
channel_decrarations:
    channel_decraration channel_decrarations
    | /* EMPTY */
    ;
channel_decraration:
    IDENTIFIER IDENTIFIER SEMICOL
    ;
list_expr:
    exprs
    | /* EMPTY */
    ;
exprs:
    expr
    | expr COMMA exprs
    ;
c_expr:
    STOP_KW
    | INPUT_KW
    | expr
    ;
stopless_c_expr:
    INPUT_KW
    | expr
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
    suffixable_expr suffixes
    | INT
    | FLOAT
    | BOOL
    | L_PARENTH expr R_PARENTH
    | cast
    | function_call
    ;
cast:
    L_PARENTH df_type R_PARENTH expr
    ;
function_call:
    IDENTIFIER L_PARENTH list_expr R_PARENTH
    ;
suffixes:
    suffix suffixes
    | /* EMPTY */
    ;
suffix:
    L_SQUA expr R_SQUA
    | L_SQUA R_SQUA
    ;
suffixable_expr:
    IDENTIFIER /* df_variable */
    | function_call 
    ;
s_suffixable_expr:
    suffixable_expr
    | IDENTIFIER PERIOD IDENTIFIER /* block named output */
    ;
loop_statement:
    FOREACH_KW IDENTIFIER IN_KW suffixable_expr L_CURL 
        statements 
    R_CURL
    ;
c_loop_statement:
    FOREACH_KW IDENTIFIER IN_KW suffixable_expr L_CURL
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
p_statements:
    p_statement p_statements
    | statements p_statements
    | /* EMPTY */
    ;
s_statements:
    s_statement s_statements
    | s_loop_statement s_statements
    | s_if_else_statement s_statements
    | s_if_statement s_statements
    | /* EMPTY */
    ;
p_statement:
    CTX_KW df_decraration SEMICOL
    ;
statement:
    df_decraration SEMICOL
    | IDENTIFIER suffixes ASSIGN expr SEMICOL
    ;
s_statement:
    IDENTIFIER suffixes IDENTIFIER SEMICOL /* functionnal block instanciation */
    | IDENTIFIER PERIOD IDENTIFIER suffixes L_PARENTH expr R_PARENTH SEMICOL /* plugging expr to block input */
    | LINK_KW IDENTIFIER TO_KW IDENTIFIER SEMICOL /* attaching logical process to another or a physical */
    | df_decraration SEMICOL /* declaring a variable */
    | function_call SEMICOL
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
    ;
output:
    ARROW L_PARENTH list_expr R_PARENTH
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
c_named_output:
    ARROW IDENTIFIER L_PARENTH c_expr R_PARENTH
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
    df_type IDENTIFIER ASSIGN stopless_c_expr
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