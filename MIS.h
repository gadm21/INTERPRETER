

#ifndef MIS_H
#define MIS_H


#include "common.h"
class Reader;
class expression;
class clientReader;
class serverReader;
class TCPSocket;

typedef int (*ScriptFunction)(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);
typedef map<string, ScriptFunction> funcMap;

class MIS{
protected:
	//a string to save the filename
    string filename;
public:
	//a constructor that takes the ifle name as input
    MIS(string f);
    MIS();

    
    ~MIS();
    
};


class serverMIS: public MIS{
	private:
		serverReader *reader;
		TCPSocket* slave1;
	public:
		serverMIS( TCPSocket* slave);
    	// a function to insert known pairs iside the map
    	map<string, ScriptFunction>& initializeMap();
		//a vector of expression pointers to hold a list of instructions from the input file
   		vector<expression*> instrVector;
    	//a vector of expression pointers to hold a list of variables 
    	vector<expression*> varVector;
    	//a vector of map to hold keys and their corresponding expression class
    		funcMap myMap ;
		//a function that calls the compareandExtract function of Reader and then calls the execute()
   		int interpret();
  		//loops through all expressions in the vector and calls the execute() function for each and every exprssion
  		void execute();
		~ serverMIS();
};

#endif /* MIS_H */


