# Additional Chips Features

- size :
    ```c
    int size(<sth>[] iterable);
    ```
    size operator to measure the size of an iterable

- resize:
    ```c
    <sth>[] size(<sth>[] iterable);
    ```
    change the quantity of information an iterable can hold. Copies or crop the initial data

- switch :
    ```c
    switch ($value) {
        (litteral){
            stt;
        }
        (litteral, litteral, litteral){
            stt;
            stt;
        }
        (default) { stts }
    }
    ```
    or
    ```c
    if ($value == litteral) {
        stt;
        stt;
    } elif($value == litteral || $value == litteral) {
        stt;
    } elif($value == litteral || $value == litteral) {
        stt;
    } else {
        bla bla...
    }
    ```
    I'd rather use the second possibility because it is easier to translate to BIP and very expressive

- flagbearer :
    list of alternative enums for which a check of presence of something would be
    easy. Need to find a proper syntax. It would look like a struct only containing
    boolean values, except they have name.
    Would allow another use of the 'in' operator.

    ```c
    flagb symb = LETTERS°NUMBERS°NONALPHANUM..SMALL°BIG..USUAL°UNUSUAL; // internal representation : 3bits
    // maybe like this
    flagb symb = (LETTERS or NUMBERS or NONALPHANUM) and (SMALL or BIG) and (USUAL or UNUSUAL);
    symb x = LETTERS..SMALL..USUAL;
    symb y = SMALL..NUMBERS..USUAL;
    symb z = UNUSUAL; // other fields will be undefined

    if (x == y)
        // do sth
    if (LETTERS in x)
        // do sth
    if (LETTERS and SMALL in y)
        // do sth
    ```

- struct :
    to more easily pass parameters between components

- control receipes:
```c
object POINT with{
    ctx float x = 0;
    ctx float y = 0;
}

object ThreePoints with {
    ctx float respected_dist = 10.0;
}
receipe among POINT {
    for point in POINT{
        for other_point in POINT {
            if (other_point != point){
                error = (point.x-other_point.x)*(point.x-other_point.x) + (point.y-other_point.y)*(point.y-other_point.y) - respected_dist;
                float [2] displ = pid(respected_dist, error);
                point.y = displ()
            }
        }
    }
}

object AA with {
    ctx int nb_quads = 0;
    ctx int command;
} receipe among A {
    
}

object AAA with {
    ctx int nb_cubes = 0;
    ctx int command = MAKE_FACES;
} receipe among AA {
    if(command == MAKE_FACES && nb_cubes == 0){
        int nb_faces = 0;
        for i in AA.nb_quads {
            nb_faces = nb_faces + i;
        }
    }
} receipe among AA {

}

```