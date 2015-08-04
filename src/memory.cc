#include "memory.h"
#include "constants.h"

Memory::Memory(unsigned size) {
  data = new char[size];
}

Memory::~Memory() {
  delete[] data;
}

int Memory::enqueue_read(unsigned valid, unsigned cnt, unsigned addr) {
  if (valid == 1 && read_delay == 0) {
    sim_read_reqid++;

    read_cur_reqid = sim_read_reqid;
    read_delay = MEMORY_CYCLES_DELAY;
    read_cur_adr = addr;

    return sim_read_reqid;
  }
  return -1;
}

int Memory::fetch_read(unsigned valid_in, unsigned reqid, unsigned cnt) {
  if (read_delay > 0) {
    read_delay--;
  }

  int ret = -1;

  // Return memory byte if request is valid
  if (read_delay == 0 && valid_in == 0 &&
      reqid == read_cur_reqid) {
    ret = data[read_cur_adr];
  }

  return ret;
}


int Memory::enqueue_write(bool valid_in, unsigned cnt, unsigned adr, char data) {
  if (valid_in && write_delay == 0) {

    write_cur_adr = adr;
    write_cur_data = data;
    write_cur_reqid = ++sim_write_reqid;
    write_delay = MEMORY_CYCLES_DELAY;
    return sim_write_reqid;
  }

  return -1;
}

int Memory::fetch_write(unsigned valid_in, unsigned reqid, unsigned cnt) {
  if (write_delay > 0)
    write_delay--;

  if (valid_in == 1 && write_delay == 0 &&
      reqid == write_cur_reqid) {
    data[write_cur_adr] = write_cur_data;
    return 0;
  }
  return -1;
}
