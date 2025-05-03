.PHONY: all test clean quicktest

all: chipsc

ChipsParser.cpp: ChipsParser.yy cpp_sources/ChipsAST.hpp
	bison --language=c++ -v -d -o $@ $<

ChipsLexer.cpp: ChipsLexer.l ChipsParser.cpp
	flex -o $@ $<

chipsc: ChipsLexer.cpp ChipsParser.cpp ChipsDriver.cpp
	g++ ChipsParser.cpp ChipsLexer.cpp ChipsDriver.cpp -lfl -o chipsc

test: chipsc
	./CompilerTests.sh

quicktest: chipsc quick.chips
	./chipsc quick.chips

clean: 
	rm -f ChipsParser.hpp ChipsParser.cpp ChipsLexer.cpp chipsc \
		position.hh stack.hh location.hh