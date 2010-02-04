all: hw3 testpoint testpatrol testsuspect testworld testcab testcivilian

rebuild: clean all

hw3: hw3.o world.o patrol.o suspect.o people.o point.o cab.o civilian.o
	g++ hw3.o world.o patrol.o suspect.o people.o point.o cab.o civilian.o -o hw3

hw3.o: hw3.cpp
	g++ hw3.cpp -c -o hw3.o

testworld: testworld.cpp world.o patrol.o suspect.o people.o point.o cab.o civilian.o
	g++ testworld.cpp world.o patrol.o suspect.o point.o people.o cab.o civilian.o -o testworld

world.o: world.cpp patrol.o suspect.o cab.o civilian.o
	g++ world.cpp -c -o world.o

testcivilian: testcivilian.cpp civilian.o point.o people.o
	g++ testcivilian.cpp civilian.o point.o people.o -o testcivilian

civilian.o: civilian.cpp people.o
	g++ civilian.cpp -c -o civilian.o

testcab: testcab.cpp cab.o point.o people.o
	g++ testcab.cpp cab.o point.o people.o -o testcab

cab.o: cab.cpp people.o
	g++ cab.cpp -c -o cab.o

testpatrol: testpatrol.cpp patrol.o point.o people.o
	g++ testpatrol.cpp patrol.o point.o people.o -o testpatrol

patrol.o: patrol.cpp people.o
	g++ patrol.cpp -c -o patrol.o

testsuspect: testsuspect.cpp suspect.o point.o people.o
	g++ testsuspect.cpp suspect.o point.o people.o -o testsuspect

suspect.o: suspect.cpp people.o
	g++ suspect.cpp -c -o suspect.o

people.o: people.cpp point.o
	g++ people.cpp -c -o people.o

testpoint: testpoint.cpp point.o
	g++ testpoint.cpp point.o -o testpoint

point.o: point.cpp
	g++ point.cpp -c -o point.o

clean:
	rm -f testpoint testpatrol testsuspect testworld testcivilian testcab hw3 *.o

