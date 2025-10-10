# State of the Chips metamodel

A chips program is divided in two parts: definitions and a description.
The definitions allow the specification of the components behaviors by declaring their inputs, outputs, inner variables, etc.
The descriptipon specifies the number of components, their configuration and the way they transmit data among themselves.
The following sections describe the elements of the metamodel realted to each part. 

## Definition metamodel

- import definition is a datastructure holding two String values: 
    - the device specification source file name,
    - the name of the physical function that will be associated to the device.

- pure function is definable as:
    - a String attribute 'name'
    - a list of references of parameters 'parameters'
    - a list of references of expressions 'output_flow'
which are syntactically organized this way in the program:
```
pure name(parameters1, parameters2, ...)
-> (output_flow1, output_flow2, ...)
```

- logical or physical functions are definable as:
    - a String attribute 'name'
    - a list of references of parameters 'parameters'
    - a list of references of expressions 'output_flow'
    - a list of references of process instructions 'init_instruction'
    - a list of references of process instructions 'then_instruction'
    - a reference to a specification file import (only for physical functions)

which are syntactically organized this way in the program:
```
physical | logical name(parameters1, parameters2, ...)
init {
    init_instruction1
    init_instruction2
    ...
} then {
    then_instruction1
    then_instruction2
    ...
}
->  (output_flow1, output_flow2, ...)
```
- Currently, available primitive types are:
    - int,
    - float,
    - bool.

- An 'instance' and a 'variable' class are defined and automatically implemented when the designed model declares functions (pure, logical, physical) and variables (int, float, bool) respectively so the other elements of the model can refer to them.

- Parameters are represented by a String 'name' associated with a primitive type.

- process_instructions are among:
    - variable declaration,
    - assignment.

- an assignment is linking a variable to an expression. Such expressions are the same as the one used as output_flow.

- An output_flow is one expression among: 
    - binary expression,
    - unary expression, 
    - variable expresion,
    - purecall expression (computing the output of a pure function),
    - direct value expression.

## Description metamodel

- a list of references to process instructions to define number of components or their configuration with formulas. Such process instructions are the same as the one used in the definitions of the functions :
    - variable declaration,
    - assignment.

- a list of references to description instructions to instanciate components and specify their relations. They comprise:
    - object declaration (physical or logical),
    - physical linkage between logical components and other components,
    - location specification of the declared physical components,
    - plugging instructions for connecting output of components to inputs of other components.


# What the metamodel doesn't do

- Type checking still needs to be done since Eclipse Modeling Framework doesn't fully support type genericity with the type parameters feature -> it is difficult to encode the number or sort of the parameters of the functions to only allow correct-by-construction programs.
- Automatically generate examples of programs / write more xmi samples of code to test transformations.

# To be done

- adding program flow control constructs such as 'if-then-else', 'for', 'for-each', 'switch', 'while', etc.
- adding user defined data structures
- making use of the 'program_var -> instance' as a global variable for both the definitions and the description
- including array-like data structures for dataflows of primitive types
