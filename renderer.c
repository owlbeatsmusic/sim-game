#include <stdio.h>
#include <unistd.h> /* sleep() */
#include "sim-game.h"

//Tile global_grid[GLOBAL_SCREEN_HEIGHT][GLOBAL_SCREEN_WIDTH];

/* Much faster and does not require iteration */
int renderer_terminalclear_internal() {
	printf("\033[H\033[J");
	return 0;
}

int renderer_screenclear_internal() {
	
	return 0;
}

/* Just places cursor, use printf after this function */
int renderer_gotoxy_internal(int x, int y) {
	printf("\033[%d;%dH", y, x);
	return 0;
}

int renderer_initialize() {
	renderer_terminalclear_internal();
	renderer_render_screen();
	return 0;
}

int renderer_render_screen() {
	renderer_screenclear_internal();
	for (int y = 0; y < GLOBAL_SCREEN_HEIGHT; y++) {
		printf("%c", (char*)main_grid[y]);
		//for (int x = 0; x < GLOBAL_SCREEN_WIDTH; x++) {	
		//	printf("%c", global_grid[y][x].symbol);
		//}
		printf("\n");
	}	
	return 0;	
}
