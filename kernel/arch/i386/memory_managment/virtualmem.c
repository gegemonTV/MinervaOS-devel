#include <kernel/virtualmem.h>
#include <stdio.h>

#include "memdef.h"

#define PAGE_PRESENT                    0x01    // Must be 1 to reference page-directory
#define PAGE_WRITE                      0x02    // Write access
#define PAGE_USER                       0x04    // User-mode access
#define PAGE_WRITE_THROUGH              0x08    // Page-level write-through
#define PAGE_CACHE_DISABLE              0x10    // Page-level cache-disable

#define PD_2MB                          0x80    // 2MB Page

static uintptr_t s_nextAlloc;

// ------------------------------------------------------------------------------------------------
typedef struct MemoryRegion
{
    uint64_t start;
    uint64_t size;
    uint32_t type;
    uint32_t acpi_3_0;
} MemoryRegion;

// ------------------------------------------------------------------------------------------------
static void DumpMemoryMap()
{
    int i = 0;

    MemoryRegion *region = (MemoryRegion *)MEMORY_MAP;
    while (region->type)
    {
        printf("region %d: start: 0x%016llx end: 0x%016llx type: %d\n", i++,
            region->start, region->start + region->size, region->type);

        ++region;
    }
}

// ------------------------------------------------------------------------------------------------
static void VMEnablePD(uint64_t pdOffset, uint64_t base, uint64_t flags)
{
    uint64_t *pd = (uint64_t *)pdOffset;
    for (uint_fast16_t i = 0; i < 512; ++i)
    {
        pd[i] = base | PD_2MB | flags;
        base += 0x200000;
    }
}

// ------------------------------------------------------------------------------------------------
static void VMEnablePDP(uint_fast16_t pdpIndex, uint64_t pdOffset, uint64_t base, uint_fast16_t flags)
{
    VMEnablePD(pdOffset, base, flags);
    uint64_t *pdp = (uint64_t *)VM_PDP;
    pdp[pdpIndex] = pdOffset | flags;
}

// ------------------------------------------------------------------------------------------------
static void VMUpdatePage(uintptr_t addr, uint_fast16_t flags)
{
    // Break address into table indices
    uint_fast16_t pdpIndex = (addr >> 30) & 0x1ff;
    uint_fast16_t pdIndex = (addr >> 21) & 0x1ff;
    uint_fast16_t ptIndex = (addr >> 12) & 0x1ff;

    uint64_t *pdpBase = (uint64_t *)VM_PDP;
    uint64_t pdp = pdpBase[pdpIndex];
    uint64_t *pdBase = (uint64_t *)(pdp & ~0xfff);
    uint64_t pd = pdBase[pdIndex];

    uint64_t *ptBase = (uint64_t *)(pd & ~0xfff);
    if (pd & PD_2MB)
    {
        // Switch to page table
        uint64_t oldBase = (uint64_t)ptBase;
        uint_fast16_t oldFlags = pd & 0x1f;

        ptBase = malloc(4096);

        for (uint_fast16_t i = 0; i < 512; ++i)
        {
            ptBase[i] = oldBase | oldFlags;
            oldBase += 0x1000;
        }

        pd = (uintptr_t)ptBase | PAGE_PRESENT | PAGE_WRITE | PAGE_USER;
        pdBase[pdIndex] = pd;
    }

    // Update entry
    ptBase[ptIndex] = addr | flags;
}

// ------------------------------------------------------------------------------------------------
void virtualmem_init()
{
    // Enable 4GB of memory access
    uint_fast16_t flags = PAGE_PRESENT | PAGE_WRITE | PAGE_USER;
    VMEnablePDP(0, VM_PD + 0x0000, 0x00000000, flags);
    VMEnablePDP(1, VM_PD + 0x1000, 0x40000000, flags);
    VMEnablePDP(2, VM_PD + 0x2000, 0x80000000, flags);
    VMEnablePDP(3, VM_PD + 0x3000, 0xc0000000, flags | PAGE_CACHE_DISABLE);   // TODO - call VMMapPages

    DumpMemoryMap();

    s_nextAlloc = 0x00200000;
}

// ------------------------------------------------------------------------------------------------
void *malloc(uint_fast16_t size)
{
    // Align to 4k for now
    return virtualmem_alloc_align(size, 4096);
}

// ------------------------------------------------------------------------------------------------
void *virtualmem_alloc_align(uint_fast16_t size, uint_fast16_t align)
{
    // Align memory request
    uintptr_t offset = s_nextAlloc & (align - 1);
    if (offset)
    {
        s_nextAlloc += align - offset;
    }

    void *result = (void *)s_nextAlloc;
    s_nextAlloc += size;
    return result;
}

// ------------------------------------------------------------------------------------------------
void virtualmem_map_pages(void *addr, uint_fast16_t size, uint_fast16_t flags)
{
    flags |= PAGE_PRESENT | PAGE_WRITE | PAGE_USER;

    uint8_t *page = (uint8_t *)addr;
    uint8_t *end = page + size;

    while (page < end)
    {
        VMUpdatePage((uintptr_t)page & ~0xfff, flags);
        page += 4096;
    }

    // Flush TLBs
    unsigned long val;
    __asm__ volatile(
        "mov %%cr3, %0\n\t"
        "mov %0,%%cr3" : "=r" (val));
}