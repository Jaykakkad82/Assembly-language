//
// Created by jayka on 11/29/2022.
//

#include "Instruction.h"

//========================CONSTRUCTOR OF INSTRUCTION CLASS ====================================
Instruction::Instruction(Hardware & mem_ref)
:printstring {"None"}, argvalue {"None"}, vm{mem_ref}
{
    //std::cout<< "Instruc Constructor executed"<< std::endl;
}

// ============== Destructor ============================
Instruction::~Instruction()=default;

//print method inherited by all subclasses
void Instruction::print(){
    cout<< printstring << " " << argvalue << endl;
}