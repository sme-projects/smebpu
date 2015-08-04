// -*- mode: c++ -*-
#ifndef MEMORY_WRITER_FEEDER_H
#define MEMORY_WRITER_FEEDER_H

#include <libsme/sme.h>

class MemoryWriterFeeder: public SyncProcess {
private:
  Bus* mem_valid_in;
  Bus* mem_cnt_in;
  Bus* mem_adr_in;
  Bus* mem_reg_in;
  Bus* mem_writer_free;

  Bus* mem_valid_out;
  Bus* mem_valid_out_delayed;
  Bus* mem_reg_out;
  Bus* mem_adr_out;
  Bus* wr_rdy;

  unsigned cnt = 0;
  unsigned reg = 0;
  unsigned adr = 0;

  bool rdy = false;

public:
  MemoryWriterFeeder(Name name, Busses ins, Busses outs)
    :SyncProcess(name, ins, outs) {
    Bus::assign(ins, {&mem_valid_in, &mem_cnt_in,
          &mem_adr_in, &mem_reg_in, &mem_writer_free});
    Bus::assign(outs, {&mem_valid_out, &mem_valid_out_delayed, &mem_reg_out,
          &mem_adr_out, &wr_rdy});
  }

protected:
  void step();
};

#endif //MEMORY_WRITER_FEEDER_H
