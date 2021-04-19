OBJECTS = main.o estab.o info.o objectprogram.o
led: $(OJBECTS)
	g++ $(OBJECTS) -o led
estab.o main.o: estab.h
info.o main.o: info.h
objectprogram.o main.o: objectprogram.h
run: 
	./led
clean:
	rm *.o
	rm led
