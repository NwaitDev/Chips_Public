grammar Chips;

program 
    : preamble* system? EOF
    | (statement)* EOF
    ;

system
    : SYSTEM_KW L_CURL
        s_statement*    
      R_CURL
    ;

preamble
    : object_def            #ObjectDefinition
    | function_def          #FunctionDefinition
    | collective_op_def     #CollectiveOperationDefinition
    | implementation_def    #ImplementationDefinition
    ;

object_def
    : OBJECT_KW IDENTIFIER with_section
    ;

implementation_def
    : IMPLEMENTATION_KW IDENTIFIER COLUMN IDENTIFIER BY_KW IDENTIFIER L_CURL
        node_mapping*
      R_CURL
    ;

node_mapping
    : HAVING_KW IDENTIFIER AS_KW IDENTIFIER SEMICOL
    ;

function_def
    : l_function_def    #LogicalDefintion
    | p_function_def    #PhysicalDefinition
    ;

collective_op_def
    : c_signature L_CURL
        c_statement*
      R_CURL
      ARROW TARGET_KW L_PARENTH (c_expr)+ R_PARENTH
      c_output+
    ;


c_output
    : ARROW DEFAULT_KW L_PARENTH c_expr (COMMA c_expr)* R_PARENTH   #DefaultOutput
    | ARROW IDENTIFIER L_PARENTH c_expr (COMMA c_expr)* R_PARENTH   #ChanneledOutput
    ;

l_function_def
    : LOGICAL_KW IDENTIFIER L_PARENTH (df_parameter_decl (COMMA df_parameter_decl)*)? R_PARENTH
        init_section
        then_section
        named_output*
    ;

p_function_def
    : PHYSICAL_KW IDENTIFIER L_PARENTH (pdf_parameter_decl (COMMA pdf_parameter_decl)*)? R_PARENTH
        with_section
        init_section
        then_section
        p_named_output*
    ;

c_signature
    : c_keywords L_PARENTH (cdf_defaulted_decl (COMMA cdf_defaulted_decl)*)? R_PARENTH
        IDENTIFIER AMONG_KW IDENTIFIER
    ;

c_keywords
    : SPREAD_KW
    | COLLECT_KW
    ;

with_section
    : WITH_KW L_CURL
        with_statement*
      R_CURL
    ;

with_statement
    : IDENTIFIER IDENTIFIER SEMICOL                     #ChannelDeclaration
    | CTX_KW df_type suffixes IDENTIFIER (ASSIGN expr)? SEMICOL  #ContextualDeclaration
    | statement                                         #WithRegularStatement
    ;

init_section
    : INIT_KW L_CURL
        (statement)*
      R_CURL
    ;

then_section
    : THEN_KW L_CURL
        (statement)*
      R_CURL
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
    : expr01 PLUS expr0      # PLUS
    | expr01 MINUS expr0     # SUB
    | expr01                # PassExpr01
    ;

expr01
    : MINUS expr1           # Negate
    | expr1                 # PassExpr1
    ;

expr1
    : expr2 TIMES expr1     # MULT
    | expr2 DIV expr1       # DIV
    | expr2 MOD expr1       # MOD
    | NOT expr2             # NOT
    | expr2                 # PassExpr2
    ;

expr2
    : INT                                       # IntLiteral
    | FLOAT                                     # FloatLiteral
    | BOOL                                      # BoolLiteral
    | IDENTIFIER suffixes                       # Var
    | L_PARENTH expr R_PARENTH                  # Parens
    | CTX_KW PERIOD IDENTIFIER suffixes         # VarContext
    | IDENTIFIER L_PARENTH (expr (COMMA expr)*)? R_PARENTH    # Function
    | cast                                      # CastAs
    ;

cast    
    : L_PARENTH df_type R_PARENTH expr
    ;

c_expr
    : c_stopless_expr   #CStoplessExpression
    | STOP_KW           #Stop
    ;

c_stopless_expr 
    : c_stopless_expr0 LT c_stopless_expr   #CLT
    | c_stopless_expr0 GT c_stopless_expr   #CGT
    | c_stopless_expr0 LEQ c_stopless_expr  #CLEQ
    | c_stopless_expr0 GEQ c_stopless_expr  #CGEQ
    | c_stopless_expr0 NEQ c_stopless_expr  #CNEQ
    | c_stopless_expr0 EQ c_stopless_expr   #CEQ
    | c_stopless_expr0 AND c_stopless_expr  #CAND
    | c_stopless_expr0 OR c_stopless_expr   #COR
    | c_stopless_expr0                      #PassCExpr0
    ;

c_stopless_expr0
    : c_stopless_expr01 PLUS c_stopless_expr0    #CPLUS
    | c_stopless_expr01 MINUS c_stopless_expr0   #CSUB
    | c_stopless_expr01                         #PassCExpr01
    ;

c_stopless_expr01
    : MINUS c_stopless_expr1                    #CNegate
    | c_stopless_expr1                          #PassCExpr1
    ;

c_stopless_expr1
    : c_stopless_expr2 TIMES c_stopless_expr1   #CMULT
    | c_stopless_expr2 DIV c_stopless_expr1     #CDIV
    | c_stopless_expr2 MOD c_stopless_expr1     #CMOD
    | NOT c_stopless_expr1                      #CNOT
    | c_stopless_expr2                          #PassCExpr2
    ;

c_stopless_expr2
    : IDENTIFIER c_suffixes                                     #CVariableExpression
    | INT                                                       #CINT
    | FLOAT                                                     #CFLOAT
    | BOOL                                                      #CBOOL
    | INPUT_KW                                                  #INPUT
    | CTX_KW PERIOD IDENTIFIER c_suffixes                       #CtxVariableExpression
    | IDENTIFIER PERIOD IDENTIFIER c_suffixes                   #ChanneledAccuExpression
    | IDENTIFIER L_PARENTH (c_expr (COMMA c_expr)*)? R_PARENTH  #FunctionCall
    | L_PARENTH c_stopless_expr R_PARENTH                       #CParenthesis
    | c_cast                                                    #CCastAs
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

s_suffixable_expr
    : IDENTIFIER                                                #SSuffixableVariableExpression
    | IDENTIFIER (L_PARENTH (expr (COMMA expr)*)? R_PARENTH)?   #SSuffixableFunctionCallExpression
    | block PERIOD IDENTIFIER                                   #SSuffixableBlockOutputExpression
    ;

block
    : IDENTIFIER suffixes
    ;

loop_in
    :  IDENTIFIER (L_PARENTH (expr (COMMA expr)*)? R_PARENTH)?
    ;

loop_statement
    : FOREACH_KW IDENTIFIER IN_KW loop_in L_CURL
        statement*
      R_CURL
    ;

c_loop_statement
    : FOREACH_KW IDENTIFIER IN_KW loop_in L_CURL
        c_statement*
      R_CURL
    ;

s_loop_statement
    : FOREACH_KW IDENTIFIER IN_KW s_suffixable_expr L_CURL
        s_statement*
      R_CURL
    ;

if_else_statement
    : if_statement
      ELSE_KW L_CURL
        (statement)*
      R_CURL
    ;

s_if_else_statement
    : s_if_statement
      ELSE_KW L_CURL
        s_statement*
      R_CURL
    ;

c_if_else_statement
    : c_if_statement
      ELSE_KW L_CURL
        c_statement*
      R_CURL
    ;

if_statement
    : IF_KW L_PARENTH expr R_PARENTH L_CURL
        (statement)*
      R_CURL
    ;

s_if_statement
    : IF_KW L_PARENTH expr R_PARENTH L_CURL
        s_statement*
      R_CURL
    ;

c_if_statement
    : IF_KW L_PARENTH c_expr R_PARENTH L_CURL
        c_statement*
      R_CURL
    ;

statement
    : df_type suffixes IDENTIFIER (ASSIGN expr)? SEMICOL    # StatementDeclaration
    | IDENTIFIER suffixes ASSIGN expr SEMICOL               # StatementAssignment
    | CTX_KW PERIOD IDENTIFIER suffixes ASSIGN expr SEMICOL # StatementContextualAssignment
    | loop_statement                                        # StatementLoop
    | if_else_statement                                     # StatementIfElse
    | if_statement                                          # StatementIf
    ;

s_statement
    : IDENTIFIER suffixes IDENTIFIER SEMICOL                                                #ObjectDeclaration
    | block PERIOD IDENTIFIER L_PARENTH s_expr R_PARENTH SEMICOL                            #FeedingStatement
    | LINK_KW IDENTIFIER suffixes TO_KW IDENTIFIER suffixes SEMICOL                         #LinkingStatement
    | IDENTIFIER suffixes IMPLEMENTATION_KW IDENTIFIER suffixes USING_KW IDENTIFIER SEMICOL #ImplementationStatement
    | s_loop_statement                                                                      #SLoopStatement
    | s_if_else_statement                                                                   #SIfElseStatement
    | s_if_statement                                                                        #SIfStatement
    | statement                                                                             #RegularStatement
    ;

s_expr
    : block PERIOD IDENTIFIER                       #SBlockOutputExpression
    | collective_operation block PERIOD IDENTIFIER  #SCollectiveCastExpression
    | expr                                          #SRegularExpression
    ;

collective_operation
    : L_PARENTH IDENTIFIER R_PARENTH
    ;

c_statement
    : cdf_full_declaration SEMICOL                              #CollectiveVariableDeclaration
    | IDENTIFIER c_suffixes ASSIGN c_expr SEMICOL               #CollectiveAssignment
    | CTX_KW PERIOD IDENTIFIER c_suffixes ASSIGN c_expr SEMICOL #ContextualAssignment
    | c_loop_statement                                          #CollectiveLoopStatement
    | c_if_else_statement                                       #CollectiveIfElseStatement
    | c_if_statement                                            #CollectiveIfStatement
    ;

named_output
    : ARROW IDENTIFIER L_PARENTH expr (COMMA expr)* R_PARENTH
    ;

p_named_output
    : ARROW ACTUATOR_KW IDENTIFIER L_PARENTH expr (COMMA expr)* R_PARENTH    #ActuatorOutput
    | named_output                                                          #FunctionOutput
    ;

df_parameter_decl
    : df_type suffixes IDENTIFIER (ASSIGN expr)?
    ;

df_type
    : INT_KW       # IntType
    | FLOAT_KW     # FloatType
    | BOOL_KW      # BoolType
    ;

pdf_parameter_type
    : df_type suffixes           #FunctionParameterType
    | SENSOR_KW df_type suffixes #SensorParameterType
    ;

pdf_parameter_decl
    : pdf_parameter_type IDENTIFIER (ASSIGN expr)?
    ;

cdf_defaulted_decl
    : df_type suffixes IDENTIFIER ASSIGN c_expr
    ;

cdf_full_declaration
    : df_type suffixes IDENTIFIER (ASSIGN c_expr)?
    ;


SYSTEM_KW           : 'system'|'SYSTEM';
INT_KW              : 'int';
FLOAT_KW            : 'float';
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

BOOL                : 'true'| 'false';

fragment DIGIT      : [0-9] ;

fragment DOTTED_NUMBER
    : '.'DIGIT+
    | DIGIT+'.'DIGIT*
    ;
fragment ID_START   : [a-zA-Z];
fragment ID_NEXT    : [a-zA-Z0-9_];

FLOAT               : DOTTED_NUMBER;
INT                 : DIGIT+;
IDENTIFIER          : ID_START ID_NEXT*;

NEWLINE : ('\r'? '\n')+ -> skip ;
WS          : [ \t\r]+ -> skip ;
COMMENT     : '//' ~[\r\n]* -> skip ;