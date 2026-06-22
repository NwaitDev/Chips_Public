# Chips to BIP transformations

Chips to BIP transformations are developed with ATL (ATL Transformation Language), based on the metamodels of Chips and BIP.

- All the tools required to use ATL independantly from Eclipse are provided within the folder ```ChipsCompiler/FullCompileChain/Chips2BipTransformer```. Take a look at the makefile inside that folder to have an example on how to run the transformations on models.
- The Chips metamodel was designed during this project. If the Chips language is to evolve to the point the metamodel has to be modified, It is recomanded to modify the metamodel using the Eclipse Toolchain because it provides (how fortunate) a robust interface to handle EMF related file formats (```.ecore``` and ```.xmi```).
- The BIP metamodel comes from the (GitLab repository of the Verimag Laboratory)[https://gricad-gitlab.univ-grenoble-alpes.fr/verimag/bip].


TODO