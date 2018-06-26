#include "MIS.h"
#include "Reader.h"
#include "common.h"
#include "includes.h"
#include "Instruction.h"
#include "TCPServerSocket.h"
#include "TCPSocket.h"

typedef int (*ScriptFunction)(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);
typedef map<string, ScriptFunction> funcMap;

serverMIS::serverMIS( TCPSocket *slv){
	slave1= slv;
	reader= new serverReader(slv);
	myMap= initializeMap();
}
serverMIS::~serverMIS(){
	delete reader;
}

//the instructions defined in this interpreter are all inserted in the map
map<string, ScriptFunction>& serverMIS::initializeMap(){
    funcMap *myMap= new funcMap();

	//inserting pairs in the map. pairs are: the first word in a line
	// and an object used to call the validate function of its type to return a new type or a nullptr
	//if the syntax of the line is wrong.
	myMap->insert(pair<string, ScriptFunction> ("VAR", &VAR::valid ));
	myMap->insert(pair<string, ScriptFunction> ("MUL", &MUL::valid ));
	myMap->insert(pair<string, ScriptFunction> ("ADD", &ADD::valid ));
	myMap->insert(pair<string, ScriptFunction> ("SUB", &SUB::valid ));
	myMap->insert(pair<string, ScriptFunction> ("DIV", &DIV::valid ));
	myMap->insert(pair<string, ScriptFunction> ("ASSIGN", &ASSIGN::valid ));
	myMap->insert(pair<string, ScriptFunction> ("SET_STR_CHAR", &SET_STR_CHAR::valid ));
	myMap->insert(pair<string, ScriptFunction> ("GET_STR_CHAR", &GET_STR_CHAR::valid ));
	myMap->insert(pair<string, ScriptFunction> ("OUT", &OUT::valid ));
	myMap->insert(pair<string, ScriptFunction> ("LABEL", &LABEL::valid ));
	myMap->insert(pair<string, ScriptFunction> ("JMP", &JMP::valid ));
	myMap->insert(pair<string, ScriptFunction> ("SLEEP", &SLEEP::valid ));
	myMap->insert(pair<string, ScriptFunction> ("JMPZ", &JMPZ::valid ));
	myMap->insert(pair<string, ScriptFunction> ("JMPNZ", &JMPNZ::valid ));
	myMap->insert(pair<string, ScriptFunction> ("JMPGT", &JMPGT::valid ));
	myMap->insert(pair<string, ScriptFunction> ("JMPGTE", &JMPGTE::valid ));
	myMap->insert(pair<string, ScriptFunction> ("JMPLT", &JMPLT::valid));
	myMap->insert(pair<string, ScriptFunction> ("JMPLTE", &JMPLTE::valid ));
	myMap->insert(pair<string, ScriptFunction> ("THREAD_BEGIN", &THREAD_BEGIN::valid ));
	myMap->insert(pair<string, ScriptFunction> ("THREAD_END", &THREAD_END::valid ));
	myMap->insert(pair<string, ScriptFunction> ("THREAD", &THREAD::valid ));
	myMap->insert(pair<string, ScriptFunction> ("BARRIER", &BARRIER::valid ));
	myMap->insert(pair<string, ScriptFunction> ("SETAFFINITY", &SETAFFINITY::valid ));
	myMap->insert(pair<string, ScriptFunction> ("LOCK", &LOCK::valid ));
	myMap->insert(pair<string, ScriptFunction> ("UNLOCK", &UNLOCK::valid ));
	//returning the map after filling it with pairs
	return *myMap;
}


int serverMIS::interpret(){

    //calling the Reader's recieveandExtract function that takes the map
    // with which the input file lines are compared, and an empty vector to fill it with expressions
    if(reader!= nullptr) reader->recieveandExtract(myMap, instrVector, varVector);

   // calling the MIS's execute() function which in return calls the execute() function
    //of every expression in the exprVector vector


    execute();
	cout<<"ending"<<endl;
    return 1;
}

void serverMIS::execute(){
	//  holding the index of expression being executed right now.
	string outputs;
	outputs="";
    	int i=0;
  	  while(i!=instrVector.size()){
    	//calling every element's execute() function
    	int x=instrVector[i]->execute(instrVector, varVector, outputs);
	if(x==0) break;
    	//add the returned offset from function execute() to the current index.
    	i+=x;
	}
	for(auto it= instrVector.begin(); it!=instrVector.end(); it++) delete (*it);
	for(auto it= varVector.begin(); it!=varVector.end(); it++) delete (*it);

   	 string output= outputs;
	

   	 char buffer[1024];
	memset(buffer, 0, 1024);
	double siz= output.length();
	string s= to_string(siz);
	slave1->writeToSocket(s.c_str(), 10);


        if(siz< 2) return ;

    int currentindex= 0;
    while(currentindex< siz){

        int i=0;
       for(; i< 1024 && currentindex< siz; i++, currentindex++) buffer[i]= output[currentindex];
        for(; i<1024; i++) buffer[i]= '\\';
        slave1->writeToSocket(buffer, 1024);
	memset(buffer, 0, 1024);
    }

} 
