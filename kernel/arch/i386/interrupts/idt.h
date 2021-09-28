#ifndef _IDT_H
#define _IDT_H

#include <stdint.h>

#define INTERRUPT_GATE              0x8e00
#define TRAP_GATE                   0x8f00

struct IdtDesc
{
    uint16_t limit;
    uint64_t base;
} PACKED;

typedef struct IdtDesc IdtDesc;

typedef struct IdtEntry
{
    uint16_t offset0;
    uint16_t selector;
    uint16_t type;
    uint16_t offset1;
    uint32_t offset2;
    uint32_t reserved;
} PACKED;

typedef struct IdtEntry IdtEntry;

typedef void (*Handler)();

extern void default_exception_handler();
extern void default_interrupt_handler();
extern void (*exception_handlers[20])();


void idt_init();
void idt_set_handler(uint8_t index, uint16_t type, void (*handler)());

#endif