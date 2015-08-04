#include <libsme/sme.h>

#include "memory_writer_feeder.h"

void MemoryWriterFeeder::step() {
  if (cnt == 0 && mem_valid_in->read() == 1) {
    cnt = mem_cnt_in->read();
    adr = mem_adr_in->read();
    reg = mem_reg_in->read();

    if (cnt <= 1)
      rdy = 1;
  }

  mem_reg_out->write(reg);
  mem_adr_out->write(adr);

  if (cnt != 0 && mem_writer_free->read() == 1) {
    mem_valid_out->write(1);
    cnt--;
    reg++;
    adr++;

    rdy |= cnt == 1;
  } else {
    // Send same value on busses destined for RegisterFile and MemoryWriter
    mem_valid_out->write(0);
    mem_valid_out_delayed->write(0);
  }

  wr_rdy->write(rdy);
}
