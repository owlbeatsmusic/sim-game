#include <stdio.h>
#include "sim-game.h"

void main_print_red_dot() {
	printf("[%s*%s] ", COLORCODE_FG_RED, COLORCODE_DEFAULT);
}
void main_print_green_dot() {
	printf("[%s*%s] ", COLORCODE_FG_GREEN, COLORCODE_DEFAULT);
}
void main_print_yellow_dot() {
	printf("[%s*%s] ", COLORCODE_FG_YELLOW, COLORCODE_DEFAULT);
}

int main() {
	//renderer_initialize();
	world_initialize();
	return 0;
}
