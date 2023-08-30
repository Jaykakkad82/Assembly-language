//
// Created by jayka on 11/29/2022.
//

#ifndef PROJECT4_CPP_ALI_HARDWARE_H
#define PROJECT4_CPP_ALI_HARDWARE_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iterator>

class Instruction;          // This is a forward declaration - With this we can use pointer to Instruction classes.

using namespace std;


class Hardware {
protected:
// data members : two memory array/vector, register_a,
// register_b, data_pointers, source_pointer , symbol table, zeros, pc, overflow

Instruction* source_memory[128];
int data_mem[128] ;

int pc {0};
int overflow{0};
int zeros {0};
int data_pointer {0};
int source_pointer {0};
int register_a {0};
int register_b {0};
size_t msize {128};

public:
    map<string,int> symbol_table;

// Constructors
Hardware();

// Destructors
~ Hardware();

// getter and setters for Source and Data memory
void set_source(int index, Instruction*ptr );
Instruction* get_source(int index );

void set_data(int index, int datapoint);
int get_data(int index);

void set_pc(int val);
int get_pc();
void increment_pc();


void set_Dpointer(int val);
int get_Dpointer();
void increment_Dpointer();

void set_Spointer(int val);
int get_Spointer();
void increment_Spointer();

void set_registerA(int val);
int get_registerA();

void set_registerB(int val);
int get_registerB();

void overflow_set1();
void overflow_set0();
int overflow_get();


void zeros_set1();
void zeros_set0();
int zeros_get();


    };


#endif //PROJECT4_CPP_ALI_HARDWARE_H
