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
// %type <std::unique_ptr<preambles_node>> preambles
%type <std::unique_ptr<chips::system_node>> system
// %type <std::unique_ptr<preamble_node>> preamble
// %type <std::unique_ptr<import_node>> import
// %type <std::unique_ptr<function_definition_node>> function_def
// %type <std::unique_ptr<signature_node>> pure_signature
// %type <std::unique_ptr<output_node>> output
// %type <std::unique_ptr<dataflow_declarations_node>> df_decl_list_or_nothing
// %type <std::unique_ptr<dataflow_declarations_node>> df_decl_list
// %type <std::unique_ptr<dataflow_declaration_node>> df_decl_lhs
// %type <std::unique_ptr<dataflow_type_node>> df_type
// %type <std::unique_ptr<expressions_node>> exprs
// %type <std::unique_ptr<signature_node>> object_signature
// %type <std::unique_ptr<statements_node>> statements
// %type <std::unique_ptr<statement_node>> statement
// %type <std::unique_ptr<loop_node>> loop
// %type <std::unique_ptr<if_node>> if
// %type <std::unique_ptr<if_else_node>> if_else
// %type <std::unique_ptr<dataflow_full_declaration_node>> df_full_decl
// %type <std::unique_ptr<assignment_node>> assignment
// %type <std::unique_ptr<function_call_node>> function_call
// %type <std::unique_ptr<function_call_statement_node>> function_call_sttmt
// %type <std::unique_ptr<rhs_assignment_node>> may_assign
// %type <std::unique_ptr<suffix_node>> suffix
// %type <std::unique_ptr<suffixes_node>> suffixes
// %type <std::unique_ptr<expression_node>> expr expr0 expr1 expr2
// %type <std::unique_ptr<suffixable_node>> suffixable_expr
// %type <std::unique_ptr<rhs_assignment_node>> assign_rhs
// %type <std::unique_ptr<expressions_node>> list_expr
%type <std::unique_ptr<chips::dimension_node>> optional_dim
// %type <std::unique_ptr<c_statements_node>> c_statements
// %type <std::unique_ptr<c_statement_node>> c_statement
// %type <std::unique_ptr<c_loop_node>> c_loop
// %type <std::unique_ptr<c_if_else_node>> c_if_else
// %type <std::unique_ptr<c_if_node>> c_if
// %type <std::unique_ptr<cast_node>> cast



%%

%start chips;

chips:
    preambles system                    { $$ = std::move(std::make_unique<chips::chips_node>(std::move($2)));
                                          drv.ast = std::move($$);                                          }
    ;
preambles:
    preamble preambles                  {/* $$ = std::move($2); $$->append($1);  $$->hello(); */}
    | /* EMPTY */                       {/* $$ = std::move(std::make_unique<preambles_node>());  $$->hello(); */}
    ;
preamble:
    import                              {/* $$ = std::move($1);  $$->hello(); */}
    | function_def                      {/* $$ = std::move($1);  $$->hello(); */}
    ;
import:
    IMPORT_KW STR AS_KW NAME SEMICOL   {/* $$ = std::move(std::make_unique<import_node>($4, $2));  $$->hello(); */}
    ;
function_def:
    pure_signature output               {/* $$ = std::move(std::make_unique<function_definition_node>($1,$2));  $$->hello(); */}
    | object_signature INIT_KW L_CURL 
        statements 
    R_CURL THEN_KW L_CURL 
        statements 
    R_CURL output                       {/* $$ = std::move(std::make_unique<function_definition_node>($1,$4,$8,$10));  $$->hello(); */}
    ;
pure_signature:
    PURE_KW NAME L_PARENTH df_decl_list_or_nothing R_PARENTH  {/* $$ = std::move(std::make_unique<signature_node>(PURE, $2, $4));  $$->hello(); */}
    ;
df_decl_list_or_nothing:
    df_decl_list                        {/* $$=std::move($1);  $$->hello(); */}
    | /* EMPTY */                       {/* $$=std::move(std::make_unique<dataflow_declarations_node>());  $$->hello(); */}
    ;
df_decl_list:
    df_decl_lhs                         {/* $$ = std::move(std::make_unique<dataflow_declarations_node>()); $$->append($1);  $$->hello(); */}
    | df_decl_lhs COMMA df_decl_list    {/* $$ = std::move($3); $$->append($1);  $$->hello(); */}
    ;
df_decl_lhs:
    df_type NAME                        {/* $$ = std::move(std::make_unique<dataflow_declaration_node>($1, $2));  $$->hello(); */}
    ;
df_type:
    INT_KW suffixes                     {/* $$ = std::move(std::make_unique<dataflow_type_node>(INT_DF,$2));  $$->hello(); */}
    | FLOAT_KW suffixes                 {/* $$ = std::move(std::make_unique<dataflow_type_node>(FLOAT_DF,$2));  $$->hello(); */}
    | BOOL_KW suffixes                  {/* $$ = std::move(std::make_unique<dataflow_type_node>(BOOL_DF,$2));  $$->hello(); */}
    ;
output:
    ARROW L_PARENTH exprs R_PARENTH     {/* $$ = std::move(std::make_unique<output_node>($3));  $$->hello(); */}
    ;
object_signature:
    VIRT_KW NAME L_PARENTH df_decl_list_or_nothing R_PARENTH           {/* $$ = std::move(std::make_unique<signature_node>(VIRTUAL, $2, $4));  $$->hello(); */}
    | PHYSICAL_KW NAME L_PARENTH df_decl_list_or_nothing R_PARENTH     {/* $$ = std::move(std::make_unique<signature_node>(PHYSICAL, $2, $4));  $$->hello(); */}
    ;
statements: 
    statement SEMICOL statements        {/* $$ = std::move($3); $$->append($1);  $$->hello(); */}
    | loop statements                   {/* $$ = std::move($2); $$->append((std::unique_ptr<statement_node>&)$1);  $$->hello(); */}
    | if_else statements                {/* $$ = std::move($2); $$->append((std::unique_ptr<statement_node>&)$1);  $$->hello(); */}
    | if statements                     {/* $$ = std::move($2); $$->append((std::unique_ptr<statement_node>&)$1);  $$->hello(); */}
    | /* EMPTY */                       {/* $$ = std::move(std::make_unique<statements_node>());  $$->hello(); */}
    ;
statement:
    df_full_decl                        {/* $$ = std::move($1);  $$->hello(); */}
    | assignment                        {/* $$ = std::move($1);  $$->hello(); */}
    ;
c_statement: 
    NAME suffixes NAME                                              {/* $$ = std::move(std::make_unique<function_declaration_node>($1, $2, $3));  $$->hello(); */}
    | NAME suffixes INPUT_SUF L_PARENTH exprs R_PARENTH             {/* $$ = std::move(std::make_unique<c_assignment_node>($1, $2, $5));  $$->hello(); */}
    | LINK_KW NAME TO_KW NAME                                       {/* $$ = std::move(std::make_unique<link_node>($2, $4));  $$->hello(); */}
    | NAME AT_KW L_PARENTH exprs R_PARENTH                          {/* $$ = std::move(std::make_unique<at_node>($1, $4));  $$->hello(); */}
    | df_full_decl                                                  {/* $$ = std::move($1);  $$->hello(); */}
    | assignment                                                    {/* $$ = std::move($1);  $$->hello(); */}
    | function_call_sttmt                                           {/* $$ = std::move($1);  $$->hello(); */}
    ;
df_full_decl:
    df_decl_lhs may_assign              {/* $$ = std::move(std::make_unique<dataflow_full_declaration_node>($1, $2));  $$->hello(); */}
    ;
suffixes:
    suffix suffixes                     {/* $$ = std::move($2); $$->append($1);  $$->hello(); */}
    | /* EMPTY */                       {/* $$ = std::move(std::make_unique<suffixes_node>());  $$->hello(); */}
    ;
suffix:
    L_SQUA expr R_SQUA                  {/* $$ = std::move(std::make_unique<suffix_node>($2));  $$->hello(); */}
    | L_SQUA R_SQUA                     {/* $$ = std::move(std::make_unique<suffix_node>());  $$->hello(); */}
    ;
may_assign:
    assign_rhs                          {/* $$ = std::move($1);  $$->hello(); */}
    | /* EMPTY */                       {/* $$ = std::move(std::make_unique<rhs_assignment_node>());  $$->hello(); */}
    ;
assign_rhs: 
    ASSIGN expr                         {/* $$ = std::move(std::make_unique<rhs_assignment_node>($2));  $$->hello(); */}
    ;
cast:
    df_type L_PARENTH expr R_PARENTH    {/* $$ = std::move(std::make_unique<cast_node>($1, $3));  $$->hello(); */}
    ;
expr:
    expr0 LT expr                       {/* $$ = std::move(std::make_unique<binary_expression_node>($1,LT_EXP,$3));  $$->hello(); */}
    | expr0 GT expr                     {/* $$ = std::move(std::make_unique<binary_expression_node>($1,GT_EXP,$3));  $$->hello(); */}
    | expr0 LEQ expr                    {/* $$ = std::move(std::make_unique<binary_expression_node>($1,LEQ_EXP,$3));  $$->hello(); */}
    | expr0 GEQ expr                    {/* $$ = std::move(std::make_unique<binary_expression_node>($1,GEQ_EXP,$3));  $$->hello(); */}
    | expr0 NEQ expr                    {/* $$ = std::move(std::make_unique<binary_expression_node>($1,NEQ_EXP,$3));  $$->hello(); */}
    | expr0 EQ expr                     {/* $$ = std::move(std::make_unique<binary_expression_node>($1,EQ_EXP,$3));  $$->hello(); */}
    | expr0                             {/* $$ = std::move($1);  $$->hello(); */}
    ;
expr0:
    expr1 PLUS expr0                    {/* $$ = std::move(std::make_unique<binary_expression_node>($1,PLUS_EXP,$3));  $$->hello(); */}
    | expr1 MINUS expr0                 {/* $$ = std::move(std::make_unique<binary_expression_node>($1,MINUS_EXP,$3));  $$->hello(); */}
    | MINUS expr0                       {/* $$ = std::move(std::make_unique<unary_expression_node>(U_MINUS_EXP,$2));  $$->hello(); */}
    | expr1                             {/* $$ = std::move($1);  $$->hello(); */}
    ;
expr1: 
    expr2 TIMES expr1                   {/* $$ = std::move(std::make_unique<binary_expression_node>($1,TIMES_EXP,$3));  $$->hello(); */}
    | expr2 DIV expr1                   {/* $$ = std::move(std::make_unique<binary_expression_node>($1,DIV_EXP,$3));  $$->hello(); */}
    | expr2 MOD expr1                   {/* $$ = std::move(std::make_unique<binary_expression_node>($1,MOD_EXP,$3));  $$->hello(); */}
    | expr2                             {/* $$ = std::move($1);  $$->hello(); */}
    | NOT expr2                         {/* $$ = std::move(std::make_unique<unary_expression_node>(NOT_EXP,$2));  $$->hello(); */}
    ;
expr2: 
    suffixable_expr suffixes                    {/* $$ = std::move(std::make_unique<suffixised_node>($1,$2));  $$->hello(); */}
    | INT                                       {/* $$ = std::move(std::make_unique<number_literal_node>($1));  $$->hello(); */}
    | FLOAT                                     {/* $$ = std::move(std::make_unique<number_literal_node>($1));  $$->hello(); */}
    | BOOL                                      {/* $$ = std::move(std::make_unique<number_literal_node>($1));  $$->hello(); */}
    | L_PARENTH expr R_PARENTH                  {/* $$ = std::move($2);  $$->hello(); */}
    | cast                                      {/* $$ = std::move($1);  $$->hello(); */}
    ;
suffixable_expr:
    function_call                               {/* $$ = std::move($1);  $$->hello(); */}
    | NAME                                      {/* $$ = std::move(std::make_unique<variable_node>($1));  $$->hello(); */}
    | NAME OUTPUT_SUF                           {/* $$ = std::move(std::make_unique<object_virtual_output_node>($1));  $$->hello(); */}
    | THIS_KW PERIOD NAME PERIOD NAME           {/* $$ = std::move(std::make_unique<object_physical_attribute_node>($5,$3));  $$->hello(); */}
    ;
assignment:
    NAME suffixes assign_rhs                                   {/* $$ = std::move(std::make_unique<variable_assignment_node>($1, $2, $3));  $$->hello(); */}
    | THIS_KW PERIOD NAME PERIOD NAME suffixes assign_rhs      {/* $$ = std::move(std::make_unique<this_assignment_node>($3, $5, $6, $7));  $$->hello(); */}
    ;
loop:
    FOREACH_KW NAME IN_KW suffixable_expr L_CURL 
        statements 
    R_CURL                                      {/* $$ = std::move(std::make_unique<loop_node>($2,(std::unique_ptr<suffixable_node>&)$4,$6));  $$->hello(); */}
    ;
if_else:
    if 
    ELSE_KW L_CURL 
        statements 
    R_CURL                                      {/* $$ = std::move(std::make_unique<if_else_node>($1,$4));  $$->hello(); */}
    ;
if: 
    IF_KW L_PARENTH expr R_PARENTH L_CURL 
        statements 
    R_CURL                                      {/* $$ = std::move(std::make_unique<if_node>($3,$6));  $$->hello(); */}
    ;
c_loop:
    FOREACH_KW NAME IN_KW suffixable_expr L_CURL 
        c_statements 
    R_CURL                                      {/* $$ = std::move(std::make_unique<c_loop_node>($2,(std::unique_ptr<suffixable_node>&) $4, $6));  $$->hello(); */}
    ;
c_if_else:
    c_if 
    ELSE_KW L_CURL 
        c_statements 
    R_CURL                                      {/* $$ = std::move(std::make_unique<c_if_else_node>($1,$4));  $$->hello(); */}
    ;
c_if: 
    IF_KW L_PARENTH expr R_PARENTH L_CURL 
        c_statements 
    R_CURL                                      {/* $$ = std::move(std::make_unique<c_if_node>($3,$6));  $$->hello(); */}
    ;
function_call:
    NAME L_PARENTH exprs R_PARENTH              {/* $$ = std::move(std::make_unique<function_call_node>($1,$3));  $$->hello(); */}
    ;
function_call_sttmt:
    function_call                               {/* $$ = std::move(std::make_unique<function_call_statement_node>($1));  $$->hello(); */}
    ;
exprs:
    list_expr                                   {/* $$ = std::move($1);  $$->hello(); */}
    | /* EMPTY */                               {/* $$ = std::move(std::make_unique<expressions_node>());  $$->hello(); */}
    ;
list_expr:
    expr                                        {/* $$ = std::move(std::make_unique<expressions_node>()); $$->append($1);  $$->hello(); */}
    | expr COMMA list_expr                      {/* $$ = std::move($3); $$->append($1);  $$->hello(); */}
    ;

system:
    SYSTEM_KW optional_dim L_CURL 
        c_statements
    R_CURL                                      {/* $$ = std::move(std::make_unique<system_node>($2, $4));  $$->hello(); */ $$ = std::move(std::make_unique<chips::system_node>(std::move($2))); }
    ;
optional_dim:
    DIMENSION_KW L_PARENTH INT R_PARENTH        { $$ = std::move(std::make_unique<chips::dimension_node>(std::move(std::make_unique<chips::number_literal_node>($3)))); }
    | /* EMPTY */                               { $$ = std::move(std::make_unique<chips::dimension_node>(std::move(std::make_unique<chips::number_literal_node>(0)))); }
    ;
c_statements:
    c_statement SEMICOL c_statements            {/* $$ = std::move($3); $$->append((std::unique_ptr<c_statement_node>&)$1);  $$->hello(); */}
    | c_loop c_statements                       {/* $$ = std::move($2); $$->append((std::unique_ptr<c_statement_node>&)$1);  $$->hello(); */}
    | c_if_else c_statements                    {/* $$ = std::move($2); $$->append((std::unique_ptr<c_statement_node>&)$1);  $$->hello(); */}
    | c_if c_statements                         {/* $$ = std::move($2); $$->append((std::unique_ptr<c_statement_node>&)$1);  $$->hello(); */}
    | /* EMPTY */                               {/* $$ = std::move(std::make_unique<c_statements_node>());  $$->hello(); */}
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