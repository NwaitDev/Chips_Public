.PHONY: all test clean run

SRCS := $(shell ls -d sources/*)

all: chipsc

chipsc: $(SRCS)
	mkdir -p build ; cd build ; cmake ..
	cd build && make 2> ../debug.log

clean:
	rm -rf ./generated ./build
