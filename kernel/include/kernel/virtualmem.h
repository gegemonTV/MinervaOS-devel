#ifndef _VIRTUALMEM_H
#define _VIRTUALMEM_H

#include <stdint.h>

#define PAGE_WRITE_THROUGH              0x08    // Page-level write-through
#define PAGE_CACHE_DISABLE              0x10    // Page-level cache-disable

void virtualmem_init();

void* virtualmem_alloc(uint_fast16_t);
void* virtualmem_alloc_align(uint_fast16_t, uint_fast16_t);

void virtualmem_map_pages(void*, uint_fast16_t, uint_fast16_t);

#endif