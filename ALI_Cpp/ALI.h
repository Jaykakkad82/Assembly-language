//
// Created by jayka on 11/29/2022.
//

#ifndef PROJECT4_CPP_ALI_ALI_H
#define PROJECT4_CPP_ALI_ALI_H

#include "Instruction.h"
#include "subclasses.h"
#include "Hardware.h"
#include <vector>
#include <string>
#include <fstream>
#include<sstream>
using namespace std;

class ALI {
//data members:  Command array, input_array, vm - memory instance, input-command
public:
vector<string> input_array;
Hardware vm;
string input_cmd;


// member function : Print, Constructor , read_file, select_command, invoker, run_it,
ALI ();
~ALI();

void read_file();
Instruction* select_command(string str);
void invoker();
void runit();
void print_memory();
//
};


#endif //PROJECT4_CPP_ALI_ALI_H
