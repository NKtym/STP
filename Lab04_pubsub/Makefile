all: bc_demo

bc_demo: main.o circular_buf.o
	clang++ -std=c++17 -Wall -Wextra -pthread -fsanitize=thread -o bc_demo main.o circular_buf.o

main.o: main.cpp circular_buf.hpp
	clang++ -std=c++17 -Wall -Wextra -pthread -fsanitize=thread -c main.cpp

circular_buf.o: circular_buf.cpp circular_buf.hpp
	clang++ -std=c++17 -Wall -Wextra -pthread -fsanitize=thread -c circular_buf.cpp

clean:
	rm -f bc_demo *.o
