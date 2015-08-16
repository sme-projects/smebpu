#ifndef MEMORY_READER_H
#define MEMORY_READER_H

#include "memory.h"

class MemoryReader: public SyncProcess {
private:

  //Bus* rd_mem_rdy_in;
  Bus* rd_mem_valid_in;
  Bus* rd_mem_reg_in;
  Bus* rd_mem_adr_in;
  Bus* rd_mem_cnt_in;

  Bus* rd_mem_rdy_out;
  Bus* rd_mem_valid_out;
  Bus* rd_mem_data_out;
  Bus* rd_mem_reg_out;


  unsigned int cnt = 0;
  unsigned int reg = 0;
  unsigned int adr = 0;
  unsigned int reqid = 0;
  bool pending_read = false;

  unsigned int pending_cnt = 0;
  unsigned int pending_reg = 0;

  unsigned rdy = 0;

  Memory* mem;

public:
  MemoryReader(Name name, Busses ins, Busses outs, Memory* mem)
    :SyncProcess(name, ins, outs), mem{mem} {

    Bus::assign(ins, {&rd_mem_valid_in,
          &rd_mem_reg_in, &rd_mem_adr_in, &rd_mem_cnt_in});
    Bus::assign(outs, {&rd_mem_rdy_out, &rd_mem_valid_out,
          &rd_mem_data_out, &rd_mem_reg_out});
  }
protected:
  void step();
};

#endif //MEMORY_READER_H
