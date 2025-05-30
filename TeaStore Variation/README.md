# About this model

Model written for the Workshop on Adaptable Cloud Architectures (WACA) of the DisCoTec2025 conference..
Here is the diagram on which the Chips development was based:

<img src="../img/ChipsIntended.png">

Finally, the version kept for WACA was much simpler because it only cares about one signal, and no hierarchy is used for the controllers. The general controller was removed, only to keep a controler at the level of the image provider + controller blocks (both encapsulated in the data treatment block in the BIP verison).

<img src="../img/simpleDataTreatment.png">

In further version, it should be possible to develop versions of the data treatment block where many caches are managed in parallel:

<img src="../img/aggregateDataTreatment.png">

The BIP model is mainly copied/pasted then refactored Chips.

The BIP/Chips model finally implemented can be represented by this diagram :

<img src="../img/BIPcompiled.png">

The compilation process was as follow :

- each Chips physical or virtual function is translated into a single BIP automaton.
- for each input flow, a state ``\<input_data_name\>_RCVD'' is added to the automaton and an exported port is added to synchronize the automaton transition to that state with the data sending automaton transition,
- symmetrically, the same operation is done for each output flow,
- in the end, the automata states form a loop.
- the user action model component was arbitrarily chosen to be the component starting the simulation, therefore, its initial state is the state just before sending its data,
- for every other automaton, the initial state is the state just before receiving its input data.


