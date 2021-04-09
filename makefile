CC = g++
OBJECTS = main.o

led: ${OBJECTS}
	${CC} ${OBJECTS} -o led
run: 
	./led
clean:
	rm *.o
