# BIP Compiler

The BIP Compiler in ```ChipsCompiler/FullCompileChain/BipCompiler``` is directly extracted from the Verimag Gitlab repository. It has been slightly modified to handle the compilation of already serialized BIP models, thus skipping the parsing and building of the model internal representation. 

Normally, it shouldn't be necessary to modify such part of the Chips/BIP Compiler again unless need be to reuse bip compiler specific features.