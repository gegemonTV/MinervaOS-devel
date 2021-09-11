#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, MinervaOS!\n");
	printf("Welcome to the club, !\n");
	for (int i = 0; i < 23; i++){
		printf("12\n");
	}
}
