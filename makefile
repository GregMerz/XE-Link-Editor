CC = g++
OBJECTS = main.o

led: main.o
	${CC} -g objectprogram.h objectprogram.cpp estab.h estab.cpp info.h info.cpp ${OBJECTS} -o led -std=c++11
main.o: main.cpp
	${CC} -c main.cpp
run: 
	./led
clean:
	rm *.o
	rm led
