#include <iostream>
#include <libsme/sme.h>

#include "alu.h"

ALU::ALU (Name name, Busses ins, Busses outs)
    :SyncProcess(name, ins, outs) {
    Bus::assign(ins, {&op1, &op2, &opcode},
                outs,{&result});
  }

void ALU::step() {
  switch(opcode->read()) {
  case ADD:
    result->write(op1->read() + op2->read());
    break;
  case SUB:
    result->write(op1->read() - op2->read());
    break;
  case MUL:
    result->write(op1->read() * op2->read());
    break;
  case DIV:
    result->write(op1->read() / op2->read());
    break;
  case NOP:
    break;
  }
  //std::cout << "ALU incoming values " << op1->read() << " " << op2->read() << " " << opcode->read() << std::endl;
}
