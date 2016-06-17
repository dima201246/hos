#ifndef SCREEN_H
#define SCREEN_H

	#include <curses.h>

	void init_display();
	void init_color();

	/*Colors*/
	#define TEXT_WHITE_BLACK	0
	#define TEXT_WHITE_YELLOW	1
	#define TEXT_WHITE_BLUE		2
	#define TEXT_WHITE_GREEN	3
	#define TEXT_WHITE_RED		4
	#define TEXT_WHITE_MAGENTA	5
	#define TEXT_WHITE_CYAN		6

	#define TEXT_BLACK_WHITE	7
	#define TEXT_BLACK_YELLOW	8
	#define TEXT_BLACK_BLUE		9
	#define TEXT_BLACK_GREEN	10
	#define TEXT_BLACK_RED		11
	#define TEXT_BLACK_MAGENTA	12
	#define TEXT_BLACK_CYAN		13

#endif  
