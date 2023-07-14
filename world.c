
/* 
	WORLD-GEN:
	
	1. fyll hela grid-et med gräs från början.
	
	2. rita ut random linjer som kan ändras i längd och förgrenings antal. spetsen på varje gren fördelar sig i flera grenar och sedan fortsätter det i ett valt antal gånger. 
	
	3. fylla större kvadrater runt varje punkt av grenarna för att skapa en tjock outline som sedan är vattnet.

	4. sedan välja en skumpmässig mängd berg som ska genereas. dessa väljs slumpmässigt ut på alla tiles som inte är vatten(alltså bara gräs nu i processen). sedan skapa en klump av ett berg som är en random linje som går helt slumpmässigt.

	5. se till så att det inte finns berg bredvid vatten. fortsättning följer.
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "sim-game.h"

Tile world_grid[GLOBAL_WORLD_HEIGHT][GLOBAL_WORLD_WIDTH];
ScreenPixel map_grid[GLOBAL_WORLD_HEIGHT][GLOBAL_WORLD_WIDTH];

const ScreenPixel water_pixel = {'~', "\x1b[34m", "\x1b[40m"};
const ScreenPixel sand_pixel  = {'.', "\x1b[33m", "\x1b[40m"};
const ScreenPixel grass_pixel = {',', "\x1b[32m", "\x1b[40m"};
const ScreenPixel stone_pixel = {'*', "\x1b[37m", "\x1b[40m"};

int world_render_map(int offset_x, int offset_y, int map_width, int map_height) {

	if ((offset_x + map_width > GLOBAL_SCREEN_WIDTH) || (offset_y + map_height > GLOBAL_SCREEN_HEIGHT)) {
		printf("\nerror: can't render map outside of screen.\n");
		exit(-1);
	}
	
	int map_chunk_height = floor(GLOBAL_WORLD_HEIGHT / map_height);
	int map_chunk_width  = floor(GLOBAL_WORLD_WIDTH  / map_width);

	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {	
			map_grid[y][x] = world_grid[y * map_chunk_height + (map_chunk_height/2)][x * map_chunk_width + (map_chunk_width/2)].screen_pixel;
		}		
	}
	
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			renderer_screengrid[offset_y + y][offset_x + x] = map_grid[y][x];
		}
	}
	renderer_render_screen();
	return 0;
}	

int world_create_branches_internal(int thickness, int avg_length, int avg_rebranches) {
	
	return 0;
}

int world_initialize() {			

	/* step 1 : fill with grass */
	for (int y = 0; y < GLOBAL_WORLD_HEIGHT; y++) {
		for (int x = 0; x < GLOBAL_WORLD_WIDTH; x++) {
			world_grid[y][x].screen_pixel = grass_pixel;
		}
	}
	world_render_map(0, 0, 80, 24);
	
	
	/* step 2 : generate random lines */
		
	
	
	return 0;
}

