#include "memdump.h"

static uint_fast16_t 
memory_char(
    uint_fast16_t val)
    {
        return (val >= 0x20 && val < 0x80) ? val : '.';
}

void
memory_dump(
    const void* start,
    const void* end
) {
    printf("memory dump from 0x%016x to 0x%016x\n", start, end);

    uint8_t *p = (uint8_t*) start;

    while (p < (uint8_t *)end)
    {
        uint_fast16_t offset = (uint64_t)p & 0xffff;
        printf("%04x:  "
                "%02x %02x %02x %02x  "
                "%02x %02x %02x %02x  "
                "%02x %02x %02x %02x  "
                "%02x %02x %02x %02x  "
                "%c%c%c%c%c%c%c%c"
                "%c%c%c%c%c%c%c%c\n",
                offset,
                p[0x0], p[0x1], p[0x2], p[0x3],
                p[0x4], p[0x5], p[0x6], p[0x7],
                p[0x8], p[0x9], p[0xa], p[0xb],
                p[0xc], p[0xd], p[0xe], p[0xf],
                memory_char(p[0x0]), memory_char(p[0x1]),
                memory_char(p[0x2]), memory_char(p[0x3]),
                memory_char(p[0x4]), memory_char(p[0x5]),
                memory_char(p[0x6]), memory_char(p[0x7]),
                memory_char(p[0x8]), memory_char(p[0x9]),
                memory_char(p[0xa]), memory_char(p[0xb]),
                memory_char(p[0xc]), memory_char(p[0xd]),
                memory_char(p[0xe]), memory_char(p[0xf]));

        p += 16;
    }
}
