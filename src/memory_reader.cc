#include <libsme/sme.h>

#include "memory.h"
#include "memory_reader.h"

void MemoryReader::step() {

  int ret;

  if (pending_read) {
    ret = mem->fetch_read(1, reqid, pending_cnt);

    if (ret > 0) {
      rd_mem_valid_out->write(1);
      rd_mem_reg_out->write(pending_reg);
      rd_mem_data_out->write(ret);
      pending_read = 0;
    }
  } else {
    rd_mem_valid_out->write(0);
  }

  // Set next op from opcode
  if (cnt == 0 && rd_mem_valid_in->read() == 1) {
    cnt = rd_mem_cnt_in->read();
    adr = rd_mem_adr_in->read();
    reg = rd_mem_reg_in->read();

    if (cnt <= 1)
      rdy = 1;

  }

  if (cnt != 0 && pending_read == 0) {
    ret = mem->enqueue_read(1, cnt, adr);
    reqid = ret;
    pending_read = 1;
    pending_cnt = cnt;
    pending_reg = reg;

    adr++;
    reg++;
    cnt--;

    rdy |= cnt == 1;

  }

  rd_mem_rdy_out->write(rdy);
}
