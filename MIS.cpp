#include "Instruction.h"
#include "MIS.h"
#include "Reader.h"

//constructor that takes a file name and initialize the reader
MIS::MIS(string f):filename(f){
    generatedOutput="";
}

MIS::MIS(){
    generatedOutput="";
}
MIS::~MIS(){
}


