all: hw4 testpoint

rebuild: clean all

hw4: hw4.o world.o civilian.o patrol.o suspect.o people.o point.o cab.o
	g++ hw4.o world.o civilian.o patrol.o suspect.o people.o point.o cab.o -o hw4

hw4.o: hw4.cpp
	g++ hw4.cpp -c -o hw4.o

world.o: world.cpp civilian.o patrol.o suspect.o cab.o
	g++ world.cpp -c -o world.o

civilian.o: civilian.cpp people.o
	g++ civilian.cpp -c -o civilian.o

patrol.o: patrol.cpp people.o
	g++ patrol.cpp -c -o patrol.o

cab.o: cab.cpp people.o suspect.o
	g++ cab.cpp -c -o cab.o

suspect.o: suspect.cpp people.o
	g++ suspect.cpp -c -o suspect.o

people.o: people.cpp point.o
	g++ people.cpp -c -o people.o

testpoint: testpoint.cpp point.o
	g++ testpoint.cpp point.o -o testpoint

point.o: point.cpp
	g++ point.cpp -c -o point.o

clean:
	rm -f testpoint hw4 *.o

