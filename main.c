#include <stdio.h>
#include "sim-game.h"

Tile main_grid[GLOBAL_SCREEN_HEIGHT][GLOBAL_SCREEN_WIDTH];

int main() {
	
	 for (int y = 0; y < GLOBAL_SCREEN_HEIGHT; y++) {
		for (int x = 0; x < GLOBAL_SCREEN_WIDTH; x++) {
			main_grid[y][x].symbol = '.';
		}
	}

	renderer_initialize();
	return 0;
}
