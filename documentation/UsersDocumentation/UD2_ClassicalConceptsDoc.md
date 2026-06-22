# Chips classical programming concepts

TODO 

## Types

Chips is integrating two different categories of types : data types, and function types.

### Data types

On the one hand, dataflow types are a set of usual primitive types found in most programming languages:

- **int** for relative numbers;
- **float** for floating point values;
- **bool** for true and false;
- **\<type>[]** for dynamic data arrays;

These data types serve as input and output types for all the components of the complex systems. They can be manipulated with classical imperative code operators within the definition of Chips functions.

### Function types

On the other hand, function types are there to give context to the operations:

- **physical** is the type for procedures that are, by default, embodied in physical devices. The main idea behind such type is to model the part of the system that is *not* programmable but still occurs on the systems we wish to operate on (like the noises on signals, the delays between transmitted data, etc). In a future version of Chips, a **physical** could be associated to a .json sort of feature model describing the device it models, thus enriching simulations with real field data.
- **virtual** is the type of the procedures that may independently be instanciated on any device of the system. 

## Function Definition

TODO

- Input parameters

- Output parameters

- Init section

- Then section

### Logical Functions

TODO

### Physical Functions

TODO

- Contextuals

- Channels

## System Description

- ```link .. to```

- Plugging
  - Channels
  - Dataflows

- Constant dataflow definitions