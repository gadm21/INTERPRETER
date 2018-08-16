#include "Reader.h"
#include "Instruction.h"
#include "common.h"
#include "TCPServerSocket.h"
#include "TCPSocket.h"

typedef int (*ScriptFunction)(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);
typedef map<string, ScriptFunction> funcMap;

//Reader constructor takes the file name as a parameter but doesn't initialize
// it until the user calls compareandExtract() function.
Reader::Reader(string name):fileName(name){
}
Reader::Reader(){
}
Reader::~Reader(){
}

serverReader::serverReader(string _fileName){
	fileName= _fileName;
}
serverReader::serverReader(TCPSocket* slave){
	slave1= slave;
}
serverReader::~serverReader(){
	delete slave1;
}

//a function that takes a string as a parameter and checks if it can be converted to a long
bool Reader::isLong(string s){
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

//a function that takes a reference to a string as a parameter and
// erase the first and last digit of that string
string Reader::removeQoutes(string &text){
	text.erase(0,1);
	text.erase(text.end()-1);
        return text;
}

//a function that takes a stirng and a reference to double and checks
//if the string can be converted to a double it will convert it and
//saves the double vlaue in the passed parameter and returns a bool
//declaring whether the process succeded or not.
bool Reader::isDouble(string s, double &d){
	istringstream str(s);
	//return true if you can convert to double
	if(str >> d) return true;
	else return false;
}

//a function that takes a string vector and reestablish the full string from it
//then reseparate the full string again but this time separating every substring
//with commas in the full string.
vector<string>& Reader::toCommaTokens(vector<string>& tokens){
	string full, full2;
	auto it=tokens.begin();
	// go right to the second element, because the first was already processed.
	it++;
	//reestablish the full string
	for(it; it!=tokens.end(); it++) full=full+(*it);

	//make a new string vector to hold the new string segments
	vector<string> *parameters=new vector<string>();
	//separate the new string according to the commas in it
	for(int i=0; i<full.length(); i++){
		if(full[i]!=',') full2+=full[i];
		else{
			parameters->push_back(full2);
			full2="";
		}
	}
	if(full2!="") parameters->push_back(full2);
	return *parameters;
}

//a function that takes a string and separates it according to spaces in that text
vector<string>& Reader::toTokens(string longstring){
	string temp;
	//initialze a new string vector to hold the elements of substring
	vector<string> *tokens= new vector<string>();
	bool flag= false;

	//find spaces and pushing elements to the vector
	for(int i=0; i<longstring.length(); i++){
		if(longstring[i]!=' '){
			if(longstring[i]!='\"') temp+= longstring[i];
			else{
				if(flag){
					flag=false;
					temp+= longstring[i];
					tokens->push_back(temp);
					temp="";
				}
				else{
					flag= true;
					if(temp!= "") tokens->push_back(temp);
					temp="\"";
				}
			}
		}
		else{
			if(flag) temp+= longstring[i];
			else{
				if(temp!= "")tokens->push_back(temp);
				temp= "";
			}
		}
	}
	if(temp!="") tokens->push_back(temp);
	return *tokens;
}

string Reader::clean(string &input){
	int i=0;
	while(i<input.length()){
		if(input[i]=='\r'||input[i]=='\t')
			input= input.substr(0, i)+ input.substr(i+1);
		else i++;
	}
	return input;
}

vector<string> serverReader::Read(){
	vector<string> inputVector;
	ifstream input;  input.open(fileName.c_str());
	string line="";
	bool accept=true;
	while(!input.eof()){
		getline(input, line);
		line= clean(line);
		if(line.empty()) continue;
		inputVector.push_back(line);
	}
	input.close();
	return inputVector;

}

string Reader::Parse(vector<string> input, map<string, ScriptFunction> myMap, vector<expression*> &instrVector, vector<expression*> &varVector){
	string errorsContainer="";
	bool accept= true;
	for(int i=0; i<input.size(); i++){
		string line= input[i];
		while(line[line.length()-1]=='\r' || line[line.length()-1]=='\0') line=line.substr(0, line.length()-1);
		while(line[0]==' ' || line[0]=='\t') line= line.substr(1, line.length());
		auto tokens= toTokens(line);
		string error="";
		auto it= myMap.find(tokens.front());
		if(it!= myMap.end()) (*it->second)(tokens, instrVector, varVector, error, accept);
		else accept= false;
		if(!error.empty())errorsContainer+= error+='\n';
	}
	return errorsContainer;
}

void serverReader::printErrors(string &errorContainer){
	ofstream errorFile; errorFile.open("error.err");
	errorFile<< errorContainer;
	errorFile.close();
}
//a function that takes an initialized map and an empty vector of expressions
//inside the function the input file is opened and lines are read and compared with pairs
//in the map. if the line syntax is right, a new expression is pushed to the vector
vector<string> serverReader::Receive(){

	string errorsContainer="";

	stringstream inputContainer;
	char buffer[1024];
	memset(buffer, 0, 1024);

    slave1->readFromSocket(buffer, 10);	//get the size of the file from the client
    string ss(buffer, 10);
    double siz= atof(ss.c_str());
    siz= ceil(siz/1024); //because number of reads will be filesize/ buffersize
    //stringstream str;
	string data="";
    for(int i=0; i< siz; i++){ //read from client and store in buffer
        memset(buffer, 0, 1024);
		string s="";
        slave1->readFromSocket(buffer, 1024);
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
       // string s(buffer, 1024);
		data+= s;
    }
	vector<string> input= rawDataToVector(data);
	return input;
   
}

void serverReader::sendErrors(string &errorContainer){
	int siz= errorContainer.length();
	char buffer[1025];
    memset(buffer, 0, 1024);
    string s= to_string(siz);	//send the size
    slave1->writeToSocket(s.c_str(), 10);


	if(siz< 2) return ; //leave if there're no errors 
	
	

    int currentindex= 0;
    while(currentindex< siz){

        int i=0;
       for(; i< 1024 && currentindex< siz; i++, currentindex++) buffer[i]= errorContainer[currentindex];
        for(; i<1024; i++) buffer[i]= '\\';
        slave1->writeToSocket(buffer, 1024);
	memset(buffer, 0, 1024);
	}
}


vector<string> serverReader::rawDataToVector(string &s){
	vector<string> inputVec;
	string line="";
	for(int i=0; i<s.length(); i++){
		if(s[i]!='\n') line+= s[i];
		else{
			inputVec.push_back(line);
			line="";
		}
	}
	for(int i=0; i<inputVec.size(); i++) cout<<inputVec[i]<<endl;
	return inputVec;
}







