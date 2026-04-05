.PHONY: all test clean quicktest

SRCS := $(shell ls -d sources/*)

all: chipsc

chipsc: $(SRCS)
	mkdir -p build ; cd build ; cmake ..
	cd build && make 2> ../debug.log

run: quick.chips
	./build/chipsc quick.chips

clean:
	rm -rf ./generated ./build
