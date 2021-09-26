#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	terminal_setcolor(0, 3);
	printf("minerva OS\n");
	printf("hello, %s!\n", "User");
	printf("CPU Loaded for: %d%s", 5, "%");
}
