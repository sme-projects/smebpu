#ifndef BPU_MEMORY_H
#define BPU_MEMORY_H

class Memory {
private:
  unsigned read_cur_reqid = 0;
  unsigned read_cur_adr = 0;
  unsigned read_delay = 0;

  unsigned write_cur_reqid = 0;
  unsigned write_cur_adr = 0;
  unsigned write_cur_data = 0;
  unsigned write_delay = 0;

  unsigned sim_read_reqid = 0;
  unsigned sim_write_reqid = 0;

  char* data;

public:
  Memory(unsigned size);
  ~Memory();

  int enqueue_read(unsigned valid, unsigned cnt, unsigned addr);
  int fetch_read(unsigned valid_in, unsigned reqid, unsigned cnt);
  int enqueue_write(bool valid_in, unsigned cnt, unsigned adr, char data);
  int fetch_write(unsigned valid_in, unsigned reqid, unsigned cnt);
};

#endif //BPU_MEMORY_H
