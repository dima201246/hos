#include "../../fswork/fswork.h"
#include <curses.h>


using namespace std;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	keypad (stdscr, TRUE);
	noecho();
	curs_set(0);
	erase();

	vector <FILEINFO> test_vec;
	FILEINFO test_str;
	// get_files("./test", test_vec);
	get_files(".", test_vec);
	/*for(unsigned int i = 0; i < test_vec.size(); i++) {
		test_str = test_vec[i];
		printw("%s\n", test_str.name.c_str());
	}*/

	printw("\n");
	files_sort_by('n', test_vec);
	for(unsigned int i = 0; i < test_vec.size(); i++) {
		test_str = test_vec[i];
		printw("%i %s\n", (int)test_str.name[0], test_str.name.c_str());
	}
	getch();
	
	endwin();
	return 0;
}