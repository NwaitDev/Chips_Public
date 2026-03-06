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
    #include "cpp_sources/parserXmetamodel/chips_ast_classes.hpp"
    #include "cpp_sources/parserXmetamodel/chips_overall_definition.hpp"
    #include "cpp_sources/parserXmetamodel/chips_overall_variable.hpp"
    #include "cpp_sources/parserXmetamodel/chips_overall_stts.hpp"
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
%token COMMA ARROW L_PARENTH R_PARENTH L_CURL R_CURL L_SQUA R_SQUA SEMICOL ASSIGN COLUMN PLUS MINUS TIMES DIV MOD LT GT LEQ GEQ NEQ EQ AND OR NOT INT_KW FLOAT_KW BOOL_KW LOGICAL_KW PHYSICAL_KW AS_KW INIT_KW THEN_KW FOREACH_KW TO_KW IN_KW IF_KW ELSE_KW SYSTEM_KW LINK_KW PERIOD IMPLEMENTS_KW HAVING_KW INPUT_KW STOP_KW CHANNEL_KW CHANNELS_KW AMONG_KW SPREAD_KW COLLECT_KW SRC_CHAN_KW CTX_KW OBJECT_KW WITH_KW IMPLEMENTATION_KW BY_KW TARGET_KW DEFAULT_KW USING_KW ACTUATOR_KW SENSOR_KW

%left PLUS MINUS
%left TIMES DIV


/*defining the variable tokens of the grammar*/
%token <int> INT
%token <double> FLOAT
%token <std::string> IDENTIFIER
%token <std::string> STR
%token <bool> BOOL


/*defining the non-terminal symbols of the grammar*/
%type <std::unique_ptr<chips::program_node>> chips
%type <std::unique_ptr<chips::preamble_section_node>> preambles
%type <std::unique_ptr<chips::system_section_node>> system
// %type <std::unique_ptr<chips_node>> chips
// %type <std::unique_ptr<preambles_node>> preambles
// %type <std::unique_ptr<system_node>> system

%type <std::unique_ptr<chips::definition>> preamble
// %type <std::unique_ptr<preamble_node>> preamble
// %type <std::unique_ptr<object_definition_node>> object_def
// %type <std::unique_ptr<implementation_definition_node>> implementation_def
// %type <std::unique_ptr<node_mappings_node>> node_mappings
// %type <std::unique_ptr<collective_operation_definition_node>> collective_op_def
%type <std::unique_ptr<chips::function_definition>> function_def l_function_def
// %type <std::unique_ptr<function_definition_node>> function_def p_function_def l_function_def

%type <std::vector<chips::function_parameter_variant>> df_parameter_list
// %type <chips::function_parameter_variant> df_parameter_decl
// %type <std::unique_ptr<dataflow_parameter_decls_node>> df_parameter_list
// %type <std::unique_ptr<physical_dataflow_parameter_decls_node>> pdf_parameter_list
// %type <std::unique_ptr<dataflow_parameter_decls_node>> df_parameter_decls
// %type <std::unique_ptr<physical_dataflow_parameter_decls_node>> pdf_parameter_decls
// %type <std::unique_ptr<dataflow_parameter_decl_node>> df_parameter_decl
// %type <std::unique_ptr<physical_dataflow_parameter_decl_node>> pdf_parameter_decl
// %type <std::unique_ptr<chips::primitive_variable>> df_type
// %type <std::unique_ptr<physical_dataflow_parameter_type_node>> pdf_parameter_type
// %type <std::unique_ptr<chips::dataflow_assignment>> may_assign
// %type <std::unique_ptr<with_section_node>> with_section
// %type <std::unique_ptr<with_statements_node>> with_statements
// %type <std::unique_ptr<statement_node>> with_statement
%type <std::unique_ptr<chips::init_section>> init_section
%type <std::unique_ptr<chips::then_section>> then_section
%type <std::vector<chips::primitive_statement_variant>> statements
// %type <std::unique_ptr<statement_node>> statement
// %type <std::unique_ptr<expression_node>> loop_in
// %type <std::unique_ptr<loop_node>> loop_statement
// %type <std::unique_ptr<if_node>> if_statement
// %type <std::unique_ptr<if_else_node>> if_else_statement
// %type <std::unique_ptr<physical_named_outputs_node>> p_named_outputs
%type <std::vector<chips::function_output_variant>> named_outputs
// %type <std::unique_ptr<physical_named_output_node>> p_named_output
// %type <std::unique_ptr<named_output_node>> named_output

// %type <std::unique_ptr<suffixes_node>> suffixes c_suffixes

// %type <std::unique_ptr<expressions_node>> list_expr
// %type <std::unique_ptr<expressions_node>> exprs
// %type <std::unique_ptr<expression_node>> expr expr0 expr1 expr2
// %type <std::unique_ptr<cast_node>> cast

// %type <std::unique_ptr<s_statements_node>> s_statements
// %type <std::unique_ptr<s_statement_node>> s_statement
// %type <std::unique_ptr<s_if_node>> s_if_statement
// %type <std::unique_ptr<s_if_else_node>> s_if_else_statement
// %type <std::unique_ptr<s_loop_node>> s_loop_statement

// %type <std::unique_ptr<c_expressions_node>> c_list_expr c_exprs
// %type <std::unique_ptr<c_cast_node>> c_cast
// %type <std::unique_ptr<c_keywords_node>> c_keywords
// %type <std::unique_ptr<c_signature_node>> c_signature
// %type <std::unique_ptr<expression_node>> c_expr c_stopless_expr c_stopless_expr0 c_stopless_expr1 c_stopless_expr2
// %type <std::unique_ptr<collective_dataflow_defaulted_decls_node>> cdf_defaulted_decls
// %type <std::unique_ptr<collective_dataflow_defaulted_decl_node>> cdf_defaulted_decl
// %type <std::unique_ptr<c_output_node>> c_output
// %type <std::unique_ptr<c_optionnal_outputs_node>> c_optionnal_outputs
// %type <std::unique_ptr<c_statements_node>> c_statements
// %type <std::unique_ptr<c_statement_node>> c_statement
// %type <std::unique_ptr<c_loop_node>> c_loop_statement
// %type <std::unique_ptr<c_if_node>> c_if_statement
// %type <std::unique_ptr<c_if_else_node>> c_if_else_statement
// %type <std::unique_ptr<collective_dataflow_full_declaration_node>> cdf_full_declaration
// %type <std::unique_ptr<collective_rhs_assignment_node>> c_may_assign

// %type <std::unique_ptr<expression_node>> s_suffixable_expr
// %type <std::unique_ptr<expression_node>> s_expr
// %type <std::unique_ptr<block_node>> block
// %type <std::unique_ptr<collective_operation_node>> collective_operation

%%

%start chips;
chips:
    preambles system                        { /*auto preambles = std::move($1);
                                              auto system = std::move($2);
                                              $$ = std::move(std::make_unique<chips::program_node>(preambles, system));
                                              $$->set_line(@$.begin.line);
                                              $$->set_column(@$.begin.column);
                                              drv.ast = std::move($$);*/
                                              $$ = std::make_unique<chips::program_node>(drv.file, std::move($1), std::move($2));
                                              $$->set_line(@$.begin.line);
                                              $$->set_column(@$.begin.column);
                                              drv.ast = std::move($$);                                                    }
    ;
preambles:
    preamble preambles                      { $$ = std::move($2); $$->append(std::move(std::move($1))); 
                                              $$->set_line(@$.begin.line);
                                              $$->set_column(@$.begin.column);}
    | /* EMPTY */                           { $$ = std::move(std::make_unique<chips::preamble_section_node>()); /*$$ = std::move(std::make_unique<preambles_node>());*/ }                       
    ;
system:
    SYSTEM_KW  L_CURL                       
        s_statements
    R_CURL                                  { /*$$ = std::move(std::make_unique<system_node>(std::move($3)));
                                              $$->set_line(@$.begin.line);
                                              $$->set_column(@$.begin.column);*/ }
    | /* EMPTY */                           { $$ = std::move(std::make_unique<chips::system_section_node>()); /*$$ = std::move(std::make_unique<system_node>());*/ }
    ;
preamble:
    object_def                              { /*$$ = std::move($1);*/ }
    | function_def                          { $$ = std::move(std::move($1)); }            
    | collective_op_def                     { /*$$ = std::move($1);*/ }
    | implementation_def                    { /*$$ = std::move($1);*/ }
    ;
object_def:
    OBJECT_KW IDENTIFIER with_section       { /*$$ = std::move(std::make_unique<object_definition_node>(std::move($2), std::move($3)));
                                              $$->set_line(@$.begin.line);
                                              $$->set_column(@$.begin.column);*/ }
    ;
implementation_def:
    IMPLEMENTATION_KW IDENTIFIER COLUMN IDENTIFIER BY_KW IDENTIFIER L_CURL
        node_mappings
    R_CURL                                  { /*$$ = std::move(std::make_unique<implementation_definition_node>(std::move($2), std::move($4), std::move($6), std::move($8)));
                                              $$->set_line(@$.begin.line);
                                              $$->set_column(@$.begin.column);*/ }
    ;
node_mappings:
    HAVING_KW IDENTIFIER AS_KW IDENTIFIER SEMICOL node_mappings { /*$$ = std::move(std::make_unique<node_mappings_node>(std::move($2), std::move($4), std::move($6)));
                                                                  $$->set_line(@$.begin.line);
                                                                  $$->set_column(@$.begin.column);*/ }
    | /* EMPTY */                                               { /*$$ = std::move(std::make_unique<node_mappings_node>());*/ }
    ;
function_def:
    l_function_def                          { $$ = std::move($1); }
    | p_function_def                        { /*$$ = std::move($1);*/ }
    ;
collective_op_def:
    c_signature L_CURL
        c_statements
    R_CURL
    ARROW TARGET_KW L_PARENTH c_list_expr R_PARENTH
    c_output
    c_optionnal_outputs                     { /*$$ = std::move(std::make_unique<collective_operation_definition_node>(std::move($1), std::move($3), std::move($8), std::move($10), std::move($11)));
                                              $$->set_line(@$.begin.line);
                                              $$->set_column(@$.begin.column);*/ }
    ;
c_optionnal_outputs:
    c_output c_optionnal_outputs            { /*$$ = std::move($2); $$->append(std::move($1)); 
                                              $$->set_line(@$.begin.line);
                                              $$->set_column(@$.begin.column);*/}
    | /* EMPTY */                           { /*$$ = std::move(std::make_unique<c_optionnal_outputs_node>());*/ }
    ;
c_output:
    ARROW DEFAULT_KW L_PARENTH c_list_expr R_PARENTH    { /*$$ = std::move(std::make_unique<c_output_node>(std::move($4)));
                                                          $$->set_line(@$.begin.line);
                                                          $$->set_column(@$.begin.column);*/ }
    | ARROW IDENTIFIER L_PARENTH c_list_expr R_PARENTH  { /*$$ = std::move(std::make_unique<c_output_node>(std::move($2), std::move($4)));
                                                          $$->set_line(@$.begin.line);
                                                          $$->set_column(@$.begin.column);*/ }
    ;
l_function_def:
    LOGICAL_KW IDENTIFIER L_PARENTH df_parameter_list R_PARENTH
    init_section
    then_section
    named_outputs                  { /*$$ = std::move(std::make_unique<chips::logical_definition>(std::move($2), std::move($4), std::move($6), std::move($7), std::move($8)));
                                     $$->set_line(@$.begin.line);
                                     $$->set_column(@$.begin.column);*/
                                     auto def = std::make_unique<chips::logical_definition>(
                                     std::move($2), std::move($4), std::move($6), std::move($7), std::move($8));
                                     def->set_line(@$.begin.line);
                                     def->set_column(@$.begin.column);
                                     $$ = std::move(def);
                                      }
    ;
p_function_def:
    PHYSICAL_KW IDENTIFIER L_PARENTH pdf_parameter_list R_PARENTH
    with_section
    init_section
    then_section
    p_named_outputs                 {/* $$ = std::move(std::make_unique<physical_function_definition_node>(std::move($2), std::move($4), std::move($6), std::move($7), std::move($8), std::move($9)));
                                      $$->set_line(@$.begin.line);
                                      $$->set_column(@$.begin.column);*/ }
    ;
c_signature:
    c_keywords L_PARENTH cdf_defaulted_decls R_PARENTH 
      IDENTIFIER AMONG_KW IDENTIFIER    { /*$$ = std::move(std::make_unique<c_signature_node>(std::move($1), std::move($3), std::move($5), std::move($7)));
                                          $$->set_line(@$.begin.line);
                                          $$->set_column(@$.begin.column);*/ }
    ;
c_keywords:
    SPREAD_KW           { /*$$ = std::move(std::make_unique<spread_node>()); 
                          $$->set_line(@$.begin.line);
                          $$->set_column(@$.begin.column);*/}
    | COLLECT_KW        { /*$$ = std::move(std::make_unique<collect_node>());
                          $$->set_line(@$.begin.line);
                          $$->set_column(@$.begin.column);*/ }
    ;
with_section:
    WITH_KW L_CURL      
        with_statements
    R_CURL              { /*$$ = std::move(std::make_unique<with_section_node>(std::move($3)));
                          $$->set_line(@$.begin.line);
                          $$->set_column(@$.begin.column);*/ }
    | /* EMPTY */       { /*$$ = std::move(std::make_unique<with_section_node>());*/ }
    ;
with_statements:
    with_statement with_statements  { /*$$ = std::move($2); $$->append(std::move($1));
                                      $$->set_line(@$.begin.line);
                                      $$->set_column(@$.begin.column);*/ }
    | /* EMPTY */                   { /*$$ = std::move(std::make_unique<with_statements_node>());*/ }
    ;
with_statement:
    IDENTIFIER IDENTIFIER SEMICOL                   { /*$$ = std::move(std::make_unique<with_two_identifier_node>(std::move($1), std::move($2)));
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    | CTX_KW df_type IDENTIFIER may_assign SEMICOL  { /*$$ = std::move(std::make_unique<with_context_statement_node>(std::move($2), std::move($3), std::move($4)));
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    | statement                                     { /*$$ = std::move($1);*/ }
    ;
init_section:
    INIT_KW L_CURL      
        statements 
    R_CURL              { $$ = std::move(std::make_unique<chips::init_section>(std::move($3))); 
                          $$->set_line(@$.begin.line);
                          $$->set_column(@$.begin.column);}
    | /* EMPTY */       { $$ = nullptr; }
    ;
then_section:
    THEN_KW L_CURL 
        statements      
    R_CURL              { $$ = std::move(std::make_unique<chips::then_section>(std::move($3)));
                          $$->set_line(@$.begin.line);
                          $$->set_column(@$.begin.column); }
    | /* EMPTY */       { $$ = nullptr; }
    ;
list_expr:
    exprs               { /*$$ = std::move($1);*/ }
    | /* EMPTY */       { /*$$ = std::move(std::make_unique<expressions_node>());*/ }
    ;
c_list_expr:
    c_exprs             { /*$$ = std::move($1);*/ }
    | /* EMPTY */       { /*$$ = std::move(std::make_unique<c_expressions_node>());*/ }
    ;
exprs:
    expr                { /*$$ = std::move(std::make_unique<expressions_node>()); $$->append(std::move($1));
                          $$->set_line(@$.begin.line);
                          $$->set_column(@$.begin.column);*/ }
    | expr COMMA exprs  { /*$$ = std::move(std::move($3)); $$->append(std::move($1)); 
                          $$->set_line(@$.begin.line);
                          $$->set_column(@$.begin.column);*/}
    ;
c_exprs:
    c_expr                  { /*$$ = std::move(std::make_unique<c_expressions_node>()); $$->append(std::move($1));
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);*/ }
    | c_expr COMMA c_exprs  { /*$$ = std::move($3); $$->append(std::move($1));
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);*/ }
    ;
expr:
    expr0 LT expr           { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), LT_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | expr0 GT expr         { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), GT_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | expr0 LEQ expr        { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), LEQ_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | expr0 GEQ expr        { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), GEQ_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | expr0 NEQ expr        { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), NEQ_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | expr0 EQ expr         { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), EQ_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | expr0 AND expr        { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), AND_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | expr0 OR expr         { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), OR_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | expr0                 { /*$$ = std::move($1);*/ }
    ;
expr0:
    expr1 PLUS expr0        { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), PLUS_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | expr1 MINUS expr0     { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), MINUS_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | MINUS expr0           { /*$$ = std::move(std::make_unique<unary_expression_node>(U_MINUS_EXP, std::move($2))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | expr1                 { /*$$ = std::move($1);*/ }
    ;
expr1: 
    expr2 TIMES expr1       { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), TIMES_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);

                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }  */
                            }
    | expr2 DIV expr1       {/* $$ = std::move(std::make_unique<binary_expression_node>(std::move($1), DIV_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | expr2 MOD expr1       { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), MOD_EXP, std::move($3))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    | expr2                 { /*$$ = std::move($1);*/ }
    | NOT expr2             { /*$$ = std::move(std::make_unique<unary_expression_node>(NOT_EXP, std::move($2))); 
                              $$->set_line(@$.begin.line);
                              $$->set_column(@$.begin.column);
                              
                              if($$->have_implicit_cast()){
                                throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                              }*/
                            }
    ;
expr2: 
    IDENTIFIER suffixes         { /*$$ = std::move(std::make_unique<suffixised_node>(std::move($1), std::move($2))); 
                                  $$->set_line(@$.begin.line);
                                  $$->set_column(@$.begin.column);*/}
    | INT                       {/* $$ = std::move(std::make_unique<number_literal_node>(std::move($1))); 
                                  $$->set_line(@$.begin.line);
                                  $$->set_column(@$.begin.column);*/}
    | FLOAT                     { /*$$ = std::move(std::make_unique<number_literal_node>(std::move($1))); 
                                  $$->set_line(@$.begin.line);
                                  $$->set_column(@$.begin.column);*/}
    | BOOL                      { /*$$ = std::move(std::make_unique<number_literal_node>(std::move($1))); 
                                  $$->set_line(@$.begin.line);
                                  $$->set_column(@$.begin.column);*/}
    | L_PARENTH expr R_PARENTH  { /*$$ = std::move(std::make_unique<paren_expression_node>(std::move($2))); 
                                  $$->set_line(@$.begin.line);
                                  $$->set_column(@$.begin.column);*/}
    | CTX_KW PERIOD IDENTIFIER suffixes       { /*$$ = std::move(std::make_unique<context_decl_node>(std::move($3), std::move($4))); 
                                                $$->set_line(@$.begin.line);
                                                $$->set_column(@$.begin.column);*/}
    | IDENTIFIER L_PARENTH list_expr R_PARENTH { /*$$ = std::move(std::make_unique<integrated_function_node>(std::move($1), std::move($3))); 
                                                 $$->set_line(@$.begin.line);
                                                $$->set_column(@$.begin.column);*/}
    | cast                      { /*$$ = std::move($1);*/ }
    ;
cast:
    L_PARENTH df_type R_PARENTH expr           { /*$$ = std::move(std::make_unique<cast_node>(std::move($2), std::move($4))); 
                                                 $$->set_line(@$.begin.line);
                                                 $$->set_column(@$.begin.column);
                                                 
                                                 if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                 }*/
                                                }
    ;
c_expr:
    c_stopless_expr                             { /*$$ = std::move($1);*/ }
    | STOP_KW                                   { /*$$ = std::move(std::make_unique<stop_node>()); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    ;
c_stopless_expr:
    c_stopless_expr0 LT c_stopless_expr         { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), LT_EXP, std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr0 GT c_stopless_expr       { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), GT_EXP, std::move($3)));
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr0 LEQ c_stopless_expr      { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), LEQ_EXP, std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr0 GEQ c_stopless_expr      { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), GEQ_EXP, std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr0 NEQ c_stopless_expr      { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), NEQ_EXP, std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr0 EQ c_stopless_expr       { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), EQ_EXP, std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr0 AND c_stopless_expr      { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), AND_EXP, std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr0 OR c_stopless_expr       { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), OR_EXP, std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr0                          { /*$$ = std::move($1);*/ }
    ;
c_stopless_expr0:
    c_stopless_expr1 PLUS c_stopless_expr0      { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), PLUS_EXP, std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr1 MINUS c_stopless_expr0   { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), MINUS_EXP, std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | MINUS c_stopless_expr0                    { /*$$ = std::move(std::make_unique<unary_expression_node>(U_MINUS_EXP, std::move($2))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr1                          { /*$$ = std::move($1);*/ }
    ;
c_stopless_expr1: 
    c_stopless_expr2 TIMES c_stopless_expr1     { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), TIMES_EXP, std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr2 DIV c_stopless_expr1     { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), DIV_EXP, std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr2 MOD c_stopless_expr1     { /*$$ = std::move(std::make_unique<binary_expression_node>(std::move($1), MOD_EXP, std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    | c_stopless_expr2                          { /*$$ = std::move($1);*/ }
    | NOT c_stopless_expr2                      { /*$$ = std::move(std::make_unique<unary_expression_node>(NOT_EXP, std::move($2))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    ;
c_stopless_expr2: 
    IDENTIFIER c_suffixes                       { /*$$ = std::move(std::make_unique<suffixised_node>(std::move($1), std::move($2))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | INT                                       { /*$$ = std::move(std::make_unique<number_literal_node>(std::move($1))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | FLOAT                                     { /*$$ = std::move(std::make_unique<number_literal_node>(std::move($1))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | BOOL                                      { /*$$ = std::move(std::make_unique<number_literal_node>(std::move($1))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | INPUT_KW                                  { /*$$ = std::move(std::make_unique<input_node>()); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | CTX_KW PERIOD IDENTIFIER c_suffixes       { /*$$ = std::move(std::make_unique<context_expression_node>(std::move($3), std::move($4))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | IDENTIFIER L_PARENTH list_expr R_PARENTH  { /*$$ = std::move(std::make_unique<integrated_function_node>(std::move($1), std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | L_PARENTH c_stopless_expr R_PARENTH       { /*$$ = std::move($2);*/ }
    | c_cast                                    { /*$$ = std::move($1);*/ }
    ;
c_cast:
    L_PARENTH df_type R_PARENTH c_stopless_expr { /*$$ = std::move(std::make_unique<c_cast_node>(std::move($2), std::move($4))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);
                                                  
                                                  if($$->have_implicit_cast()){
                                                    throw syntax_error(@$, "Implicit cast doesn't exist in chips");
                                                  }*/
                                                }
    ;
suffixes:
    L_SQUA expr R_SQUA suffixes                 { /*$$ = std::move($4); $$->append(std::move($2)); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | /* EMPTY */                               { /*$$ = std::move(std::make_unique<suffixes_node>());*/ }
    ;
c_suffixes:
    L_SQUA c_stopless_expr R_SQUA c_suffixes    { /*$$ = std::move(std::move($4)); $$->append(std::move($2)); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | /* EMPTY */                               { /*$$ = std::move(std::make_unique<suffixes_node>());*/ }
    ;
s_suffixable_expr:
    IDENTIFIER                                  { /*$$ = std::move(std::make_unique<variable_node>(std::move($1))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | block PERIOD IDENTIFIER                   { /*$$ = std::move(std::make_unique<plugging_expr_node>(std::move($1), std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | IDENTIFIER L_PARENTH list_expr R_PARENTH { /*$$ = std::move(std::make_unique<integrated_function_node>(std::move($1), std::move($3))); 
                                                 $$->set_line(@$.begin.line);
                                                 $$->set_column(@$.begin.column);*/}
    ;
block:
    IDENTIFIER suffixes                         { /*$$ = std::move(std::make_unique<block_node>(std::move($1), std::move($2))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    ;

loop_in:
    IDENTIFIER                                 { /*$$ = std::move(std::make_unique<variable_node>(std::move($1))); 
                                                 $$->set_line(@$.begin.line);
                                                 $$->set_column(@$.begin.column);*/}
    | IDENTIFIER L_PARENTH list_expr R_PARENTH { /*$$ = std::move(std::make_unique<integrated_function_node>(std::move($1), std::move($3))); 
                                                 $$->set_line(@$.begin.line);
                                                 $$->set_column(@$.begin.column);*/}
    ;
loop_statement:
    FOREACH_KW IDENTIFIER IN_KW loop_in L_CURL 
        statements 
    R_CURL                                      { /*$$ = std::move(std::make_unique<loop_node>(std::move($2), std::move($4), std::move($6))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    ;
c_loop_statement:
    FOREACH_KW IDENTIFIER IN_KW loop_in L_CURL
        c_statements 
    R_CURL                                      { /*$$ = std::move(std::make_unique<c_loop_node>(std::move($2), std::move($4), std::move($6))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    ;
s_loop_statement:
    FOREACH_KW IDENTIFIER IN_KW s_suffixable_expr L_CURL 
        s_statements 
    R_CURL                                      { /*$$ = std::move(std::make_unique<s_loop_node>(std::move($2), std::move($4), std::move($6))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    ;
if_else_statement:
    if_statement 
    ELSE_KW L_CURL 
        statements 
    R_CURL                                      { /*$$ = std::move(std::make_unique<if_else_node>(std::move($1), std::move($4))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    ;
s_if_else_statement:
    s_if_statement 
    ELSE_KW L_CURL 
        s_statements 
    R_CURL                                      { /*$$ = std::move(std::make_unique<s_if_else_node>(std::move($1), std::move($4))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    ;
c_if_else_statement:
    c_if_statement
    ELSE_KW L_CURL 
        c_statements 
    R_CURL                                      { /*$$ = std::move(std::make_unique<c_if_else_node>(std::move($1), std::move($4))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    ;
if_statement: 
    IF_KW L_PARENTH expr R_PARENTH L_CURL 
        statements 
    R_CURL                                      { /*$$ = std::move(std::make_unique<if_node>(std::move($3), std::move($6))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    ;
s_if_statement: 
    IF_KW L_PARENTH expr R_PARENTH L_CURL 
        s_statements 
    R_CURL                                      { /*$$ = std::move(std::make_unique<s_if_node>(std::move($3), std::move($6))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    ;
c_if_statement: 
    IF_KW L_PARENTH c_expr R_PARENTH L_CURL 
        c_statements
    R_CURL                                      { /*$$ = std::move(std::make_unique<c_if_node>(std::move($3), std::move($6))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    ;
statements: 
    statement statements                        { /*$$ = std::move($2); $$->append(std::move($1)); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | loop_statement statements                 { /*$$ = std::move($2); $$->append(std::move($1)); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | if_else_statement statements              { /*$$ = std::move($2); $$->append(std::move($1)); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | if_statement statements                   { /*$$ = std::move($2); $$->append(std::move($1)); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | /* EMPTY */                               { $$ = std::vector<chips::primitive_statement_variant>(); }
    ;
s_statements:
    s_statement s_statements                    { /*$$ = std::move($2); $$->append(std::move($1)); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | s_loop_statement s_statements             { /*$$ = std::move($2); $$->append(std::move($1));
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/ }
    | s_if_else_statement s_statements          { /*$$ = std::move($2); $$->append(std::move($1)); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | s_if_statement s_statements               { /*$$ = std::move($2); $$->append(std::move($1)); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | /* EMPTY */                               { /*$$ = std::move(std::make_unique<s_statements_node>());*/ }
    ;
statement:
    df_type IDENTIFIER may_assign SEMICOL       { /*$$ = std::move(std::make_unique<dataflow_full_declaration_node>(std::move($1), std::move($2), std::move($3))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | IDENTIFIER suffixes ASSIGN expr SEMICOL   { /*$$ = std::move(std::make_unique<variable_assignment_node>(std::move($1), std::move($2), std::move($4))); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    | CTX_KW PERIOD IDENTIFIER suffixes ASSIGN expr SEMICOL { /*$$ = std::move(std::make_unique<context_variable_assignment_node>(std::move($3), std::move($4), std::move($6))); 
                                                              $$->set_line(@$.begin.line);
                                                              $$->set_column(@$.begin.column);*/}
    ;
s_statement:
    IDENTIFIER suffixes IDENTIFIER SEMICOL        { /*$$ = std::move(std::make_unique<functionnal_block_instanciation_node>(std::move($1), std::move($2), std::move($3)));
                                                    $$->set_line(@$.begin.line);
                                                    $$->set_column(@$.begin.column);*/ }/* functionnal block instanciation */
    | block PERIOD IDENTIFIER suffixes L_PARENTH s_expr R_PARENTH SEMICOL { /*$$ = std::move(std::make_unique<plugging_node>(std::move($1), std::move($3), std::move($4), std::move($6)));
                                                                            $$->set_line(@$.begin.line);
                                                                            $$->set_column(@$.begin.column);*/ } /* plugging expr to block input */
    | LINK_KW IDENTIFIER suffixes TO_KW IDENTIFIER suffixes SEMICOL { /*$$ = std::move(std::make_unique<link_node>(std::move($2), std::move($3), std::move($5), std::move($6)));
                                                                      $$->set_line(@$.begin.line);
                                                                      $$->set_column(@$.begin.column);*/ }/* attaching logical process to a node */
    | IDENTIFIER suffixes IMPLEMENTS_KW IDENTIFIER suffixes USING_KW IDENTIFIER SEMICOL { /*$$ = std::move(std::make_unique<implements_node>(std::move($1), std::move($2), std::move($4), std::move($5), std::move($7)));
                                                                                          $$->set_line(@$.begin.line);
                                                                                          $$->set_column(@$.begin.column);*/ }
    | statement                                 {/* $$ = std::move($1);*/ }
    ;
s_expr:
    block PERIOD IDENTIFIER                        { /*$$ = std::move(std::make_unique<plugging_expr_node>(std::move($1), std::move($3)));
                                                     $$->set_line(@$.begin.line);
                                                     $$->set_column(@$.begin.column);*/ }
    | collective_operation block PERIOD IDENTIFIER { /*$$ = std::move(std::make_unique<collective_cast_node>(std::move($1), std::move($2), std::move($4))); 
                                                     $$->set_line(@$.begin.line);
                                                     $$->set_column(@$.begin.column);*/ }
    | expr                                         { /*$$ = std::move($1);*/ }
    ;

collective_operation:
    L_PARENTH IDENTIFIER R_PARENTH { /*$$ = std::move(std::make_unique<collective_operation_node>(std::move($2)));
                                     $$->set_line(@$.begin.line);
                                     $$->set_column(@$.begin.column); *//* ex l363 all.chips */}
    ;
c_statements:
    c_statement c_statements                    { /*$$ = std::move($2); $$->append(std::move($1));
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/ }
    | c_loop_statement c_statements             { /*$$ = std::move($2); $$->append(std::move($1));
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/ }
    | c_if_else_statement c_statements          { /*$$ = std::move($2); $$->append(std::move($1));
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/ }
    | c_if_statement c_statements               { /*$$ = std::move($2); $$->append(std::move($1));
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/ }
    | /* EMPTY */                               { /*$$ = std::move(std::make_unique<c_statements_node>());*/ }
    ;
c_statement:
    cdf_full_declaration SEMICOL                   { /*$$ = std::move($1);*/}
    | IDENTIFIER c_suffixes ASSIGN c_expr SEMICOL    { /*$$ = std::move(std::make_unique<c_variable_assignment_node>(std::move($1), std::move($2), std::move($4))); 
                                                       $$->set_line(@$.begin.line);
                                                       $$->set_column(@$.begin.column);*/ }
    | CTX_KW PERIOD IDENTIFIER c_suffixes ASSIGN c_expr SEMICOL { /*$$ = std::move(std::make_unique<c_context_variable_assignment_node>(std::move($3), std::move($4), std::move($6))); 
                                                                  $$->set_line(@$.begin.line);
                                                                  $$->set_column(@$.begin.column);*/}
    ;
named_outputs:
    named_output named_outputs                  { /*$$ = std::move($2); $$->append(std::move($1)); 
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/  }
    | /* EMPTY */                               { $$ = std::vector<chips::function_output_variant>(); }
    ;
named_output:
    ARROW IDENTIFIER L_PARENTH list_expr R_PARENTH { /*$$ = std::move(std::make_unique<named_output_node>(std::move($2), std::move($4)));
                                                     $$->set_line(@$.begin.line);
                                                     $$->set_column(@$.begin.column);*/ }
    ;
p_named_outputs:
    p_named_output p_named_outputs              { /*$$ = std::move(std::move($2)); $$->append(std::move($1));
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/ }
    | /* EMPTY */                               { /*$$ = std::move(std::make_unique<physical_named_outputs_node>());
                                                  $$->set_line(@$.begin.line);
                                                  $$->set_column(@$.begin.column);*/}
    ;
p_named_output:
    ARROW ACTUATOR_KW IDENTIFIER L_PARENTH exprs R_PARENTH  { /*$$ = std::move(std::make_unique<actuator_node>(std::move($3), std::move($5)));
                                                              $$->set_line(@$.begin.line);
                                                              $$->set_column(@$.begin.column);*/ }
    | named_output                                          { /*$$ = std::move(std::move($1)); */}
    ;
df_parameter_list:
    df_parameter_decls                              { /*$$ = std::move($1);*/ }
    | /* EMPTY */                                   { $$ = std::vector<chips::function_parameter_variant>(); }
    ;
df_parameter_decls:
    df_parameter_decl                               { /*$$ = std::vector<chips::function_parameter_variant>();
                                                      $$.push_back($1);*//*std::vector<std::unique_ptr<dataflow_parameter_decl_node>> vec;
                                                      vec.push_back(std::move($1));
                                                      //$$ = std::make_unique<dataflow_parameter_decls_node>(std::move(vec));
                                                      $$ = vec;*/
                                                      /*$$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    | df_parameter_decl COMMA df_parameter_decls    { /*$$ = std::move($3);
                                                      $$.insert($$.begin(), $1);*//*$3->append(std::move($1)); $$ = std::move($3);
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    | /* EMPTY */                                   { /*$$ = std::make_unique<chips::function_parameter_variant>();*/ }
    ;
df_parameter_decl:
    df_type IDENTIFIER may_assign                   { /*$$ = std::make_unique<chips::function_parameter_variant>(std::move($1), std::move($2), std::move($3));
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    ;
df_type:
    INT_KW suffixes                                 { /*$$ = std::move(std::make_unique<chips::dataflow_primitive_variable<dataflow_type::INT>>());*/
                                                      /*$$ = std::move(std::make_unique<dataflow_type_node>(INT_DF, std::move(std::move($2))));
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column); */}
    | FLOAT_KW suffixes                             { /*$$ = std::move(std::make_unique<chips::dataflow_primitive_variable<dataflow_type::FLOAT>>());*/
                                                    /* $$ = std::move(std::make_unique<dataflow_type_node>(FLOAT_DF, std::move(std::move($2))));
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    | BOOL_KW suffixes                              { /*$$ = std::move(std::make_unique<chips::dataflow_primitive_variable<dataflow_type::BOOL>>());*/
                                                    /*$$ = std::move(std::make_unique<dataflow_type_node>(BOOL_DF, std::move(std::move($2))));
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    ;
pdf_parameter_type:
    df_type                                         { /*$$ = std::make_unique<physical_dataflow_parameter_type_node>(std::move($1));
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    | SENSOR_KW df_type                             { /*$$ = std::make_unique<physical_dataflow_parameter_type_node>(true, std::move($2));
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    ;
pdf_parameter_list:
    pdf_parameter_decls                             { /*$$ = std::move($1);*/ } 
    | /* EMPTY */                                   {/* $$ = std::move(std::make_unique<physical_dataflow_parameter_decls_node>());*/ }
    ;
pdf_parameter_decls:                                
    pdf_parameter_decl                              { /*std::vector<std::unique_ptr<physical_dataflow_parameter_decl_node>> vec; 
                                                      vec.push_back(std::move($1)); 
                                                      $$ = std::make_unique<physical_dataflow_parameter_decls_node>(std::move(vec));
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    | pdf_parameter_decl COMMA pdf_parameter_decls  { /*$3->append(std::move($1)); $$ = std::move($3);
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    | /* EMPTY */                                   { /*$$ = std::move(std::make_unique<physical_dataflow_parameter_decls_node>());*/ }
    ;
pdf_parameter_decl:
    pdf_parameter_type IDENTIFIER may_assign        { /*$$ = std::make_unique<physical_dataflow_parameter_decl_node>(std::move($1), std::move($2), std::move($3));
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    ;
cdf_defaulted_decls:
    cdf_defaulted_decl                              { /*std::vector<std::unique_ptr<collective_dataflow_defaulted_decl_node>> vec;
                                                      vec.push_back(std::move($1));
                                                      $$ = std::make_unique<collective_dataflow_defaulted_decls_node>(std::move(vec)); 
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/}
    | cdf_defaulted_decl COMMA cdf_defaulted_decls  { /*$3->append(std::move($1)); $$ = std::move($3);
                                                      $$->set_line(@$.begin.line);
                                                      $$->set_column(@$.begin.column);*/ }
    | /* EMPTY */                                   { /*$$ = std::move(std::make_unique<collective_dataflow_defaulted_decls_node>());*/ }
    ;
cdf_defaulted_decl:
    df_type IDENTIFIER ASSIGN c_expr {/* $$ = std::move(std::make_unique<collective_dataflow_defaulted_decl_node>(std::move($1), std::move($2), std::move($4)));
                                       $$->set_line(@$.begin.line);
                                       $$->set_column(@$.begin.column);*/ }
    ;
cdf_full_declaration:
    df_type IDENTIFIER c_may_assign {/* $$ = std::move(std::make_unique<collective_dataflow_full_declaration_node>(std::move($1), std::move($2), std::move($3)));
                                      $$->set_line(@$.begin.line);
                                      $$->set_column(@$.begin.column);*/ }
    ;
c_may_assign:
    ASSIGN c_expr       {/* $$ = std::move(std::make_unique<collective_rhs_assignment_node>(std::move($2)));
                          $$->set_line(@$.begin.line);
                          $$->set_column(@$.begin.column); */}
    | /* EMPTY */       {/* $$ = std::move(std::make_unique<collective_rhs_assignment_node>());*/ }
    ;
may_assign:
    ASSIGN expr         {/* $$ = std::move(std::make_unique<rhs_assignment_node>(std::move($2)));
                          $$->set_line(@$.begin.line);
                          $$->set_column(@$.begin.column);*/ }
    | /* EMPTY */       { /*$$ = std::move(std::make_unique<chips::dataflow_assignment>());*/ }
    ;
%%

int main(int argc, char *argv[])
{
    if(argc < 2){
        std::cout << "Usage: ./chipsc <file.chips> [options]\n"
                  << "Options:\n"
                  << " --skip-semantic : Skip semantic analysis phase\n"
                  << "  --skip-xmi    : Skip XMI generation phase\n"
                  << "  --xmi-output <file.xmi> : Specify XMI output file name and file path\n";
        return -1;
    }
    driver drv;
    std::string filename = std::string(argv[1]);

    for(int i = 2; i < argc; i++){
        std::string arg = argv[i];
        if(arg == "--skip-semantic"){
            drv.skip_semantic_analysis = true;
            std::cout << "\033[1;33m[Warning] Semantic analysis phase will be skipped.\033[0m\n";
        }
        else if(arg == "--skip-xmi"){
            drv.skip_xmi_generation = true;
            std::cout << "\033[1;33m[Warning] XMI generation phase will be skipped.\033[0m\n";
        }
        else if(arg == "--xmi-output" && i + 1 < argc){
            drv.xmi_output_filename = std::string(argv[i + 1]);
            i++;
            // TODO : refactor la génération des fichier xmi avec un string builder dans les visiteurs et les writers
        }
        else if(arg == "--schema-version" && i + 1 < argc){
            drv.schema_version = std::string(argv[i + 1]);
            std::cout << "\033[1;36m[Info] Using CHIPS schema version: " << drv.schema_version << "\033[0m\n";
            i++;
        }
         
    }

    return drv.parse(filename);   
}


void yy::parser::error(const location_type& l, const std::string& m)
{
    std::cerr << "\033[1;31m[Erreur syntaxique]\033[0m ligne " 
                  << l
                  << ": " << m << '\n';
}