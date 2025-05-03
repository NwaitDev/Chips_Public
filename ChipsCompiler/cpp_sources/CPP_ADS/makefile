.PHONY: all test

all: makefile *.cpp
	g++ -o unit_tests unit_tests.cpp -L/usr/local/lib -lgtest -pthread
test: all
	valgrind --track-origins=yes --leak-check=full ./unit_tests
