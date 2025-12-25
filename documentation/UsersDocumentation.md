# Documentation

## Structural configuration

The **structural configuration** is the physical model of all the components of a chips program. It serves as the base for describing all the possible paths of communication between instantiated components. 

## Dataflow

A **dataflow** is a sequence of values. The type of the dataflow is the type of its values. It can be a sequence of **integers** (int), **floating point values** (float) or **booleans** (bool).

## Contextual attribute

A **contextual attribute** is a located variable. Its value is a **dataflow**.

## Channel

A **channel** is an abstraction for a communication link. When two **channels** have the same type identifier, they can *feed* each other. A **Channel** has 1 **input** and 1 **output**. One **channel output** is able to feed one other **channel input** if they have the same type identifier and doesn't already feed a **channel input**.

## Node

A **Node** is an abstraction for a spatial location. It can have **channels** and **contextual attributes**. All instantiated **nodes** form a directed graph according to which node channel feeds which other node channel. We call such graphs **structural configurations**.


## Physical device specification

A **physical device specification** is an external file that is some sort of feature model for a device that would execute a part of a chips program. Its structure is still to be decided (it will probably be serialized SysML or UML).

## Computation capacities specifications

A **computation capacities specification** is an element of a **physical device specification** that gives information about the available *RAM*, *ROM* and/or *processing frequencies*, etc. 

## Sensor/Actuator

A **sensor** is a super type that can be added to a parameter of a **physical function**. An **actuator** is a super type that can be added to a **physical function** output.

## Logical function

A **logical function** is a chips component that can *eat* and/or *provide* **dataflow(s)**. It serves as a model for the behavior of a component.

## Physical function

A **physical function** is both a **logical function** and an **Node** with a concrete spatial location. A **physical function** can be implemented by a **physical device specification**. It serves as a model for the devices behaviors outside of the scope of the program they implement. So most of the time, it can just be an interface between the physical behavior model and the logical behavior model. But it can also include additional operations that model behaviors that are neither part of the programs they realize or the environment they are in (disturbances that are inherent to the devices).

## Object 

An **object** is a **node** that doesn't have a concrete spatial location yet.

## Implementation

**Implementation** is the concept of making a **node** realize the processes of another **node**. **Implementation** is a transitive relation. If ```A implements B``` and ```B implements C```, then ```A implements C```. 

- To **implement** an **object**, another **object** or a **physical function** must provide aliases for all the **contextual attributes** and **channels** of the implemented **object**. 
- The same is true for the **implementation** of a **physical function** with a **physical device specification**.

## (To) Support

To say that something **supports** a logical function means that thing has the same spatial location as the logical function.
A **logical function** can be **supported** by a **node**. If there is at least one **node** instantiated, each instantiated **logical function** has to be supported.
As long as an instantiated **physical function** is not implemented by a **physical device specification** with **computation capacities specifications**, it can *support* any number of **logical functions**. Given A and B, two **objects**, if ```A implements B```, then A inherits of all the supported functions of B.

## (To) Feed

The **feeding** relation is the relation between an instantiated element of the model providing an output and an instantiated element of the model providing an input. Therefore, a **logical function** output can feed another **logical function** parameter, and a **node** **channel** output can feed another **node** **channel** input (as long as inputs have the same types as outputs).

During the system instanciation, a **logical function** can also be fed by instantiated dataflow variables. However, developers must mind that they are feeding the function with a constant dataflow that is a copy of the current variable value. Finally, **logical functions** can be fed by direct values of the right type as well.
For what concerns **physical functions** instances, a **sensor** parameter can only be fed by an **actuator** output and an **actuator** output can only feed a **sensor** parameter.

## Sources

A **function** that can effectively produce an output is what we call a **source**. Therefore,a **function** for which all its **parameters** have a default value is a **source**. A **function** for which all the **parameters** are *fed* is also a **source**.


## Deadlock freedom

A system is said to be **deadlock free** if all functions are **sources**. A system must be deadlock free to be compiled and run.

-------------------------------------------


# Further developments

- Pure addition and extension (syntactic sugar)
- multiple devices node implementation
- external chips libraries/packages