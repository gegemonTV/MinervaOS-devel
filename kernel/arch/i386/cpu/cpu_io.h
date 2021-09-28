#ifndef _CPU_IO_H
#define _CPU_IO_H

#include <stdint.h>

static inline void IoWrite8(uint16_t port, uint8_t data)
{
    __asm__ volatile("outb %b0, %w1" : : "a" (data), "Nd" (port));
}

static inline uint8_t IoRead8(uint16_t port)
{
    uint8_t data;
    __asm__ volatile("inb %w1, %b0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline void IoWrite16(uint16_t port, uint16_t data)
{
    __asm__ volatile("outw %w0, %w1" : : "a" (data), "Nd" (port));
}

static inline uint16_t IoRead16(uint16_t port)
{
    uint16_t data;
    __asm__ volatile("inw %w1, %w0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline void IoWrite32(uint16_t port, uint32_t data)
{
    __asm__ volatile("outl %0, %w1" : : "a" (data), "Nd" (port));
}

static inline uint32_t IoRead32(uint16_t port)
{
    uint32_t data;
    __asm__ volatile("inl %w1, %0" : "=a" (data) : "Nd" (port));
    return data;
}

static inline void io_wait()
{
    __asm__ volatile("jmp 1f;1:jmp 1f;1:");
}

// ------------------------------------------------------------------------------------------------
// memory mapped i/o functions

static inline void MmioWrite8(void *p, uint8_t data)
{
    *(volatile uint8_t *)(p) = data;
}

static inline uint8_t MmioRead8(void *p)
{
    return *(volatile uint8_t *)(p);
}

static inline void MmioWrite16(void *p, uint16_t data)
{
    *(volatile uint16_t *)(p) = data;
}

static inline uint16_t MmioRead16(void *p)
{
    return *(volatile uint16_t *)(p);
}

static inline void MmioWrite32(void *p, uint32_t data)
{
    *(volatile uint32_t *)(p) = data;
}

static inline uint32_t MmioRead32(void *p)
{
    return *(volatile uint32_t *)(p);
}

static inline void MmioWrite64(void *p, uint64_t data)
{
    *(volatile uint64_t *)(p) = data;
}

static inline uint64_t MmioRead64(void *p)
{
    return *(volatile uint64_t *)(p);
}

static inline void MmioReadN(void *dst, const volatile void *src, size_t bytes)
{
    volatile uint8_t *s = (volatile uint8_t *)src;
    uint8_t *d = (uint8_t *)dst;
    while (bytes > 0)
    {
        *d =  *s;
        ++s;
        ++d;
        --bytes;
    }
}

#endif