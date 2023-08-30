//
// Created by jayka on 11/29/2022.
//

#ifndef PROJECT4_CPP_ALI_INSTRUCTION_H
#define PROJECT4_CPP_ALI_INSTRUCTION_H

using namespace std;
#include <iostream>
#include <string>
#include "Hardware.h"
//class Hardware;             //THIS is FORWARD DECLARATION - Need https://stackoverflow.com/questions/8526819/c-header-files-including-each-other-mutually

class Instruction {
public:
    // data members: printstring, argvalue, vm
    string printstring;
    string argvalue;
  Hardware &vm ;


    // Member functions: Constructor(VM as reference parameter) ; Execute (virtual); print(inherited by other fns)
    // Constructor & Destructor
    explicit Instruction(Hardware & mem_ref);
    virtual ~Instruction()=0;       // A VIrtual DESTRUCTOR

    // member functions
    virtual void execute()=0;       // dynamic binding of messages
    void print();

};


#endif //PROJECT4_CPP_ALI_INSTRUCTION_H
