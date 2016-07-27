#include "../../screen/screen.h"

int main() {
	init_display();
	timeout(-1);
	int key = 0;
	while (key != 27) {
		erase();
		printw("%d", key);
		key = getch();
	}
	endwin();
	return 0;
}