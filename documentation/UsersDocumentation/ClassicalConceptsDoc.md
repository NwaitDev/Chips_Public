# Chips classical programming concepts

As Chips is a synchronous language, it allows programmers to develop models that compute information just as a sort of industrial production line.

Every function is meant to process as long as it is fed by new data. Therefore, as opposed to other more general languages, when you define a variable in Chips, what you actually define is a *dataflow*. Chips is all about manipulating dataflows. Whenever you want to combine several dataflows, or even turn a single dataflow into another, you need to define a function.

## Dataflow types

On the one hand, dataflow types are a set of usual primitive types found in most programming languages:

- **int** for relative numbers,
- **float** for floating point values,
- **bool** for true and false.

A dataflow of type ```<T>``` called ```myDataflow``` is declared by writing ```<T> myDataflow```.

You can also define static arrays of dataflows (or dataflows of static arrays, think of it the way you like) by using the square brackets operator **[]**.
An array of 10 dataflows of type ```<T>``` called ```tenDataflows``` is declared by writing ```<T>[10] tenDataflows```.
You can access the *n*-th element of such array using ```tenDataflows[n]```. Of course, *n* must be in [0,10). Arrays are 0-indexed. You can also define multi-dimensional arrays by chaining indexes in [].

These dataflow types serve as input and output types for all the components of the complex systems. They can be manipulated with classical imperative code operators within the definition of Chips functions. They are the only way to operate on dataflows.

## Function Definition

A function definition is a specification of how a dataflow can be modified. It features 5 key elements:

- A **name** (how original) so we can refer to it later,
- **Input parameters**, the declarations of the dataflows that must be provided to the function,
- **Output parameters**, the different dataflows that the function exposes to the rest of the system,
- an **Init section**, a code snippet defining the initial state of the function, and
- a **Then section**, which defines how the inner state of the function and the outputs of the function evolve according to the input dataflow it receives.

In Chips, there exist two types of functions.

- **physical** is the type for procedures that are, by default, embodied in physical devices. The main idea behind such type is to model the part of the system that is *not* programmable but still occurs on the systems we wish to operate on (like the noises on signals, the delays between transmitted data, etc).
- **logical** is the type of the procedures that may independently be instanciated on any device of the system.

They must be diferentiated to allow some of Chips features when it comes to the automatic generation of code for real-world implementation of models (see section [From Chips Specs to embeddable code](./RealWorldCPS.md)).

If you are only interested in describing programs in a synchronous way or just intend to simulate the execution of the systems you design, you can only focus on logical functions. Physical functions are described in the [Chips Specific programming concepts](./ChipsSpecificConceptsDoc.md) section.

### Logical Functions

They solely feature the elements mentionned above. Their syntax is as follow:

```c
logical myFunctionName( /* declaration of the input parameters, comma separated */)
init {
  // initialization statements
  // every dataflow declared in this
  // scope is considered part of the
  // function inner state
}
then {
  // update statements for the inner
  // state variables of the function.
}
-> anOutputDataflowName(/* expression defining the output dataflow (can refer to the inner state dataflows) */)
// any number of outputs can be defined
-> lastoutputDataflowName(/* expression defining the output dataflow */)
```

For instance, functions that compute mathematical operations over signals could be defined as:

```c
logical square(float x) init {} then {}->result(x*x)

logical integral(float x, float dt)
init {
  float time = 0;
  float sum = 0;
}
then {
  sum = sum + x*dt;
}
-> result(sum)
```

## System Description

The system section is where you define what components are part of your model, and how they are connected together. The code in this section *looks* imperative, but it actually is *synchronous*. That is why several kind of statements in this section don't exist in most general purpose progamming languages. The system section of a Chips model allows you to:

- Use the same kind of statements[^1] as in the definition of functional blocks to define dataflow variables and modify them,
- Use the functional block definitions name as first class datatype to define instances of logical/physical components,
- Specify which functional block output should be plugged to which functional block input.


[^1]: except for the *fromfile* and *probe* statement, which are sorts of debug statements that only make sense during the simulation of the components behaviors. More details in the [From Chips Specs to embeddable code](./RealWorldCPS.md) section.

A system section must be written at the end of each Chips file that one wants to compile. Assuming the previous definitions of the integral and square functional blocks preceed, an example of system definition that computes the integral of some quantity which grows proportionally to the square of the time passed:

```c
// ... Previous definitions ...

// component consuming a float output and writing the dataflow received to a csv file
logical printer(float data) init {} then {probe(data);}

system{

  // definition of a dataflow variable 
  float dt = 0.001; 
  
  // definition of actual components that will run the processes
  integral time;
  square quantity;
  integral integrator;
  printer p;

  // dataflow expressions can act as feeders for functional block inputs
  time.x(1);

  // an expression feeding a functionnal block input is only interpreted once, at compile time 
  time.dt(dt);
  integrator.dt(dt);

  // Functional block outputs also can be used to feed functional block inputs
  quantity.x(time.result);
  integrator.x(quantity.result);
  p.data(integrator.result);
}
```
