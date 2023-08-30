//
// Created by jayka on 11/29/2022.
//


#include "Hardware.h"
using namespace std;

Hardware:: ~Hardware()=default;   // default destructor

// ================================================Constructor & Initialization list===============================================
    Hardware::Hardware()
    : data_mem{}, source_memory {} {
   // cout<< "Hardware Constructor executed"<< endl;
    };



//=================================================GETTERS and SETTERS for HARDWARE COMPONENTS ========================================
void Hardware::set_source(int index, Instruction*ptr ){
    if (index>=msize) throw std::out_of_range("Bad idx passed");
    source_memory[index] = ptr;
}
Instruction* Hardware::get_source(int index ){
    if (index>=msize) throw std::out_of_range("Bad idx passed");
    return source_memory[index];
}

void Hardware::set_data(int index, int datapoint){
    if (index>=msize) throw std::out_of_range("Bad idx passed");
    data_mem[index] = datapoint;
}
int Hardware::get_data(int index){
    if (index>=msize) throw std::out_of_range("Bad idx passed");
    return data_mem[index];
}

void Hardware::set_pc(int val){
    pc=val;
}
int Hardware::get_pc(){
    return pc;
}
void Hardware::increment_pc(){
    pc=pc+1;
}


void Hardware::set_Dpointer(int val){
  data_pointer= val;
}
int Hardware::get_Dpointer(){
    return data_pointer;
}
void Hardware::increment_Dpointer(){
    data_pointer = data_pointer+1;
}

void Hardware::set_Spointer(int val){
    source_pointer = val;
}
int Hardware::get_Spointer(){
    return source_pointer;
}
void Hardware::increment_Spointer(){
    source_pointer = source_pointer+1;
}

void Hardware:: set_registerA(int val){
    register_a = val;
}
int Hardware::get_registerA(){
    return register_a;
}

void Hardware::set_registerB(int val){
    register_b = val;
}
int Hardware::get_registerB(){
    return register_b;
}

void Hardware::overflow_set1(){
    overflow =1;
}
void Hardware::overflow_set0(){
    overflow =0;
}

int Hardware::overflow_get(){
    return overflow;
}

void Hardware::zeros_set1(){
    zeros=1;
}
void Hardware::zeros_set0(){
    zeros=0;
}
int Hardware::zeros_get(){
    return zeros;
}