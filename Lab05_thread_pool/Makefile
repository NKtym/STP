all: main

main: main.o thread_pool.o
	clang++ -std=c++20 -Wall -Wextra -pthread -fsanitize=thread -o main main.o thread_pool.o

main.o: main.cpp thread_pool.hpp
	clang++ -std=c++20 -Wall -Wextra -pthread -fsanitize=thread -c main.cpp

thread_pool.o: thread_pool.cpp thread_pool.hpp
	clang++ -std=c++20 -Wall -Wextra -pthread -fsanitize=thread -c thread_pool.cpp

clean:
	rm -f main *.o
