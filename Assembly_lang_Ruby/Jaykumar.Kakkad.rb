
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

#======================================== Class Virtual Machine ===================================================================

# THis CLASS MAINLY holds all different kinds of MEmory and provides methods to print/Access them
class VirtualM
  attr_accessor :register_a, :register_b, :pc, :zeros, :overflows, :amemory, :data_pointer, :source_pointer, :symbols_t
  def initialize
    @amemory = [0]*256          # 256 words
    @register_a = 0             # 32bit register
    @register_b = 0             # 32bit Additional register
    @pc = 0                     # program counter - saves the next instruction
    @zeros=0                    # if AND produces 0
    @overflows= 0               # if overflow i.e. more than 32bit values from AND

    # pointer to memory
    @data_pointer = 128         # Points to the next free location address in DATA memory
    @source_pointer= 0          # Points to the next free location address in DATA memory

    #symbol table
    @symbols_t = Hash.new       # Maintains Key: Value ===> symbol:address

  end

  # needs accessors for data and source memory
  def read_data addr
    @amemory[addr]
  end

  # checks for overflow whenever writing in Memory
  def write_data data, addr
    # check for oveflow event
    if data > (2**31) or data < (-2**31)
      @overflows =1                            # Set the bit if Overflow
      (@amemory[addr] = (2**31)) if data>0
      (@amemory[addr] = (2**31)) if data<0
    else
      @amemory[addr] = data
      @overflows =0                           # need to set it back to 0
    end
  end

  # Reads the source memory , but limits it till 127
  def read_source addr
    if addr >127
      p "Exceeded source memory boundary of 127"
    else
      return @amemory[addr]
    end

  end

  #Write in source memory
  def write_source sdata
    if @source_pointer<128                          # limits the write to only 127th location
      @amemory[@source_pointer] = sdata
      @source_pointer+=1
    else
      p "Error- source memory usage exceed - cannot write in source memory"         # geneates error message if it goes beyond 127
    end
  end

  # Prints the source memory till the end of program
  def print_source_memory
    if @source_pointer==0
      p "No code in source"
    else
    puts @amemory[0...@source_pointer]        # only till the end of program
    end
  end

  # Increments Program counter till it reaches the end of program
  def increment_pc
    if @pc >= @source_pointer
      p "No more code to execute"
    else
      @pc+=1
    end
  end

  # Prints the SYMBOL table
  def print_source_table
    arr= []
    if @symbols_t.empty?                # checks if its empty
      p "Symbol table empty"
    else
    @symbols_t.each{|k,v| arr+=["#{k} : #{@amemory[v]}"]}       # prints [symbol: Value] by accessing the memory using address stored in symbol table
    puts "Values of Variables are : #{arr}"
    end
  end

  # print all values - memory, registers, source table, etc
  def print_all
    self.print_source_table
    puts "Register A: #{self.register_a}, Register B: #{self.register_b}, Program_Counter: #{self.pc}, Overflow #{self.overflows}, Zeros #{self.zeros}"
    puts "Data memory in use: #{self.amemory[128...@data_pointer]}"
    puts "Source code in use:"
    self.print_source_memory
  end
end

#========================= INSTRUCTIONS as SUPERCLASS and each instruction as SUBCLASS ==========================

#ABSTRACT CLASS
class Instructions
  attr_accessor :string_val, :args

  def initialize avirtualm
    @vm = avirtualm                           # a virtual Machine instance is taken as an argument; so the same instance is modified by each sublcass
    @string_val = ""                          # used to select the command in ALI (command line design)
    @args = nil
  end

  #Method is refined in each subclass
  def execute
    @vm.increment_pc                          # this is common to every sub-class, hence it is executed here and subclasses refine it further
  end

  # printing method - Inherited by all the subclasses
  def to_s
    "#{self.class} #{@args}"
  end
end

#==========> SUBCLASSES of INSTRUCTION Class <=========
# Declare Instruction
class DEC < Instructions
  def initialize avirtualm
    super
    @string_val = "DEC"             # used to select the command in ALI (command line design)
    @args = nil                     # Argument is fed to the instance before it is stored in the memory
  end

  def execute
    super                                               # executes statements in Superclass's method first
    #p "Executing DEC with args #{@args}"
    @vm.symbols_t[@args] = @vm.data_pointer             # symbol is place in symbol table and memory is allocated
    @vm.data_pointer+=1
  end
end

# Load A
class LDA < Instructions
  def initialize avirtualm
    super
    @string_val = "LDA"
    @args = nil
  end

  def execute
    super
    #p "Executing LDA with args #{@args}"
    @vm.register_a = @vm.read_data( @vm.symbols_t[@args])       # register A gets the value from address of Symbol
  end
end

# Load B
class LDB < Instructions
  def initialize avirtualm
    super
    @string_val = "LDB"
    @args = nil
  end

  def execute
    super
    #p "Executing LDB with args #{@args}"
    @vm.register_b = @vm.read_data( @vm.symbols_t[@args])     # register B gets the value from address of Symbol
  end
end

# load integer into register A
class LDI < Instructions
  def initialize avirtualm
    super
    @string_val = "LDI"
    @args = nil
  end
  def execute
    super
    #p "Executing LDI with args #{@args}"
    @vm.register_a = @args.to_i     #  just loads the register A with the integer value (after converting to int type)
  end
end

# Load value of register_a into the variable's memory (points to data memory)
class STR < Instructions
  def initialize avirtualm
    super
    @string_val = "STR"
    @args = nil
  end

  def execute
    super
    #p "Executing STR with args #{@args}"
    addr = @vm.symbols_t[@args]               # memory address of variable/symbol
    val = @vm.register_a                      # value of the register a
    @vm.write_data val, addr                  # writing it into data memory
  end
end

# Xchange values of register_a and register_b
class XCH < Instructions
  def initialize avirtualm
    super
    @string_val = "XCH"
    @args = nil
  end

  def execute
    super
    #p "Executing XCH with args #{@args}"
    temp=@vm.register_a                         # exchange temp=a, a=b, b=temp
    @vm.register_a = @vm.register_b
    @vm.register_b = temp
  end
end

# Jump to a specific line (infamous go-to)
class JMP < Instructions
  def initialize avirtualm
    super
    @string_val = "JMP"
    @args = nil
  end

  def execute
    super
    #p "Executing JMP with args #{@args}"
    @vm.pc = @args.to_i                           # the program counter is updated -- changes the flow of control
  end
end

#
class JZS < Instructions
  def initialize avirtualm
    super
    @string_val = "JZS"
    @args = nil
  end

  def execute
    super
    # p "Executing JZS with args #{@args}"
    if @vm.zeros == 1                            # only if register A is zero. i.e zero bit =1 :
      @vm.pc = @args.to_i                       # the program counter is updated -- changes the flow of control
    end
  end
end

class JVS < Instructions
  def initialize avirtualm
    super
    @string_val = "JVS"
    @args = nil
  end
  def execute
    super
    #p "Executing JVS with args #{@args}"
    if @vm.overflows == 1                     # only if overflow is 1 ; that is number exceeds the +/- 2**31 range
      @vm.pc = @args.to_i                     # the program counter is updated -- changes the flow of control
    end
  end
end

# Adds the two registers - a & b and stores value in a
class ADD < Instructions
  def initialize avirtualm
    super
    @string_val = "ADD"
    @args = nil
  end

  def execute
    super
    #p "Executing ADD with args #{@args}"
    temp = @vm.register_a + @vm.register_b
    # 1) Check for zero
    if temp==0
      @vm.zeros = 1   # set to 1 if zero found
    else
      @vm.zeros = 0     # reset
    end

    # 2) check for overflow
    if temp > (2**31) or temp < (-2**31)        # if overflow
      @vm.overflows =1                           # overflow bit =1 and..
      (temp = (2**31)) if temp>0                # .. register A = max range value
      (temp = -(2**31)) if temp<0
    else
      @vm.overflows =0
    end
    # after all checks, set the register a value
    @vm.register_a = temp
  end
end

# halts the program execution
class HLT < Instructions
  def initialize avirtualm
    super
    @string_val = "HLT"
    @args = nil
  end
  def execute
    super
    #p "Executing HLT with args #{@args}"
  end
end

#=======================================CLASS ADL  -- Assembly level Interpreter ====================================================

# The interpreter class is an interface between Memory, Instructions and the User
class ALI
  def initialize
    @input_array=[]
    @vm = VirtualM.new                                  # intiates  virtual memory instance which is passed to instructions for operations
    # commands array is used to implement the command level design; it stores instruction instances
    @command_array = [DEC.new(@vm),LDA.new(@vm),LDB.new(@vm), LDI.new(@vm), HLT.new(@vm)]          # Note - all instruction instances work on same VM instance
    @command_array += [STR.new(@vm), XCH.new(@vm), JMP.new(@vm), JZS.new(@vm), JVS.new(@vm), ADD.new(@vm)]
  end

  # the method reads program file and store in an input-array
  def read_file
    p "=======Enter the FILE NAME with directory======; eg:C:/Users/jayka/OneDrive/Desktop/UIC/CS474/project2_Ruby_Interpreter/test_program.txt"
    filename = gets.chomp
    aFile = File.new(filename, "r")
    @input_array= aFile.readlines           # each line is an array element
    aFile.close
  end

  # the Method is used to SELECT the Command INStruction based on the @string_val of instruction instance
  def select_command str
    #p str
    for obj in @command_array
      if obj.string_val == str            # compares object's string value with the argument str
        return obj                        # returns the object when it finds a match
      end
    end
  end

  # the method processes the array element + Uses select_command to find an instance + stores that instance in source memory
  def invoker
    for items in @input_array
      items.rstrip!
      items = items.split(" ")        # items[0] is the str argmenet

      # what if there is no argument
      if items.length ==1
        args = nil          # we pass nil if no item[1] exists; makes the instruction class consistent
      else
        args= items[1]      # else pass item[1]
      end

      # Selects the correct instance
      obj = self.select_command items[0]
      obj = obj.class.new @vm             # reinitiates the instance ; this is because use of same command_array element creates reference to same object
      obj.args = args                     # stores the argument in the instance
      @vm.write_source obj                # stores the instance in the source memory

    end
  end

  # this method executes the command prompt for user and is an interface
  def runit
    p "===========This is Assembly level interpreter==================="
    p " Project implementation by Jaykumar Kakkad"
    self.read_file              # read file
    self.invoker                # ready the source memory with commands

    puts "Please enter execution options s: One-line, a: all-lines, q: quit "
    @input_cmd = gets.chomp
    i=0
    while @input_cmd!="q"                     # THE COMMAND LOOP
      # =============== for prompt 's'=============
      if @input_cmd == 's'
        obj = @vm.read_source(@vm.pc)
        obj.execute
      end
      # ========= for prompt 'a' ============
      if @input_cmd == 'a'
        while @vm.pc< @vm.source_pointer
          break if i>2500
          obj = @vm.read_source(@vm.pc)
          obj.execute
          i+=1
        end
      end
      # Check for infinite loops - Limit set at 2500
      i+=1
      if i>25000
        puts "TIMEOUT: Exceeded 2500 instructions limit "
        break
      end
      if @vm.pc >= @vm.source_pointer
        p "=================================================================="
        @vm.print_all
        puts "=======No more code to execute, Press 'q' to exit execution========="
        else
          p "=================================================================="
          @vm.print_all
          puts "Please enter execution options s: One-line, a: all-lines, q: quit "
      end
      @input_cmd = gets.chomp
    end
  end
end


#p Dir.pwd
#Dir.chdir("C:/Users/jayka/OneDrive/Desktop/UIC/CS474/project2_Ruby_Interpreter")
#p Dir.pwd
a = ALI.new
a.runit
