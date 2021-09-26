#ifndef _MEMDEF_H
#define _MEMDEF_H

#ifndef TEST

#define IDT_BASE                    0x00001000
#define VM_PML4                     0x00002000
#define VM_PDP                      0x00003000
#define MEMORY_MAP                  0x00005000
#define LOADER_DATA                 0x00006000
#define VGA_TEXT_BASE               ((volatile u16 *)0x000b8000)

#define VM_PD                       0x00010000
#define KERNEL_STACK                0x00020000  // 4k per CPU (up to 0x00030000 for 16 cpus)
#define KERNEL_BASE                 0x00100000

#define MEM_START                   0x00200000

#else

extern u16 g_vgaTextBase[80*25];
#endif

#define VGA_TEXT_BASE               g_vgaTextBase

#endif