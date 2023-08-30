# Assembly-language
Toy Assembly level language to find difference between C++ and Ruby

# CPP based code
## =>> DESIGN CHOICES:
- "Command Line Design pattern" is used to implement the problem. Based on this design, we created below classes:::
- "Hardware" class : Is a virtual machine, holds memory, registers and has getters and setters to access/print memory, registers, counter, etc
-  "Instruction" as ABSTRACT SUPER CLASS of SUBCLASSES----> Class DEC, Class STR , and all other instructions
-  "ALI" class: This reads the program and INVOKES appropriates "Instances" of subclasses of instructions and stores them in source code memory.
-  Command line Design ensures that the correct 'instance of Instruction subclass' is selected and stored in the memory


## ===>>> USE OF INHERITANCE and POLYMORPHISM:
- "Every subclass specialized the super-class"
-  The Instruction sublcasses DEC, STR and others inherit instance variables - pstring and argvalue. pstring is used to finding the relevant instruction instance. argvalue store argument.
-  The subclasses also inherit the PURE virtual method "execute". This method is dynamically bound at runtime in effect implementing Polymorphism.
-  Finally, subclasses inherit print method to print the Instructions as string.
-  INTERESTINGLY, A Virtual Destructor is implemented for Abstract Instruction classes and its subclass.

## ===>> FLOW OF THE PROGRAM
- "ALI" creates an instance of "HARDWARE" class. This instance is passed "BY REFERENCE" as parameter to the Instances of Instructions & its sublcasses
- HENCE, Every instance of "Instruction class & subclasses", operates on the SAME instance of "HARDWARE"
- The Instruction subclass instances are created on the Dynamic HEAP by ALI. Then an Instruction class pointer in HARDWARE program memory is made to points to it.


## NOTE: 
- You need to input q to exit the command loop. This command also delloactes objects in the Heap
- After 500 iterations, the program will prompt if you want to continue.

# Ruby based code

## ====>>>> DESIGN OF THE CODE
"Command Line Design patter" is used to implement the problem. Based on this design, we created below classes:::
  - "VirtualM" class : Is a virtual machine, holds memory, registers etc and has methods to access/print memory, registers, counter, etc
  -  "Instruction" as SUPER CLASS of SUBCLASSES----> Class DEC, Class STR , and all other instructions
  -  "ALI" class: This reads the program and stores "Instances" of instructions in source code memory, Also Executes based on the prompt
  -  Command line Design ensures that the correct 'instance of Instruction' is selected and stored in the memory; The arguments are also stored

 ## ===>>> USE OF INHERITANCE:
"Every subclass specialized the super-class"
 - The sublcasses DEC, STR, etc inherit instance variables. string_val is used to finding the relevant instruction instance.
 - The subclasses also inherit the method "execute" and further refines it. (incrementing the program counter is executed in Superclass)
 - to_s method is inherited to print the strings

## ===>> FLOW OF THE PROGRAM
 - "ALI" creates an instance of "VirtualM" class. This instance is passed as parameter to the Instances of Instructions & its sublcasses
 - Hence, Every instance of "Instruction class & subclasses", operates on the SAME instance of "VirtualM"
 - The flow of the program/ execution is driven by the value of the Program counter
