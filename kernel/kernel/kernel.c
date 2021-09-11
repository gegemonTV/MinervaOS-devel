#include <stdio.h>

#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, MinervaOS!\n");
	printf("Welcome to the club, !");
	for (int i = 0; i < 30; i++){
		printf("1\n");
	}
}
