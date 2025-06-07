CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g
LDFLAGS = -lgtest -lgtest_main -pthread

all: test

test: time_and_time_span.o test.o
	$(CXX) $(CXXFLAGS) $^ -o test $(LDFLAGS)
	./test

time_and_time_span.o: time_and_time_span.cpp time_and_time_span.hpp
	$(CXX) $(CXXFLAGS) -c time_and_time_span.cpp -o time_and_time_span.o

test.o: test.cpp time_and_time_span.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o

clean:
	rm -f *.o test
