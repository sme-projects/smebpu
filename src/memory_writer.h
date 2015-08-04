// -*- mode: c++ -*-
#ifndef MEMORY_WRITER_H
#define MEMORY_WRITER_H

#include <libsme/sme.h>

#include "memory.h"

constexpr int BUFFER_SIZE = 2;


class MemoryWriter: public SyncProcess {
private:

  Memory* mem;

  Bus* wr_mem_valid_in;
  Bus* wr_mem_adr_in;
  Bus* wr_data_in;

  Bus* wr_mem_available_out;

  struct buffer_item {
    unsigned adr;
    char data;
  };

  struct buffer_item buffer[BUFFER_SIZE];
  unsigned buffer_start = 0;
  unsigned buffer_fill_count = 0;

  bool pending_write = false;
  unsigned pending_reqid = 0;


public:
  MemoryWriter(Name name, Busses ins, Busses outs, Memory* mem)
    :SyncProcess(name, ins, outs), mem{mem} {
    Bus::assign(ins, {&wr_mem_valid_in, &wr_mem_adr_in,
          &wr_data_in});
    Bus::assign(outs, {&wr_mem_available_out});
  }

protected:
  void step();
};

#endif //MEMORY_WRITER_H
