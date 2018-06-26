#include "Connection.h"
#include "common.h"
#include "MIS.h"
//Constructor: Call parent Thread Constructor
Connection::Connection(serverMIS * _servermis): Thread()
{
   // tcpSocket = p_tcpSocket; 
	servermis= _servermis;// Set the servermis
    next_connection = NULL; // Set the next pointer to NULL
}

void* Connection::threadMainBody (void* arg)
{


}
// A modifier that sets the pointer of the next connection
void Connection::setNextConnection(Connection * connection){next_connection = connection;}
// A Selectot that returned a pointer to the next connection
Connection * Connection::getNextConnection (){return next_connection;}
// Destructor: delete the TCP socket if set
Connection::~Connection(){
//if ( tcpSocket != NULL ) delete (tcpSocket);
}
