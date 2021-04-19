<<<<<<< HEAD
CC = g++
OBJECTS = main.o

led: main.o
	${CC} -g objectprogram.h objectprogram.cpp estab.h estab.cpp info.h info.cpp ${OBJECTS} -o led -std=c++11
main.o: main.cpp
	${CC} -c main.cpp
=======
OBJECTS = main.o estab.o info.o objectprogram.o
led: $(OJBECTS)
	g++ $(OBJECTS) -o led
estab.o main.o: estab.h
info.o main.o: info.h
objectprogram.o main.o: objectprogram.h
>>>>>>> 7552d567332b73a6261e8810f4485ffe9e8b7a1c
run: 
	./led
clean:
	rm *.o
	rm led
