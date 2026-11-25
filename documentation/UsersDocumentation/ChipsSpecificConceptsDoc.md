# Chips Specific programming concepts

Chips is especially designed for the specification and easy deployment of programs for structured distributed systems.
While its synchronous aspect covers the need to design processes, it must be enhanced with an additional concept we define as **nodes** to handle the definition of networks of devices embedding these proceses.

## Nodes


- Physical
- Object

### Physical Functions

Physical functions feature the elements of logical functions (described in the [Chips classical programming concepts](./ClassicalConceptsDoc.md) section) along with other ones relative to the fact they represent entities in space (i.e. nodes), able to interact with their environment.
Which mean they also:

- have an additional **With section**,
- allow to label their input parameters with the **sensor** supertype, and
- allow to label their output dataflows with the **actuator** supertype.

When an input is declared as sensor, its data can only come from an actuator dataflow. And actuator dataflows can only provide data to sensor input parameters. Such mechanism is relevant for 2 reasons, the first one is that it allows some defensive programming when designing cyber physical systems, and the second one is that when deriving our models into a code base for real systems, the compiler can warn the developper about the need to complete the interface of such functions so it matches the hardware that is about to realize the function.

The **With section** is there to define information about the function that is relative to the topology of the network formed by all the functions the deveopper puts together. Procedural code can be written in such section, but only two kinds of information can outlive this scope: **contextual data** and **channel declarations**.

A **contextual data** is a variable that is meant to be shared with other functions. to declare a new contextual data called ```id```, of type ```int```, write ```ctx int id``` in the scope of the with section. Then, it can be refered to with ```ctx.id```.

**Channels** are a way to specify the connectivity capabilities of components. They can for instance model USB ports or GPIOs on a given hardware. Programatically, they don't make much sense as long as you are not using Chips more advanced features. More explanation on channels is provided in the [Chips Specific programming concepts](./ChipsSpecificConceptsDoc.md) section.

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
-> actuator turnOnAirRefrigiration(temperature > 40.0)
-> actuator LED(ctx.lock)
```

## Collective primitives

TODO

- Spread
- Collect

## What does everything means in a system section?

- ```link .. to```

- Plugging
  - Channels
  - Dataflows