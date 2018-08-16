#include "Instruction.h"
#include "Reader.h"


//expression class constructor. Every and each class inhereting from experssion must pass a label to this constructor
expression::expression(int l){
	label=l;
}
expression::~expression(){
}


int expression::getlabel(){
	return label;
}

//get name functions for variables that has a name for the value they hold
string VAR::getname(){
	return name;
}
//label is a special case for a class that needs the name variable to store the name of the label
string LABEL::getname(){
	return name;
}

//JMP also has a name variable refering to the name of some label
string JMP::getname(){
	return name;
}

//classes that inheret from JMP have two values that will be compared
//and based on the output of the comparison the instruction will be executed or not
string JMPGT::getfirst(){
	return first;
}
string JMPGT::getsecond(){
	return second;
}

//constructors of all classes. note that every and each class must pass the label number to the expression constructor
VAR::VAR(int l, string n): expression(l){
	name=n;
	pthread_mutex_init(&lock, NULL);
    pthread_mutex_init(&explicitlock, NULL);
}
SETAFFINITY::SETAFFINITY(int l, int _cpuid): expression(l){cpuid= _cpuid;}

VAR::~VAR(){
    pthread_mutex_destroy(&lock);
    pthread_mutex_destroy(&explicitlock);
}
void VAR::locking(){
    pthread_mutex_lock(&explicitlock);
}
void VAR::unlocking(){
    pthread_mutex_unlock(&explicitlock);
}
CHAR::CHAR(int l, string n, char v): VAR(l, n){
	value=v;
}
JMPZ::JMPZ(int l, string n, string v):JMP(l, n){
	value=v;
}
JMPNZ::JMPNZ(int l, string n, string v):JMP(l, n){
	name=n;
	value=v;
}
JMPGT::JMPGT(string f, string s, int l, string n):JMP(l, n){
	first=f;
	second=s;
}
JMPGTE::JMPGTE(string f, string s, int l, string n):JMPGT(f,s,l, n){
}
JMPLT::JMPLT(string f, string s, int l, string n):JMPGT(f,s,l, n){
}
JMPLTE::JMPLTE(string f, string s, int l, string n):JMPGT(f,s,l, n){
}
STRING::STRING(int l, string n, string v):VAR(l, n){
	value=v;
}
NUMERIC::NUMERIC(int l, string n, long v):VAR(l, n){
	value=v;
}

REAL::REAL(int l, string n, double v):VAR(l, n){
	value=v;
}
ADD::ADD(int l, vector<string> myp):expression(l){
	myparameters=myp;

}
MUL::MUL(int l, vector<string> myp):expression(l){
	myparameters=myp;
}
SUB::SUB(int l, vector<string> myp):expression(l){
	myparameters=myp;
}
DIV::DIV(int l, vector<string> myp):expression(l){
	myparameters=myp;
}
OUT::OUT(int l, vector<string> myp):expression(l){
	myparameters=myp;
	pthread_mutex_init(&lock, NULL);
}
OUT::~OUT(){    pthread_mutex_destroy(&lock);}
ASSIGN::ASSIGN(int l, vector<string> myp):expression(l){
	myparameters=myp;
}
SET_STR_CHAR::SET_STR_CHAR(int l, vector<string> myp):expression(l){
	myparameters=myp;
}
GET_STR_CHAR::GET_STR_CHAR(int l, vector<string> myp):expression(l){
	myparameters=myp;
}
LABEL::LABEL(int l, string n):expression(l){
	name=n;
}
JMP::JMP(int l, string n):expression(l){
	name=n;
}
SLEEP::SLEEP(int l, long v):expression(l){
	value=v;
}
THREAD::THREAD(int l): expression(l){
}
BARRIER::BARRIER(int l): expression(l){}
LOCK::LOCK(int l, string _name): expression(l){name= _name;}
UNLOCK::UNLOCK(int l, string _name): expression(l){name= _name;}

int THREAD::threadFlag= 0;

THREAD_BEGIN::THREAD_BEGIN(int l): THREAD(l){
}
THREAD_END::THREAD_END(int l, vector<expression*> _myinstrVector): THREAD(l){ myinstrVector= _myinstrVector;}
THREAD_END::~THREAD_END(){for(auto it= myinstrVector.begin(); it!= myinstrVector.end(); it++) delete (*it);}
//four setvalue() functions for the four different class types representing different variable types
void REAL::setvalue(double v){
	pthread_mutex_lock(&lock);
	 value= v;
	pthread_mutex_unlock(&lock);
}
void STRING::setvalue(string v){
	pthread_mutex_lock(&lock);
	 value= v;
	pthread_mutex_unlock(&lock);
}
void CHAR::setvalue(char v){
	pthread_mutex_lock(&lock);
	 value= v;
	pthread_mutex_unlock(&lock);
}
void NUMERIC::setvalue(long v){
	pthread_mutex_lock(&lock);
	 value= v;
	pthread_mutex_unlock(&lock);
}

//getter functions for the MIS variable classes
double REAL::getvalue(){
	return value;
}
string STRING::getvalue(){
	return value;
}
char CHAR::getvalue(){
	return value;
}
long NUMERIC::getvalue(){
	return value;
}

//get the value of sleep time
long SLEEP::getvalue(){
	return value;
}

//get the value of the variable JMPZ and JMPNZ will check
string JMPZ::getvalue(){
	return value;
}
string JMPNZ::getvalue(){
	return value;
}

//valid() functions
//...
//these functions take a string cutted according to spaces of the line read from the input file
// and a vector of expressions that are interpreted until now
// and will return a pointer to the same type of object from which the function was called from
// if the line syntax is right, or will return nullptr if the line syntax is wrong

//note that NUMERIC, CHAR, STRING, and REAL vaild() functions are never called because the key
//that is used to search in the map for a matching is the first word in the line before the first space.
//since all these variables share one line starting keyword (i.e. VAR), it's VAR that checks for the validity
// for all its different types of variables.
int NUMERIC::valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	return 1;
}
int REAL::valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	return 1;
}
int CHAR::valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	return 1;
}
int STRING::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	return 1;
}

//the VAR valid() function that accually checks for the validity of NUMERIC, REAL, STRING, and CHAR classes
int VAR::valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//cout<<"inside var valid"<<endl;
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//delete &tokens;
	double d;

	//for a line defining any VAR type to be right, it must has 3 or 4 parameters separated by commas
	if(parameters.size()<3 || parameters.size()>4){
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for any VAR is 3 or 4";
		accept= false;
		return 0;
	}

	//to define a VAR, the name of any VAR type must start with $ sign
	if(parameters[0][0]!='$'){
		error= "the first parameter in a variable declaration must be the name of that varible thus it must start with \'&\'";
		accept= false;
		return 0;
	}

	//to define a VAR, the name of that VAR must be unique (i.e. you
	//can't define two variables with the same name even if they of different types
	if(VAR::alreadyExist(varVector, parameters[0])){
		error= "parameter: "+ parameters[0]+ " already exists";
		accept= false;
		return 0;
	}
	if(parameters.size()==3){
		//if the second word is CHAR, check that the last word is only 3characters (i.e. single qoutations and a character)
		//also make sure the first character of those three characters equals the last character
		if(parameters[1]=="CHAR") if(parameters[2].length()==3) if(parameters[2][0]== parameters[2][2]){
			 varVector.push_back(new CHAR(Char, parameters[0], parameters[2][1])) ;
			 return 1;
		}else{
            string v="first: ";
            v+= parameters[2][0];
            v+= "  second: ";
            v+= parameters[2][2];

		}
		//if the second word is STRING, make sure the first character of those three characters equals the last character
		 if(parameters[1]=="STRING") if(parameters[2][0]== parameters[2][(parameters[2].length()-1)]){
		 	varVector.push_back(new STRING(String, parameters[0], Reader::removeQoutes(parameters[2])));
		 	return 1;
		 }else{
            string v="first: ";
            v+= parameters[2][0];
            v+= "  second: ";
            v+= parameters[2][(parameters[2].length()-1)];

		}
		 //if the second word is NUMERIC make sure the last word is convertable to number NOTE: although i check here that the last word is a double
		 //when the number is stored in the long variable inside the NUMERIC class its value will be casted to long
		if(parameters[1]=="NUMERIC") if(Reader::isDouble(parameters[2], d)){
			varVector.push_back(new NUMERIC(Numeric, parameters[0], d ));
			return 1;
		}
		if(parameters[1]=="REAL"){
			//the same as NUMERIC
			if(Reader::isDouble(parameters[2], d)){
				varVector.push_back(new REAL(Real, parameters[0], d));
				return 1;
			}
			else {
				error= "to declare a REAL variable, the value passed must be a double";
				accept= false;
				return 0;
			}
		}
	//if the size is not 3, then we check if its 4 $$ it's a STRING. otherwise, return a nullptr because this is a wrong syntax
	}else if(parameters.size()==4){
		if(parameters[1]=="STRING") if(parameters[3][0]== parameters[3][(parameters[3].length()-1)]){
			varVector.push_back(new STRING(String, parameters[0], parameters[3]));
			return 1;
		}else{
				error= "the value of a STRING variable must be put between double qoutations";
				accept= false;
				return 0;
		}

	}
	accept= false;
	return 0;



}

int SETAFFINITY::valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){

	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//delete &tokens;
	int size=0;

	//checks if the paramters aren't empty and the first parameter,that the result of the multiplication process
	//will be stored in is a variable && is registered in the expression vector as NUMERIC
	if(parameters.empty()&& parameters.size()>1){
		error= "SETAFFINITY must have 1 parameter ";
		accept= false;
		return 0;
	}
	if(THREAD::threadFlag==0){
		error= "SETAFFINITY must be called from within a thread body ";
		accept= false;
		return 0;
	}
	double dou=0;
	if(!VAR::checkexpr(varVector, Numeric, parameters[0])){ 

		if(!Reader::isDouble(parameters[0], dou)){
			error= "SETAFFINITY parameter must be either a double or a NUMERIC variable ";
			accept= false;
			return 0;	
		}
	}else dou= expression::getdou(varVector, parameters[0]);

	
	//if you passed all these conditions successfully, return a pointer to ADD class
	if(accept){
		instrVector.push_back(new SETAFFINITY(SetAffinity, dou));
		return 1;
	}else return 1;

	

}
//ADD class valid() function.
int ADD::valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//delete &tokens;
	int size=0;

	//size can't be less than 3 and can't be more than 13 to have right syntax
	if(parameters.size()<3 || parameters.size()>13){
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for ADD must be between 3 and 13";
		accept= false;
		return 0;
	}

	//since the first parameter of an ADD instruction is a variable that the addition operation result will be saved in
	//the first parameter must be a variable that is listed in the expression vector before this valid() function is called
	if(parameters[0][0]!='$'){
		error= "the first parameter in ADD must start with \'&\' to hold the result of the addition process ";
		accept= false;
		return 0;
	}

	size= parameters.size();

	if(!VAR::checkexpr(varVector, Numeric, parameters[0]) && !VAR::checkexpr(varVector, Real, parameters[0])){
		error= "the first parameter in ADD must be either a NUMERIC or a REAL varible already declared before ";
		accept= false;
		return 0;
	}

	for(int i=1;i<size; i++){
		//for all parameters of the ADD instruction to be valid. the parameter must be either a number or a variable already
		//existed in the expression vector && is of type numeric or real
		double dou;
		if(Reader::isDouble(parameters[i], dou)) continue;
		if(parameters[i][0]=='$') if(!VAR::checkexpr(varVector, Numeric, parameters[i]) && !VAR::checkexpr(varVector, Real, parameters[i])){
			error= "the"+ to_string(i)+"th parameter in ADD must be either a NUMERIC or a REAL varible already declared before ";
			accept= false;
			return 0;
		}


	}

	//if you passed all these conditions successfully, return a pointer to ADD class
	if(accept){
		vector<string> *myV= &parameters;
		instrVector.push_back(new ADD(Add, *myV));
		return 1;
	}else return 1;

}

//MUL class valid() function.
int MUL::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//delete &tokens;
	int size=0;

	//checks if the paramters aren't empty and the first parameter,that the result of the multiplication process
	//will be stored in is a variable && is registered in the expression vector as NUMERIC or REAL
	if(parameters.empty()){
		error= "MUL can't be called without parameters ";
		accept= false;
		return 0;
	}
	if(parameters[0][0]!='$'){
		error= "the first parameter in MUL must start with \'&\' to hold the result of the multiplication process ";
		accept= false;
		return 0;
	}
	if(parameters.size()<3 || parameters.size()>13){
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for MUL must be between 3 and 13";
		accept= false;
		return 0;
	}
	size= parameters.size();
	if(!VAR::checkexpr(varVector, Numeric, parameters[0]) && !VAR::checkexpr(varVector, Real, parameters[0])){
		error= "the first parameter in MUL must be either a NUMERIC or a REAL varible already declared before ";
		accept= false;
		return 0;
	}


	for(int i=1;i<size; i++){
		//for all parameters of the ADD instruction to be valid. the parameter must be either a number or a variable already
		//existed in the expression vector && is of type numeric or real
		if(Reader::isLong(parameters[i])) continue;
		if(parameters[i][0]=='$')
			if(!VAR::checkexpr(varVector, Numeric, parameters[i]) && !VAR::checkexpr(varVector, Real, parameters[i])){
				error= "the"+ to_string(i)+"th parameter in ADD must be either a NUMERIC or a REAL varible already declared before ";
				accept= false;
				return 0;
			}

	}
	//if you passed all these conditions successfully, return a pointer to MUL class
	if(accept){
			vector<string> *myV= &parameters;
			instrVector.push_back(new MUL(Mul, *myV));
			return 1;
	}else return 1;

}

//SUB class valid() function.
int SUB::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//delete &tokens;
	//checks the size of parameters is exactly 3 and the first parameter, that the result of subtraction process will be stored in,
	//is a variable registered in the expression vector and it's of type NUMERIC or REAL
	if(parameters.size()!=3){
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for SUB is 3";
		accept= false;
		return 0;
	}
	if( parameters[0][0]!='$'){
		error= "the first parameter in SUB must start with \'&\' to hold the result of the subtraction process ";
		accept= false;
		return 0;
	}

	if(!VAR::checkexpr(varVector, Numeric, parameters[0]) && !VAR::checkexpr(varVector, Real, parameters[0])){
		error= "the first parameter in SUB must be either a NUMERIC or a REAL varible already declared before ";
		accept= false;
		return 0;
	}
	//check that the second and third parameters are either a number or a varible of type NUMERIC or REAL
	if(!Reader::isLong(parameters[1])) if(!VAR::checkexpr(varVector, Numeric, parameters[1]) && !VAR::checkexpr(varVector, Real, parameters[1])){
		error= parameters[1]+" is not a NUMERIC or a REAL variable";
		accept= false;
		return 0;
	}
	if(!Reader::isLong(parameters[2])) if(!VAR::checkexpr(varVector, Numeric, parameters[2]) && !VAR::checkexpr(varVector, Real, parameters[2])){
		error= parameters[2]+" is not a NUMERIC or a REAL variable";
		accept= false;
		return 0;
	}

	//if you passed all these conditions successfully, return a pointer to SUB class
	if(accept){
		vector<string> *myV= &parameters;
		instrVector.push_back(new SUB(Sub, *myV));
		return 1;
	}else return 1;


}

//DIV class valid() function.
int DIV::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//delete &tokens;
	//checks the size of parameters is exactly 3 and the first parameter, that the result of division process will be stored in,
	//is a variable registered in the expression vector and it's of type NUMERIC or REAL
	if(parameters.size()!=3){
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for DIV is 3";
		accept= false;
		return 0;
	}
	if( parameters[0][0]!='$'){
		error= "the first parameter in DIV must start with \'&\' to hold the result of the division process ";
		accept= false;
		return 0;
	}


	if(!VAR::checkexpr(varVector, Numeric, parameters[0]) && !VAR::checkexpr(varVector, Real, parameters[0])){
		error= "the first parameter in DIV must be either a NUMERIC or a REAL varible already declared before ";
		accept= false;
		return 0;
	}
	//check that the second and third parameters are either a number or a varible of type NUMERIC or REAL
	if(!Reader::isLong(parameters[1])) if(!VAR::checkexpr(varVector, Numeric, parameters[1]) && !VAR::checkexpr(varVector, Real, parameters[1])){
		error= parameters[1]+" is not a NUMERIC or a REAL variable";
		accept= false;
		return 0;
	}
	if(!Reader::isLong(parameters[2])) {
		if(!VAR::checkexpr(varVector, Numeric, parameters[2]) && !VAR::checkexpr(varVector, Real, parameters[2])){
			error= parameters[2]+" is not a NUMERIC or a REAL variable";
			accept= false;
			return 0;
		}
		REAL *PTR= (REAL*) (expression::getexpr(varVector, (parameters[2])));
		if(PTR->getvalue()==0){
			//make sure you're not dividing by zero
			error= "can't divide by zero\n";
			accept= false;
			return 0;
		}
	}
	else{
		double d=0;
		Reader::isDouble(parameters[2], d);
		if(d==0){
			//make sure you're not dividing by zero
			error= "can't divide by zero\n";
			accept= false;
			return 0;
		}
	}



	//if you passed all these conditions successfully, return a pointer to DIV class
	if(accept){
		vector<string> *myV= &parameters;
		instrVector.push_back(new DIV(Div, *myV));
		return 1;
	}else return 1;

}
//BARRIER class valid() function.
int BARRIER::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
		vector<string> parameters= Reader::toCommaTokens(tokens);
	//delete &tokens;
        if(!parameters.empty()){
		error="BARRIER has no parameters ";
		accept= false;
		return 0;
    }

	if(accept){
		instrVector.push_back(new BARRIER(Barrier));
		return 1;
	}else return 1;
}
int BARRIER::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	for(auto it= instrVector.begin(); it!= instrVector.end(); it++){
		if((*it)->getlabel()== Thread_End){
			THREAD_END* temp= (THREAD_END*) (*it);
			temp->join();
		}
	}
	return 1;
}
//THREAD class valid() function.
int THREAD::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//delete &tokens;



    return 1;
}
//THREAD execute() function
int THREAD::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
    return 1;
}


//THREAD_END class valid() function.
void* THREAD_END::run(void* arg){

	THREAD_END* mine= (THREAD_END*) arg;
	mine->threadMainBody(mine);

}


void THREAD_END::threadMainBody(void* arg){
    int i=0;	
    while(i!= myinstrVector.size()){
        int x= myinstrVector[i]->execute(myinstrVector, myvarVector, *threadoutput);
	if(x==0) break;
        i+=x;
    }

}
void THREAD_END::join(){
	pthread_join(mythread, NULL);
}
int THREAD_END::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){

	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//delete &tokens;
        if(!parameters.empty()){
		error="THREAD_END has no parameters ";
		accept= false;
		return 0;
    }
    if(THREAD::threadFlag==0){
		error= "you're ending the thread before starting it";
		accept= false;
		return 0;
    }
    THREAD::threadFlag= 0;
 	//if you passed all these conditions successfully, return a pointer to THREAD_END class
	if(accept){
	vector<expression*> _myinstrVector;
	vector<expression*> _myinstrVector2;
        while(!instrVector.empty()){
            auto it= instrVector.back();
            instrVector.pop_back();
            if((it)->getlabel()==Thread_Begin) break;
            else _myinstrVector.push_back(it);
        }
		auto it= _myinstrVector.end();
		while(it!= _myinstrVector.begin()){
			it--;
			_myinstrVector2.push_back(*it);
		}

		instrVector.push_back(new THREAD_END(Thread_End, _myinstrVector2));
		return 1;
	}else return 1;
}


//THREAD execute() function
int THREAD_END::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){

	myvarVector= varVector;
	threadoutput= &outputs;
    int created = pthread_create (&mythread,NULL,&run,this);
    if(created!= 0) cout<<"error creating the thread"<<endl;
    //THREAD_END TE(Thread_End);
    //TE.instructionVector= instructionVector;
    //TE.mythread(TE.thread_callback, varVector);
    //thread th(&THREAD_END::thread_callback, this, varVector);
    return 1;
}


//THREAD_BEGIN class valid() function.
int THREAD_BEGIN::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){

 	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//delete &tokens;
    if(!parameters.empty()){
		error="THREAD_BEGIN has no parameters ";
		accept= false;
		return 0;
    }
    if(THREAD::threadFlag==1){
		error= "you started the thread before ";
		accept= false;
		return 0;
    }

        THREAD::threadFlag=1;
 	//if you passed all these conditions successfully, return a pointer to THREAD_BEGIN class
	if(accept){
		instrVector.push_back(new THREAD_BEGIN(Thread_Begin));

		return 1;
	}else return 1;
}
//THREAD_BEGIN execute() function
int THREAD_BEGIN::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
    return 1;
}

//ASSIGN class valid() function.
int ASSIGN::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);

	//checks the size of parameters is exactly 2 and the first parameter is a registed variable of any type
	if(parameters.size()!=2 ){
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for ASSIGN is 2";
		accept= false;
		return 0;
	}
	if( parameters[0][0]!='$' ){
		error= "the first parameter in ASSIGN must be a variable name ";
		accept= false;
		return 0;
	}
	if(VAR::checkexpr(varVector, Numeric, parameters[0]) || VAR::checkexpr(varVector, Real, parameters[0])){
		double d=0;
		//if the first parameter is of type NUMERIC or REAL, the second paramter must be either a number or a registered
		//variable of type NUMERIC or REAL
		if(parameters[1][0]!='$'){
			if(!Reader::isDouble(parameters[1], d)){
				error= "the second parameter must be either a number or a NUMERIC/REAL variable decalred before ";
				accept= false;
				return 0;
			}
		}
		else{
			if(!VAR::checkexpr(varVector, Numeric, parameters[1]) || !VAR::checkexpr(varVector, Real, parameters[1])){
				error= parameters[1]+ " isn't a variable";
				accept= false;
				return 0;
			}
		}
	}
	else if(VAR::checkexpr(varVector, String, parameters[0])){
		//if the first parameter is of type STRING, the second paramter must be either a text or a registered
		//variable of type STRING
		if(parameters[1][0]=='$'){
			if(!VAR::checkexpr(varVector, String, parameters[1])){
				error= parameters[1]+ " isn't a variable ";
				accept= false;
				return 0;
			}
		}
		else{
			if(parameters[1][0]!=parameters[1][parameters[1].length()-1]){
				error= "the second parameter must be either a string or a STRING variable decalred before ";
				accept= false;
				return 0;
			}
		}
	}else if(VAR::checkexpr(varVector, Char, parameters[0])){
		//if the first parameter is of type CHAR, the second paramter must be either a character or a registered
		//variable of type CHAR
		if(parameters[1][0]=='$'){
			if(!VAR::checkexpr(varVector, Char, parameters[1])){
				error= parameters[1]+ " isn't a variable ";
				accept= false;
				return 0;
			}
		}
		else{
			if(parameters[1].length()!=3){
				error= "the second parameter must be either a char or a CHAR variable decalred before ";
				accept= false;
				return 0;
			}
			if(parameters[1][0]!=parameters[1][2]){
				error= "the second parameter must be either a char or a CHAR variable decalred before ";
				accept= false;
				return 0;
			}
		}
	} else{
		accept= false;
		return 0;
	}

	//if you passed all these conditions successfully, return a pointer to ASSIGN class
	if(accept){
		vector<string> *myV= &parameters;
		instrVector.push_back(new ASSIGN(Assign, *myV));
		return 1;
	}else return 1;

}

//OUT class valid() function.
int OUT::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);

	//check that the parameters are not empty and aren't more than 12 parameter
	if(parameters.empty() || parameters.size()>12) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for OUT must be less than 13 ";
		accept= false;
		return 0;
	}
	int size= parameters.size();
	for(int i=0;i<size; i++){

        //for each parameter, check that it's a number, a text, or a registered variable of any type.
		if(Reader::isLong(parameters[i])){
			 continue;

		}
		else if(parameters[i][0]=='$'){
			 if(!VAR::checkexpr(varVector, Numeric, parameters[i]) && !VAR::checkexpr(varVector, Real, parameters[i]) && !VAR::checkexpr(varVector, Char, parameters[i])  && !VAR::checkexpr(varVector, String, parameters[i])) {
				error= parameters[1]+ " isn't a variable";
				accept= false;
				return 0;
			 }
		}
		else if(parameters[i][0]==parameters[i][parameters[i].length()-1]){
					 Reader::removeQoutes(parameters[i]);
		}
		else {
			accept= false;
			return 0;
		}
	}

   //if you passed all these conditions successfully, return a pointer to OUT class
	if(accept){
		cout<<"OUT::valid: adding to instrVector"<<endl;
		vector<string> *myV= &parameters;
		instrVector.push_back(new OUT(Out, *myV));
		return 1;
	}else return 1;

}

int LOCK::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);

	//check that parameters size is exactly 3.
	if(parameters.empty() || parameters.size()!=1) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for LOCK is 1";
		accept= false;
		return 0;
	}

 	if(VAR::checkexpr(varVector, Numeric, parameters[0])||VAR::checkexpr(varVector, Numeric, parameters[0])||VAR::checkexpr(varVector, 		Numeric, parameters[0])||VAR::checkexpr(varVector, Numeric, parameters[0])){
		if(accept){
			instrVector.push_back(new LOCK(Lock, parameters[0]));
			return 1;
		}else return 1;
	}else{
		error= "LOCK'S parameter must be a variable";
		accept= false;
		return 0;
	}

}

int UNLOCK::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);

	//check that parameters size is exactly 3.
	if(parameters.empty() || parameters.size()!=1) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for UNLOCK is 1";
		accept= false;
		return 0;
	}

 	if(VAR::checkexpr(varVector, Numeric, parameters[0])||VAR::checkexpr(varVector, Numeric, parameters[0])||VAR::checkexpr(varVector, 		Numeric, parameters[0])||VAR::checkexpr(varVector, Numeric, parameters[0])){
		if(accept){
			instrVector.push_back(new UNLOCK(Unlock, parameters[0]));
			return 1;
		}else return 1;
	}else{
		error= "UNLOCK'S parameter must be a variable";
		accept= false;
		return 0;
	}
}

int LOCK::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
			VAR *PTR= (VAR*) (expression::getexpr(varVector, name));
			PTR->locking();
	return 1;
}
int UNLOCK::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
		VAR *PTR= (VAR*) (expression::getexpr(varVector, name));
			PTR->unlocking();
	return 1;
}
//SET_STR_CHAR class valid() function.
int SET_STR_CHAR::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);

	//check that parameters size is exactly 3.
	if(parameters.empty() || parameters.size()!=3) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for SET_STR_CHAR is 3";
		accept= false;
		return 0;
	}

	//the first parameter must be a registered variable of type STRING
	if(parameters[0][0]!='$') {
		error= "the first parameter in SET_STR_CHAR must be a STRING variable name ";
		accept= false;
		return 0;
	}
	if(!VAR::checkexpr(varVector, String, parameters[0])) {
		error= "the first parameter in SET_STR_CHAR must be a STRING variable name ";
		accept= false;
		return 0;
	}

	//the third parameter must be a char or a registered variable of type CHAR
	if(parameters[2][0]!='$'){
		if(parameters[2].length()!=3) {
			error= "the third parameter in SET_STR_CHAR must be either a char or a CHAR variable name ";
			accept= false;
			return 0;
		}
		if(parameters[2][0]!= parameters[2][2]) {
			error= "the third parameter in SET_STR_CHAR must be either a char or a CHAR variable name ";
			accept= false;
			return 0;
		}

	}
	else if(!VAR::checkexpr(varVector, Char, parameters[2])) {
		error= "the third parameter in SET_STR_CHAR must be either a char or a CHAR variable name ";
		accept= false;
		return 0;
	}

	//the second parameter must be a number less than the length of the string
	int index;
	if(!(Reader::isLong(parameters[1]))) {
		error= "the second parameter of  SET_STR_CHAR must be a number ";
		accept= false;
		return 0;
	}
	else index=atoi(parameters[1].c_str());

	if(index< 0){
		error= "index can't be a negative number ";
		accept= false;
		return 0;
	}

	//static cast
	bool flag= true;
	//loop through all registered expressions and find the concerned string
	//get its length and compare it to the given index.
	//If the index is bigger than the length of the string return nullptr
	for(auto it=varVector.begin(); it!=varVector.end(); it++){
		if((*it)->getlabel()==String){
			STRING *strptr= (STRING*) (*it);
			if(strptr->getname()==parameters[0]){
				if(strptr->getvalue().length()>= index) flag=false;
				break;
			}
		}
	}

	if(!flag) {
		error= "the index you intered is bigger than the length of the string";
		accept= false;
		return 0;
	}
	if(accept){
		vector<string> *myV= &parameters;
		instrVector.push_back(new SET_STR_CHAR(Set_str_char, *myV));
		return 1;
	}else return 1;

}

//GET_STR_CHAR class valid() function.
int GET_STR_CHAR::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);

	//check that parameters size is exactly 3.
	if(parameters.empty() || parameters.size()!=3) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for GET_STR_CHAR is 3";
		accept= false;
		return 0;
	}

	//the first parameter must be a registered variable of type STRING
	if(parameters[0][0]!='$') {
		error= "the first parameter in GET_STR_CHAR must be a STRING variable name ";
		accept= false;
		return 0;
	}
	if(!VAR::checkexpr(varVector, String, parameters[0])) {
		error= "the first parameter in GET_STR_CHAR must be a STRING variable name ";
		accept= false;
		return 0;
	}
	//the first parameter must be a registered variable of type STRING
	if(parameters[2][0]!='$') {
			error= "the third parameter in GET_STR_CHAR must be a CHAR variable name ";
			accept= false;
			return 0;
	}
	if(!VAR::checkexpr(varVector, Char, parameters[2])) {
			error= "the third parameter in GET_STR_CHAR must be a CHAR variable name ";
			accept= false;
			return 0;
	}
	//the second parameter must be a number less than the length of the string
	int index;

	if(!(Reader::isLong(parameters[1]))) {
		error= "the second parameter of  GET_STR_CHAR must be a number ";
		accept= false;
		return 0;
	}
	else index=atoi(parameters[1].c_str());
	if(index< 0){
		error= "index can't be a negative number ";
		accept= false;
		return 0;
	}
	//static cast
	bool flag= false;
	//loop through all registered expressions and find the concerned string
	//get its length and compare it to the given index.
	//If the index is bigger than the length of the string return nullptr
	for(auto it=varVector.begin(); it!=varVector.end(); it++){
		if((*it)->getlabel()==String){
			STRING *strptr= (STRING*) (*it);
			if(strptr->getname()==parameters[0]){
				if(strptr->getvalue().length()> index) flag=true;
				break;
			}
		}
	}

	if(!flag) {
		error= "the index you intered is bigger than the length of the string";
		accept= false;
		return 0;
	}
	if(accept){
		vector<string> *myV= &parameters;
		instrVector.push_back(new GET_STR_CHAR(Get_str_char, *myV));
		return 1;
	}else return 1;


}

//LABEL class valid() function.
int LABEL::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);

	//check there is only one parameter
	if(parameters.empty() || parameters.size()!=1) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for LABEL is 1";
		accept= false;
		return 0;
	}

	if(accept){
		instrVector.push_back(new LABEL(Label, parameters[0]));
		cout<<"new label:"<< parameters[0]<<endl;
		return 1;
	}else return 1;

}

//JMP class valid() function.
int JMP::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//check there is only one parameter
	if(parameters.empty() || parameters.size()!=1) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for JMP is 1";
		accept= false;
		return 0;
	}

	bool flag=false;

	//loop through the expressions registered in the vector, get all labels
	//and check that there is a label with the name of the parameter we read
	for(auto it=instrVector.begin(); it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==parameters[0]){
				flag=true;
				break;
			}
		}
	}

	//check if we found a label with the name of the parameter
	if(!flag) {
		error= parameters[0]+ "isn't a name of a LABEL'";
		accept= false;
		return 0;
	}
	if(accept){
		instrVector.push_back(new JMP(Jmp, parameters[0]));
		return 1;
	}else return 1;

}

//SLEEP class valid() function.
int SLEEP::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//check there is exactly one parameter
	if(parameters.empty() || parameters.size()!=1) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for SLEEP is 1";
		accept= false;
		return 0;
	}

	//the parameter must be a number
	long value=0;
	if(!Reader::isLong(parameters[0])) {
		if(VAR::checkexpr(varVector, Numeric, parameters[0]) || VAR::checkexpr(varVector, Real, parameters[0])){
			value= expression::getdou(varVector, parameters[0]);

		}else{
			error= "SLEEP's parameter must be a number or a variable of type numeric/real";
			accept= false;
			return 0;
		}
	}else value= atoi(parameters[0].c_str());

	if(accept){
		instrVector.push_back(new SLEEP(Sleep, value));
		return 1;
	}else return 1;


}

//JMPZ class valid() function.
int JMPZ::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//check the parameters are exactly two parameters
	if(parameters.empty() || parameters.size()!=2) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for JMPZ is 2";
		accept= false;
		return 0;
	}
	bool flag=false;
	//loop through all expressions , find label, get their name, and find
	//whether there is one that has the name of our parameter
	for(auto it=instrVector.begin(); it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==parameters[0]){
				flag=true;
				break;
			}
		}
	}

	//check if we found a label expression with the same name as the parameter
	if(!flag) {
		error= parameters[0]+ "isn't a name of a LABEL'";
		accept= false;
		return 0;
	}

	double d;
	//the second parameter must be either a number or a registered variable of type NUMERIC or REAL
	if(Reader::isDouble(parameters[1], d)){
		if(accept){
			instrVector.push_back(new JMPZ(Jmpz, parameters[0], parameters[1]));
			return 1;
		}else return 1;
	}
	if(!VAR::checkexpr(varVector, Numeric, parameters[1]) && !VAR::checkexpr(varVector, Real, parameters[1]) ) {
		error= "JMPZ's second parameter must be a number or a NUMERIC/CHAR variable ";
		accept= false;
		return 0;
	}

		if(accept){
			instrVector.push_back(new JMPZ(Jmpz, parameters[0], parameters[1]));
			return 1;
		}else return 1;

}

//JMPNZ class valid() function.
int JMPNZ::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//check the parameters are exactly two parameters
	if(parameters.empty() || parameters.size()!=2) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for JMPNZ is 2";
		accept= false;
		return 0;
	}
	bool flag=false;
	//loop through all expressions , find label, get their name, and find
	//whether there is one that has the name of our parameter
	for(auto it=instrVector.begin(); it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==parameters[0]){
				flag=true;
				break;
			}
		}
	}
	//check if we found a label expression with the same name as the parameter
	if(!flag) {
		error= parameters[0]+ "isn't a name of a LABEL'";
		accept= false;
		return 0;
	}

	double d;
	//the second parameter must be either a number or a registered variable of type NUMERIC or REAL
	if(Reader::isDouble(parameters[1], d)){
		if(accept){
			instrVector.push_back(new JMPNZ(Jmpnz, parameters[0], parameters[1]));
			return 1;
		}else return 1;
	}
	if(!VAR::checkexpr(varVector, Numeric, parameters[1]) && !VAR::checkexpr(varVector, Real, parameters[1]) ) {
		error= "JMPNZ's second parameter must be a number or a NUMERIC/CHAR variable ";
		accept= false;
		return 0;
	}

		if(accept){
			instrVector.push_back(new JMPNZ(Jmpnz, parameters[0], parameters[1]));
			return 1;
		}else return 1;

}

//JMPGT class valid() function.
int JMPGT::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//check the parameters are exactly three parameters
	if(parameters.empty() || parameters.size()!=3) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for JMPGT is 3";
		accept= false;
		return 0;
	}
	bool flag=false;
	//loop through all expressions , find label, get their name, and find
	//whether there is one that has the name of our parameter
	for(auto it=instrVector.begin(); it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==parameters[0]){
				flag=true;
				break;
			}
		}
	}
	//check if we found a label expression with the same name as the parameter
	if(!flag) {
		error= parameters[0]+ "isn't a name of a LABEL'";
		accept= false;
		return 0;
	}

	double d;
	//parameter 2 and parameter 3 must be either numbers or registered variable of type NUMERIC or REAL
	if(!Reader::isDouble(parameters[1], d)) if(!VAR::checkexpr(varVector, Numeric, parameters[1]) && !VAR::checkexpr(varVector, Real, parameters[1]) ) {
		error= "JMPGT's second parameter must be a number or a NUMERIC/CHAR variable ";
		accept= false;
		return 0;
	}
	if(!Reader::isDouble(parameters[2], d)) if(!VAR::checkexpr(varVector, Numeric, parameters[2]) && !VAR::checkexpr(varVector, Real, parameters[2]) ) {
		error= "JMPGT's third parameter must be a number or a NUMERIC/CHAR variable ";
		accept= false;
		return 0;
	}

	if(accept){
		instrVector.push_back(new JMPGT(parameters[1], parameters[2], Jmpgt, parameters[0]));
		return 1;
	}else return 1;

}
//JMPLTE class valid() function.
int JMPLTE::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//check the parameters are exactly three parameters
	if(parameters.empty() || parameters.size()!=3) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for JMPLTE is 3";
		accept= false;
		return 0;
	}
	bool flag=false;
	//loop through all expressions , find label, get their name, and find
	//whether there is one that has the name of our parameter
	for(auto it=instrVector.begin(); it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==parameters[0]){
				flag=true;
				break;
			}
		}
	}

	if(!flag) {
		error= parameters[0]+ "isn't a name of a LABEL'";
		accept= false;
		return 0;
	}

	double d;
	//parameter 2 and parameter 3 must be either numbers or registered variable of type NUMERIC or REAL
	if(!Reader::isDouble(parameters[1], d)) if(!VAR::checkexpr(varVector, Numeric, parameters[1]) && !VAR::checkexpr(varVector, Real, parameters[1]) ) {
		error= "JMPLTE's second parameter must be a number or a NUMERIC/CHAR variable ";
		accept= false;
		return 0;
	}
	if(!Reader::isDouble(parameters[2], d)) if(!VAR::checkexpr(varVector, Numeric, parameters[2]) && !VAR::checkexpr(varVector, Real, parameters[2]) ) {
		error= "JMPLTE's third parameter must be a number or a NUMERIC/CHAR variable ";
		accept= false;
		return 0;
	}

	if(accept){
		instrVector.push_back(new JMPLTE(parameters[1], parameters[2], Jmplte, parameters[0]));
		return 1;
	}else return 1;

}
//JMPLT class valid() function.
int JMPLT::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//check the parameters are exactly three parameters
	if(parameters.empty() || parameters.size()!=3) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for JMPLT is 3";
		accept= false;
		return 0;
	}
	bool flag=false;
	//loop through all expressions , find label, get their name, and find
	//whether there is one that has the name of our parameter
	for(auto it=instrVector.begin(); it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==parameters[0]){
				flag=true;
				break;
			}
		}
	}

	if(!flag) {
		error= parameters[0]+ "isn't a name of a LABEL'";
		accept= false;
		return 0;
	}

	double d;
	//parameter 2 and parameter 3 must be either numbers or registered variable of type NUMERIC or REAL
	if(!Reader::isDouble(parameters[1], d)) if(!VAR::checkexpr(varVector, Numeric, parameters[1]) && !VAR::checkexpr(varVector, Real, parameters[1]) ) {
		error= "JMPLT's second parameter must be a number or a NUMERIC/CHAR variable ";
		accept= false;
		return 0;
	}
	if(!Reader::isDouble(parameters[2], d)) if(!VAR::checkexpr(varVector, Numeric, parameters[2]) && !VAR::checkexpr(varVector, Real, parameters[2]) ) {
		error= "JMPLT's third parameter must be a number or a NUMERIC/CHAR variable ";
		accept= false;
		return 0;
	}

	if(accept){
		instrVector.push_back(new JMPLT(parameters[1], parameters[2], Jmplt, parameters[0]));
		return 1;
	} else return 1;
}
//JMPGTE class valid() function.
int JMPGTE::valid(vector<string> & tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept){
	//give the vector of strings we got by separating the line according to spaces to toCommaTokens()
	//and take back another vector of strings that we got by separating the line according to commas.
	vector<string> parameters= Reader::toCommaTokens(tokens);
	//check the parameters are exactly three parameters
	if(parameters.empty() || parameters.size()!=3) {
		error= "you passed "+ to_string(parameters.size())+ " parameters, while the number of parameters for JMPGTE is 3";
		accept= false;
		return 0;
	}
	bool flag=false;
	//loop through all expressions , find label, get their name, and find
	//whether there is one that has the name of our parameter
	for(auto it=instrVector.begin(); it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==parameters[0]){
				flag=true;
				break;
			}
		}
	}

	if(!flag) {
		error= parameters[0]+ "isn't a name of a LABEL'";
		accept= false;
		return 0;
	}

	double d;
	//parameter 2 and parameter 3 must be either numbers or registered variable of type NUMERIC or REAL
	if(!Reader::isDouble(parameters[1], d)) if(!VAR::checkexpr(varVector, Numeric, parameters[1]) && !VAR::checkexpr(varVector, Real, parameters[1]) ) {
		error= "JMPGTE's second parameter must be a number or a NUMERIC/CHAR variable ";
		accept= false;
		return 0;
	}
	if(!Reader::isDouble(parameters[2], d)) if(!VAR::checkexpr(varVector, Numeric, parameters[2]) && !VAR::checkexpr(varVector, Real, parameters[2]) ) {
		error= "JMPGTE's third parameter must be a number or a NUMERIC/CHAR variable ";
		accept= false;
		return 0;
	}

	if(accept){
		instrVector.push_back(new JMPGTE(parameters[1], parameters[2], Jmpgte, parameters[0]));
		return 1;
	} else return 1;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ADD execute() function
int ADD::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	double result= 0, d;
	//iterate over saved parameters and get thier value. either by directly converting them to numbers or by fetching
	//thier values from the expression vector
	auto it= myparameters.begin();	it++;
	while(it!=myparameters.end()){
		if(Reader::isDouble((*it), d)) result+=d;
		else result+= expression::getdou(varVector, (*it));
		it++;
	}

	//set the value of the first parameter to the result of addition of all values
	//of all other parameters
	expression::setdou(varVector, (*myparameters.begin()), result);
	return 1;
}

int SETAFFINITY::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    pthread_t self;
    self= pthread_self();
    int i= cpuid;
    string six=to_string(i);
    i= atoi(six.c_str());
    CPU_SET(i, &cpuset);
    pthread_setaffinity_np(self, sizeof(cpu_set_t), &cpuset);
	return 1;
}

//static string that is used to make us just open the output file once at the last output instruction
//instead of opening, writing and closing it every time an OUT instruction is called
string expression::print="";

//OUT execute() function
int OUT::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	pthread_mutex_lock(&lock);
	string output="";
	//an iterator over all the parameters
        auto it= myparameters.begin();
        while(it!=myparameters.end()){
        	//find the type of the parameter (variable or a direct text) in order to know how to get its value
            if((*it)[0]!='$'){
            	//if the parameter doesn't start with the '$' sign, then its not a variable and thus
            	//print character by character to take care of /n as  a new line not an ordinary characters
                    for(int i=0; i<(*it).length(); i++){
                        if((*it)[i]=='\\'){
                            if((*it)[i+1]=='n'){
				output+="\n";
				i++;
				continue;
                            }
                        }
                        output+=(*it)[i];
                    }
            } else{
			if(VAR::checkexpr(varVector, Numeric, (*it)) || VAR::checkexpr(varVector, Real, (*it))){
                            double d=   expression::getdou(varVector, (*it));
                            long l= d;
                            string s;
                            if(l== d) s= to_string(l);
                            else{
                                stringstream stream;
                                stream << fixed << setprecision(1) << d;
                                s = stream.str();
                            }
                            output+=s;

                        }
			else if(VAR::checkexpr(varVector, String, (*it))){
                            string s= expression::getstr(varVector, (*it));
                            for(int i=0; i<s.length(); i++){
                                if(s[i]=='\\'){
                                     if(s[i+1]=='n'){
                                         output+="\n";
                                         i++;
                                        continue;
                                    }
                                }
                                output+=s[i];
                            }
                        }
			else if(VAR::checkexpr(varVector, Char, (*it))){
                            char c= expression::getchr(varVector, (*it));
                            output+=c;
                        }


		}
	it++;
    }
    //add the string generated from this particualr OUT instruction to the static string variable
    //so we can sum all the outputs of all OUT instrucions
    outputs+= output;
	cout<<"first output:"<<outputs<<endl;
	pthread_mutex_unlock(&lock);

	//if you want, you can uncomment the following 3lines to check the core the current thread is running on.	
	//int cpu= sched_getcpu();
	//string z= "cpu: "+  to_string(cpu);
    	//output+=z;


        return 1;

}

//JMP execute() function
int JMP::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){

	//this instruction has no conditions to check. If you reach this instruction
	//just search for the label having your name and jump to it by returning
	//a negative offset to the index of that label
	auto it= instrVector.begin();
	for(;it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==getname()) break;
		}
	}
	int i=0;
	while((*it)!=this) i--;

	return i;
}
//JMPZ execute() function
int JMPZ::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){

	//get the value of the operand. it's either a number or a variable
	//regirstered in the expression vector as NUMERIC or REAL
	double d= 0;
	if(value[0]=='$') d= expression::getdou(varVector, value);
	else Reader::isDouble(value, d);

	//this function has a condition to check. if the extracted value is 0, return 1 (the next instruction's offset)
	//else do just like JMP would do ( return the negative distance between this instruction and the label you're concerned with).
	if(d!= 0) return 1;

	//just search for the label having your name and jump to it by returning
	//a negative offset to the index of that label
	else{
		auto it= instrVector.begin();
	for(;it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==getname()) break;
		}
	}
	int i=0;
	while((*it)!=this) i--;
	return i;
	}
}

//JMPNZ execute() function
int JMPNZ::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){

	//get the value of the operand. it's either a number or a variable
	// in the expression vector as NUMERIC or REAL
	double d= 0;
	if(value[0]=='$') d= expression::getdou(varVector, value);
	else Reader::isDouble(value, d);

	//this function has a condition to check. if the extracted value is not 0, return 1 (the next instruction's offset)
	//else do just like JMP would do ( return the negative distance between this instruction and the label you're concerned with).
	if(d== 0) return 1;
	//just search for the label having your name and jump to it by returning
	//a negative offset to the index of that label
		auto it= instrVector.begin();
	for(;it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==getname()) break;
		}

	}
	int i=0;
	while((*it)!=this){
		i--;
		it++;
	}
	return i;

}

//LABEL execute() function
int LABEL::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	return 1;
}

//ASSIGN execute() function
int ASSIGN::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){

	//here we only have two values. where one of them is to be assigned to the other
	//the check we need to do here is to know which type they are both of.
	//NOTE that we already checked that both parameters are of the same type in the validation phase.
	expression *expptr= expression::getexpr(varVector, myparameters[0]);
	if(expptr->getlabel()==String){
		if(myparameters[1][0]=='$') expression::setstr(varVector, myparameters[0], expression::getstr(varVector, myparameters[1]));
		else expression::setstr(varVector, myparameters[0], myparameters[1]);
	}
	else if(expptr->getlabel()==Numeric){
		if(myparameters[1][0]=='$') expression::setdou(varVector, myparameters[0], expression::getdou(varVector, myparameters[1]));
		else{
			double d=0;
			Reader::isDouble(myparameters[1], d);
			expression::setdou(varVector, myparameters[0], d);
		}
	}
	else if(expptr->getlabel()==Char){
		if(myparameters[1][0]=='$') expression::setchr(varVector, myparameters[0], expression::getchr(varVector, myparameters[1]));
		else expression::setchr(varVector, myparameters[0], myparameters[1][0]);
	}
	else if(expptr->getlabel()==Real){
		if(myparameters[1][0]=='$') expression::setdou(varVector, myparameters[0], expression::getdou(varVector, myparameters[1]));
		else{
			double d=0;
			Reader::isDouble(myparameters[1], d);
			expression::setdou(varVector, myparameters[0], d);
		}
	}
	return 1;
}

//MUL execute() function
int MUL::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	double result=1;

	//iterate throught all parameters
	auto it= myparameters.begin();
	it++;
	while(it!=myparameters.end()){
		// paramers are either numbers or refering to a variable that
		//is of type NUMERIC or REAL
		//NOTE that we already checked for that in the validation phase
		double d=1;
		if(Reader::isDouble((*it), d)) result= result*d;
		else result*= expression::getdou(varVector, (*it));

		it++;
	}

	//finally you have to update the first parameter's value with the result of the multiplication process
	expression::setdou(varVector, (*myparameters.begin()), result);
	return 1;
}

//SUB execute() function
int SUB::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
		double fnum, snum;
		double result;
		//go directly to the second parameter because the first parameter is not part of the subtraction operation
    	auto it=myparameters.begin();
    	it++;

    	//get the value of the second parameter and save it in the fnum variable
    	if(Reader::isDouble((*it), fnum));
    	else fnum= expression::getdou(varVector, (*it));

    	it++;
    	//get the value of the third parameter and save it in the  snum variable
    	if(Reader::isDouble((*it), snum));
    	else snum= expression::getdou(varVector, (*it));

    	//subtract the third from the second and save the result in the variable whose name is the first parameter
		result= fnum- snum;
		expression::setdou(varVector, (*myparameters.begin()), result);
		return 1;
}

	//DIV execute() function
int DIV::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	double first, second;
		double result;
    	auto it= myparameters.begin();

		it++;
		//get the value of the second parameter and save it in the first variable
		if(Reader::isDouble((*it), first));
		else first= expression::getdou(varVector, (*it));

		it++;
		//get the value of the third parameter and save it in the  second variable
		if(Reader::isDouble((*it), second));
		else second= expression::getdou(varVector, (*it));

		//do the division operation itself
		//this is the only runtime error we check for.
		if( second== 0) return 0;
		result= first/ second;

		//save the result in the variable refered to by the first parameter
		expression::setdou(varVector, *myparameters.begin(),result );
		return 1;
}

//SLEEP execute() function
int SLEEP::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	//the sleep execute() function is simply just looping for some time
	long limit= getvalue();
	sleep(limit);
	return 1;
}

//SET_STR_CHAR execute() function
int SET_STR_CHAR::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){

	char c;
	CHAR *chrptr;

	//get the value of parameter 2, which is either a character or a name of a variable
	//registered in the expression vector representing a char
	//NOTE that we already checked that in the validation phase
	if (myparameters[2][0]=='$')c= expression::getchr(varVector, myparameters[2]);
	else c=myparameters[2][0];

	//get the value of parameter 0, which is a name of a variable
	//registered in the expression vector representing a STRING
	//NOTE that we already checked that in the validation phase
	string temp= expression::getstr(varVector, myparameters[0]);

	//get the index of the character in the string that will be replaced
	//NOTE that we already checked that this index is less than the length of the string
	//so we can just directly use it
	int index=atoi(myparameters[1].c_str());

	//replacing the character in the index specified with the value of the character
	temp[index]=c;
	//return the value back to the STRING variable after editing it
	expression::setstr(varVector, myparameters[0], temp);
	return 1;
}

//GET_STR_CHAR execute() function
int GET_STR_CHAR::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	//get the value of parameter 2, which is  a name of a variable
	//registered in the expression vector representing a char
	//NOTE that we already checked that in the validation phase
	char dest= expression::getchr(varVector, myparameters[2]);

	//get the value of parameter 0, which is either a string or a name of a variable
	//registered in the expression vector representing a STRING
	//NOTE that we already checked that in the validation phase
	string src= expression::getstr(varVector, myparameters[0]);
	//get the index of the character in the string that will be replaced
	//NOTE that we already checked that this index is less than the length of the string
	//so we can just directly use it
	int index=atoi(myparameters[1].c_str());

	//changin the value of the char to the character in the string at the index specified
	dest= src[index];

	//return the value back to the CHAR variable after editing it
	expression::setchr(varVector, myparameters[2], dest);
	return 1;

}

int CHAR::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	return 1;
}

int NUMERIC::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	return 1;
}

int STRING::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	return 1;
}

int REAL::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	return 1;
}

//JMPGT execute() function
int JMPGT::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	double fnum, snum;
	//get the value of the first parameter and save it in fnum. the first
	//parameter is either a number or a variable name registered as NUMERIC or REAL
	if(first[0]=='$') fnum= expression::getdou(varVector, first);
	else fnum= atoi(first.c_str());
	//get the value of the second parameter and save it in snum. the second
	//parameter is either a number or a variable name registered as NUMERIC or REAL
	if(second[0]=='$') snum= expression::getdou(varVector, second);
	else snum= atoi(second.c_str());

	//do the comparison between fnum and snum. if the condision isn't satisfied, return 1
	//else coninue to find the negative offset to the label you're refereing to
	if(fnum <= snum) return 1;
	//just search for the label having your name and jump to it by returning
	//a negative offset to the index of that label
	else{
		auto it= instrVector.begin();
	for(;it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==getname()) break;
		}
	}
	int i=0;
	while((*it)!=this) i--;
	return i;
	}
}

int JMPGTE::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	double fnum, snum;
	//get the value of the first parameter and save it in fnum. the first
	//parameter is either a number or a variable name registered as NUMERIC or REAL
	if(first[0]=='$') fnum= expression::getdou(varVector, first);
	else fnum= atoi(first.c_str());
	//get the value of the second parameter and save it in snum. the second
	//parameter is either a number or a variable name registered as NUMERIC or REAL
	if(second[0]=='$') snum= expression::getdou(varVector, second);
	else snum= atoi(second.c_str());

	//do the comparison between fnum and snum. if the condision isn't satisfied, return 1
	//else coninue to find the negative offset to the label you're refereing to
	if(fnum < snum) return 1;
	//just search for the label having your name and jump to it by returning
	//a negative offset to the index of that label
	else{
		auto it= instrVector.begin();
	for(;it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==getname()) break;
		}
	}
	int i=0;
	while((*it)!=this) i--;
	return i;
	}
}

int JMPLT::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	double fnum, snum;
	//get the value of the first parameter and save it in fnum. the first
	//parameter is either a number or a variable name registered as NUMERIC or REAL
	if(first[0]=='$') fnum= expression::getdou(varVector, first);
	else fnum= atoi(first.c_str());
	//get the value of the second parameter and save it in snum. the second
	//parameter is either a number or a variable name registered as NUMERIC or REAL
	if(second[0]=='$') snum= expression::getdou(varVector, second);
	else snum= atoi(second.c_str());

	//do the comparison between fnum and snum. if the condision isn't satisfied, return 1
	//else coninue to find the negative offset to the label you're refereing to
	if(fnum >= snum) return 1;
	//just search for the label having your name and jump to it by returning
	//a negative offset to the index of that label
	else{
		auto it= instrVector.begin();
	for(;it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==getname()) break;
		}
	}
	int i=0;
	while((*it)!=this) i--;
	return i;
	}
}

int JMPLTE::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	double fnum, snum;
	//get the value of the first parameter and save it in fnum. the first
	//parameter is either a number or a variable name registered as NUMERIC or REAL
	if(first[0]=='$') fnum= expression::getdou(varVector, first);
	else fnum= atoi(first.c_str());
	//get the value of the second parameter and save it in snum. the second
	//parameter is either a number or a variable name registered as NUMERIC or REAL
	if(second[0]=='$') snum= expression::getdou(varVector, second);
	else snum= atoi(second.c_str());

	//do the comparison between fnum and snum. if the condision isn't satisfied, return 1
	//else coninue to find the negative offset to the label you're refereing to
	if(fnum> snum) return 1;
	//just search for the label having your name and jump to it by returning
	//a negative offset to the index of that label
	else{
		auto it= instrVector.begin();
	for(;it!=instrVector.end(); it++){
		if((*it)->getlabel()==Label){
			LABEL *lblptr= (LABEL*) (*it);
			if(lblptr->getname()==getname()) break;
		}
	}
	int i=0;
	while((*it)!=this) i--;
	return i;
	}
}

int VAR::execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs){
	return 1;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//this static function takes the expression vector we collected from the input file lines and a label defining the type of a class
//and the name of the varible stored inside the expression
//this function is used only with VAR child classes to check if a class of that type and that name exists or not
bool expression::checkexpr(const vector<expression*> &exprVector,int label, string name){
	for(auto it=exprVector.begin(); it!=exprVector.end(); it++){
		if((*it)->getlabel()==label){
			VAR *numptr=(VAR*) (*it);
			if(numptr->getname()==name) return true;
		}

	}
	return false;
}

//this static function takes the expression vector we collected from the input file lines and a name of a CHAR class that we know exists
//and a character we want to replace the current value of the concerned STRING with it.
void expression::setchr(const vector<expression*> &exprVector, string name, char c){
	for(auto it=exprVector.begin(); it!=exprVector.end(); it++){
		int label= (*it)->getlabel();
		if(label==Char ){
			CHAR *chr_ptr= (CHAR*) (*it);
			if(chr_ptr->getname()==name){
				chr_ptr->setvalue(c);
				return;
			}
		}
	}
}
//this static function takes the expression vector we collected from the input file lines and a name of a STRING class that we know exists
//and a string we want to replace the current value of the concerned STRING with it.
void expression::setstr(const vector<expression*> &exprVector, string name, string s){
	for(auto it=exprVector.begin(); it!=exprVector.end(); it++){
		int label= (*it)->getlabel();
		if(label==String ){
			STRING *str_ptr= (STRING*) (*it);
			if(str_ptr->getname()==name){
				str_ptr->setvalue(s);
				return ;
			}
		}
	}
}

//this static function takes the expression vector we collected from the input file lines and a name of a NUMERIC or REAL class that we know exists
//and a number we want to replace the current value of the concerned NUMERIC or REAL  with it.
void expression::setdou(const vector<expression*> &exprVector, string name, double d){
	for(auto it=exprVector.begin(); it!=exprVector.end(); it++){
		int label= (*it)->getlabel();
		if(label==Numeric ){
			NUMERIC *num_ptr= (NUMERIC*) (*it);
			if(num_ptr->getname()==name){
				num_ptr->setvalue(d);
				return ;
			}
		}
		else if(label==Real ){
			REAL *real_ptr= (REAL*) (*it);
			if(real_ptr->getname()==name){
				real_ptr->setvalue(d);
				return ;
			}
		}
	}
}

//this static function takes the expression vector we collected from the input file lines and a name of STRING to fetch its value
string expression::getstr(const vector<expression*> &exprVector, string name){
	string value;
	for(auto it=exprVector.begin(); it!=exprVector.end(); it++){
		int label= (*it)->getlabel();
		if(label==String ){
			STRING *str_ptr= (STRING*) (*it);
			if(str_ptr->getname()==name){
				value= str_ptr->getvalue();
				return value;
			}
		}
	}
}
//this static function takes the expression vector we collected from the input file lines and a name of CHAR to fetch its value
char expression::getchr(const vector<expression*> &exprVector, string name){
	char value;
	for(auto it=exprVector.begin(); it!=exprVector.end(); it++){
		int label= (*it)->getlabel();
		if(label==Char ){
			CHAR *chr_ptr= (CHAR*) (*it);
			if(chr_ptr->getname()==name){
				value= chr_ptr->getvalue();
				return value;
			}
		}
	}
}
//this static function takes the expression vector we collected from the input file lines and a name of NUMERIC OR REAL to fetch its value
double expression::getdou(const vector<expression*> &exprVector, string name){
	double value;
	for(auto it=exprVector.begin(); it!=exprVector.end(); it++){
		int label= (*it)->getlabel();
		if(label==Numeric ){
			NUMERIC *num_ptr= (NUMERIC*) (*it);
			if(num_ptr->getname()==name){
				value= num_ptr->getvalue();
				return value;
			}
		}
		else if(label==Real ){
			REAL *real_ptr= (REAL*) (*it);
			if(real_ptr->getname()==name){
				value= real_ptr->getvalue();
				return value;
			}
		}
	}
}
//this static function takes the expression vector we collected from the input file lines and a name of a variable to fetch a pointer to
expression* expression::getexpr(const vector<expression*> &exprVector, string name){
	for(auto it=exprVector.begin(); it!=exprVector.end(); it++){


			VAR *varptr= (VAR*) (*it);
			if(varptr->getname()==name) return varptr;

	}
	return nullptr;
}
//this static function takes the expression vector we collected from the input file lines and a name of a variable
//the function loops through all the expressions in the vector and returns a bool indicating a variable with the name we
//passed exist or not
bool expression::alreadyExist(const vector<expression*> &exprVector, string name){
	for(auto it=exprVector.begin(); it!=exprVector.end(); it++){


			VAR *varptr= (VAR*) (*it);
			if(varptr->getname()==name) return true;

	}
	return false;
}


