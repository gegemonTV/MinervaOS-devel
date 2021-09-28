#include "ioapic.h"
#include <stdio.h>
#include "../cpu/cpu_io.h"

uint8_t *g_ioApicAddress;

static void
io_apic_out(
    uint8_t *base,
    uint8_t reg,
    uint32_t val)
{
    MmioWrite32(base + IOREGSEL, reg);
    MmioWrite32(base + IOWIN, val);
}

static uint32_t
io_apic_in(
    uint8_t *base,
    uint8_t reg)
{
    MmioWrite32(base + IOREGSEL, reg);
    return MmioRead32(base + IOWIN);
}

void
io_apic_set_entry(
    uint8_t* base,
    uint8_t index,
    uint64_t data)
    {
        io_apic_out(base, IOREDTBL + index * 2, (uint32_t)data);
        io_apic_out(base, IOREDTBL + index * 2 + 1, (uint32_t)(data >> 32));
    }

void
io_apic_init()
{
    uint32_t x = io_apic_in(g_ioApicAddress, IOAPICVER);

    uint16_t count = ((x >> 16) & 0xff) + 1;    // maximum redirection entry

    printf("I/O APIC pins = %d\n", count);

    for (uint16_t i = 0; i < count; ++i){
        io_apic_set_entry(g_ioApicAddress, i, 1 << 16);
    }
}