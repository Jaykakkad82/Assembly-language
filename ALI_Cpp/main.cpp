//
//=================== Created by Jaykumar Kakkad - ASSEMBLY LEVEL INTERPRETER using C++ ======================

//===>> DESIGN CHOICES:
//**  "Command Line Design pattern" is used to implement the problem. Based on this design, we created below classes:::
//** "Hardware" class : Is a virtual machine, holds memory, registers and has getters and setters to access/print memory, registers, counter, etc
//** "Instruction" as ABSTRACT SUPER CLASS of SUBCLASSES----> Class DEC, Class STR , and all other instructions
//** "ALI" class: This reads the program and INVOKES appropriates "Instances" of subclasses of instructions and stores them in source code memory.
//** Command line Design ensures that the correct 'instance of Instruction subclass' is selected and stored in the memory

// ===>>> USE OF INHERITANCE and POLYMORPHISM:
// "Every subclass specialized the super-class"
// The Instruction sublcasses DEC, STR and others inherit instance variables - pstring and argvalue. pstring is used to finding the relevant instruction instance. argvalue store argument.
// The subclasses also inherit the PURE virtual method "execute". This method is dynamically bound at runtime in effect implementing Polymorphism.
// Finally, subclasses inherit print method to print the Instructions as string.
// INTERESTINGLY, A Virtual Destructor is implemented for Abstract Instruction classes and its subclass.

//===>> FLOW OF THE PROGRAM
// "ALI" creates an instance of "HARDWARE" class. This instance is passed "BY REFERENCE" as parameter to the Instances of Instructions & its sublcasses
// HENCE, Every instance of "Instruction class & subclasses", operates on the SAME instance of "HARDWARE"
// The Instruction subclass instances are created on the Dynamic HEAP by ALI. Then an Instruction class pointer in HARDWARE program memory is made to points to it.

#include "ALI.h"

int main(){
        ALI a;          // We just create an ALI instance
        a.runit();      // Invoke the runit method which is a command loop
}
