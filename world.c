


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
#include <unistd.h>
#include "sim-game.h"

Tile world_grid[GLOBAL_WORLD_HEIGHT][GLOBAL_WORLD_WIDTH];
ScreenPixel map_grid[GLOBAL_WORLD_HEIGHT][GLOBAL_WORLD_WIDTH];

const ScreenPixel water_pixel = {'~', "\x1b[34m", "\x1b[40m", 1};
const ScreenPixel sand_pixel  = {'.', "\x1b[33m", "\x1b[40m", 2};
const ScreenPixel grass_pixel = {',', "\x1b[32m", "\x1b[40m", 3};
const ScreenPixel stone_pixel = {'*', "\x1b[37m", "\x1b[40m", 4};

int current_map_width;
int current_map_height;

int map_chunk_width;
int map_chunk_height;

int realscale_pos_in_map_x = 0; 
int realscale_pos_in_map_y = 0;

void world_render_map(int offset_x, int offset_y, int map_width, int map_height) {
	
	current_map_width  = map_width;
	current_map_height = map_height;
	
	map_chunk_width  = (int)((GLOBAL_WORLD_WIDTH  / current_map_width));
	map_chunk_height = (int)((GLOBAL_WORLD_HEIGHT / current_map_height));
	
	if ((offset_x + map_width > GLOBAL_SCREEN_WIDTH) || (offset_y + map_height > GLOBAL_SCREEN_HEIGHT)) {
		main_print_red_dot();
		printf("\nerror: can't render map outside of screen.\n");
		exit(-1);
	}
	
	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {	
			map_grid[y][x] = world_grid[y * map_chunk_height + (map_chunk_height/2)][x * map_chunk_width + (map_chunk_width/2)].screen_pixel;
			map_grid[y][x].symbol = '#';
			renderer_fullstrcpy(map_grid[y][x].bg_color, "\x1b[47m", sizeof(map_grid[y][x].bg_color));
		}	
	}
	
	ScreenPixel realscale_pos = {'*', "\x1b[31m", "\x1b[47m"};
	map_grid[realscale_pos_in_map_y][realscale_pos_in_map_x] = realscale_pos;

	for (int y = 0; y < map_height; y++) {
		for (int x = 0; x < map_width; x++) {
			renderer_screengrid[offset_y + y][offset_x + x] = map_grid[y][x];
		}
	}
	renderer_render_screen();
}	



int branch_limit;
int branch_count = 0;

void world_create_branches_internal(int branch_x, int branch_y, ScreenPixel screen_pixel, int thickness, int avg_length, int rebranches, int x_dir, int y_dir, int always_follow_dir) {
	branch_count++;
	if (branch_count > branch_limit) {
		return;
	}
	int rand_from = avg_length - (avg_length/4); 
	int rand_to = avg_length + (avg_length/4);
	int length = rand() % (rand_to - rand_from + 1) + rand_from;


	for (int i = 0; i < length; i++) {

		for (int y = -thickness/2; y < thickness/2; y++) {
			for (int x = -thickness; x < thickness; x++) {
				if (!(branch_y + y < 0) & 
				    !(branch_y + y >= GLOBAL_WORLD_HEIGHT) &
				    !(branch_x + x < 0)  &
				    !(branch_x + x >= GLOBAL_WORLD_WIDTH)) {
					if (world_grid[branch_y + y][branch_x + x].screen_pixel.id ==  screen_pixel.id) continue;
					world_grid[branch_y + y][branch_x + x].screen_pixel =  screen_pixel;
				}
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
	for (int i = 0; i < rebranches; i++) {
		if (!always_follow_dir) {
			rand_from = -1; 
			rand_to = 1;
			x_dir = rand() % (rand_to - rand_from + 1) + rand_from;
			y_dir = rand() % (rand_to - rand_from + 1) + rand_from;
		}
		world_create_branches_internal(branch_x, branch_y, water_pixel, thickness, avg_length, rebranches, x_dir, y_dir, always_follow_dir);
	}
}



void world_render_realscale(int world_x, int world_y, int offset_x, int offset_y, int view_width, int view_height) {
	if (world_x+view_width > GLOBAL_WORLD_WIDTH || world_y+view_height > GLOBAL_WORLD_HEIGHT) return; 
	realscale_pos_in_map_x = round((world_x + (int)(view_width /2)) / map_chunk_width);
	realscale_pos_in_map_y = round((world_y + (int)(view_height/2)) / map_chunk_height);
	for (int y = 0; y < view_height; y++) {
		for (int x = 0; x < view_width; x++) {
			renderer_screengrid[offset_y + y][offset_x + x] = world_grid[world_y + y][world_x + x].screen_pixel;
		}		
	}
	//renderer_render_screen();
	return;
}




void world_initialize() {

	srand(time(NULL));			

	/* step 1 : fill with grass */
	for (int y = 0; y < GLOBAL_WORLD_HEIGHT; y++) {
		for (int x = 0; x < GLOBAL_WORLD_WIDTH; x++) {
			world_grid[y][x].screen_pixel = grass_pixel;
		}
	}
	
	/* step 2 : generate random lines */
	/* border water */ 
	
	int begin = time(NULL);
	branch_limit = 1;
	int thickness = 100;
	int length = 8000;
	int branches = 0;
	/*
	world_create_branches_internal(0, 0, water_pixel, thickness, length, branches, 5, 0, 1);
	branch_count = 0;		

	world_create_branches_internal(GLOBAL_WORLD_WIDTH, GLOBAL_WORLD_HEIGHT, water_pixel, thickness, length, branches, -5, 0, 1);
	branch_count = 0;
	
	world_create_branches_internal(GLOBAL_WORLD_WIDTH-30, 0, water_pixel, thickness, length, branches, 0, 5, 1);
	branch_count = 0;

	world_create_branches_internal(10, GLOBAL_WORLD_HEIGHT, water_pixel, thickness, length, branches, 0, -5, 1);
	branch_count = 0;
	*/	
	int end = time(NULL);
	main_print_green_dot();
	printf("border water generated (time:%ds)\n", (int)(end - begin));

	begin = time(NULL);
	for (int i = 0; i < 2; i++) {
		
		// river water 
		branch_limit = 5;
		thickness = 30;
		length = 1600;
		branches = 8;
	
		world_create_branches_internal(0, 0, water_pixel, thickness, length, branches, 2, 1, 0);
		branch_count = 0;		

		world_create_branches_internal(GLOBAL_WORLD_WIDTH, GLOBAL_WORLD_HEIGHT, water_pixel, thickness, length, branches, -2, -1, 0);
		branch_count = 0;
		
		world_create_branches_internal(GLOBAL_WORLD_WIDTH, 0, water_pixel, thickness, length, branches, -2, 1, 0);
		branch_count = 0;

		world_create_branches_internal(0, GLOBAL_WORLD_HEIGHT, water_pixel, thickness, length, branches, 2, -1, 0);
		branch_count = 0;
		
	}
	end = time(NULL);
	main_print_green_dot();
	printf("large waterpockets generated (time:%ds)\n", (int)(end - begin));
	

	/* random splashes of water */

	begin = time(NULL);
	
	branch_limit = 6;
	thickness = 80;
	length = 500;
	branches = 4;

	int rand_from = 0;
	int rand_to = 0;
	for (int i = 0; i < 30; i++) {
		rand_to = GLOBAL_WORLD_WIDTH; 
		int x = rand() % (rand_to - rand_from + 1) + rand_from;
		rand_to = GLOBAL_WORLD_HEIGHT;
		int y = rand() % (rand_to - rand_from + 1) + rand_from;
		
		rand_from = -1;
		rand_to = 1;	
		int x_dir = rand() % (rand_to - rand_from + 1) + rand_from;
		int y_dir = rand() % (rand_to - rand_from + 1) + rand_from;
		
		world_create_branches_internal(x, y, water_pixel, thickness, length, branches, x_dir, y_dir, 0);
		branch_count = 0;
	}

	end = time(NULL);
	main_print_green_dot();
	printf("random small water pockets generated (time:%ds)\n", (int)(end - begin));

	sleep(1);

	world_render_map(0, 0, GLOBAL_SCREEN_WIDTH, GLOBAL_SCREEN_HEIGHT);

	sleep(5);
	
	int current_x = 100;
	int current_y = 200;
	
	while (1) {	
		current_x += 1;
		current_y += 0;
		/*
		branch_limit = 1;
		int thickness = 100;
		int length = 2;
		int branches = 0;
		world_create_branches_internal(current_x, current_y, stone_pixel, thickness, length, branches, 5, 0, 1);
		branch_count = 0;		
		*/
		//world_render_map(0, 0, GLOBAL_SCREEN_WIDTH, GLOBAL_SCREEN_HEIGHT);
		world_render_map(0, 0, 21, 8);
		world_render_realscale(current_x, current_y, 0, 0, GLOBAL_SCREEN_WIDTH, GLOBAL_SCREEN_HEIGHT);
		usleep(10000);

	}
}
