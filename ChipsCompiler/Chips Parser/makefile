.PHONY: all test clean quicktest

all: chipsc

ChipsParser.cpp: ChipsParser.yy cpp_sources/ChipsAST.hpp
	bison --language=c++ -v -d -o $@ $<

ChipsLexer.cpp: ChipsLexer.l ChipsParser.cpp
	flex -o $@ $<

chipsc: ChipsLexer.cpp ChipsParser.cpp ChipsDriver.cpp cpp_sources/chips_node_print.cpp cpp_sources/chips_exceptions.cpp
	g++ -fPIC ChipsParser.cpp ChipsLexer.cpp ChipsDriver.cpp \
	    cpp_sources/chips_node_print.cpp \
	    cpp_sources/chips_exceptions.cpp \
	    cpp_sources/chips_ast_impl.cpp \
		cpp_sources/chips_semantic_analyzer.cpp \
	    to_xmi/ChipsToXmiWriter.cpp \
	    to_xmi/ChipsToXmiVisitor.cpp \
	    -lfl -std=c++17 -o chipsc

test: chipsc
	./CompilerTests.sh

quicktest: chipsc quick.chips
	./chipsc quick.chips

clean:
	rm -f ChipsParser.hpp ChipsParser.cpp ChipsLexer.cpp chipsc \
	      position.hh stack.hh location.hh output_*.xmi *.output
