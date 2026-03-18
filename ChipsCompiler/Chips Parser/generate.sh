rm -rf build
java -jar antlr-4.13.1-complete.jar -Dlanguage=Cpp -visitor -no-listener -o generated Chips.g4 
mkdir -p build && cd build
cmake ..