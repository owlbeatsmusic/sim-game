#ifndef SIM_GAME_H_
#define SIM_GAME_H_

#define GLOBAL_SCREEN_WIDTH  80
#define GLOBAL_SCREEN_HEIGHT 24

int renderer_initialize();
int renderer_render_screen();

typedef struct {
	char symbol;
	char fg_color[6];
	char bg_color[6];
} ScreenPixel;

extern ScreenPixel renderer_screengrid[GLOBAL_SCREEN_HEIGHT][GLOBAL_SCREEN_WIDTH];

#endif
