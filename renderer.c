#include <stdio.h>
#include <unistd.h>
#include "sim-game.h"

int renderer_clear_internal() {
	printf("\033[H\033[J");
	return 0;
}

int renderer_gotoxy_internal(int x, int y) {
	printf("\033[%d;%dH", y, x);
	printf("@");
	return 0;
}

int renderer_render_screen() {
	renderer_clear_internal();
	renderer_gotoxy_internal(5, 5);
	sleep(1);
	renderer_gotoxy_internal(6, 5);
	sleep(1);
	renderer_gotoxy_internal(7, 5);
	sleep(1);
	return 0;	
}
