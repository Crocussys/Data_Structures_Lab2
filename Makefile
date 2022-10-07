all: main.o matrixtl.o matrixccs.o
	g++ main.o matrixtl.o matrixccs.o -o Lab2

main.o: main.cpp
	g++ -c main.cpp

matrixtl.o: matrixtl.cpp
	g++ -c matrixtl.cpp

matrixccs.o: matrixccs.cpp
	g++ -c matrixccs.cpp

clean:
	rm -rf *.o
