/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Instruction.h
 * Author: gad
 *
 * Created on April 25, 2018, 2:49 PM
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H


#include "common.h"

class expression{
	protected:
		int label;
              
	public:
		expression(){}
		expression(int l);
		virtual int getlabel();
		static string print;
		//valid() and execute() functions are the core of the interpretation process thus 
		//every class that inherits from expression must difine this function
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);
		virtual int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs)=0;
		//this static function takes the expression vector we collected from the input file lines and a name of a variable to fetch a pointer to
		static expression* getexpr(const vector<expression*> &exprVector, string name);
		//this static function takes the expression vector we collected from the input file lines and a label defining the type of a class
		//and the name of the varible stored inside the expression
		//this function is used only with VAR child classes to check if a class of that type and that name exists or not
		static bool checkexpr(const vector<expression*> &exprVector,int label, string name);
		//this static function takes the expression vector we collected from the input file lines and a name of a variable
		//the function loops through all the expressions in the vector and returns a bool indicating a variable with the name we 
		//passed exist or not
		static bool alreadyExist(const vector<expression*> &exprVector, string name);
		//this static function takes the expression vector we collected from the input file lines and a name of STRING to fetch its value
		static string getstr(const vector<expression*> &exprVector, string name);
		//this static function takes the expression vector we collected from the input file lines and a name of NUMERIC OR REAL to fetch its value		
		static double getdou(const vector<expression*> &exprVector, string name);
		//this static function takes the expression vector we collected from the input file lines and a name of CHAR to fetch its value
		static char getchr(const vector<expression*> &exprVector, string name);
		//this static function takes the expression vector we collected from the input file lines and a name of a NUMERIC or REAL class that we know exists
		//and a number we want to replace the current value of the concerned NUMERIC or REAL  with it.
		static void setdou(const vector<expression*> &exprVector, string name, double d);
		//this static function takes the expression vector we collected from the input file lines and a name of a CHAR class that we know exists
		//and a character we want to replace the current value of the concerned STRING with it.		
		static void setchr(const vector<expression*> &exprVector, string name, char c);
		//this static function takes the expression vector we collected from the input file lines and a name of a STRING class that we know exists
		//and a string we want to replace the current value of the concerned STRING with it.
		static void setstr(const vector<expression*> &exprVector, string name, string s);
		//the destructor is virtual so that if a new instruction is to be added at any time 
		//and that instruction uses a pointer to some object
		//it can delete that pointer
		virtual ~expression();
};

class ADD: public expression{
	protected:
	 	vector <string> myparameters;
	public:
		ADD(){}
		ADD(int l, vector<string> myparameters);
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);
};

class MUL: public expression{
	protected:
	 	vector <string> myparameters;
	public:
		MUL(){}
		MUL(int l, vector<string> myparameters);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   	                		
                
};

class SUB: public expression{
	protected:
	 	vector <string> myparameters;
	public:
		SUB(){}
		SUB(int l, vector<string> myparameters);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                		
 		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);               
};

class DIV: public expression{
	protected:
	 	vector <string> myparameters;
	public:
		DIV(){}
		DIV(int l, vector<string> myparameters);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	 
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);               		
};

class OUT: public expression{
	protected:
  
	 	vector <string> myparameters;
		pthread_mutex_t lock;
	public:
		OUT(){}
		~OUT();
		OUT(int l, vector<string> myparameters);
		string outputs;
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                		
        int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);           
};

class ASSIGN: public expression{
	protected:
	 	vector <string> myparameters;
	public:
		ASSIGN(){}
		ASSIGN(int l, vector<string> myparameters);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};
class SETAFFINITY: public expression{
	protected:
	 	int cpuid;
	public:
		SETAFFINITY(){}
		SETAFFINITY(int l, int _cpuid);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class LABEL: public expression{
	protected:
	 	string name;
	public:
		LABEL(){}
		LABEL(int l, string n);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		string getname();
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class THREAD: public expression{
protected:

public:
	THREAD(){}
	THREAD(int l);
	static int threadFlag;
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
};

class THREAD_BEGIN: public THREAD{
protected:
public:
	THREAD_BEGIN(){}
	THREAD_BEGIN(int l);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
};

class THREAD_END: public THREAD{
protected:
	vector<expression*> myvarVector;
	vector<expression*> myinstrVector;
	pthread_t mythread;
public:
	THREAD_END(){}
	THREAD_END(int l, vector<expression*> _myinstrVector);
	~THREAD_END();
	static void* run(void* arg);
	string *threadoutput;
	void threadMainBody(void* arg);
	void join();
	static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
	int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
};

class BARRIER: public expression{
protected:
public:
	BARRIER(){}
	BARRIER(int l);
	static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
	int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);  
};

class LOCK: public expression{
protected:
	string name;
public:
	LOCK(){}
	LOCK(int l, string _name);
	static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
	int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);	
};

class UNLOCK: public expression{
protected:
	string name;
public:
	UNLOCK(){}
	UNLOCK(int l, string _name);
	static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
	int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);	
};

class JMP: public expression{
	protected:
	 	string name;
	public:
		JMP(){}
		JMP(int l, string n);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		string getname();
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);	 
                
};

//child classes of JMP uses the string name that JMP has in addition to a value or two to apply conditions on
class JMPZ: public JMP{
	protected:
		string value;
	public:
		JMPZ(){}
		JMPZ(int l, string n, string v);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		string getvalue();
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class JMPNZ: public JMP{
	protected:
		string value;
	public:
		JMPNZ(){}
		JMPNZ(int l, string n, string v);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		string getvalue();
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class JMPGT: public JMP{
	protected:
		string first;
		string second;
	public:
		JMPGT(){}
		JMPGT(string f, string s, int l, string n);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		string getfirst();
		string getsecond();
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class JMPLT: public JMPGT{
	protected:
	public:
		JMPLT(){}
		JMPLT(string f, string s, int l, string n);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class JMPGTE: public JMPGT{
	protected:
	public:
		JMPGTE(){}
		JMPGTE(string f, string s, int l, string n);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class JMPLTE: public JMPGT{
	protected:
	public:
		JMPLTE(){}
		JMPLTE(string f, string s, int l, string n);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class SLEEP: public expression{
	protected:
	 	long value;
	public:
		SLEEP(){}
		SLEEP(int l, long v);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		long getvalue();
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class SET_STR_CHAR: public expression{
	protected:
	 	vector <string> myparameters;
	public:
		SET_STR_CHAR(){}
		SET_STR_CHAR(int l, vector<string> myparameters);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class GET_STR_CHAR: public expression{
	protected:
	 	vector <string> myparameters;
	public:
		GET_STR_CHAR(){}
		GET_STR_CHAR(int l, vector<string> myparameters);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class VAR: public expression{

	protected:
		string name;
		pthread_mutex_t lock;
		pthread_mutex_t explicitlock;
	public:
		VAR(){}
		~VAR();
		VAR(int l, string n);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		virtual string getname();
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
		void locking();
		void unlocking();
                
};

class CHAR: public VAR{
	protected:
		char value;
	public:
		CHAR(){}
		CHAR(int l, string n, char v);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		char getvalue();
		void setvalue(char v);
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class NUMERIC: public VAR{
	protected:
		long value;
	public:
		NUMERIC(){}
		NUMERIC(int l, string n, long v);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		long getvalue();
		void setvalue(long v);
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class REAL: public VAR{
	protected:
		double value;
	public:
		REAL(){}
		REAL(int l, string n, double v);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		double getvalue();
		void setvalue(double v);
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
};

class STRING: public VAR{
	protected:
		string value;
	public:
		STRING(){}
		STRING(int l, string n, string v);
		static int valid(vector<string> &tokens, vector<expression*> &instrVector, vector<expression*> &varVector, string &error, bool &accept);	                
		string getvalue();
		void setvalue(string v);
		int execute(vector<expression*> &instrVector, vector<expression*> &varVector, string &outputs);   
                
		
};

#endif /* INSTRUCTION_H */


