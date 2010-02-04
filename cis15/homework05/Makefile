all: hw5a hw5b hw5c hw5d

rebuild: clean all

hw5a: hw5a.o point.o
	g++ hw5a.o point.o -o hw5a

hw5a.o: hw5a.cpp
	g++ hw5a.cpp -c -o hw5a.o

hw5b: hw5b.o point.o
	g++ hw5b.o point.o -o hw5b

hw5b.o: hw5b.cpp
	g++ hw5b.cpp -c -o hw5b.o

hw5c: hw5c.o point.o
	g++ hw5c.o point.o -o hw5c

hw5c.o: hw5c.cpp
	g++ hw5c.cpp -c -o hw5c.o

hw5d: hw5d.o point.o
	g++ hw5d.o point.o -o hw5d

hw5d.o: hw5d.cpp
	g++ hw5d.cpp -c -o hw5d.o


point.o: point.cpp
	g++ point.cpp -c -o point.o
clean:
	rm -f hw5a hw5b hw5c hw5d *.o
