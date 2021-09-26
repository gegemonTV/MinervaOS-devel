#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/virtualmem.h>

void init(
	void)
	{
		terminal_initialize();
		terminal_setcolor(0, 15);
		printf("Started Initialization\n");

		virtualmem_init();

		printf("Finished initialization\n");
		//terminal_clear();
		terminal_setcolor(0, 3);
	}

void kernel_main(void) {
	init();

	printf("minerva OS\n");
	printf("hello, %s!\n", "User");
	printf("CPU Loaded for: %d%s", 5, "%");
	
}
