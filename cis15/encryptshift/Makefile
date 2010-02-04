all: encrypt_caesar

encrypt_caesar: encrypt.cpp Encryption.o Message.o Caesar.o fileHandleChar.o fileHandleString.o
	g++ encrypt.cpp Encryption.o Message.o Caesar.o fileHandleChar.o fileHandleString.o -o encrypt_caesar

Encryption.o: Encryption.cpp 
	g++ Encryption.cpp -c -o Encryption.o

Message.o: Message.cpp
	g++ Message.cpp -c -o Message.o

Caesar.o: Caesar.cpp
	g++ Caesar.cpp -c -o Caesar.o

fileHandleChar.o: fileHandleChar.cpp
	g++ fileHandleChar.cpp -c -o fileHandleChar.o

fileHandleString.o: fileHandleString.cpp
	g++ fileHandleString.cpp -c -o fileHandleString.o

clean:
	rm encrypt_caesar *.o

