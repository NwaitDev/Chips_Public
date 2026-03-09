#ifndef __metamodel_enums__
#define __metamodel_enums__


namespace chips{
    /**
     * Components that can be plugged in system section
     */ 
    enum class block_type {
        LOGICAL, // only using regular in/outputs
        PHYSICAL, // can use regular in/outputs, sensor/actuators and channel in/outputs
        OBJECT // can only be plugged to other objects with channel in/outputs
    };

    /** 
     * Types of the elements that can appear in the preamble section
     */
    enum class definition_type {
        NODE, // to define objects and physicals
        FUNCTION, // to define logical and physicals
        IMPLEMENTATION // to define node inheritance (work in progress, do not use)
    };

    /**
     * Environments for the interpretation 
     * of direct values and variables
     */
    enum class expression_env {
        PRIMITIVE, // each value is interpreted as a regular variable
        COLLECTIVE, // each value can be interpreted as either a value of its type or a "NULL" (stop value)
        SYSTEM // each value is interpreted as a regular variable until it is plugged. Then, it represents a constant dataflow
    };

    /**
     * Primitive types of data that Chips handles
     */
    enum class dataflow_type {
        INT, // regular integers
        FLOAT, // floating point values
        BOOL // booleans
    };

    /**
     * Kind of signals to be distinguished when working with Cyber Physical Systems
     */
    enum class dataflow_kind {
        LOGICAL, // produced by any functional block or system variable
        PHYSICAL // specific to physical functional blocks
    };

    /**
     * Node specific variable kinds
     */
    enum class node_element {
        CHANNEL, // communication port to refer to when transmitting a signal between nodes
        CONTEXTUAL_INT, // Chips integer variable shared by all the functional blocks supported by a node
        CONTEXTUAL_FLOAT, // Chips float variable shared by all the functional blocks supported by a node
        CONTEXTUAL_BOOL // Chips bool variable shared by all the functional blocks supported by a node
    };

    /**
     * Statements that are encountered in different environments
     */
    enum class recurring_statement {
        // generic statements
        IF, // if ( bool expr ){ statements } [ else { statements } ]
        FOREACH, // for variable in iterable { statements }
        DECLARATION, // type identifier
        ASSIGNMENT, // identifier = expression
        // system specific statements
        IMPLEMENTS, // identifier implements identifier using identifier
        PLUGGING, // identifier.identifier(identifier.identifier)
        FEEDING, // identifier.identifier(expression | identifier.identifier)
        LINKING, // link identifier to identifier
        // implementation specific statements
        ALIASING // specific to implementation section (work in progress, do not use)
    };

    /**
     * Environments that should allow to distinguish
     * the kind of statements that can be used in the code
     */
    enum class statement_env {
        DEFINITION, // in the body of function definitions (init/then sections)
        COLLECTIVE, // in the body of collective primitive definitions
        SYSTEM, // in the system description
        IMPLEMENTATION, // in the body of node implementation definition (work in progress, do not use)
        NODE // in the body of a node definitions (with sections)
    };

    /**
     * Kinds of output that can be used to 
     * spread or collect information among
     * a crowd of interconnected components
     * reparted in nodes (i.e. object or physical).
     */
    enum class collective_output_kind {
        CHANNELED, // accumulator transmitted to another component via a specific channel
        DEFAULTED, // accumulator transmitted to another component via a non specified channel
        TARGET // data transmited to the current component input parameter
    };

    /**
     * Kinds of collective primitives designed
     * to wisely use information in a crowd of 
     * interconnected components reparted in nodes (i.e. object or physical).
     */
    enum class collective_function_type {
        SPREAD, // generalization of the broadcast operation
        COLLECT // generalization of the merge operation
    };
}

#endif