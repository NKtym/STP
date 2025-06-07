CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g
LDFLAGS = -lgtest -lgtest_main -pthread

all: sh_test un_test #failer_test_un

sh_test: sh_test.o
	$(CXX) $(CXXFLAGS) $^ -o sh_test $(LDFLAGS)

un_test: un_test.o
	$(CXX) $(CXXFLAGS) $^ -o un_test $(LDFLAGS)

sh_test.o: sh_test.cpp sh.hpp
	$(CXX) $(CXXFLAGS) -c sh_test.cpp -o sh_test.o

un_test.o: un_test.cpp un.hpp
	$(CXX) $(CXXFLAGS) -c un_test.cpp -o un_test.o

failer_test_un: failer_test_un.o
	$(CXX) $(CXXFLAGS) $^ -o failer_test_un $(LDFLAGS)

failer_test_un.o: failer_test_un.cpp un.hpp
	$(CXX) $(CXXFLAGS) -c failer_test_un.cpp -o failer_test_un.o

clean:
	rm -f *.o sh_test
	rm -f *.o un_test
