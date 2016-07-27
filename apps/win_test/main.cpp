/*
	:DV company (c) 1997-2016
*/

#include <unistd.h>
#include <sys/stat.h>

#include "../../configurator/configurator.h"
#include "../../windlg/windlg.h"
// #include "../../windlgV2/windlgV2.h"
#include "../../desktop/desktop.h"
#include "../../fswork/fswork.h"
#include "../../screen/screen.h"
#include "../../system/system_defines.h"


using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	init_display();
	init_color();

	vector <string> items;
	// items.insert(items.end(), "%cwWhite");
	// items.insert(items.end(), "%cbRed");
	// items.insert(items.end(), "%cgGreen");
	// items.insert(items.end(), "%crBlue");
	// items.insert(items.end(), "%cmYellow");
	// items.insert(items.end(), "M%cyba%cgg%cre%cmn%ccta");
	// items.insert(items.end(), "%ccCyan");
	// items.insert(items.end(), "%cyYellow");
	// items.insert(items.end(), "Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234Yellow123234234");
	items.push_back("%cwWhite");
	items.push_back("%cyYellow");
	items.push_back("%cbBlue");
	items.push_back("%cgGreen");
	items.push_back("%crRed");
	items.push_back("%cmMagenta");
	items.push_back("%ccCyan");
	items.push_back("%cw1%cy2%cb3%cg4%cr5%cm6%cc7");
	items.push_back("Yellow");
	items.push_back("Yellow//");
	items.push_back("%cy/'Yellow %crTEST 123/'//");
	items.push_back("white");
	items.push_back("blue");
	items.push_back("cyan");
	items.push_back("red");
	items.push_back("yellow");
	items.push_back("magenta");
	items.push_back("green");
/*	items.insert(items.end(), "Red");
	items.insert(items.end(), "Yellow");
	items.insert(items.end(), "Yellow123234234");
	items.insert(items.end(), "White");
	items.insert(items.end(), "Green");
	items.insert(items.end(), "Blue");
	items.insert(items.end(), "Yellow");
	items.insert(items.end(), "Magenta");
	items.insert(items.end(), "Cyan");
	items.insert(items.end(), "Yellow");
	items.insert(items.end(), "Yellow123234234");
	items.insert(items.end(), "White");
	items.insert(items.end(), "Red");
	items.insert(items.end(), "Green");
	items.insert(items.end(), "Blue");
	items.insert(items.end(), "Yellow");
	items.insert(items.end(), "Magenta");
	items.insert(items.end(), "Cyan");
	items.insert(items.end(), "Yellow");
	items.insert(items.end(), "Yellow123234234");*/
	Init_MENSTR(test_menu_win);

	test_menu_win.posX = 1;
	test_menu_win.posY = 1;
	// test_menu_win.posYmax = 30;
	test_menu_win.posYmax = 5;
	test_menu_win.animation_delay = 100;
	test_menu_win.std_selected = 11;

	color_t	color_test = WHITE_WIN;

	unsigned int	selected = 1;
	// menu_winV2(&test_menu_win, "TEST---------1", items, TEXT_BLUE_BLACK);
	
	// while (false) {
	while (selected != 0) {
		selected = menu_win(&test_menu_win, "TEST---------1", items, color_test);
		switch (selected) {
			case 1:		color_test = WHITE_WIN;
						break;

			case 2:		color_test = YELLOW_WIN;
						break;

			case 3:		color_test = BLUE_WIN;
						break;

			case 4:		color_test = GREEN_WIN;
						break;

			case 5:		color_test = RED_WIN;
						break;

			case 6:		color_test = MAGENTA_WIN;
						break;

			case 7:		color_test = CYAN_WIN;
						break;

			default:	selected	= 0;
						test_menu_win.posX	= test_menu_win.returned_x;
						test_menu_win.posY	= test_menu_win.returned_y;
						menu_win(&test_menu_win, "TEST---------2", items, color_test);
						break;
		}
	}
	// menu_winV2(&test_menu_win, "TEST---------1", items, WHITE_WIN);

	endwin();
	// exit(0);

	// test_menu_win.posX = test_menu_win.returned_x;
	// test_menu_win.posY = test_menu_win.returned_y;
	// menu_winV2(&test_menu_win, "TEST---------2", items, CYAN_WIN);
	// menu_winV2(NULL, "Test", items, CYAN_WIN);

	endwin();
	return 0;
}