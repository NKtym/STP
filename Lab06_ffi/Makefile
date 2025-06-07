all: libinstructions.so libinstructions-c.so run

libinstructions.so:
	g++ -std=c++17 -fPIC -IInstructions -IInstructions-c -shared -o libinstructions.so Instructions/instructions.cpp

libinstructions-c.so: libinstructions.so
	gcc -fPIC -IInstructions -IInstructions-c -shared -o libinstructions-c.so Instructions-c/instructions_c.cpp -L. -linstructions

run: libinstructions.so libinstructions-c.so
	cd "Go!" && LD_LIBRARY_PATH=..:$$LD_LIBRARY_PATH go run main.go

clean:
	rm -f *.so