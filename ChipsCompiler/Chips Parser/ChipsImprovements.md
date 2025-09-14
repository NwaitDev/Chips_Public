# Ideas of commands to include to Chips ?

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

- nupto :
    To provide a way to iterate like 
    ```c 
    for(int i =0; i<100; ++i){}
    ```
    in a :
    ```c
    for i in nupto(100) {} 
    ```
- downtoz :
    Same but from upper bound to zero

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