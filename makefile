CC = g++
OBJECTS = main.o objectprogram.o

led: main.o
	${CC} ${OBJECTS} -o led -std=c++11
main.o: main.cpp
	${CC} -c main.cpp
objectprogram.o: objectprogram.cpp
	${CC} -c objectprogram.cpp
run: 
	./led
clean:
	rm *.o
	rm led
