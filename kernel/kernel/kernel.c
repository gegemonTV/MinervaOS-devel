#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	terminal_setcolor(0, 3);
	printf("minerva OS");
	for (int i = 0; i < 25; i++){
		printf("%s\n", "1");
	}
}
