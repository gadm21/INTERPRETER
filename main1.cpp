#include "common.h"
#include "Instruction.h"
#include "Reader.h"
#include "MIS.h"
#include "TCPServerSocket.h"
#include "TCPSocket.h"
#include "GarbageCollector.h"
#include "Connection.h"
#include "Thread.h"

void* thread_callback( void* servermis){
   ((serverMIS*)servermis)->interpret();
}

int main(int argc, char* argv[]) {

    int portNum= atoi(argv[1]);
    TCPServerSocket *server= new TCPServerSocket(NULL, portNum, 5);
    GarbageCollector *garbageCollector= new GarbageCollector();

    server->initializeSocket();
	//initialize a MIS object and give it the string given by the command line as an input

    while(true){
        cout<<"waiting for connections "<<endl;
	TCPSocket* slave= server->getConnection();
	serverMIS* servermis= new serverMIS(slave);
        cout<<"got a connection"<<endl;
	garbageCollector->cleanup();
	Connection *c= new Connection(servermis);
	c->start();
	garbageCollector->addConnection(c);
    }
	delete(garbageCollector);
	delete(server);

    return 0;
}
