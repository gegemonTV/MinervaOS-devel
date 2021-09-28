#ifndef _IOAPIC_H
#define _IOAPIC_H

#include <stdint.h>

// Memory mapped registers for IO APIC register access
#define IOREGSEL                        0x00
#define IOWIN                           0x10

// ------------------------------------------------------------------------------------------------
// IO APIC Registers
#define IOAPICID                        0x00
#define IOAPICVER                       0x01
#define IOAPICARB                       0x02
#define IOREDTBL                        0x10


extern uint8_t *g_ioApicAddress;

void io_apic_init();
void io_apic_set_entry(uint8_t, uint8_t, uint64_t);

#endif