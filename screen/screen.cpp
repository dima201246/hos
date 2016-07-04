#include "screen.h"

int	main_system_color,
	main_system_color_selection;

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
	init_pair (TEXT_WHITE_YELLOW, COLOR_WHITE, COLOR_YELLOW);
	init_pair (TEXT_WHITE_BLUE, COLOR_WHITE, COLOR_BLUE);
	init_pair (TEXT_WHITE_GREEN, COLOR_WHITE, COLOR_GREEN);
	init_pair (TEXT_WHITE_RED, COLOR_WHITE, COLOR_RED);
	init_pair (TEXT_WHITE_MAGENTA, COLOR_WHITE, COLOR_MAGENTA);
	init_pair (TEXT_WHITE_CYAN, COLOR_WHITE, COLOR_CYAN);

	init_pair (TEXT_BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
	init_pair (TEXT_BLACK_YELLOW, COLOR_BLACK, COLOR_YELLOW);
	init_pair (TEXT_BLACK_BLUE, COLOR_BLACK, COLOR_BLUE);
	init_pair (TEXT_BLACK_GREEN, COLOR_BLACK, COLOR_GREEN);
	init_pair (TEXT_BLACK_RED, COLOR_BLACK, COLOR_RED);
	init_pair (TEXT_BLACK_MAGENTA, COLOR_BLACK, COLOR_MAGENTA);
	init_pair (TEXT_BLACK_CYAN, COLOR_BLACK, COLOR_CYAN);

	init_pair (TEXT_YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
	init_pair (TEXT_BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
	init_pair (TEXT_GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
	init_pair (TEXT_RED_BLACK, COLOR_RED, COLOR_BLACK);
	init_pair (TEXT_MAGENTA_BLACK, COLOR_MAGENTA, COLOR_BLACK);
	init_pair (TEXT_CYAN_BLACK, COLOR_CYAN, COLOR_BLACK);

	init_pair (TEXT_YELLOW_WHITE, COLOR_YELLOW, COLOR_WHITE);
	init_pair (TEXT_BLUE_WHITE, COLOR_BLUE, COLOR_WHITE);
	init_pair (TEXT_GREEN_WHITE, COLOR_GREEN, COLOR_WHITE);
	init_pair (TEXT_RED_WHITE, COLOR_RED, COLOR_WHITE);
	init_pair (TEXT_MAGENTA_WHITE, COLOR_MAGENTA, COLOR_WHITE);
	init_pair (TEXT_CYAN_WHITE, COLOR_CYAN, COLOR_WHITE);
}

void get_normal_inv_color(std::string color_str, int &color, int &sel_color) { // Получение кода цвета из имени и его инвертированной состовляющей
	if (color_str == "cyan") {
		color		= TEXT_CYAN_BLACK;
		sel_color	= TEXT_BLACK_CYAN;
	} else if (color_str == "blue"){
		color		= TEXT_BLUE_BLACK;
		sel_color	= TEXT_BLACK_BLUE;
	} else if (color_str == "red"){
		color		= TEXT_RED_BLACK;
		sel_color	= TEXT_BLACK_RED;
	} else if (color_str == "yellow"){
		color		= TEXT_YELLOW_BLACK;
		sel_color	= TEXT_BLACK_YELLOW;
	} else if (color_str == "magenta"){
		color		= TEXT_MAGENTA_BLACK;
		sel_color	= TEXT_BLACK_MAGENTA;
	} else if (color_str == "green"){
		color		= TEXT_GREEN_BLACK;
		sel_color	= TEXT_BLACK_GREEN;
	} else {
		color		= TEXT_WHITE_BLACK;
		sel_color	= TEXT_BLACK_WHITE;
	}
}

int get_inv_color(int color) { // Получение кода инвертированного цвета
	if (color == TEXT_CYAN_BLACK) {
		return TEXT_BLACK_CYAN;
	} else if (color == TEXT_BLUE_BLACK) {
		return TEXT_BLACK_BLUE;
	} else if (color == TEXT_RED_BLACK) {
		return TEXT_BLACK_RED;
	} else if (color == TEXT_YELLOW_BLACK) {
		return TEXT_BLACK_YELLOW;
	} else if (color == TEXT_MAGENTA_BLACK) {
		return TEXT_BLACK_MAGENTA;
	} else if (color == TEXT_GREEN_BLACK) {
		return TEXT_BLACK_GREEN;
	} else {
		return TEXT_BLACK_WHITE;
	}
}
