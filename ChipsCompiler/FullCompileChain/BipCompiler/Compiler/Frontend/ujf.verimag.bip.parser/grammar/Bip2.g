/**
 * Copyright Verimag laboratory.
 * 
 * contributors:
 *  Marc Pouhliès
 *  Jacques Combaz (jacques.combaz@univ-grenoble-alpes.fr)
 *  Anakreontas Mentis
 * 
 * This software is a computer program whose purpose is to generate
 * executable code from BIP models.
 * 
 * This software is governed by the CeCILL-B license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-B
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info".
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability.
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security.
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-B license and that you accept its terms.
 */

grammar Bip2;

options {
    output=AST;
    backtrack=true;
    memoize=true;
}


tokens {
    PACKAGE_NAME;
    BIP_PACKAGE;

    ANNOTATED_TYPE;
    ANNOTATION;
    ANNOTATION_PARAM;
    ANNOTATIONS;
    
    TYPE_PARAMS;

    CONST_DATA_DECLARATION;

    PORT_TYPE;
    ATOM_TYPE;
    EXTERN_DATA_TYPE;
    EXTERN_FUNCTION_PROTOTYPE;
    EXTERN_BINARY_OPERATOR_PROTOTYPE;
    EXTERN_UNARY_OPERATOR_PROTOTYPE;
    COMPOUND_TYPE;
    CONNECTOR_TYPE;

    FULLY_QUALIFIED_NAME;

    ATOM_PRIORITY_DECLARATION;
    ATOM_PRIORITY_GUARD;
    ATOM_PRIORITY_OR_INVARIANT_DECLARATIONS;
    
    INVARIANT_AT;
    INVARIANT_FROM;
    INVARIANT_GUARD;

    CONNECTOR_INTERACTIONS;
    CONNECTOR_INTERACTION;
    CONNECTOR_INTERACTION_PORTS;
    CONNECTOR_DECLARATION;
    CONNECTOR_DECLARATION_NAMES;

    CONNECTOR_INTERACTION;
    CONNECTOR_PORT_INTERACTION;

    COMPONENT_DECLARATION_NAMES;
    COMPONENT_DECLARATION;

    COMPONENT_OR_CONNECTOR_DECLARATIONS;

    COMPOUND_EXPORT_DATA_OR_PORT;
    COMPOUND_EXPORT_DATA;
    COMPOUND_EXPORT_PORT;

    COMPOUND_PRIORITY_DECLARATION;
    COMPOUND_PRIORITY_DECLARATIONS;
    COMPOUND_PRIORITY_GUARD;

    DATA_PARAM;
    DATA_PARAMS;

    PORT_PARAM;
    PORT_PARAMS;

    EXPORT_PORT_MERGED;

    TRANSITION_DECLARATIONS;
    TRANSITION_DECLARATION;

    INITIAL_TRANSITION_DECLARATION;
    TRANSITION_ACTION;
    TRANSITION_GUARD;

    PRIMARY_PORT_EXPRESSION;
    NESTED_PORT_EXPRESSION;

    INNER_PORT_REFERENCE;

    DATA_OR_PORT_DECLARATIONS;

    PORT_DECLARATION;
    PORT_DECLARATIONS;
    PORT_DECLARATION_NAMES;
    PORT_MODIFIERS;
    PORT_DECLARATION_WITH_MODIFIERS;
    ANNOTATED_EXPORT_PORT_DECLARATION;

    INNER_DATA_REFERENCE;

    DATA_DECLARATION;
    DATA_DECLARATIONS;
    DATA_DECLARATION_NAMES;
    DATA_MODIFIERS;
    DATA_DECLARATION_WITH_MODIFIERS;
    ANNOTATED_DATA_DECLARATION;

    DATA_TYPE;
    NATIVE_DATA_TYPE;

    PLACES;

    // Imaginary Tokens for action language

    FUNCTION_CALL_EXPRESSION;
    IFTHENELSE_EXPRESSION;
    THEN_SUBEXPR;
    ELSE_SUBEXPR;
    ARGUMENT_EXPR_LIST;

    UNARY_MINUS;
}

@parser::header {
package ujf.verimag.bip.parser;
import ujf.verimag.bip.parser.error.ParserOrLexerError;
}

@members {
  public List<ParserOrLexerError> errors = new ArrayList<ParserOrLexerError>();

  @Override
  public void reportError(RecognitionException re) {
    if (! state.errorRecovery ) {
      registerError(re);
      state.syntaxErrors++; // don't count spurious
      state.errorRecovery = true;
    }
  }

  protected void registerError(RecognitionException re) {
    ParserOrLexerError new_error = new ParserOrLexerError(re);
    this.errors.add(new_error);
  }
}

@rulecatch{
  catch (RecognitionException recogException){
    reportError(recogException);
    //recover(input, recogException);
    throw recogException;
  }
}

@lexer::header {
 package ujf.verimag.bip.parser;
 import ujf.verimag.bip.parser.error.ParserOrLexerError;
}

@lexer::members {
  public List<ParserOrLexerError> errors = new ArrayList<ParserOrLexerError>();

/*
 * The strange error handling comes from the ANTLR mailing list:
 * Message from "Tim Halloran" [antlr-interest] How does one suppress 'no viable alternative at character' warning messages
 * Published Sep 17, 2008 11:14:10 am
 */
  @Override
  public void reportError(RecognitionException re) {
    if (! state.errorRecovery ) {
      registerError(re);
      state.syntaxErrors++; // don't count spurious
      state.errorRecovery = true;
      Thrower.sneakyThrow(re);
    }
  }

  protected void registerError(RecognitionException re) {
    ParserOrLexerError new_error = new ParserOrLexerError(re);
    this.errors.add(new_error);
  }

 /*
  * See "Puzzle 43: Exceptionally Unsafe" from Bloch Gafter, <i>Java
  * Puzzlers</i>. Addison Wesley 2005.
  */
static class Thrower {
    private static Throwable t;
    private Thrower() throws Throwable {
        throw t;
    }
    public static synchronized void sneakyThrow(Throwable t) {
        Thrower.t = t;
        try {
            Thrower.class.newInstance();
        } catch (InstantiationException e) {
            throw new IllegalArgumentException(e);
        } catch (IllegalAccessException e) {
            throw new IllegalArgumentException(e);
        } finally {
            Thrower.t = null; // Avoid memory leak
        }
    }
}
}

CT_INT  :   'int';
CT_BOOL :   'bool';
CT_FLOAT:   'float';
CT_STRING:   'string';

TRUE : 'true';
FALSE : 'false';
REFINE : 'refine';
EXTERN  : 'extern';
REMEMBER : 'remember';
IGNORE : 'ignore';
ERROR : 'error';
EXPORT  :   'export';
FUNCTION :   'function';
OPERATOR :   'operator';
DEFINE  :   'define';
DATA    :   'data';
PACKAGE :   'package';
END :   'end';
USE :   'use';
AS  :   'as';
ATOM    :   'atom';
COMPOUND:   'compound';
COMPONENT
    :   'component';
ON  :   'on';
INTERNAL : 'internal';
DO  :   'do';
PROVIDED:   'provided';
INITIAL :   'initial';
PLACE   :   'place';
FROM    :   'from';
AT      :   'at';
TO  :   'to';
PRIORITY:   'priority';
INVARIANT:  'invariant';
CONNECTOR
    :   'connector';
UP_ACTION   :   'up';
DOWN_ACTION :   'down';
PORT    :   'port';
TYPE    :   'type';
CONST   :   'const';
LPAREN  :   '(';
RPAREN  :   ')';
LBRACE  :   '{';
RBRACE  :   '}';
COMMA   :   ',';
QUOTE   :   '\'';
DOT     :   '.';
SEMICOL :   ';';
COLON   :   ':';
AT_SIGN :   '@';

IF : 'if';
THEN : 'then';
ELSE : 'else';
FI : 'fi';


ID  :   ('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*
    ;

INT :   '0'..'9'+
    ;

FLOAT
    :   ('0'..'9')+ '.' ('0'..'9')* EXPONENT?
    |   '.' ('0'..'9')+ EXPONENT?
    |   ('0'..'9')+ EXPONENT
    ;

COMMENT
    :   '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    |   '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
    ;

WS  :   ( ' '
        | '\t'
        | '\r'
        | '\n'
        ) {$channel=HIDDEN;}
    ;

STRING
    :  '"' ( ESC_SEQ | ~('\\'|'"') )* '"'
    ;

fragment
EXPONENT : ('e'|'E') ('+'|'-')? ('0'..'9')+ ;

fragment
HEX_DIGIT : ('0'..'9'|'a'..'f'|'A'..'F') ;

fragment
ESC_SEQ
    :   '\\' ('b'|'t'|'n'|'f'|'r'|'\"'|'\''|'\\')
    |   UNICODE_ESC
    |   OCTAL_ESC
    ;

fragment
OCTAL_ESC
    :   '\\' ('0'..'3') ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7')
    ;

fragment
UNICODE_ESC
    :   '\\' 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
    ;

LT_OP   :   '<';
GT_OP   :   '>';
LE_OP   :   '<=';
GE_OP   :   '>=';
EQ_OP   :   '==';
NE_OP   :   '!=';
AND_OP  :   '&&';
OR_OP   :   '||';
NOT_OP  :   '!';

PLUS_OP :   '+';
MINUS_OP:   '-';
MULT_OP :   '*';
DIV_OP  :   '/';
MOD_OP  :   '%';

BWISE_AND_OP : '&';
BWISE_OR_OP : '|';
BWISE_XOR_OP : '^';
BWISE_NOT_OP : '~';

ASSIGN_OP : '=';

binary_operator
    : comparison_operator
    | arithmetic_binary_operator
    | bwise_binary_operator
    | logical_binary_operator
    ;
  
unary_operator
    : arithmetic_unary_operator
    | bwise_unary_operator
    | logical_unary_operator
    ;

comparison_operator
    : EQ_OP | NE_OP | GT_OP | GE_OP | LT_OP | LE_OP
    ;
   
arithmetic_binary_operator
    : PLUS_OP | MINUS_OP | MULT_OP | DIV_OP | MOD_OP
    ;
    
arithmetic_unary_operator
    : PLUS_OP | MINUS_OP
    ;
    
bwise_binary_operator
    : BWISE_AND_OP | BWISE_OR_OP | BWISE_XOR_OP
    ;
    
bwise_unary_operator
    : BWISE_NOT_OP
    ;
    
logical_binary_operator
    : AND_OP | OR_OP
    ;
    
logical_unary_operator
    : NOT_OP
    ;

fully_qualified_name
    : i=ID (DOT ID)* ->  ^(FULLY_QUALIFIED_NAME[$i] ID+)
    ;

simple_name
    : ID
    ;

bip_package
    :
    annotation*
    PACKAGE package_name=fully_qualified_name
    (USE used_package_names+=fully_qualified_name)*
    annotated_declaration*
    END -> ^(BIP_PACKAGE[$PACKAGE]
             $package_name
             ^(USE $used_package_names+)?
             annotated_declaration*
             (^(ANNOTATIONS annotation+))?)
    ;

annotated_declaration
    : annotated_const_data_declaration
    | annotated_extern_data_type
    | annotated_extern_prototype
    | annotated_type_definition
    ;

annotated_extern_prototype
    : annotated_extern_function_prototype
    | annotated_extern_binary_operator_prototype
    | annotated_extern_unary_operator_prototype
    ;

annotated_extern_data_type
  : annotation* EXTERN DATA TYPE simple_name (REFINE data_type_name (COMMA data_type_name)*)? (AS backend_name=STRING)?
      -> ^(EXTERN_DATA_TYPE[$EXTERN] simple_name ^(REFINE data_type_name+)? ^(AS $backend_name)? (^(ANNOTATIONS annotation+))?)
  ;

annotated_extern_function_prototype
  : annotation* EXTERN FUNCTION
      data_type? simple_name LPAREN prototype_data_params? RPAREN
        -> ^(EXTERN_FUNCTION_PROTOTYPE[$EXTERN] simple_name prototype_data_params? data_type? (^(ANNOTATIONS annotation+))?)
  ;
  
annotated_extern_binary_operator_prototype
  : annotation* EXTERN OPERATOR ret=data_type binary_operator LPAREN left=prototype_data_param COMMA right=prototype_data_param RPAREN
        -> ^(EXTERN_BINARY_OPERATOR_PROTOTYPE[$EXTERN] binary_operator ^(DATA_PARAMS $left $right) $ret  (^(ANNOTATIONS annotation+))?)
  ;
  
annotated_extern_unary_operator_prototype
  : annotation* EXTERN OPERATOR ret=data_type unary_operator LPAREN operand=prototype_data_param RPAREN
        -> ^(EXTERN_UNARY_OPERATOR_PROTOTYPE[$EXTERN] unary_operator ^(DATA_PARAMS $operand) $ret (^(ANNOTATIONS annotation+))? )
  ;
  
prototype_data_param
    : data_type simple_name? -> ^(DATA_PARAM data_type simple_name?)
    ;

prototype_data_params
    : prototype_data_param (COMMA prototype_data_param)*
        -> ^(DATA_PARAMS prototype_data_param+)
    ;
  
annotated_const_data_declaration
  : annotation*
    (const_data_declaration
         -> ^(ANNOTATED_DATA_DECLARATION
                const_data_declaration
                (^(ANNOTATIONS annotation+))?)
    | data_const_declaration
         -> ^(ANNOTATED_DATA_DECLARATION
                data_const_declaration
                (^(ANNOTATIONS annotation+))?)
    )
  ;
    
const_data_declaration
  : CONST DATA data_type_name variable_declaration (COMMA variable_declaration)*
        -> ^(DATA_DECLARATION[$CONST]
               ^(DATA_TYPE data_type_name CONST)
               ^(DATA_DECLARATION_NAMES[$CONST] variable_declaration+))
  ;
  
data_const_declaration
  : DATA CONST data_type_name variable_declaration (COMMA variable_declaration)*
        -> ^(DATA_DECLARATION[$CONST]
               ^(DATA_TYPE data_type_name CONST)
               ^(DATA_DECLARATION_NAMES[$DATA] variable_declaration+))
  ;

places_declaration
    : PLACE simple_name (COMMA simple_name)*
        -> ^(PLACES[$PLACE] simple_name+)
    ;

transition_action
    : LBRACE!  ((statement SEMICOL!)| if_then_else_expression)*  RBRACE!

    ;

transition_guard
    : LPAREN logical_or_expression RPAREN -> ^(logical_or_expression)
    ;

transition
    :
    annotation*
    (e=ON port_name=simple_name | e=INTERNAL)
    FROM fromp += simple_name (COMMA fromp += simple_name)*
    TO     top += simple_name (COMMA top += simple_name)*
    (PROVIDED transition_guard)?
    (DO transition_action)?
        -> ^(TRANSITION_DECLARATION[$e]
            $port_name?
            ^(PLACES[$FROM] $fromp+)
            ^(PLACES[$TO] $top+)
            ^(TRANSITION_GUARD[$PROVIDED] transition_guard)?
            ^(TRANSITION_ACTION[$DO] transition_action)?
            (^(ANNOTATIONS annotation+))?
            )
    ;

compound_interaction
    : simple_name c=COLON (fully_qualified_name (COMMA fully_qualified_name)*|MULT_OP)
        -> ^(CONNECTOR_INTERACTION simple_name
                  ^(CONNECTOR_PORT_INTERACTION[$c] fully_qualified_name+)?)
    ;

compound_interaction_wildcard
  : compound_interaction | MULT_OP COLON MULT_OP;

// here, we may have to watch for data access: force it to be: comp.port.data. ?
compound_priority_guard
    : LPAREN logical_or_expression RPAREN -> ^(logical_or_expression)
    ;

compound_priority_declaration
    : PRIORITY simple_name lci=compound_interaction_wildcard LT_OP hci=compound_interaction_wildcard
        (PROVIDED compound_priority_guard)?
            -> ^(COMPOUND_PRIORITY_DECLARATION[$PRIORITY] simple_name $lci $hci
                    ^(COMPOUND_PRIORITY_GUARD[$PROVIDED] compound_priority_guard)?)
    ;



initial_transition
    :
     INITIAL TO simple_name (COMMA simple_name)* (DO transition_action)?
        -> ^(INITIAL_TRANSITION_DECLARATION[$INITIAL]
             simple_name+
             ^(TRANSITION_ACTION[$DO] transition_action)?)
    ;

atom_priority_guard
    : LPAREN logical_or_expression RPAREN -> ^(logical_or_expression)
    ;

port_name_wildcard
    : simple_name | MULT_OP
    ;

atom_priority_declaration
    : PRIORITY simple_name lp=port_name_wildcard LT_OP hp=port_name_wildcard
        (PROVIDED atom_priority_guard)?
            -> ^(ATOM_PRIORITY_DECLARATION[$PRIORITY] simple_name $lp $hp
                    ^(ATOM_PRIORITY_GUARD[$PROVIDED] atom_priority_guard)?)
    ;
    
atom_invariant_guard
    : LPAREN logical_or_expression RPAREN -> ^(logical_or_expression)
    ;

atom_invariant_declaration
    : INVARIANT simple_name atom_invariant_places? PROVIDED atom_invariant_guard
        -> ^(INVARIANT
             simple_name
             atom_invariant_places?
             ^(INVARIANT_GUARD atom_invariant_guard))
    ;

atom_invariant_places
    : AT place += simple_name (COMMA place += simple_name)*
        -> ^(INVARIANT_AT[$AT] $place+)
    | FROM place += simple_name (COMMA place += simple_name)*
        -> ^(INVARIANT_FROM[$FROM] $place+)
    ;
    
atom_priority_or_invariant_declaration
    : atom_invariant_declaration
    | atom_priority_declaration
    ;

atom_type_definition
    :
    ATOM TYPE simple_name
    LPAREN (component_data_params)? RPAREN
    (multi_data_or_port_declaration_with_modifiers)*
    places_declaration
    initial_transition
    transition+
    atom_priority_or_invariant_declaration*
    END
        -> ^(ATOM_TYPE[$ATOM] simple_name
                component_data_params?
                ^(DATA_OR_PORT_DECLARATIONS[$ATOM] multi_data_or_port_declaration_with_modifiers+)?
                places_declaration
                initial_transition
                ^(TRANSITION_DECLARATIONS[$ATOM] transition+)
                ^(ATOM_PRIORITY_OR_INVARIANT_DECLARATIONS[$ATOM] atom_priority_or_invariant_declaration+)?
        )
    ;

multi_data_or_port_declaration_with_modifiers
    : multi_data_declaration_with_modifiers
    | multi_port_declaration_with_modifiers
    ;
    
main_component_declaration
    : fully_qualified_name LPAREN (logical_or_expression (COMMA logical_or_expression)*)? RPAREN
        -> ^(COMPONENT_DECLARATION fully_qualified_name
            ^(DATA_PARAMS[$LPAREN] logical_or_expression+)?)
    ;        

fragment_component_declaration
    : simple_name
      LPAREN (logical_or_expression (COMMA logical_or_expression)*)? RPAREN
         -> ^(simple_name ^(DATA_PARAMS[$LPAREN] logical_or_expression+)?)
    ;

multi_component_declaration
    :
    annotation*
    COMPONENT fully_qualified_name fragment_component_declaration (COMMA fragment_component_declaration)*
        -> ^(COMPONENT_DECLARATION[$COMPONENT] fully_qualified_name
            ^(COMPONENT_DECLARATION_NAMES[$COMPONENT] fragment_component_declaration+)
            (^(ANNOTATIONS annotation+))?)
    ;

fragment_connector_declaration
    : simple_name
      LPAREN fully_qualified_name (COMMA fully_qualified_name)* RPAREN
        -> ^(simple_name ^(PORT_PARAMS[$LPAREN] fully_qualified_name+))
    ;

multi_connector_declaration
    : 
    annotation*
    CONNECTOR fully_qualified_name fragment_connector_declaration (COMMA fragment_connector_declaration)*
            -> ^(CONNECTOR_DECLARATION[$CONNECTOR] fully_qualified_name
                 ^(CONNECTOR_DECLARATION_NAMES[$CONNECTOR] fragment_connector_declaration+)
                 (^(ANNOTATIONS annotation+))?)
    ;

export_inner_port
    :
    annotation*
    EXPORT PORT fully_qualified_name (COMMA fully_qualified_name)* AS simple_name
        -> ^(COMPOUND_EXPORT_PORT[$EXPORT]
                  fully_qualified_name+
                  simple_name
                  (^(ANNOTATIONS annotation+))?)
    ;

export_inner_data
    :
    annotation*
    EXPORT DATA fully_qualified_name AS simple_name
        -> ^(COMPOUND_EXPORT_DATA[$EXPORT]
                 fully_qualified_name
                 simple_name
                 (^(ANNOTATIONS annotation+))?)
    ;


compound_type_definition
    :
    COMPOUND TYPE simple_name
    LPAREN (component_data_params)? RPAREN
    multi_component_or_connector_declaration+
    compound_priority_declaration*
    export_inner_data_or_port*
    END

        -> ^(COMPOUND_TYPE[$COMPOUND] simple_name
            component_data_params?
            ^(COMPONENT_OR_CONNECTOR_DECLARATIONS[$COMPOUND] multi_component_or_connector_declaration+)
            ^(COMPOUND_PRIORITY_DECLARATIONS[$COMPOUND] compound_priority_declaration+)?
            ^(COMPOUND_EXPORT_DATA_OR_PORT[$COMPOUND] export_inner_data_or_port+)?
        )
    ;

multi_component_or_connector_declaration
    : multi_component_declaration
    | multi_connector_declaration
    ;

export_inner_data_or_port
    : export_inner_port
    | export_inner_data
    ;

native_data_type_name
    :
    ( i=CT_INT
    | i=CT_BOOL
    | i=CT_FLOAT
    | i=CT_STRING
    ) -> ^(NATIVE_DATA_TYPE[$i] $i)
    ;

data_type_name
    : fully_qualified_name
    | native_data_type_name
    ;
	
data_type
    : CONST? data_type_name
    	-> ^(DATA_TYPE data_type_name CONST?)
    ;

component_data_param
    : data_type simple_name -> ^(DATA_PARAM data_type simple_name)
    ;

component_data_params
    : component_data_param (COMMA component_data_param)*
        -> ^(DATA_PARAMS component_data_param+)
    ;

multi_data_declaration_with_modifiers
    :
    annotation*
    e=EXPORT? multi_data_declaration
        -> ^(DATA_DECLARATION_WITH_MODIFIERS
            ^(DATA_MODIFIERS EXPORT[$e]?)
            multi_data_declaration
            (^(ANNOTATIONS annotation+))?)
    ;
    
annotated_multi_data_declaration
    : annotation* multi_data_declaration
        -> ^(ANNOTATED_DATA_DECLARATION
            multi_data_declaration
            (^(ANNOTATIONS annotation+))?)
    ;

multi_data_declaration
    : d=DATA data_type variable_declaration (COMMA variable_declaration)*
            -> ^(DATA_DECLARATION[$d]
                   data_type
                   ^(DATA_DECLARATION_NAMES[$d]
                       variable_declaration+))
    ;
    
variable_declaration
    : simple_name (ASSIGN_OP logical_or_expression)?
            -> ^(simple_name logical_or_expression?)
    ;

port_type_definition
    : p=PORT TYPE simple_name
      lp=LPAREN (port_data_params)? RPAREN
            -> ^(PORT_TYPE[$p] simple_name port_data_params?)
    ;

port_data_param
    : data_type simple_name -> ^(DATA_PARAM data_type simple_name)
    ;

port_data_params
    : port_data_param (COMMA port_data_param)*
        -> ^(DATA_PARAMS port_data_param+)
    ;

port_primary_expression
    : simple_name QUOTE? -> ^(PRIMARY_PORT_EXPRESSION simple_name QUOTE?)
    ;

port_nested_expression
    : LPAREN connector_port_expression RPAREN QUOTE? -> ^(NESTED_PORT_EXPRESSION connector_port_expression QUOTE?)
    ;

connector_port_expression
    : (port_primary_expression | port_nested_expression)+
    ;

port_type_param
    : fully_qualified_name simple_name -> ^(PORT_PARAM fully_qualified_name simple_name)
    ;

fragment_port_declaration
    : simple_name lp=LPAREN (simple_name (COMMA simple_name)*)? RPAREN
        -> ^(simple_name ^(DATA_PARAMS[$lp] simple_name+)?)
    ;

multi_port_declaration_with_modifiers
    :
    annotation*
        (
            EXPORT multi_port_declaration
            (as_merged=AS simple_name
                -> ^(PORT_DECLARATION_WITH_MODIFIERS
                    ^(PORT_MODIFIERS ^(EXPORT_PORT_MERGED[$as_merged] simple_name))
                    multi_port_declaration
                    (^(ANNOTATIONS annotation+))?)
            |
                -> ^(PORT_DECLARATION_WITH_MODIFIERS
                    ^(PORT_MODIFIERS EXPORT)
                    multi_port_declaration
                    (^(ANNOTATIONS annotation+))?)
            )
            |  multi_port_declaration
            -> ^(PORT_DECLARATION_WITH_MODIFIERS
                ^(PORT_MODIFIERS EXPORT?)
                multi_port_declaration
                (^(ANNOTATIONS annotation+))?)
            |  EXTERN multi_port_declaration (as_extern=AS backend_name=STRING)? event_consumption_policy?
            -> ^(PORT_DECLARATION_WITH_MODIFIERS
                ^(PORT_MODIFIERS EXTERN ^(AS[$as_extern] $backend_name)? event_consumption_policy?)
                multi_port_declaration
                (^(ANNOTATIONS annotation+))?)
        )
    ;

event_consumption_policy
    : REMEMBER
    | IGNORE
    | ERROR
    ;

multi_port_declaration
    : p=PORT fully_qualified_name fragment_port_declaration (COMMA fragment_port_declaration)*
            -> ^(PORT_DECLARATION fully_qualified_name
                    ^(PORT_DECLARATION_NAMES fragment_port_declaration+))
    ;
    
annotated_export_port_declaration
    : annotation* e=EXPORT single_port_declaration
        -> ^(ANNOTATED_EXPORT_PORT_DECLARATION[$e]
            single_port_declaration
            (^(ANNOTATIONS annotation+))?)
    ;
    
single_port_declaration
    : p=PORT fully_qualified_name fragment_port_declaration
        -> ^(PORT_DECLARATION fully_qualified_name
                    ^(PORT_DECLARATION_NAMES fragment_port_declaration))
    ;

connector_provided_expression
    : LPAREN logical_or_expression RPAREN -> ^(logical_or_expression)
    ;

connector_action
    : ((statement SEMICOL!)| if_then_else_expression)+
    ;

connector_interaction
    :
    annotation*
    o=ON simple_name+
    (p=PROVIDED connector_provided_expression)?
    (u=UP_ACTION LBRACE upa=connector_action? RBRACE)?
    (d=DOWN_ACTION LBRACE downa=connector_action? RBRACE)?
          -> ^(CONNECTOR_INTERACTION[$o]
              ^(CONNECTOR_INTERACTION_PORTS[$o] simple_name+)
              ^(PROVIDED[$p] connector_provided_expression)?
              ^(UP_ACTION[$u] $upa?)?
              ^(DOWN_ACTION[$d] $downa?)?
              (^(ANNOTATIONS annotation+))?
              )
    ;

connector_type_definition
    :
    c=CONNECTOR TYPE simple_name
    lp=LPAREN (port_params+=port_type_param (COMMA port_params+=port_type_param)*)  RPAREN
    annotated_multi_data_declaration*
    annotated_export_port_declaration?
    DEFINE connector_port_expression
    connector_interaction*
    END ->

    ^(CONNECTOR_TYPE[$c] simple_name
        ^(PORT_PARAMS[$lp] $port_params+)
        ^(DATA_DECLARATIONS annotated_multi_data_declaration+)?
        annotated_export_port_declaration?
        ^(DEFINE connector_port_expression)
        ^(CONNECTOR_INTERACTIONS connector_interaction*)?
     )
    ;

annotation_param
    :
    k=ID
    (ASSIGN_OP (v=ID|v=TRUE|v=FALSE|v=STRING) -> ^(ANNOTATION_PARAM[$k] $k $v)
    | -> ^(ANNOTATION_PARAM[$k] $k))
    ;


annotation
    :
        a=AT_SIGN n=ID (LPAREN annotation_param (COMMA annotation_param)* RPAREN)? -> ^(ANNOTATION[$a] $n annotation_param*)
    ;

annotated_type_definition
    : annotation* type_definition ->
              ^(ANNOTATED_TYPE
                     type_definition
                     (^(ANNOTATIONS annotation+))?)
    ;

type_definition
     : atom_type_definition
     | compound_type_definition
     | port_type_definition
     | connector_type_definition
     ;

// Rules for action language

primary_expression
    : fully_qualified_name
    | INT
    | FLOAT
    | STRING
    | TRUE
    | FALSE
    | LPAREN! logical_or_expression RPAREN!
    ;

statement
    : assignment_expression
    | postfix_expression
    ;

if_then_else_expression
    : IF LPAREN logical_or_expression RPAREN THEN ((then_stmts+=statement SEMICOL)|then_stmts+=if_then_else_expression)+
      (ELSE ((else_stmts+=statement SEMICOL)|else_stmts+=if_then_else_expression)+)?
      FI ->
        ^(IFTHENELSE_EXPRESSION logical_or_expression ^(THEN_SUBEXPR $then_stmts+) ^(ELSE_SUBEXPR ($else_stmts+)?))
    ;

assignment_expression
    : postfix_expression ASSIGN_OP^ logical_or_expression
    ;

logical_or_expression
    : (left+=logical_and_expression -> logical_and_expression)
      (OR_OP right+=logical_or_expression -> ^(OR_OP $left $right))?
    ;

logical_and_expression
    : (left+=inclusive_or_expression -> inclusive_or_expression)
      (AND_OP right+=logical_and_expression -> ^(AND_OP $left $right))?
    ;

inclusive_or_expression
    :  (left+=exclusive_or_expression -> exclusive_or_expression)
       (BWISE_OR_OP right+=inclusive_or_expression -> ^(BWISE_OR_OP  $left $right))?
    ;

exclusive_or_expression
    : (left+=and_expression -> and_expression)
      (BWISE_XOR_OP right+=exclusive_or_expression -> ^(BWISE_XOR_OP  $left $right))?
    ;

and_expression
    : (left+=equality_expression -> equality_expression)
      (BWISE_AND_OP right+=and_expression -> ^(BWISE_AND_OP  $left $right))?
    ;

equality_expression
    : relational_expression ((EQ_OP^|NE_OP^) relational_expression)?
    ;

relational_expression
    : additive_expression ((LT_OP^|GT_OP^|LE_OP^|GE_OP^) additive_expression)?
    ;

additive_expression
    : multiplicative_expression ((PLUS_OP^|MINUS_OP^) multiplicative_expression)*
    ;

multiplicative_expression
    :  unary_expression ((DIV_OP^|MOD_OP^|MULT_OP^) unary_expression)*
    ;

unary_expression
    : (MINUS_OP postfix_expression) -> ^(UNARY_MINUS postfix_expression)
    | (BWISE_NOT_OP^| NOT_OP^)? postfix_expression
    ;

postfix_expression
    : primary_expression
    | function_call_expression
    ;
    
function_call_expression
    : fully_qualified_name LPAREN argument_expression_list? RPAREN
        -> ^(FUNCTION_CALL_EXPRESSION fully_qualified_name argument_expression_list?)
    ;

argument_expression_list
    : logical_or_expression (COMMA logical_or_expression)*
        -> ^(ARGUMENT_EXPR_LIST logical_or_expression+)
    ;
