.PHONY: all test clean run

SRCS := $(shell ls -d sources/*)

all: chipsparser

chipsparser: $(SRCS)
	mkdir -p build ; cd build ; cmake ..
	cd build && make 2> ../debug.log
	cp build/chipsparser chipsparser

clean:
	rm -rf ./generated ./build chipsparser *.log .antlr
