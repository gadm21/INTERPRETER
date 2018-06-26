
#ifndef CLIENTREADER_H
#define CLIENTREADER_H


#include "common.h"
class TCPSocket;

class clientReader{
	private:
	string file_name;
	TCPSocket *client;
	string line;
	public:
	clientReader(string f, TCPSocket* _client);
	//read a file and send it
	int readandSend();
	void recieveError();
	void recieveOutput();
	void Run();
	~clientReader();//remove the client 
};


#endif /* CLIENTREADER_H */


