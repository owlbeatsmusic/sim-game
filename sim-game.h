#ifndef SIM_GAME_H_
#define SIM_GAME_H_

#define GLOBAL_SCREEN_WIDTH  100
#define GLOBAL_SCREEN_HEIGHT 50

int renderer_initialize();
int renderer_render_screen();

typedef struct {
	char symbol;
} Tile;

extern Tile main_grid[GLOBAL_SCREEN_HEIGHT][GLOBAL_SCREEN_WIDTH];

#endif
