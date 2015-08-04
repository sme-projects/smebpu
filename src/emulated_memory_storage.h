#ifndef BPU_EMULATED_STORAGE_H
#define BPU_EMULATED_STORAGE_H

#include "typedefs.h"
#include "bpu_config.h"

void enqueue_dma_read_operation(data_t* memory, bit_t valid, uint32_t cnt, memadr_t memadr, uint32_t* reqid);

void fetch_dma_read_operation(data_t* memory, bit_t valid_in, uint32_t reqid, uint32_t cnt, bit_t* valid_out, data_t* data);

void enqueue_dma_write_operation(data_t* memory, bit_t valid_in, uint32_t cnt, memadr_t memadr, data_t data, bit_t* valid_out, uint32_t* reqid);

void fetch_dma_write_operation(data_t* memory, bit_t valid_in, uint32_t reqid, uint32_t cnt, bit_t* valid_out);

#endif
