# The Chips syntax

Chips grammar is inpired from C but intends to be a functionnal language by essence where each declared object is to be connected to others by flows of data.
```
chips:
    preambles system
    ;
preambles:
    preamble preambles
    | /* EMPTY */
    ;
preamble:
    import
    | function_def
    ;
import:
    IMPORT_KW STR AS_KW NAME SEMICOL
    ;
function_def:
    pure_signature output
    | object_signature INIT_KW L_CURL 
        statements 
    R_CURL THEN_KW L_CURL 
        statements 
    R_CURL output
    ;
pure_signature:
    PURE_KW NAME L_PARENTH df_decl_list_or_nothing R_PARENTH
    ;
df_decl_list_or_nothing:
    df_decl_list
    | /* EMPTY */
    ;
df_decl_list:
    df_decl_lhs
    | df_decl_lhs COMMA df_decl_list
    ;
df_decl_lhs:
    df_type NAME
    ;
df_type:
    INT_KW suffixes
    | FLOAT_KW suffixes
    | BOOL_KW suffixes
    ;
output:
    ARROW L_PARENTH exprs R_PARENTH
    ;
object_signature:
    VIRT_KW NAME L_PARENTH df_decl_list_or_nothing R_PARENTH
    | PHYSICAL_KW NAME L_PARENTH df_decl_list_or_nothing R_PARENTH
    ;
statements: 
    statement SEMICOL statements
    | loop statements
    | if_else statements
    | if statements
    | /* EMPTY */
    ;
statement:
    df_full_decl
    | assignment
    ;
sstatement: 
    NAME suffixes NAME
    | NAME suffixes INPUT_SUF L_PARENTH exprs R_PARENTH
    | LINK_KW NAME TO_KW NAME
    | NAME AT_KW L_PARENTH exprs R_PARENTH
    | df_full_decl
    | assignment
    | function_call_sttmt
    ;
df_full_decl:
    df_decl_lhs may_assign
    ;
suffixes:
    suffix suffixes
    | /* EMPTY */
    ;
suffix:
    L_SQUA expr R_SQUA
    | L_SQUA R_SQUA
    ;
may_assign:
    assign_rhs
    | /* EMPTY */
    ;
assign_rhs: 
    ASSIGN expr
    ;
cast:
    df_type L_PARENTH expr R_PARENTH
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
    ;
suffixable_expr:
    function_call
    | NAME
    | NAME OUTPUT_SUF
    | THIS_KW PERIOD NAME PERIOD NAME
    ;
assignment:
    NAME suffixes assign_rhs
    | THIS_KW PERIOD NAME PERIOD NAME suffixes assign_rhs
    ;
loop:
    FOREACH_KW NAME IN_KW suffixable_expr L_CURL 
        statements 
    R_CURL
    ;
if_else:
    if 
    ELSE_KW L_CURL 
        statements 
    R_CURL
    ;
if: 
    IF_KW L_PARENTH expr R_PARENTH L_CURL 
        statements 
    R_CURL
    ;
sloop:
    FOREACH_KW NAME IN_KW suffixable_expr L_CURL 
        sstatements 
    R_CURL
    ;
sif_else:
    sif 
    ELSE_KW L_CURL 
        sstatements 
    R_CURL
    ;
sif: 
    IF_KW L_PARENTH expr R_PARENTH L_CURL 
        sstatements 
    R_CURL
    ;
function_call:
    NAME L_PARENTH exprs R_PARENTH
    ;
function_call_sttmt:
    function_call
    ;
exprs:
    list_expr
    | /* EMPTY */
    ;
list_expr:
    expr
    | expr COMMA list_expr
    ;

system:
    SYSTEM_KW optional_dim L_CURL 
        sstatements
    R_CURL
    ;
optional_dim:
    DIMENSION_KW L_PARENTH INT R_PARENTH
    | /* EMPTY */
    ;
sstatements:
    sstatement SEMICOL sstatements
    | sloop sstatements
    | sif_else sstatements
    | sif sstatements
    | /* EMPTY */
    ;

```