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
    #include "cpp_sources/ChipsAST.hpp"
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
%token COMMA ARROW L_PARENTH R_PARENTH L_CURL R_CURL L_SQUA R_SQUA SEMICOL ASSIGN PLUS MINUS TIMES DIV MOD LT GT LEQ GEQ NEQ EQ NOT INT_KW FLOAT_KW BOOL_KW PURE_KW VIRT_KW PHYSICAL_KW IMPORT_KW AS_KW INIT_KW THEN_KW THIS_KW FOREACH_KW AT_KW TO_KW IN_KW IF_KW ELSE_KW SYSTEM_KW DIMENSION_KW LINK_KW PERIOD INPUT_SUF OUTPUT_SUF

%left PLUS MINUS
%left TIMES DIV


/*defining the variable tokens of the grammar*/
%token <int> INT
%token <double> FLOAT
%token <std::string> NAME
%token <std::string> STR
%token <bool> BOOL


/*defining the non-terminal symbols of the grammar*/
%type <std::unique_ptr<chips::chips_node>> chips
%type <std::unique_ptr<chips::preambles_node>> preambles
%type <std::unique_ptr<chips::system_node>> system
%type <std::unique_ptr<chips::preamble_node>> preamble
%type <std::unique_ptr<chips::import_node>> import
%type <std::unique_ptr<chips::function_definition_node>> function_def
%type <std::unique_ptr<chips::signature_node>> pure_signature
%type <std::unique_ptr<chips::output_node>> output
%type <std::unique_ptr<chips::dataflow_declarations_node>> df_decl_list_or_nothing
%type <std::unique_ptr<chips::dataflow_declarations_node>> df_decl_list
%type <std::unique_ptr<chips::dataflow_declaration_node>> df_decl_lhs
%type <std::unique_ptr<chips::dataflow_type_node>> df_type
%type <std::unique_ptr<chips::expressions_node>> exprs
%type <std::unique_ptr<chips::signature_node>> object_signature
%type <std::unique_ptr<chips::statements_node>> statements
%type <std::unique_ptr<chips::statement_node>> statement
%type <std::unique_ptr<chips::loop_node>> loop
%type <std::unique_ptr<chips::if_node>> if
%type <std::unique_ptr<chips::if_else_node>> if_else
%type <std::unique_ptr<chips::dataflow_full_declaration_node>> df_full_decl
%type <std::unique_ptr<chips::assignment_node>> assignment
%type <std::unique_ptr<chips::function_call_node>> function_call
%type <std::unique_ptr<chips::function_call_statement_node>> function_call_sttmt
%type <std::unique_ptr<chips::rhs_assignment_node>> may_assign
%type <std::unique_ptr<chips::suffix_node>> suffix
%type <std::unique_ptr<chips::suffixes_node>> suffixes
%type <std::unique_ptr<chips::expression_node>> expr expr0 expr1 expr2
%type <std::unique_ptr<chips::suffixable_node>> suffixable_expr
%type <std::unique_ptr<chips::rhs_assignment_node>> assign_rhs
%type <std::unique_ptr<chips::expressions_node>> list_expr
%type <std::unique_ptr<chips::dimension_node>> optional_dim
%type <std::unique_ptr<chips::c_statements_node>> c_statements
%type <std::unique_ptr<chips::c_statement_node>> c_statement
%type <std::unique_ptr<chips::c_loop_node>> c_loop
%type <std::unique_ptr<chips::c_if_else_node>> c_if_else
%type <std::unique_ptr<chips::c_if_node>> c_if
%type <std::unique_ptr<chips::cast_node>> cast



%%

%start chips;

chips:
    preambles system                    { $$ = std::move(std::make_unique<chips::chips_node>(std::move($1), std::move($2)));
                                          drv.ast = std::move($$);                                          }
    ;
preambles:
    preamble preambles                  { $$ = std::move($2); $$->append(std::move($1)); }
    | /* EMPTY */                       {$$ = std::move(std::make_unique<chips::preambles_node>()); }
    ;
preamble:
    import                              { $$ = std::move($1); }
    | function_def                      { $$ = std::move($1);}
    ;
import:
    IMPORT_KW STR AS_KW NAME SEMICOL   { $$ = std::move(std::make_unique<chips::import_node>(std::move($4), std::move($2))); }
    ;
function_def:
    pure_signature output               { $$ = std::move(std::make_unique<chips::function_definition_node>(std::move($1),std::move($2))); }
    | object_signature INIT_KW L_CURL 
        statements 
    R_CURL THEN_KW L_CURL 
        statements 
    R_CURL output                       { $$ = std::move(std::make_unique<chips::function_definition_node>(std::move($1),std::move($4),std::move($8),std::move($10))); }
    ;
pure_signature:
    PURE_KW NAME L_PARENTH df_decl_list_or_nothing R_PARENTH  { $$ = std::move(std::make_unique<chips::signature_node>(chips::PURE, std::move($2), std::move($4))); }
    ;
df_decl_list_or_nothing:
    df_decl_list                        { $$=std::move($1); }
    | /* EMPTY */                       { $$=std::move(std::make_unique<chips::dataflow_declarations_node>()); }
    ;
df_decl_list:
    df_decl_lhs                         { $$ = std::move(std::make_unique<chips::dataflow_declarations_node>()); $$->append($1); }
    | df_decl_lhs COMMA df_decl_list    { $$ = std::move($3); $$->append($1); }
    ;
df_decl_lhs:
    df_type NAME                        { $$ = std::move(std::make_unique<chips::dataflow_declaration_node>(std::move($1), $2)); }
    ;
df_type:
    INT_KW suffixes                     { $$ = std::move(std::make_unique<chips::dataflow_type_node>(chips::INT_DF, std::move($2))); }
    | FLOAT_KW suffixes                 { $$ = std::move(std::make_unique<chips::dataflow_type_node>(chips::FLOAT_DF, std::move($2))); }
    | BOOL_KW suffixes                  { $$ = std::move(std::make_unique<chips::dataflow_type_node>(chips::BOOL_DF, std::move($2))); }
    ;
output:
    ARROW L_PARENTH exprs R_PARENTH     { $$ = std::move(std::make_unique<chips::output_node>(std::move($3))); }
    ;
object_signature:
    VIRT_KW NAME L_PARENTH df_decl_list_or_nothing R_PARENTH           { $$ = std::move(std::make_unique<chips::signature_node>(chips::VIRTUAL, std::move($2), std::move($4))); }
    | PHYSICAL_KW NAME L_PARENTH df_decl_list_or_nothing R_PARENTH     { $$ = std::move(std::make_unique<chips::signature_node>(chips::PHYSICAL, std::move($2), std::move($4))); }
    ;
statements: 
    statement SEMICOL statements        { $$ = std::move($3); $$->append(std::move($1)); }
    | loop statements                   { $$ = std::move($2); $$->append(std::move($1)); }
    | if_else statements                { $$ = std::move($2); $$->append(std::move($1)); }
    | if statements                     { $$ = std::move($2); $$->append(std::move($1)); }
    | /* EMPTY */                       { $$ = std::move(std::make_unique<chips::statements_node>()); }
    ;
statement:
    df_full_decl                        { $$ = std::move($1); }
    | assignment                        { $$ = std::move($1); }
    ;
c_statement: 
    NAME suffixes NAME                                              { $$ = std::move(std::make_unique<chips::function_declaration_node>(std::move($1), std::move($2), std::move($3))); }
    | NAME suffixes INPUT_SUF L_PARENTH exprs R_PARENTH             { $$ = std::move(std::make_unique<chips::c_assignment_node>(std::move($1), std::move($2), std::move($5))); }
    | LINK_KW NAME TO_KW NAME                                       { $$ = std::move(std::make_unique<chips::link_node>(std::move($2), std::move($4))); }
    | NAME AT_KW L_PARENTH exprs R_PARENTH                          { $$ = std::move(std::make_unique<chips::at_node>(std::move($1), std::move($4))); }
    | df_full_decl                                                  { $$ = std::move($1); }
    | assignment                                                    { $$ = std::move($1); }
    | function_call_sttmt                                           { $$ = std::move($1); }
    ;
df_full_decl:
    df_decl_lhs may_assign              { $$ = std::move(std::make_unique<chips::dataflow_full_declaration_node>(std::move($1), std::move($2))); }
    ;
suffixes:
    suffix suffixes                     { $$ = std::move($2); $$->append($1); }
    | /* EMPTY */                       { $$ = std::move(std::make_unique<chips::suffixes_node>()); }
    ;
suffix:
    L_SQUA expr R_SQUA                  { $$ = std::move(std::make_unique<chips::suffix_node>(std::move($2))); }
    | L_SQUA R_SQUA                     { $$ = std::move(std::make_unique<chips::suffix_node>()); }
    ;
may_assign:
    assign_rhs                          { $$ = std::move($1); }
    | /* EMPTY */                       { $$ = std::move(std::make_unique<chips::rhs_assignment_node>()); }
    ;
assign_rhs: 
    ASSIGN expr                         { $$ = std::move(std::make_unique<chips::rhs_assignment_node>($2)); }
    ;
cast:
    df_type L_PARENTH expr R_PARENTH    { $$ = std::move(std::make_unique<chips::cast_node>(std::move($1), std::move($3))); }
    ;
expr:
    expr0 LT expr                       { $$ = std::move(std::make_unique<chips::binary_expression_node>(std::move($1),chips::LT_EXP,std::move($3))); }
    | expr0 GT expr                     { $$ = std::move(std::make_unique<chips::binary_expression_node>(std::move($1),chips::GT_EXP,std::move($3))); }
    | expr0 LEQ expr                    { $$ = std::move(std::make_unique<chips::binary_expression_node>(std::move($1),chips::LEQ_EXP,std::move($3))); }
    | expr0 GEQ expr                    { $$ = std::move(std::make_unique<chips::binary_expression_node>(std::move($1),chips::GEQ_EXP,std::move($3))); }
    | expr0 NEQ expr                    { $$ = std::move(std::make_unique<chips::binary_expression_node>(std::move($1),chips::NEQ_EXP,std::move($3))); }
    | expr0 EQ expr                     { $$ = std::move(std::make_unique<chips::binary_expression_node>(std::move($1),chips::EQ_EXP,std::move($3))); }
    | expr0                             { $$ = std::move($1); }
    ;
expr0:
    expr1 PLUS expr0                    { $$ = std::move(std::make_unique<chips::binary_expression_node>(std::move($1),chips::PLUS_EXP,std::move($3))); }
    | expr1 MINUS expr0                 { $$ = std::move(std::make_unique<chips::binary_expression_node>(std::move($1),chips::MINUS_EXP,std::move($3))); }
    | MINUS expr0                       { $$ = std::move(std::make_unique<chips::unary_expression_node>(chips::U_MINUS_EXP,std::move($2))); }
    | expr1                             { $$ = std::move($1); }
    ;
expr1: 
    expr2 TIMES expr1                   { $$ = std::move(std::make_unique<chips::binary_expression_node>(std::move($1),chips::TIMES_EXP,std::move($3))); }
    | expr2 DIV expr1                   { $$ = std::move(std::make_unique<chips::binary_expression_node>(std::move($1),chips::DIV_EXP,std::move($3))); }
    | expr2 MOD expr1                   { $$ = std::move(std::make_unique<chips::binary_expression_node>(std::move($1),chips::MOD_EXP,std::move($3))); }
    | expr2                             { $$ = std::move($1); }
    | NOT expr2                         { $$ = std::move(std::make_unique<chips::unary_expression_node>(chips::NOT_EXP,std::move($2))); }
    ;
expr2: 
    suffixable_expr suffixes                    { $$ = std::move(std::make_unique<chips::suffixised_node>(std::move($1),std::move($2))); }
    | INT                                       { $$ = std::move(std::make_unique<chips::number_literal_node>($1)); }
    | FLOAT                                     { $$ = std::move(std::make_unique<chips::number_literal_node>($1)); }
    | BOOL                                      { $$ = std::move(std::make_unique<chips::number_literal_node>($1)); }
    | L_PARENTH expr R_PARENTH                  { $$ = std::move(std::make_unique<chips::paren_expression_node>(std::move($2))); }
    | cast                                      { $$ = std::move($1); }
    ;
suffixable_expr:
    function_call                               { $$ = std::move($1); }
    | NAME                                      { $$ = std::move(std::make_unique<chips::variable_node>(std::move($1))); }
    | NAME OUTPUT_SUF                           { $$ = std::move(std::make_unique<chips::object_virtual_output_node>(std::move($1))); }
    | THIS_KW PERIOD NAME PERIOD NAME           { $$ = std::move(std::make_unique<chips::object_physical_attribute_node>(std::move($5), std::move($3))); }
    ;
assignment:
    NAME suffixes assign_rhs                                   { $$ = std::move(std::make_unique<chips::variable_assignment_node>(std::move($1), std::move($2), std::move($3))); }
    | THIS_KW PERIOD NAME PERIOD NAME suffixes assign_rhs      { $$ = std::move(std::make_unique<chips::this_assignment_node>(std::move($3), std::move($5), std::move($6), std::move($7))); }
    ;
loop:
    FOREACH_KW NAME IN_KW suffixable_expr L_CURL 
        statements 
    R_CURL                                      { $$ = std::move(std::make_unique<chips::loop_node>(std::move($2), std::move($4),std::move($6))); }
    ;
if_else:
    if 
    ELSE_KW L_CURL 
        statements 
    R_CURL                                      { $$ = std::move(std::make_unique<chips::if_else_node>(std::move($1), std::move($4))); }
    ;
if: 
    IF_KW L_PARENTH expr R_PARENTH L_CURL 
        statements 
    R_CURL                                      { $$ = std::move(std::make_unique<chips::if_node>(std::move($3), std::move($6))); }
    ;
c_loop:
    FOREACH_KW NAME IN_KW suffixable_expr L_CURL 
        c_statements 
    R_CURL                                      { $$ = std::move(std::make_unique<chips::c_loop_node>(std::move($2), std::move($4), std::move($6))); }
    ;
c_if_else:
    c_if 
    ELSE_KW L_CURL 
        c_statements 
    R_CURL                                      { $$ = std::move(std::make_unique<chips::c_if_else_node>(std::move($1),std::move($4))); }
    ;
c_if: 
    IF_KW L_PARENTH expr R_PARENTH L_CURL 
        c_statements 
    R_CURL                                      { $$ = std::move(std::make_unique<chips::c_if_node>(std::move($3), std::move($6))); }
    ;
function_call:
    NAME L_PARENTH exprs R_PARENTH              { $$ = std::move(std::make_unique<chips::function_call_node>(std::move($1),std::move($3))); }
    ;
function_call_sttmt:
    function_call                               { $$ = std::move(std::make_unique<chips::function_call_statement_node>(std::move($1))); }
    ;
exprs:
    list_expr                                   { $$ = std::move($1); }
    | /* EMPTY */                               { $$ = std::move(std::make_unique<chips::expressions_node>()); }
    ;
list_expr:
    expr                                        { $$ = std::move(std::make_unique<chips::expressions_node>()); $$->append($1); }
    | expr COMMA list_expr                      { $$ = std::move($3); $$->append($1); }
    ;

system:
    SYSTEM_KW optional_dim L_CURL 
        c_statements
    R_CURL                                      { $$ = std::move(std::make_unique<chips::system_node>(std::move($2), std::move($4))); }
    ;
optional_dim:
    DIMENSION_KW L_PARENTH INT R_PARENTH        { $$ = std::move(std::make_unique<chips::dimension_node>(std::move(std::make_unique<chips::number_literal_node>($3)))); }
    | /* EMPTY */                               { $$ = std::move(std::make_unique<chips::dimension_node>(std::move(std::make_unique<chips::number_literal_node>(0)))); }
    ;
c_statements:
    c_statement SEMICOL c_statements            { $$ = std::move($3); $$->append(std::move($1)); }
    | c_loop c_statements                       { $$ = std::move($2); $$->append(std::move($1)); }
    | c_if_else c_statements                    { $$ = std::move($2); $$->append(std::move($1)); }
    | c_if c_statements                         { $$ = std::move($2); $$->append(std::move($1)); }
    | /* EMPTY */                               { $$ = std::move(std::make_unique<chips::c_statements_node>()); }
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