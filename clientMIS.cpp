
#include "MIS.h"
#include "Reader.h"
#include "TCPServerSocket.h"
#include "TCPSocket.h"
#include "common.h"
#include "includes.h"
#include "clientMIS.h"

#include "clientReader.h"
clientMIS::clientMIS(string f, TCPSocket &client):filename(f){

	reader= new clientReader(f, &client );
}

clientMIS::~clientMIS(){
	delete reader;
}

void clientMIS::Run(){
	reader->Run();
}
