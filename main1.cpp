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


    if(argc>1){
        int portNum; TCPServerSocket *server; GarbageCollector *garbageCollector;
    
        portNum= atoi(argv[1]);
        server= new TCPServerSocket(NULL, portNum, 5);
        garbageCollector= new GarbageCollector();

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
    }
    else{
        cout<<"enter file name"<<endl;
        string fileName; cin>>fileName;
        serverMIS* newServermis= new serverMIS(fileName);
        cout<<"localstart:"<<endl;
        newServermis->localStart();
        cout<<"end localstart"<<endl;
    }

    return 0;
}
