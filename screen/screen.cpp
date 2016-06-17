#include "screen.h"

void init_display() {
	initscr();
	start_color();
	keypad (stdscr, true);
	noecho();
	curs_set(0);
	erase();
}

void init_color() {
	init_pair (TEXT_WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
	init_pair (TEXT_BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair (TEXT_WHITE_YELLOW, COLOR_WHITE, COLOR_YELLOW);
	init_pair (TEXT_WHITE_BLUE, COLOR_WHITE, COLOR_BLUE);
	init_pair (TEXT_WHITE_GREEN, COLOR_WHITE, COLOR_GREEN);
	init_pair (TEXT_WHITE_RED, COLOR_WHITE, COLOR_RED);
	init_pair (TEXT_WHITE_MAGENTA, COLOR_WHITE, COLOR_MAGENTA);
	init_pair (TEXT_WHITE_CYAN, COLOR_WHITE, COLOR_CYAN);
	init_pair (TEXT_BLACK_YELLOW, COLOR_BLACK, COLOR_YELLOW);
	init_pair (TEXT_BLACK_BLUE, COLOR_BLACK, COLOR_BLUE);
	init_pair (TEXT_BLACK_GREEN, COLOR_BLACK, COLOR_GREEN);
	init_pair (TEXT_BLACK_RED, COLOR_BLACK, COLOR_RED);
	init_pair (TEXT_BLACK_MAGENTA, COLOR_BLACK, COLOR_MAGENTA);
	init_pair (TEXT_BLACK_CYAN, COLOR_BLACK, COLOR_CYAN);
}