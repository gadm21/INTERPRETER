
#ifndef CLIENT_MIS
#define CLIENT_MIS

#include "common.h"

class Reader;
class expression;
class clientReader;
class TCPSocket;

class clientMIS{
protected:
	//a string to save the filename
    string filename;
	clientReader* reader;
public:
	//a constructor that takes the ifle name as input
    clientMIS(string f, TCPSocket &client);
	void Run();
    
    ~clientMIS();
    
};


#endif
