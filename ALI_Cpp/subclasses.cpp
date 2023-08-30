//
// Created by jayka on 11/29/2022.
//

#include "subclasses.h"

//============================DEC =====================================================
void DEC::execute(){
    vm.increment_pc();
   // cout<< "DEC is executed" << endl;
   vm.symbol_table[argvalue]=vm.get_Dpointer();     // Saves the variable in the symbol table and allocates memory
   vm.increment_Dpointer();

}

// Constructor with initialization list
DEC::DEC(Hardware & mem_ref)
:Instruction(mem_ref){
    printstring = "DEC";
}

// Virtual Destructor
DEC::~DEC()=default;

//============================LDA =====================================================

void LDA::execute(){
    vm.increment_pc();
    //cout<< "LDA is executed" << endl;
    vm.set_registerA(vm.get_data(vm.symbol_table[argvalue]));               // Sets value of RegisterA with value of Variable (argument)
}

// LDA constructor with initialization list
LDA::LDA(Hardware & mem_ref)
        :Instruction(mem_ref){
    printstring = "LDA";
};
LDA::~LDA()=default;

//============================LDB =====================================================
void LDB::execute(){
    vm.increment_pc();
   // cout<< "LDB is executed" << endl;
   vm.set_registerB(vm.get_data(vm.symbol_table[argvalue]));                // Sets value of RegisterB with value of Variable (argument)
   //vm.register_b = vm.data_mem[vm.symbol_table[argvalue]];
}

// LDB constructor
LDB::LDB(Hardware & mem_ref)
        :Instruction(mem_ref){
    printstring = "LDB";
};
LDB::~LDB()=default;

//============================LDI =====================================================
void LDI::execute(){
    vm.increment_pc();
   // cout<< "LDI is executed" << endl;
    //vm.register_a= stoi( argvalue );
    vm.set_registerA(stoi( argvalue ));                                 // Sets value of RegisterA with value of argument
}

LDI::LDI(Hardware & mem_ref)
        :Instruction(mem_ref){
    printstring = "LDI";
};
LDI::~LDI()=default;

//============================STR =====================================================
void STR::execute(){
    vm.increment_pc();
    //cout<< "STR is executed" << endl;
    //vm.data_mem[vm.symbol_table[argvalue]]=vm.register_a;
    vm.set_data(vm.symbol_table[argvalue],vm.get_registerA());      // stores value of register A in Data Memory pointed by variable
}

// Constructor with an Initialization list
STR::STR(Hardware & mem_ref)
        :Instruction(mem_ref){
    printstring = "STR";
};
STR::~STR()=default;

//============================XCH =====================================================
void XCH::execute(){
    vm.increment_pc();
    //cout<< "XCH is executed" << endl;
    int temp{0};
    temp = vm.get_registerA();
    vm.set_registerA(vm.get_registerB());                           // switches values of register A and register B using a temporary variable
    vm.set_registerB(temp);
//vm.register_b = temp;

}

XCH::XCH(Hardware & mem_ref)
        :Instruction(mem_ref){
    printstring = "XCH";
};
XCH::~XCH()=default;

//============================JMP =====================================================
void JMP::execute(){
    vm.increment_pc();
   // cout<< "JMP is executed" << endl;
    //vm.pc = stoi( argvalue );
    vm.set_pc(stoi( argvalue ));
}

JMP::JMP(Hardware & mem_ref)
        :Instruction(mem_ref){
    printstring = "JMP";
};
JMP::~JMP()=default;
//============================JZS =====================================================
void JZS::execute(){
    vm.increment_pc();
    //cout<< "JZS is executed" << endl;
    if (vm.zeros_get() == 1) vm.set_pc(stoi( argvalue ));
}

JZS::JZS(Hardware & mem_ref)
        :Instruction(mem_ref){
    printstring = "JZS";
}
JZS::~JZS()=default;

//============================JVS =====================================================
void JVS::execute(){
    vm.increment_pc();
   // cout<< "JVS is executed" << endl;
    if (vm.overflow_get() == 1) vm.set_pc(stoi( argvalue ));
}

JVS::JVS(Hardware & mem_ref)
        :Instruction(mem_ref){
    printstring = "JVS";
}
JVS::~JVS()=default;

//============================ADD =====================================================
void ADD::execute(){
    vm.increment_pc();
   // cout<< "ADD is executed" << endl;
    int temp{0};
    temp = vm.get_registerA()+vm.get_registerB();

    if (temp==0) vm.zeros_set1();
    else vm.zeros_set0();

//Checking for Overflow
if (((vm.get_registerA()>0) && (vm.get_registerB()>0)&&(temp<0)) ||((vm.get_registerA()<0) && (vm.get_registerB()<0)&&(temp>0)))
    {vm.overflow_set1();
    temp = vm.get_registerA();}
else vm.overflow_set0();

    vm.set_registerA(temp) ;
}

ADD::ADD(Hardware & mem_ref)
        :Instruction(mem_ref){
    printstring = "ADD";
}
ADD::~ADD()=default;

//============================HLT =====================================================
void HLT::execute(){
    vm.increment_pc();
    //cout<< "HLT is executed" << endl;
    vm.set_pc(vm.get_Spointer()) ;
}

HLT::HLT(Hardware & mem_ref)
        :Instruction(mem_ref){
    printstring = "HLT";
}

HLT::~HLT()=default;