CC = g++
OBJECTS = main.o

led: main.o
	${CC} ${OBJECTS} -o led
main.o: main.cpp
	${CC} -c main.cpp
run: 
	./led
clean:
	rm *.o
	rm led
