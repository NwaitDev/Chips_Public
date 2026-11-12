# Chips to BIP transformations

Chips to BIP transformations are developed with ATL (ATL Transformation Language), based on the metamodels of Chips and BIP.

`chips2bip.atl` maps the Chips model onto a BIP model whose root compound is named `SYSTEM_COMPOUND`.

- Run the transformation using the command ```emftvm.sh <chips1.1.ecore> <BIP.ecore> <in.chips.xmi> <chips2bip.atl> <out.bip.xmi>```.
  
- Arrays of instances are flattened by helpers such as `range` (all index tuples of a shape) and `linearize` (a tuple to a flat index). Their commented-out self-tests sit at the top of the file.
  
- `bipc --xmi <out.bip.xmi> -d SYSTEM_COMPOUND --genbip-output-dir <folder>` writes the `.bip` file. `chipsc` then strips the `@0` suffixes bipc adds to identifiers.
  
- The two metamodels are the contract between the stages. A change in `chips1.1.ecore` must be matched in `ChipsToXmiWriter` and in the ATL rules that read it.

- All the tools required to use ATL independantly from Eclipse are provided within the folder ```ChipsCompiler/FullCompileChain/Chips2BipTransformer```. Take a look at the makefile inside that folder to have an example on how to run the transformations on models.
  
- The Chips metamodel was designed during this project. If the Chips language is to evolve to the point the metamodel has to be modified, It is recomanded to modify the metamodel using the Eclipse Toolchain because it provides (how fortunate) a robust interface to handle EMF related file formats (```.ecore``` and ```.xmi```).
  
- The BIP metamodel comes from the (GitLab repository of the Verimag Laboratory)[https://gricad-gitlab.univ-grenoble-alpes.fr/verimag/bip].

## TODO

Document each ATL Rule. For the moment, the Chips2BIP transformations are quite cryptic.