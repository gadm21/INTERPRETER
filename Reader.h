
#ifndef READER_H
#define READER_H

#include "common.h"
class TCPSocket;
class expression;

typedef int (*ScriptFunction)(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);
typedef map<string, ScriptFunction> funcMap;

class Reader{
	protected:
		
		//a string to hold the file name
		string fileName;
		
	public:
		//a constructor to inistantaite the filename
		Reader(string s);
		Reader();

		//a function that takes a reference to a string as a parameter and 
		// erase the first and last digit of that string 
		static string removeQoutes(string &text);
		//a function that takes a string and separates it according to spaces in that text
		static vector<string>& toTokens(string longstring);
		//a function that takes a string as a parameter and checks if it can be converted to a long
		static bool isLong(string str);
		//a function that takes a stirng and a reference to double and checks
		//if the string can be converted to a double it will convert it and 
		//saves the double vlaue in the passed parameter and returns a bool 
		//declaring whether the process succeded or not.
		static bool isDouble(string str, double &d);
		
		vector<string> rawDataToVector(string &s);
		//a function that takes a string vector and reestablish the full string from it
		//then reseparate the full string again but this time separating every substring 
		//with commas in the full string.
		static vector<string>& toCommaTokens(vector<string>& tokens);

		string Parse(vector<string> input, map<string, ScriptFunction> myMap, vector<expression*> &instrVector, vector<expression*> &varVector);
		string clean(string &input);
		~Reader();
};


class serverReader: public Reader{
	private:
		TCPSocket* slave1;
		string fileName;
	public:
	serverReader(string _fileName);
	serverReader(TCPSocket* slave1);
	//a function that takes an initialized map and an empty vector of expressions 
	//inside the function the input file is opened and lines are read and compared with pairs 
	//in the map. if the line syntax is right, a new expression is pushed to the vector
	vector<string> Receive();
	vector<string> rawDataToVector(string &s);
	vector<string> Read();
	void sendErrors(string &errorContainer);
	void printErrors(string &errorContainer);
	~serverReader(); //remove the server
};



#endif /* READER_H */


