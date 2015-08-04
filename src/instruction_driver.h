// -*- mode: c++ -*-
#ifndef SMEBPU_INSTRUCTION_DRIVER_H
#define SMEBPU_INSTRUCTION_DRIVER_H

#include <libsme/sme.h>

struct Ucode   {
  unsigned rd_wait;
  unsigned wr_wait;
  unsigned ex_wait;

  unsigned wr_mem_valid;
  unsigned wr_mem_cnt;
  unsigned wr_mem_adr;
  unsigned wr_mem_reg;

  unsigned rd_mem_valid;
  unsigned rd_mem_cnt;
  unsigned rd_mem_adr;
  unsigned rd_mem_reg;

  unsigned ex_valid;
  unsigned opcode;
  unsigned src_reg1;
  unsigned src_reg2;
  unsigned dst_reg;
  unsigned ex_cnt;
};



class Instructions: public SyncProcess {
private:

  Bus* rd_wait;
  Bus* wr_wait;
  Bus* ex_wait;

  Bus* wr_mem_valid;
  Bus* wr_mem_cnt;
  Bus* wr_mem_adr;
  Bus* wr_mem_reg;

  Bus* rd_mem_valid;
  Bus* rd_mem_cnt;
  Bus* rd_mem_adr;
  Bus* rd_mem_reg;

  Bus* ex_valid;
  Bus* opcode;

  Bus* src_reg1;
  Bus* src_reg2;
  Bus* dst_reg;
  Bus* ex_cnt;

  Ucode* program;

  int pc = 0;
  bool terminate = false;

  int need_rd_wait = 0;
  int need_wr_wait = 0;
  int need_ex_wait = 0;

public:
  Instructions(Name name, Busses ins, Busses outs, Ucode* program)
    :SyncProcess(name, ins, outs), program{program} {
    Bus::assign(ins, {&rd_wait,&wr_wait,&ex_wait});
    Bus::assign(outs,
                {&wr_mem_valid,&wr_mem_cnt,&wr_mem_adr,&wr_mem_reg,

                    &rd_mem_valid,&rd_mem_cnt,&rd_mem_adr,&rd_mem_reg,

                    &ex_valid,&opcode,

                    &src_reg1,&src_reg2,&dst_reg,&ex_cnt});
  }
protected:
  void step();
};

#endif //SMEBPU_INSTRUCTION_DRIVER_H
