#include <libsme/sme.h>

class RegisterFile: public SyncProcess {
private:
  Bus* rd_mem_valid_in;
  Bus* rd_mem_data_in;
  Bus* rd_mem_reg_in;

  Bus* wr_mem_valid_in;
  Bus* wr_mem_reg_in;

  Bus* ex_reg1_in;
  Bus* ex_reg2_in;

  Bus* ex_valid_in;
  Bus* ex_reg_in;
  Bus* ex_reg_data;

  Bus* wr_mem_data_out;

  Bus* ex_data1_out;
  Bus* ex_data2_out;

  char* regstor;

public:
  RegisterFile(Name name, Busses ins, Busses outs, char* regstor)
    :SyncProcess(name, ins, outs), regstor{regstor} {
    Bus::assign(ins, {&rd_mem_valid_in, &rd_mem_data_in, &rd_mem_reg_in,
          &wr_mem_valid_in, &wr_mem_reg_in, &ex_reg1_in, &ex_reg2_in,
          &ex_valid_in, &ex_reg_in, &ex_reg_data});
    Bus::assign(outs, {&wr_mem_data_out, &ex_data1_out, &ex_data2_out});
  }

protected:
  void step();

};
