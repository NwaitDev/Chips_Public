# Example models

Because every programmer prefers to copy/paste code instead of reading documentation, here are some kick-off examples that you may want to use when you don't know where to start.

## Additioner

```
logical Additioner(int a, int b) 
init {} then {} -> out(a+b)

logical Consumer(int data)
init{} then {
    probe(data);
}

system {
    Additioner foo;
    Consumer bar;
    bar.data(foo.out);
    foo.a(31);
    foo.b(11);
}
```


## Additioner Array

```
logical Additioners(int a, int b) 
init {} then {} -> out(a+b)

logical Consumer(int data)
init{} then {
    probe(data);
}

system {
    int nb_foos = 5;
    Additioners [nb_foos] foos;
    Consumer bar;
    for i in range(nb_foos){
        if(i>0){
            foos[i].a(foos[i-1].out);
        }
        foos[i].b(2);
    }
    foos[0].a(1);
    bar.data(foo[nb_foos-1].out);
}
```

## Message Broadcast

```
logical Sender() 
init {
    bool has_message = true;
    int message = 42;
} then {
    if(!has_message){
        message = 0;
    }
} -> communication(message)

logical Receivers(int data)
init{
    bool has_message = false;
} then {
    if(data!=0){
        if (is_fresh(data)){
            has_message = true;
            probe(data);
        } else {
            has_message = false;
        }
    }
    probe(has_message);
}

object Computers with {
    USB port1;
    USB port2;
    USB port3;
}

spread (int to_be_broadcasted = input) broadcast 
among Computers {
    int comm;
    if(to_be_broadcasted = 0){
        comm = stop;
    } else {
        comm = to_be_broadcasted
    }
} 
->@(comm)
->default(comm)

system {
    int nb_computers = 5;
    int nb_receivers = nb_computers - 1;
    Computers [nb_computers] cpt;
    Sender sender;
    Receivers[nb_receivers] receivers;
    
    //
    //   0 -- 1 -- 3
    //        |
    //        2 -- 4
    //

    cpt[0].port1(cpt[1].port1); // warning, connections are oriented
    cpt[3].port2(cpt[1].port2);
    cpt[1].port3(cpt[2].port3);
    cpt[2].port2(cpt[4].port2);


    for i in range(nb_receivers){
        link receivers[i] to cpt[i];
        receivers[i].data((broadcast) sender.communication);
    }
    link sender to cpt[nb_computers - 1];

}
```
