#include "../../include/isca_alpha.h"

int main(int argc, char** argv) {
	init_display();
	timeout(-1);
	int key = 0;

	for (int	i	= 0; i < argc; printw("%d: %s\n", i + 1, argv[i]), i++);
	getch();

	while (key != 27) {
		erase();
		printw("%d", key);
		key = getch();
	}
	endwin();
	return 0;
}