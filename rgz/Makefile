all: Test_graph

Test_graph: Test_graph.cpp Graph.hpp
	g++ -std=c++17 -isystem /usr/local/include -pthread -Wall -Wextra $^ -L/usr/local/lib -lgtest -lgtest_main -pthread -o $@
	
clean:
	rm -f Test_graph