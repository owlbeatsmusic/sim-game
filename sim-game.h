#ifndef SIM_GAME_H_
#define SIM_GAME_H_

// 10:3
#define GLOBAL_SCREEN_WIDTH  80 // 80
#define GLOBAL_SCREEN_HEIGHT 25 // 25
// 10:3
#define GLOBAL_WORLD_WIDTH  4000
#define GLOBAL_WORLD_HEIGHT 1200

extern const char COLORCODE_DEFAULT[];   
extern const char COLORCODE_FG_BLACK[];   
extern const char COLORCODE_BG_BLACK[];  
extern const char COLORCODE_FG_RED[];     
extern const char COLORCODE_BG_RED[];     
extern const char COLORCODE_FG_GREEN[]; 
extern const char COLORCODE_BG_GREEN[];  
extern const char COLORCODE_FG_YELLOW[]; 
extern const char COLORCODE_BG_YELLOW[]; 
extern const char COLORCODE_FG_BLUE[]; 
extern const char COLORCODE_BG_BLUE[]; 
extern const char COLORCODE_FG_MAGENTA[]; 
extern const char COLORCODE_BG_MAGENTA[]; 
extern const char COLORCODE_FG_CYAN[];   
extern const char COLORCODE_BG_CYAN[];    
extern const char COLORCODE_FG_WHITE[];   
extern const char COLORCODE_BG_WHITE[];

int renderer_initialize();
int renderer_render_screen();
int renderer_fullstrcpy();
 
typedef struct {
	char symbol;
	char fg_color[8];
	char bg_color[8];
	int id;
} ScreenPixel;

extern ScreenPixel renderer_screengrid[GLOBAL_SCREEN_HEIGHT][GLOBAL_SCREEN_WIDTH];

typedef struct {
	ScreenPixel screen_pixel;
	char name[20];
		
	
	/* add what is on the tile */ 
} Tile;

extern  Tile world_grid[GLOBAL_WORLD_HEIGHT][GLOBAL_WORLD_WIDTH];

int world_initialize();
int world_render_map();

#endif
