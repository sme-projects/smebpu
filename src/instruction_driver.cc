#include <iostream>
#include <libsme/sme.h>

#include "alu.h"
#include "instruction_driver.h"

void Instructions::step() {

  if (rd_wait->read() == 1 && need_rd_wait == 1) {
    need_rd_wait = 0;
  }
  if (wr_wait->read() == 1 && need_wr_wait == 1) {
    need_wr_wait = 0;
  }
  if (ex_wait->read() == 1 && need_ex_wait == 1) {
    need_ex_wait = 0;
  }

  if ((need_ex_wait | need_rd_wait | need_wr_wait) == 0 && !terminate) {

    // TODO: Make sure we increment the PC correctly
    Ucode cur = program[pc];
    Ucode next = program[++pc];
    //std::cout << "Opcode " << cur.opcode << std::endl;
    if (next.opcode == FIN) {
      std::cout << "Finished" << std::endl;
      terminate = true;

      need_rd_wait = 0;
      need_wr_wait = 0;
      need_ex_wait = 0;
    } else {
      need_rd_wait = next.rd_wait;
      need_wr_wait = next.wr_wait;
      need_ex_wait = next.ex_wait;
    }

    wr_mem_valid->write(cur.wr_mem_valid);
    wr_mem_cnt->write(cur.wr_mem_cnt);
    wr_mem_adr->write(cur.wr_mem_adr);
    wr_mem_reg->write(cur.wr_mem_reg);

    rd_mem_valid->write(cur.rd_mem_valid);
    rd_mem_cnt->write(cur.rd_mem_cnt);
    rd_mem_adr->write(cur.rd_mem_adr);
    rd_mem_reg->write(cur.rd_mem_reg);

    ex_valid->write(cur.ex_valid);
    opcode->write(cur.opcode);
    src_reg1->write(cur.src_reg1);
    src_reg2->write(cur.src_reg2);
    dst_reg->write(cur.dst_reg);
    ex_cnt->write(cur.ex_cnt);

  } else {
    //std::cout << "We wait" << std::endl;
    wr_mem_valid->write(0);
    rd_mem_valid->write(0);
    ex_valid->write(0);
  }

}
