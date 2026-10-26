.PHONY: all test clean run chipsc

SRCS := $(wildcard src/*) CMakeLists.txt

all: build/Chips2Cpp

build/Makefile: CMakeLists.txt
	mkdir -p build && cd build && cmake ..

build/Chips2Cpp: $(SRCS) build/Makefile
	$(MAKE) -C build 2> debug.log

clean:
	rm -rf ./generated ./build
