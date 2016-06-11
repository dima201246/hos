#include "screen.h"

void init_display() {
	initscr();
	start_color();
	keypad (stdscr, true);
	noecho();
	curs_set(0);
	erase();
}