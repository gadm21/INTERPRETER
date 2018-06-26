#include "Reader.h"
#include "Instruction.h"
#include "common.h"
#include "clientMIS.h"
#include "clientReader.h"
#include "TCPServerSocket.h"
#include "TCPSocket.h"
//Reader constructor takes the file name as a parameter but doesn't initialize
// it until the user calls compareandExtract() function.
clientReader::clientReader(string f, TCPSocket* _client): file_name(f){
	client = _client;

}


int clientReader::readandSend(){
	ifstream input;
	input.open(file_name.c_str());
	//sleep(2);
    char buffer[1024];
    memset(buffer, 0, 1024);
	string line="";
	string stream="";
	    while(getline(input, line)){
	    line+= "\n";
	    if(line.length()<3) continue;
		stream+= line;
		}
        double siz= stream.length();
        string s= to_string(siz);	//send the size
        client->writeToSocket(s.c_str(), 10);

    int currentindex= 0;
    while(currentindex< siz){

        int i=0;
       for(; i< 1024 && currentindex< siz; i++, currentindex++) buffer[i]= stream[currentindex];
        for(; i<1024; i++) buffer[i]= '\\';
        client->writeToSocket(buffer, 1024);
	memset(buffer, 0, 1024);
    }
         input.close();

	string errors="";

   client->readFromSocket(buffer, 10);	//get the size of the file from the client
    string st(buffer, 10);
    siz= atof(st.c_str());
    siz= ceil(siz/1024); //because number of reads will be filesize/ buffersize

   for(int i=0; i< siz; i++){ //read from client and store in buffer
        memset(buffer, 0, 1024);
	string s="";
        client->readFromSocket(buffer, 1024);
	for(int i=0; i<1024; i++){
		 if(buffer[i]!='\\') s+= buffer[i];
		 else if((i+1)<1024){
			if(buffer[i+1]!='\\') s+= buffer[i];
			else if((i+2)< 1024){
				if(buffer[i+2]!='\\') s+= buffer[i];
				else break;
			}
		}
	}
	errors+= s;
    }




	string outputs="";
   client->readFromSocket(buffer, 10);	//get the size of the file from the client
    string stt(buffer, 10);
    siz= atof(stt.c_str());
    siz= ceil(siz/1024); //because number of reads will be filesize/ buffersize

      for(int i=0; i< siz; i++){ //read from client and store in buffer
        memset(buffer, 0, 1024);
        client->readFromSocket(buffer, 1024);
	string s="";
	for(int i=0; i<1024; i++){
		 if(buffer[i]!='\\') s+= buffer[i];
		 else if((i+1)<1024){
			if(buffer[i+1]!='\\') s+= buffer[i];
			else if((i+2)< 1024){
				if(buffer[i+2]!='\\') s+= buffer[i];
				else break;
			}
		}
	}
	outputs+= s;
    }

  ofstream error;
   error.open("error.err");
	error<< errors;
    error.close();

	ofstream output;
	output.open("output.out");
	output<< outputs;
    output.close();
}

void clientReader::recieveError(){

}

void clientReader::recieveOutput(){

}

void clientReader::Run(){
	readandSend();
	//clientReader::recieveError();
	//clientReader::recieveOutput();

}

clientReader::~clientReader(){
}
