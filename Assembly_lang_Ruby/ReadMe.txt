#===========Project: CS474 - Creating a Assembly level interpreter in Ruby==============================================
# By: Jaykumar Kakkad

# ====>>>> DESIGN OF THE CODE
# "Command Line Design patter" is used to implement the problem. Based on this design, we created below classes:::
# a) "VirtualM" class : Is a virtual machine, holds memory, registers etc and has methods to access/print memory, registers, counter, etc
# b) "Instruction" as SUPER CLASS of SUBCLASSES----> Class DEC, Class STR , and all other instructions
# c) "ALI" class: This reads the program and stores "Instances" of instructions in source code memory, Also Executes based on the prompt
# Command line Design ensures that the correct 'instance of Instruction' is selected and stored in the memory; The arguments are also stored

# ===>>> USE OF INHERITANCE:
# "Every subclass specialized the super-class"
# The sublcasses DEC, STR, etc inherit instance variables. string_val is used to finding the relevant instruction instance.
# The subclasses also inherit the method "execute" and further refines it. (incrementing the program counter is executed in Superclass)
# to_s method is inherited to print the strings

#===>> FLOW OF THE PROGRAM
# "ALI" creates an instance of "VirtualM" class. This instance is passed as parameter to the Instances of Instructions & its sublcasses
# Hence, Every instance of "Instruction class & subclasses", operates on the SAME instance of "VirtualM"
# The flow of the program/ execution is driven by the value of the Program counter