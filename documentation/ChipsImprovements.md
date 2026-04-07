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