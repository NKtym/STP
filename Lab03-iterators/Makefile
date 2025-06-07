all: test

test: test.cpp two_linked_list.hpp
	clang++ -std=c++17 -Wall -Wextra -pthread -o test test.cpp -lgtest -lgtest_main

clean:
	rm -f test
