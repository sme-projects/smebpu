#include <cstring>

#include <libsme/sme.h>

#include "constants.h"
#include "alu.h"
#include "instruction_driver.h"
#include "memory.h"
#include "memory_reader.h"
#include "memory_writer.h"
#include "memory_writer_feeder.h"
#include "execute_feeder.h"
#include "register_file.h"

int main() {

  // Ucode for our program
  Ucode program[] = {
    {0,0,0, 0,0,0,0, 1,5,0,0, 0,NOP, 0,0,0,0}, // Read 5 elements from adr=0 to reg=0
    {1,0,0, 0,0,0,0, 0,0,0,0, 1,ADD, 0,0,0,5}, // Add from 0-5 into self
    {0,0,1, 0,0,0,0, 0,0,0,0, 1,MUL, 0,0,0,5}, // Mul from 0-5 into self
    {0,0,1, 1,5,0,0, 0,0,0,0, 0,NOP, 0,0,0,0}, // Write 5 elements from reg=0 to adr=0
    {0,1,0, 1,5,5,0, 0,0,0,0, 0,NOP, 0,0,0,0}, // Write 5 elements from reg=0 to adr=5
    {0,1,0, 0,0,0,0, 1,5,5,5, 0,NOP, 0,0,0,0}, // Read 5 elements from adr=5 to reg=5
    {1,0,0, 0,0,0,0, 0,0,0,0, 1,DIV, 5,5,5,5}, // Div 5-10 by 5-10 into 5-10
    {0,0,1, 1,5,5,5, 0,0,0,0, 0,NOP, 0,0,0,0}, // Write 5 elements from reg=0 to adr=5
    {0,1,0, 0,0,0,0, 0,0,0,0, 0,FIN, 0,0,0,0}, // NOOP, wait for mem write
  };

  // Initial memory contents
  //const char contents[] = {1,2,3,4,5};
  const char contents[] = {1,1,1,1,1};
  Memory mem = Memory(MEMORY_SIZE, contents, sizeof(contents));
  char* regstore = new char[REGISTER_FILE_SIZE];
  std::memset(regstore, 0, sizeof(char)*REGISTER_FILE_SIZE);

  Bus op1 = Bus();
  Bus op2 = Bus();
  Bus opcode = Bus();
  Bus result = Bus();

  SME_MKBUS(rd_rdy);
  SME_MKBUS(wr_rdy);
  SME_MKBUS(ex_rdy);

  SME_MKBUS(s1_wr_mem_valid);
  SME_MKBUS(s1_wr_mem_cnt);
  SME_MKBUS(s1_wr_mem_adr);
  SME_MKBUS(s1_wr_mem_reg);

  SME_MKBUS(s1_rd_mem_valid);
  SME_MKBUS(s1_rd_mem_cnt);
  SME_MKBUS(s1_rd_mem_adr);
  SME_MKBUS(s1_rd_mem_reg);

  SME_MKBUS(s1_ex_valid);
  SME_MKBUS(s1_opcode);
  SME_MKBUS(s1_src_reg1);
  SME_MKBUS(s1_src_reg2);
  SME_MKBUS(s1_dst_reg);
  SME_MKBUS(s1_ex_cnt);

  SME_MKBUS(s2_rd_mem_data);
  SME_MKBUS(s2_rd_mem_valid);
  SME_MKBUS(s2_rd_mem_reg);

  SME_MKDBUS(s2_wr_mem_adr, 2);
  SME_MKBUS(s2_wr_mem_valid_1s); // 1 clock to dest
  SME_MKDBUS(s2_wr_mem_valid_2s, 2); // 2 clocks to dest
  SME_MKBUS(s2_wr_mem_reg);

  SME_MKBUS(s2_src_reg1);
  SME_MKBUS(s2_src_reg2);
  SME_MKDBUS(s2_opcode, 2);
  SME_MKBUS(s2_ex_rdy);
  SME_MKDBUS(s2_dst_valid, 3);
  SME_MKDBUS(s2_dst_reg, 3);

  SME_MKBUS(s3_ex_reg1);
  SME_MKBUS(s3_ex_reg2);

  SME_MKBUS(s3_wr_mem_data);

  SME_MKBUS(s4_mem_feedback);
  SME_MKBUS(s4_alu_result);

  // -1 iterations = infinity (until halted)
  auto r = ThreadedRun(-1, 1);
  r.add_proc(new Instructions("instr",
                              {&rd_rdy,&wr_rdy,&s2_ex_rdy},
                              {&s1_wr_mem_valid,&s1_wr_mem_cnt,&s1_wr_mem_adr,&s1_wr_mem_reg,
                                  &s1_rd_mem_valid,&s1_rd_mem_cnt,&s1_rd_mem_adr,&s1_rd_mem_reg,
                                  &s1_ex_valid,&s1_opcode,&s1_src_reg1,&s1_src_reg2,
                                  &s1_dst_reg,&s1_ex_cnt},
                              program,&r));

  // Stage 2
  r.add_proc(new MemoryReader("memread",
                              {&s1_rd_mem_valid, &s1_rd_mem_reg,
                                  &s1_rd_mem_adr, &s1_rd_mem_cnt},
                              {&rd_rdy, &s2_rd_mem_valid,
                                  &s2_rd_mem_data, &s2_rd_mem_reg}, &mem));
  r.add_proc( new MemoryWriterFeeder("memwritefeed",
                                     {&s1_wr_mem_valid, &s1_wr_mem_cnt, &s1_wr_mem_adr,
                                         &s1_wr_mem_reg, &s4_mem_feedback},
                                     {&s2_wr_mem_valid_1s, &s2_wr_mem_valid_2s,
                                       &s2_wr_mem_reg, &s2_wr_mem_adr, &wr_rdy}));
  r.add_proc(new ExecuteFeeder("exec",
                               {&s1_ex_valid, &s1_opcode, &s1_src_reg1,
                                   &s1_src_reg2, &s1_dst_reg, &s1_ex_cnt},
                               {&s2_src_reg1, &s2_src_reg2, &s2_opcode,
                                   &s2_ex_rdy, &s2_dst_reg, &s2_dst_valid}));

  // Stage 3
  r.add_proc(new RegisterFile("regfile",
                              {&s2_rd_mem_valid, &s2_rd_mem_data, &s2_rd_mem_reg,
                                  &s2_wr_mem_valid_1s, &s2_wr_mem_reg, &s2_src_reg1,
                                  &s2_src_reg2, &s2_dst_valid, &s2_dst_reg,
                                  &s4_alu_result},
                              {&s3_wr_mem_data, &s3_ex_reg1, &s3_ex_reg2}, regstore));

  // Stage 4
  r.add_proc(new MemoryWriter("memwrite",
                             {&s2_wr_mem_valid_2s, &s2_wr_mem_adr, &s3_wr_mem_data},
                             {&s4_mem_feedback}, &mem));
  r.add_proc(new ALU("alu",
                     {&s3_ex_reg1, &s3_ex_reg2, &s2_opcode},
                     {&s4_alu_result}));
  r.start<BQueue>();
  //r.start();

  std::cout << "Execution halted after " << r.stepcount() << " cycles";

  mem.dump(10);

  return 0;
}
