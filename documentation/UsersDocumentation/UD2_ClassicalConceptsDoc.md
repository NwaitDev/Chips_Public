# Chips classical programming concepts

As Chips is a synchronous language, it allows programmers to develop models that compute information just as a sort of industrial production line.

<img>

Every function is meant to process as long as it is fed by new data. Therefore, as opposed to other more general languages, when you define a variable in Chips, what you actually define is a *dataflow*. Chips is all about manipulating dataflows. Whenever you want to combine several dataflows, or even turn a single dataflow into another, you need to define a function.

## Dataflow types

On the one hand, dataflow types are a set of usual primitive types found in most programming languages:

- **int** for relative numbers,
- **float** for floating point values,
- **bool** for true and false.

A dataflow of type ```<T>``` called ```myDataflow``` is declared by writing ```<T> myDataflow```.

You can also define static arrays of dataflows (or dataflows of static arrays, think of it the way you like) by using the square brackets operator **[]**.
An array of 10 dataflows of type ```<T>``` called ```tenDataflows``` is declared by writing ```<T>[10] tenDataflows```.
You can access the *n*-th element of such array using ```tenDataflows[n]```. Of course, *n* must be in [0,10). Arrays are 0-indexed. You can also define multi-dimensional arrays by chaining [].

These dataflow types serve as input and output types for all the components of the complex systems. They can be manipulated with classical imperative code operators within the definition of Chips functions. They are the only way to operate on dataflows.

## Function Definition

A function definition is a specification of how a dataflow can be modified. It features 5 key elements:

- A **name** (how original) so we can refer to it later,
- **Input parameters**, the declarations of the dataflows that must be provided to the function,
- **Output parameters**, the different dataflows that the function exposes to the rest of the system,
- an **Init section**, a code snippet defining the initial state of the function, and
- a **Then section**, which defines how the inner state of the function and the outputs of the function evolve according to the input dataflow it receives.

In Chips, there exist 2 types of functions. They must be diferentiated to allow some of Chips features when it comes to the automatic generation of code for real-world implementation of models.

- **physical** is the type for procedures that are, by default, embodied in physical devices. The main idea behind such type is to model the part of the system that is *not* programmable but still occurs on the systems we wish to operate on (like the noises on signals, the delays between transmitted data, etc). In a future version of Chips, a **physical** could be associated to a .json sort of feature model describing the device it models, thus enriching simulations with real field data.
- **logical** is the type of the procedures that may independently be instanciated on any device of the system.

If you are only interested in describing programs in a synchronous way or just intend to simulate the execution of the systems you design, you can only focus on logical functions. 

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

For instance, a function that computes the integral of a signal over time with the rectangles method would be:

```c
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

### Physical Functions

Physical functions feature the elements of logical functions along with other ones relative to the fact they represent entities in space, able to interact with their environment.
Which mean they also:

- have an additional **With section**,
- allow to label their input parameters with the **sensor** supertype, and
- allow to label their output dataflows with the **actuator** supertype.

When an input is declared as sensor, its data can only come from an actuator dataflow. And actuator dataflows can only provide data to sensor input parameters. Such mechanism is relevant for 2 reasons, the first one is that it allows some defensive programming when designing cyber physical systems, and the second one is that when deriving our models into a code base for real systems, the compiler can warn the developper about the need to complete the interface of such functions so it matches the hardware that is about to realize the function.

The **With section** is there to define information about the function that is relative to the topology of the network formed by all the functions the deveopper puts together. Procedural code can be written in such section, but only two kinds of information can outlive this scope: **contextual data** and **channel declarations**.

A **contextual data** is a variable that is meant to be shared with other functions. to declare a new contextual data called ```id```, of type ```int```, write ```ctx int id``` in the scope of the with section. Then, it can be refered to with ```ctx.id```.

**Channels** are a way to specify the connectivity capabilities of components. They can for instance model USB ports or GPIOs on a given hardware. Programatically, they don't make much sense as long as you are not using Chips more advanced features. More explanation on channels is provided in the next user documentation page.

A physical function modeling a router can be:

```c
physical fourPortsRouter(int user_defined_config, sensor float temperature)
with {
  // a channel definition
  RJ45 A;
  RJ45 B;
  RJ45 C;
  RJ45 D;
  // a contextual data
  ctx int serial_num = 12345678;
  ctx bool lock = false;
}
init {
  bool[10] config_flags;
  for index in range(10) {
    config_flags[index] = false;
  }
}
then {
  if (!ctx.lock){
    for i in range(10) {
      config_flags[i] = (user_defined_config % 2 == 0);
      user_defined_config = user_defined_config / 2;
    }
  }
}
-> actuator turnOnAirRefrigiration(temperature > 30.0)
-> actuator LED(ctx.lock)
```

## System Description

TODO

- ```link .. to```

- Plugging
  - Channels
  - Dataflows

- Constant dataflow definitions
