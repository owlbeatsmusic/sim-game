#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sim-game.h"


int is_running = 1;

int mainloop() {

	char *input = malloc(sizeof(char) * 99);
	
	scanf("input: %s", &input);
	printf("\n");

	printf("value: %s", input);
		
	sleep(1);
	
	free(input);
	
	if (is_running == 1) {
		mainloop();
	}
	return 0;
}

int main() {
	renderer_initialize();
	world_initialize();
	mainloop();
	return 0;
}
