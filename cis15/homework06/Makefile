all: hw6

rebuild: clean all

hw6: hw6.o mystring.o
	g++ hw6.o mystring.o -o hw6

hw6.o: hw6.cpp
	g++ hw6.cpp -c -o hw6.o

mystring.o: mystring.cpp
	g++ mystring.cpp -c -o mystring.o

clean:
	rm -f hw6 *.o
