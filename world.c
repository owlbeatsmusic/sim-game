
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
#include <time.h>
#include <math.h>
#include "sim-game.h"

Tile world_grid[GLOBAL_WORLD_HEIGHT][GLOBAL_WORLD_WIDTH];
ScreenPixel map_grid[GLOBAL_WORLD_HEIGHT][GLOBAL_WORLD_WIDTH];

const ScreenPixel water_pixel = {'~', "\x1b[34m", "\x1b[44m"};
const ScreenPixel sand_pixel  = {'.', "\x1b[33m", "\x1b[40m"};
const ScreenPixel grass_pixel = {',', "\x1b[32m", "\x1b[42m"};
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

int world_create_branches_internal(int branch_x, int branch_y, ScreenPixel screen_pixel, int thickness, int avg_length, int max_rebranches, int x_dir, int y_dir) {
	
	int rand_from = 0;
	int rand_to = max_rebranches;
	int re_branches = rand() % (rand_to - rand_from + 1) + rand_from;
	
	rand_from = avg_length - (avg_length/4); 
	rand_to = avg_length + (avg_length/4);
	int length = rand() % (rand_to - rand_from + 1) + rand_from;


	for (int i = 0; i < length; i++) {

		for (int y = -thickness/2; y < thickness/2; y++) {
			for (int x = -thickness/2; x < thickness/2; x++) {
				world_grid[branch_y + y][branch_x + x].screen_pixel =  water_pixel;
			}
		}
		
		rand_from = -1; 
		rand_to = 1;
		int x_change[] = {rand() % (rand_to - rand_from + 1) + rand_from, x_dir};
		int y_change[] = {rand() % (rand_to - rand_from + 1) + rand_from, y_dir};
		
		rand_from = 0;
		branch_x += x_change[rand() % (rand_to - rand_from + 1) + rand_from];
		branch_y += y_change[rand() % (rand_to - rand_from + 1) + rand_from];		
	}
	for (int i = 0; i < re_branches; i++) {
		rand_from = -1; 
		rand_to = 1;
		x_dir = rand() % (rand_to - rand_from + 1) + rand_from;
		y_dir = rand() % (rand_to - rand_from + 1) + rand_from;
		world_create_branches_internal(branch_x, branch_y, water_pixel, thickness, avg_length, max_rebranches-1, x_dir, y_dir);
	}
	world_render_map(0, 0, GLOBAL_SCREEN_WIDTH, GLOBAL_SCREEN_HEIGHT);

	return 0;
}

int world_initialize() {

	srand(time(NULL));			

	/* step 1 : fill with grass */
	for (int y = 0; y < GLOBAL_WORLD_HEIGHT; y++) {
		for (int x = 0; x < GLOBAL_WORLD_WIDTH; x++) {
			world_grid[y][x].screen_pixel = grass_pixel;
		}
	}
	
	/* step 2 : generate random lines */
	int rand_from = 0;
	int rand_to = GLOBAL_WORLD_WIDTH;
	int branch_x = rand() % (rand_to - rand_from + 1) + rand_from;
	rand_to = GLOBAL_WORLD_HEIGHT;
	int branch_y = rand() % (rand_to - rand_from + 1) + rand_from;		
	world_create_branches_internal(branch_x, branch_y, water_pixel, 20, 200, 4, -1, -1);	
	
	
	return 0;
}

