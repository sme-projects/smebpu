#include <libsme/sme.h>

#include "alu.h"
#include "execute_feeder.h"

void ExecuteFeeder::step() {
  bool rdy = 0;

  // Get opcode params
  if (cnt == 0 && valid_in->read() == 1) {
    cnt = repeat_in->read();
    opcode = opcode_in->read();
    src_reg1 = src_reg1_in->read();
    src_reg2 = src_reg2_in->read();
    dst_reg = dst_reg_in->read();

    if (cnt <= 1)
      rdy = 1;
  }

  src_reg2_out->write(src_reg1);
  src_reg2_out->write(src_reg2);
  dst_reg_out->write(dst_reg);

  if (cnt > 0) {
    opcode_out->write(opcode);
    dst_valid_out->write(opcode |= NOP);

    cnt--;
    src_reg1++;
    src_reg2++;
    dst_reg++;

    rdy |= cnt == 1;

  } else {
    opcode_out->write(NOP);
    dst_valid_out->write(0);
  }
  rdy_out->write(rdy);

}
