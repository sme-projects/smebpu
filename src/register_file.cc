#include <iostream>
#include <libsme/sme.h>

#include "register_file.h"

void RegisterFile::step() {

  // Save values read from memory
  if (rd_mem_valid_in->read() > 0) {
    regstor[rd_mem_reg_in->read()] = rd_mem_data_in->read();
  }

  // Save ALU result to registers if valid
  if (ex_valid_in->read() > 0) {
    regstor[ex_reg_in->read()] = ex_reg_data->read();
    //std::cout << "Ex saved " << ex_reg_data->read() << " in " << ex_reg_in->read() << std::endl;
  }

  // Forward data to be returned from memory
  if (wr_mem_valid_in->read() > 0) {
    std::cout << "Wrote memory " << (unsigned)regstor[wr_mem_reg_in->read()] << std::endl;
    wr_mem_data_out->write(regstor[wr_mem_reg_in->read()]);
  }

  ex_data1_out->write(regstor[ex_reg1_in->read()]);
  ex_data2_out->write(regstor[ex_reg2_in->read()]);


  //std::cout << "Wrote " << (unsigned)regstor[ex_reg1_in->read()] << " " << (unsigned)regstor[ex_reg1_in->read()] << " from " << ex_reg1_in->read() << " and " << ex_reg2_in->read() << std::endl;
}
