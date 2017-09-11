all: p1
	
p1: p1.o function.o
	g++ -o p1 p1.o function.o

p1.o: p1.cpp
	g++ -c p1.cpp

function.o: function.cpp
	g++ -c function.cpp

clean:
	rm -f  *.o
