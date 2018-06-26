# Project: Interpreter
# Makefile created by Dev-C++ 5.11

GCC      = g++
GCC_FLAGS= -std=c++11 -pthread
DEBUG	 = -c -g
SOURCES  = sources
OBJECTS  = objects
INCLUDES = -I headers
BIN      = bin


server: Reader.o MIS.o Instruction.o serverMIS.o TCPServerSocket.o TCPSocket.o main1.o GarbageCollector.o Thread.o Connection.o
	g++ $(GCC_FLAGS) -g Reader.o MIS.o Instruction.o serverMIS.o TCPServerSocket.o TCPSocket.o main1.o GarbageCollector.o Thread.o Connection.o -o server

client: Reader.o MIS.o clientMIS.o clientReader.o TCPServerSocket.o TCPSocket.o main2.o 
	g++ $(GCC_FLAGS) -g Reader.o MIS.o clientMIS.o clientReader.o TCPServerSocket.o TCPSocket.o main2.o -o client



Reader.o: Reader.cpp
	g++ $(GCC_FLAGS) -c -g Reader.cpp -o Reader.o

clientReader.o: clientReader.cpp
	g++ $(GCC_FLAGS) -c -g clientReader.cpp -o clientReader.o
TCPServerSocket.o: TCPServerSocket.cpp
	g++ $(GCC_FLAGS) -c -g TCPServerSocket.cpp -o TCPServerSocket.o

TCPSocket.o: TCPServerSocket.cpp
	g++ $(GCC_FLAGS) -c -g TCPSocket.cpp -o TCPSocket.o

GarbageCollector.o: GarbageCollector.cpp
	g++ $(GCC_FLAGS) -c -g GarbageCollector.cpp -o GarbageCollector.o

Connection.o: Connection.cpp
	g++ $(GCC_FLAGS) -c -g Connection.cpp -o Connection.o

Thread.o: Thread.cpp
	g++ $(GCC_FLAGS) -c -g Thread.cpp -o Thread.o

MIS.o: MIS.cpp
	g++ $(GCC_FLAGS) -c -g MIS.cpp -o MIS.o

Instruction.o: Instruction.cpp
	g++ $(GCC_FLAGS) -c -g Instruction.cpp -o Instruction.o

serverMIS.o: serverMIS.cpp
	g++ $(GCC_FLAGS) -c -g serverMIS.cpp -o serverMIS.o

clientMIS.o: clientMIS.cpp
	g++ $(GCC_FLAGS) -c -g clientMIS.cpp -o clientMIS.o

main1.o: main1.cpp
	g++ $(GCC_FLAGS) -c -g main1.cpp -o main1.o

main2.o: main2.cpp
	g++ $(GCC_FLAGS) -c -g main2.cpp -o main2.o

clean:
	rm -rf *.o *.exe
	rm -rf *.
