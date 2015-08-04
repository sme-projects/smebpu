// -*- mode: c++ -*-
#ifndef EXECUTE_FEEDER_H
#define EXECUTE_FEEDER_H

#include <libsme/sme.h>

class ExecuteFeeder: public SyncProcess {
private:
  Bus* valid_in;
  Bus* opcode_in;
  Bus* src_reg1_in;
  Bus* src_reg2_in;
  Bus* dst_reg_in;
  Bus* repeat_in;

  Bus* src_reg1_out;
  Bus* src_reg2_out;
  Bus* opcode_out;
  Bus* rdy_out;
  Bus* dst_reg_out;
  Bus* dst_valid_out;

  int cnt = 0;
  int src_reg1;
  int src_reg2;
  int dst_reg;
  int opcode; // = NOP

public:
  ExecuteFeeder(Name name, Busses ins, Busses outs)
    :SyncProcess(name, ins, outs) {
    Bus::assign(ins, {&valid_in, &opcode_in, &src_reg1_in,
          &src_reg2_in, &dst_reg_in, &repeat_in});
    Bus::assign(outs, {&src_reg1_out, &src_reg2_out,
          &opcode_out, &rdy_out, &dst_reg_out, &dst_valid_out});
  }

protected:
  void step();
};

#endif //EXECUTE_FEEDER_H
