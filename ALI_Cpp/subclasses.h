//
// Created by jayka on 11/29/2022.
//

#ifndef PROJECT4_CPP_ALI_SUBCLASSES_H
#define PROJECT4_CPP_ALI_SUBCLASSES_H

#include "Instruction.h"
//==========================DEC ======================================
class DEC : public Instruction{
public:
    explicit DEC(Hardware & mem_ref);
    virtual void execute() ;
    virtual ~DEC();
};

//==========================LDA ======================================
class LDA : public Instruction{
public:
    explicit LDA(Hardware & mem_ref);
    virtual void execute() ;
    virtual ~LDA();
};

//==========================LDB ======================================
class LDB : public Instruction{
public:
    explicit LDB(Hardware & mem_ref);
    virtual void execute() ;
    virtual ~LDB();
};

//==========================LDI ======================================
class LDI : public Instruction{
public:
    explicit LDI(Hardware & mem_ref);
    virtual void execute() ;
    virtual ~LDI();
};

//==========================STR ======================================
class STR : public Instruction{
public:
    explicit STR(Hardware & mem_ref);
    virtual void execute() ;
    virtual ~STR();
};

//==========================XCH ======================================
class XCH : public Instruction{
public:
    explicit XCH(Hardware & mem_ref);
    virtual void execute() ;
    virtual ~XCH();
};

//==========================JMP ======================================
class JMP : public Instruction{
public:
    explicit JMP(Hardware & mem_ref);
    virtual void execute() ;
    virtual ~JMP();
};

//==========================JZS ======================================
class JZS : public Instruction{
public:
    explicit JZS(Hardware & mem_ref);
    virtual void execute() ;
    virtual ~JZS();
};

//==========================JVS ======================================
class JVS : public Instruction{
public:
    explicit JVS(Hardware & mem_ref);
    virtual void execute() ;
    virtual ~JVS();
};

//==========================ADD ======================================
class ADD : public Instruction{
public:
    explicit ADD(Hardware & mem_ref);
    virtual void execute() ;
    virtual ~ADD();
};
//==========================HLT ======================================
class HLT : public Instruction{
public:
    explicit HLT(Hardware & mem_ref);
    virtual void execute() ;
    virtual ~HLT();
};

#endif //PROJECT4_CPP_ALI_SUBCLASSES_H
