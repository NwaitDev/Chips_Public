# Example models

Because every programmer prefers to copy/paste code instead of reading documentation, here are some kick-off examples that you may want to use when you don't know where to start.

## No physical components example

Model of an application where processes, connected in a ring, count up to 20, over and over. They each wait for their next neighbor to provide a number before saying the following one or the same one.

```chips
logical counting(int seed=0,int previous_num=0) init {
    int rseed;
    bool has_been_initialized = false; 
    int next;
} then {
    if(!has_been_initialized){
        rseed = seed;
    }
    if (0 == (random(rseed)%2)) {
        next = previous_num;
    } else {
        next = previous_num + 1;
        if(next > 20){
            next = 0;
        }
    }
    rseed = random_next_seed(rseed);
} ->next_num(next)

SYSTEM{

    // instanciating an array of 10 processes
    counting[10] counters;

    for i in range(9) { // i goes from 0 to 8

        // connection of the output of 
        // each process to the input of the next one
        counters[i+1].previous_num(counters[i].next); 

    }

    //connecting the last component to the first one
    counters[0].previous_num(counters[9].next); 

    for i in range(10) {
        // setting the seed for every component
        counters[i].seed(i);
    }

    // define that the first process provide its output 
    // before reading its input
    start(counters[0]);
}
```

## With physical components example (but no collective primitives)

TODO

## With physical components example (but no collective primitives)

TODO