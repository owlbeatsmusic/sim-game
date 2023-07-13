#include <stdio.h>
#include "sim-game.h"

Tile world_grid[GLOBAL_WORLD_HEIGHT][GLOBAL_WORLD_WIDTH];

typedef struct {
	ScreenPixel screenPixels[3][3];
} TileTemplate;

const ScreenPixel water_pixel = {'~', "\x1b[34m", "\x1b[40m"};
const ScreenPixel sand_pixel  = {'.', "\x1b[33m", "\x1b[40m"};
const ScreenPixel grass_pixel = {',', "\x1b[32m", "\x1b[40m"};
const ScreenPixel stone_pixel = {'*', "\x1b[37m", "\x1b[40m"};

TileTemplate water1 = {{
	{ water_pixel, water_pixel, water_pixel },
	{ water_pixel, grass_pixel, grass_pixel },
	{ water_pixel, grass_pixel, water_pixel }
}};

int world_initialize() {			
	return 0;
}
