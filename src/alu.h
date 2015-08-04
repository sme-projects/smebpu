// -*- mode: c++ -*-
#ifndef SMEBPU_ALU_H
#define SMEBPU_ALU_H

#include <libsme/sme.h>

enum Opcode {NOP, ADD, SUB, MUL, DIV, FIN};

class ALU: public SyncProcess {
private:
  Bus* op1;
  Bus* op2;
  Bus* opcode;

  Bus* result;

public:
  ALU(Name, Busses, Busses);
protected:
  void step();
};

#endif //SMEBPU_ALU_H
