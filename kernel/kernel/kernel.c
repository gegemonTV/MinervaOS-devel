#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	terminal_setcolor(0, 3);
	printf("minerva OS%4.5f", 5);
	for (int i = 0; i < 25; i++){
		printf("%i", i);
	}
}
