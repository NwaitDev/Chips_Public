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


physical Catom (float current, int[6] neighborhood_signals) with {
    ctx float x = 0;
    ctx float y = 0;
}

object SIMPLEX with {
    // side so the simplex tries to get equilateral
    ctx float side = 10.0;
}
receipe Equilateral among POINT {
    for point in POINT{
        for other_point in POINT {
            if (other_point != point){
                error = sqrt((point.x-other_point.x)**2 + (point.y-other_point.y)**2) - side;
                float [2] displ = pid(side, error);
                point.x = point.x + displ;
                point.y = point.y + displ;
            }
        }
    }
}

object 

```