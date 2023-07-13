
/* 
	WORLD-GEN:
	
	1. fyll hela grid-et med gräs från början.
	
	2. rita ut random linjer som kan ändras i längd och förgrenings antal. spetsen på varje gren fördelar sig i flera grenar och sedan fortsätter det i ett valt antal gånger. 
	
	3. fylla större kvadrater runt varje punkt av grenarna för att skapa en tjock outline som sedan är vattnet.

	4. sedan välja en skumpmässig mängd berg som ska genereas. dessa väljs slumpmässigt ut på alla tiles som inte är vatten(alltså bara gräs nu i processen). sedan skapa en klump av ett berg som är en random linje som går helt slumpmässigt.

	5. se till så att det inte finns berg bredvid vatten. fortsättning följer.
*/

#include <stdio.h>
#include <math.h>
#include "sim-game.h"

Tile world_grid[GLOBAL_WORLD_HEIGHT][GLOBAL_WORLD_WIDTH];

/* for each new pixel added, add one to pixel_types */
const ScreenPixel _0_water_pixel = {'~', "\x1b[34m", "\x1b[40m"};
const ScreenPixel _1_sand_pixel  = {'.', "\x1b[33m", "\x1b[40m"};
const ScreenPixel _2_grass_pixel = {',', "\x1b[32m", "\x1b[40m"};
const ScreenPixel _3_stone_pixel = {'*', "\x1b[37m", "\x1b[40m"};
const int pixel_types = 4;

int world_initialize() {			

	/* map zoom-out-ish */
	int map_chunk_height = floor(GLOBAL_WORLD_HEIGHT / GLOBAL_SCREEN_HEIGHT);
	int map_chunk_width  = floor(GLOBAL_WORLD_WIDTH  / GLOBAL_SCREEN_WIDTH);

	int pixel_type_count[pixel_types];	
	
	for (int y = 0; y < GLOBAL_WORLD_HEIGHT; y++) {
		for (int x = 0; x < GLOBAL_WORLD_WIDTH; x++) {
			
			x += map_chunk_width;	
		}
		x = 0;
		y += map_chunk_height;
	}
	
	world_grid[5][8].screen_pixel = _0_water_pixel;

	
	/* as long as world_grid is the same size as the screen grid, for testing purposes. */
	for (int y = 0; y < GLOBAL_SCREEN_HEIGHT; y++) {
		for (int x = 0; x < GLOBAL_SCREEN_WIDTH; x++) {
			renderer_screengrid[y][x] = world_grid[y][x].screen_pixel;
		}
	}
	renderer_render_screen();

	return 0;
}

