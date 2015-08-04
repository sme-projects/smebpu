#include <libsme/sme.h>

#include "register_file.h"

void RegisterFile::step() {

  if (rd_mem_valid_in->read() > 0) {
    regstor[rd_mem_reg_in->read()] = rd_mem_data_in->read();
  }

  if (ex_valid_in->read() > 0) {
    regstor[ex_reg_in->read()] = ex_reg_data->read();
  }

  if (wr_mem_valid_in->read() > 0) {
    regstor[ex_reg_in->read()] = ex_reg_data->read();
  }

  ex_data1_out->write(ex_reg1_in->read());
  ex_data2_out->write(ex_reg2_in->read());

}
