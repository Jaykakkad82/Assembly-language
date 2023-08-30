//
// Created by jayka on 11/29/2022.
//


#include "ALI.h"


// ====================================== CONSTRUCTOR AND DESTRUCTOR ===============================================
ALI::ALI(){

    //cout<< "ALI Constructor executed"<<endl;
}
ALI::~ALI(){
  //  for(auto obj:vm.source_memory) delete &obj;

   // cout<< "ALI destructor executed"<<endl;
};

// ================================== MEMBER FUNCTIONS ==========================================================

// ====>>>> READ a FILE and STORE IN AN INPUT ARRAY
void ALI::read_file(){
    string filename;
    string line;
    cout<< "Enter filename : ";
    getline(std::cin,filename);                 // USE OF GETLINE and ifstream
    //cout<< endl<<filename <<endl;
    ifstream input( filename );

    while (getline(input, line)) {
        //cout<<line<<endl;
        if (line!="")  input_array.push_back(line);   // INPUT ARRAY has all the lines from the USER CODE
    }
    input.close();

};

// ======>>>>> Splits the command into two parts; Uses Select command method to create instruction subclass instances on heap; Program Memory is then made to point to these instances
void ALI::invoker() {
    string str1,str2{""};
    string delimiter =" ";
    size_t pos= 0;
    Instruction* ptr_cmd{nullptr};

    // Iterate through instrutions
    for(auto mystr:input_array){
    pos=mystr.find(delimiter);
    str1= mystr.substr(0,pos);                  // Split command into Str1 and Str2
    if (pos<mystr.length())  str2=mystr.substr(pos);
    else str2= " ";
    //cout<< str1 << " "<< str2<< endl;
    ptr_cmd = select_command(str1);                 // Invoke select command to create an appropriate subclass Instance
    ptr_cmd->argvalue = str2;
    //ptr_cmd->print();
    vm.set_source(vm.get_Spointer(),ptr_cmd);   // Source memory pointer points to sublcass memory instance
    //vm.source_memory[vm.source_pointer] = ptr_cmd;              //accessing source memory at some location
    vm.increment_Spointer();                                        // accessing source pointer

    }
}

// USES Input string to create an appropriate Instruction subclass instance.
Instruction *ALI::select_command(std::string str) {
    Instruction*temp_ptr= nullptr;

// NOTE: INstances created on HEAP; These instances are destructed at Quit command
if (str=="DEC") temp_ptr = new DEC(vm);
if (str=="LDA") temp_ptr = new LDA(vm);
    if (str=="LDI") temp_ptr = new LDI(vm);
    if (str=="STR") temp_ptr = new STR(vm);
    if (str=="XCH") temp_ptr = new XCH(vm);
    if (str=="JMP") temp_ptr = new JMP(vm);
    if (str=="JZS") temp_ptr = new JZS(vm);
    if (str=="JVS") temp_ptr = new JVS(vm);
    if (str=="ADD") temp_ptr = new ADD(vm);
    if (str=="HLT") temp_ptr = new HLT(vm);
    if (str=="LDB") temp_ptr = new LDB(vm);
    return  temp_ptr;                           // A pointer is returned.
}

// Command Loop is implemented in this method.
void ALI::runit() {
    int iter{0};
    cout<< "==========WELCOME to ASSEMBLY level Interpreter==============="<< endl;
    cout<< "Implemented by Jaykumar Kakkad"<< endl;
    this->read_file();                              // Reads the FILE into an Input Array
    this->invoker();                                // Invokes appropriate instances and stored in Program Memory.

    do {
        cout << "Please enter execution options s: One-line, a: all-lines, q: quit " << endl;
        cin >> input_cmd;
        if (input_cmd=="q") {
            print_memory();
            cout<< "==========YOU ENDED the EXECUTION.. THANK YOU==============="<< endl;

            // Loop to delete all the instances in the HEAP MEMORY
            for (int m=0; m < vm.get_Spointer();m++){
                delete vm.get_source(m);
                vm.set_source(m, nullptr);
            }
            break;                                      // EXIT the Loop
        }
        // ONLY A SINGLE instruction is executed
        else if (input_cmd=="s"){
            if (vm.get_pc()<vm.get_Spointer()){                                           // Checks if we have reached end of program
            vm.get_source(vm.get_pc())->execute();                                     // Execute is invoked - DYNAMIC BINDING
            iter++;
            print_memory();}
            else cout<<"======REACHED HALT OR END Of PROGRAM - Press q to quit=========="<<endl;
        }
        // ALL INSTRUCTION EXECUTED - till we reach end of program of all reach HALT
        else if (input_cmd=="a"){
            while (vm.get_pc()<vm.get_Spointer()){                                  // UNTIL program end is reached.
                vm.get_source(vm.get_pc())->execute();                          // Invokes execute on all the instances in program memory
                iter++;
                if (iter==500)
                {
                    cout << "YOU REACHED 500 iteration - Enter q: to quit or any other letter to continue " << endl;         // After 500 iterations asks if user wants to continue
                    cin >> input_cmd;
                }
                if (input_cmd=="q") break;                          // EXIT if use does not want to continue
            }
            print_memory();
            // USER ENTERS Quit Command - We print details , DELETE HEAP and Exit
            if (input_cmd=="q") {
                cout<< "==========YOU ENDED the EXECUTION.. THANK YOU==============="<< endl;

                // Loop to delete instances in Heap Memory pointed by Instruction pointers in Program Memory.
                for (int m=0; m < vm.get_Spointer();m++){
                    delete vm.get_source(m);
                    vm.set_source(m, nullptr);
                }
                break;}
            }
            cout<<"======REACHED HALT OR END Of PROGRAM - Press q to quit=========="<<endl;

    } while (true);

}


// This method is used to print the state of the PROGRAM.
void ALI::print_memory() {
    cout<<"================================================================="<<endl;
    cout<< "**Register A: "<< vm.get_registerA() <<"       **Register B: "<< vm.get_registerB()<< endl;
    cout<< "**program Counter: "<< vm.get_pc() <<"   **Overflow bit: "<< vm.overflow_get()<<"   **zero bit: "<< vm.zeros_get() << endl;

    cout << "Symbol Table: { ";
    for(auto c: vm.symbol_table) cout<< c.first << "=> "<< c.second+128<<", ";
    cout<<"}"<< endl;
    cout<< "Data Memory:[ ";
    for(int i=0;i<vm.get_Dpointer();++i) cout<<vm.get_data(i)<<", ";
    cout<<"]"<< endl;
    cout << "Variable Values: { ";
    for(auto c: vm.symbol_table) cout<< c.first << "=> "<< vm.get_data(c.second)<<", ";
    cout<<"}"<< endl;
    cout<< "Source Memory: "<< endl;
    for(int i=0;i<vm.get_Spointer();++i) vm.get_source(i)->print();
}