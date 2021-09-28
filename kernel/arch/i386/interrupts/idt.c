#include "idt.h"
#include "../memory_managment/memdef.h"

void 
idt_init()
{
    for (uint16_t i = 0; i < 20; ++i)
    {
        IdtSetHandler(i, INTERRUPT_GATE, exception_handlers[i]);
    }

    for (uint16_t i = 20; i < 32; ++i)
    {
        IdtSetHandler(i, INTERRUPT_GATE, default_exception_handler);
    }

    for (uint16_t i = 32; i < 256; ++i)
    {
        IdtSetHandler(i, TRAP_GATE, default_interrupt_handler);
    }

    IdtDesc idtDesc =
        {
            .limit = 256 * sizeof(IdtEntry) - 1,
            .base = IDT_BASE};
    __asm__ volatile("lidt %0"
                     :
                     : "m"(idtDesc)
                     : "memory");

    // Test interrupt
    __asm__ volatile("int $3");
}

static void
IdtSetEntry(
    uint8_t index,
    uint64_t base,
    uint16_t selector,
    uint16_t type)
{
    IdtEntry *entry = (IdtEntry *)IDT_BASE + index;

    entry->offset0 = (uint16_t)base;
    entry->selector = selector;
    entry->type = type;
    entry->offset1 = (uint16_t)(base >> 16);
    entry->offset2 = (uint32_t)(base >> 32);
    entry->reserved = 0;
}

void idt_set_handler(
    uint8_t index,
    uint16_t type,
    void (*handler)())
{
    if (handler)
    {
        uint16_t selector = 0x8; // gdt.code
        IdtSetEntry(index, (uint64_t)handler, selector, type);
    }
    else
    {
        IdtSetEntry(index, 0, 0, 0);
    }
}