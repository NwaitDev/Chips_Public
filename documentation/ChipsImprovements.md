# Additional Chips Features

## size :
    ```c
    int size(<sth>[] iterable);
    ```
    size operator to measure the size of an iterable

## resize:
    ```c
    <sth>[] size(<sth>[] iterable);
    ```
    change the quantity of information an iterable can hold. Copies or crop the initial data

## struct :
    to more easily pass parameters between components


## some probably very useful collective primitives

All of the following collective primitive definitions assume there is only one producing/consuming function per node of the comunication tree.

### some defaultly available spread collective primitive

```c
spread (<type> v = input)
broadcast among <node type> 
{}
->@(v)
->default(v)
```

```c
spread (int d = 0)
logical_distance among <node type> 
{}
->@(d)
->default(d+1)
```

```c
spread (float d = 0.)
physical_distance among <having dist ctx node type> 
{}
->@(d)
->default(d+ctx.dist)
```

```c
spread (int value = input[0], int id = input[1])
send_to_id among <having id ctx node type> 
{
    int output;
    int next;
    if(id == ctx.id){
        output = value;
        next = stop;
    } else {
        output = stop;
        next = value;
    }
}
->@(output)
->default(next, id)
```

### some defaultly available collect collective primitive

```c
collect (<numeric type> acc = 0, int nb = 0)
avg among <node type>
{
    <numeric type> sum = 0;
    int nb_next = 0;
    for chan in channels {
        sum = sum + chan.acc;
        nb_next = nb_next + chan.nb;
    }
    sum = sum + input;
    nb_next = nb_next + 1;
} ->@(sum/nb_next)
-> default(sum, nb_next)
```

```c
collect (int[nb_keys] histog = zeros(nb_keys))
histogram among <node type>
{
    int [nb_keys] merged_histog = zeros(nb_keys);
    int nb_next = 0;
    for chan in channels {
        for i in range(nb_keys) {
            merged_histog[i] = merged_histog[i] + chan.histog[i];
        }
    }
    merged_histog[input[0]] = merged_histog[input[0]] + input[1];
} ->@(merged_histog)
-> default(merged_histog)
```

```c
collect (int[nb_values] acc = zeros(nb_values), int count = 0)
concatenate among <node type>
{
    int[nb_values] next_acc = zeros(nb_values);
    int next_count = 0
    for chan in channels {
        for i in range(chan.count) {
            next_acc[next_count + i] = chan.acc[i];
        }
        next_count = next_count + chan.count;
    }
    next_acc[next_count] = input;
} ->@(next_acc)
-> default(next_acc, next_count + 1)
```

```c
collect (<DataStructure> acc = <DataStructure>.ZERO)
VECTORSPACE among <node type>
{
    <DataStructure> next_acc = <DataStructure>.ZERO;
    for chan in channels {
        next_acc = <DataStructure>.plus(next_acc, chan.acc);
    }
    next_acc = <DataStructure>.plus(next_acc, input);
} ->@(next_acc)
-> default(next_acc)
```

## control receipes:

```c


physical Catom (float current, sensor int[12] neighborhood_signals) with {
    ctx float x = 0; // differentiate actual value and desired enforced value
    ctx float y = 0;
    ctx float z = 0;
} init {
    int [12] signals_for_neighbors;
    int r, g,b;
} then {
    // process to react to the 
    // neighborhood signals 
    // acknowledging contextual data
} -> actuator signals_for_neighbors(signals_for_neighbors)
-> actuator light(blablabla)

object CatomSet with {
    ctx float distance = 10.0;
    ctx float sensitivity = 1.0;
    ctx bool achieved = false;
    ctx float [3] avg_pos = 0;
    ctx int nb_catoms = 0;
    ctx goal_pos = 0;
} receipe DistanceHomogeneity among Catom {
    avg_pos = 0;
    nb_catoms = 0;
    for pos in Catom {
        nb_catoms = nb_catoms + 1;
        avg_pos[0] = avg_pos[0] + pos.x;
        avg_pos[1] = avg_pos[1] + pos.y;
        avg_pos[2] = avg_pos[2] + pos.z;
        for other_pos in Catom {
            if (other_pos != pos){
                error = sqrt(
                    (pos.x-other_pos.x)**2 
                    + (pos.y-other_pos.y)**2
                    + (pos.z-other_pos.z)**2
                ) - distance;
                if(error < sensitivity){
                    achieved = true;
                } else {
                    float [3] displ = pid(distance, error);
                    pos.x = pos.x + displ[0];
                    pos.y = pos.y + displ[1];
                    pos.z = pos.z + displ[2];
                }
            }
        }
    }
    for i in range(3){
        avg_pos[i] = avg_pos[i]/(float)nb_catoms;
    }
} receipe ReachGoalPos among Catom {
    if(achieved) {
        float[3] displ = normalize(goal_pos - avg_pos)*0.3;
        for pos in Catom {
            pos.x = pos.x + displ[0];
            pos.y = pos.y + displ[1];
            pos.z = pos.z + displ[2];
        }
    }
}

object CatomSetSet with {
    ctx int shape = NONE;
    ctx bool achieved = true;
    CatomSet center_piece = NULL;
    ctx int nb_catom_sets = 0; 
} receipe CountCatomSets among CatomSet {
    nb_catom_sets = 0;
    for cs in CatomSet {
        nb_catom_sets = nb_catom_sets + 1;
    }
} receipe ComputeCenterPiece among CatomSet {
    nb_catom_sets = 0;
    for cs in CatomSet {
        
    }
} receipe ShapeShift among CatomSet {
    if(achieved){
        if(shape == TOWER){
            shape = LINE;
            achieved = false;
        } else {
            shape = TOWER;
            achieved = false;
        }
    }
} receipe ToTower among CatomSet {
    if(shape == TOWER){
        // represent the process that
        // builds the TOWER by moving 
        // CatomSets on top of eachothers
    }
} receipe ToLine {
    // other kind of procedure to realize
    // the shape
} 

```