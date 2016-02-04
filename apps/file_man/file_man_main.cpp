#include "../../fswork/fswork.h"
#include "../../windlg/windlg.h"
#include <curses.h>

#define TAB_KEY 9

using namespace std;

void load_pair_fm() {
	init_pair (0, COLOR_WHITE, COLOR_BLACK);
	init_pair (1, COLOR_BLACK, COLOR_WHITE);
	init_pair (2, COLOR_RED, COLOR_BLACK);
	init_pair (3, COLOR_BLACK, COLOR_RED);
	init_pair (4, COLOR_GREEN, COLOR_BLACK);
	init_pair (5, COLOR_BLACK, COLOR_GREEN);
	init_pair (6, COLOR_BLUE, COLOR_BLACK);
	init_pair (7, COLOR_BLACK, COLOR_BLUE);
	init_pair (8, COLOR_YELLOW, COLOR_BLACK);
	init_pair (9, COLOR_BLACK, COLOR_YELLOW);
	return;
}

void load_properties(vector <string>& propvec) {
	propvec.insert(propvec.end(), "Open");
	propvec.insert(propvec.end(), "Info");
	propvec.insert(propvec.end(), "Delete");
	propvec.insert(propvec.end(), "Move");
	propvec.insert(propvec.end(), "Copy");
	propvec.insert(propvec.end(), "Test..");
	return;
}

void load_files(vector <FILEINFO> filevector, vector <string>& fileout) {
	FILEINFO temp;
	fileout.clear();
	for (unsigned int vec = 0; vec < filevector.size();vec++) {
		temp = filevector[vec];
		fileout.insert(fileout.end(), temp.name.c_str());
	}
	return;
}

void properties_open(DLGSTR properties_menu, vector <string> propvec/*, link_to_file*/) {
	bool cycle = true;
	int key = 0;
	while (cycle) {
		menu_win(properties_menu, propvec);
		key = getch();
		switch (key) {
			case KEY_UP: if (properties_menu.selected != 1) properties_menu.selected--; break;
			case KEY_DOWN: if (properties_menu.selected != properties_menu.second_border) properties_menu.selected++; break;
			case 27: return; break;
		}
	}
	return;
}


void interface_fm() {
	unsigned int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX);
	vector <string> propvec;
	/*For windlg*/
	DLGSTR winstr = {}; // Только так!!!
	winstr.line = "Please enter link to foldren";
	/*For windlg END*/
	/*For first panel*/
	DLGSTR first_panel = {};
	first_panel.xmax = maxX / 2 - 2;
	first_panel.ymax = maxY - 3;
	first_panel.xpos = 0;
	first_panel.ypos = 1;
	first_panel.style = 3;
	// first_panel.title = "TEST";
	first_panel.border_menu = true;
	/*For first panel END*/
	/*For second panel*/
	DLGSTR second_panel = {};
	second_panel.xmax = maxX / 2 - 2;
	second_panel.ymax = maxY - 3;
	second_panel.xpos = maxX / 2 + 1;
	second_panel.ypos = 1;
	second_panel.style = 0;
	second_panel.border_menu = true;
	/*For second panel END*/
	/*For properties panel*/
	DLGSTR properties_menu = {};
	properties_menu.ymax = 4;
	properties_menu.style = 2;
	properties_menu.border_menu = true;
	/*For properties panel END*/
	bool cycle = true;
	vector <FILEINFO> filevector_1; // Вектор для загрузки файлов первой панели
	vector <FILEINFO> filevector_2; // Вектор для загрузки файлов второйой панели
	vector <string> fileout_1; // Вектор вывода списка файлов первой панели
	vector <string> fileout_2; // Вектор вывода списка файлов второйой панели
	FILEINFO filestr;
	string link_to_foldren;
	link_to_foldren.clear();

	link_to_foldren = ".";
	// dlg_win(winstr, link_to_foldren);
	/*while (get_files(link_to_foldren, filevector) == -1) {
		winstr.style = 1;
		winstr.line = "Wrong link!!! Try again!";
		msg_win(winstr);
		winstr.style = 0;
		winstr.line = "Please enter link to foldren";
		dlg_win(winstr, link_to_foldren);
	}*/
	get_files(link_to_foldren, filevector_1); // TEST!!!!
	get_files(link_to_foldren + ".", filevector_2); // TEST!!!!
	files_sort_by('n', filevector_1);
	files_sort_by('t', filevector_2);
	load_files(filevector_1, fileout_1);
	load_files(filevector_2, fileout_2);
	load_properties(propvec);

	/*Init head START*/
	load_pair_fm();
	int selected_color = 0;
	string head;
	head.clear();
	for (unsigned int i = 0; i < maxX; i++, head += " ");
	/*Init head END*/
	
	/*Mode*/
	unsigned int mode_select = 1, key_pressed = 0;
	/*0 - Menu
	  1 - First panel
	  2 - Second panel*/
	/*Mode END*/

	while (cycle) {
		timeout(-1);
		/*Head START*/
		switch (mode_select) {
			case 0: selected_color = 6; first_panel.style = 0; second_panel.style = 0; break;
			case 1: first_panel.style = 3; second_panel.style = 0; break;
			case 2: second_panel.style = 3; first_panel.style = 0; break;
		}
		attron(COLOR_PAIR(1 + selected_color) | A_BOLD);
		mvprintw(0, 0, "%s", head.c_str());
		mvprintw(0, 0, "(M)enu");
		attroff(COLOR_PAIR(1 + selected_color) | A_BOLD);
		selected_color = 0;
		/*Head END*/
		menu_win(first_panel, fileout_1);
		menu_win(second_panel, fileout_2);
		key_pressed = getch();
		switch (key_pressed) {
			case TAB_KEY: if (mode_select != 2) mode_select++;
						else mode_select = 0;
						break;
			case KEY_UP: switch (mode_select) {
							case 1: if (first_panel.selected != 1) first_panel.selected--; break;
							case 2: if (second_panel.selected != 1) second_panel.selected--; break;
						} break;
			case KEY_DOWN: switch (mode_select) {
							case 1: if (first_panel.selected != first_panel.second_border) first_panel.selected++; break;
							case 2: if (second_panel.selected != second_panel.second_border) second_panel.selected++; break;
						} break;
			case '\n': switch (mode_select) {
							case 1: properties_menu.xpos = first_panel.xreturn;
									properties_menu.ypos = first_panel.yreturn;
									properties_open(properties_menu, propvec/*, link_to_file*/);
									break;
							case 2: properties_menu.xpos = second_panel.xreturn;
									properties_menu.ypos = second_panel.yreturn;
									properties_open(properties_menu, propvec/*, link_to_file*/);
									break;
						} break;
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	keypad (stdscr, TRUE);
	noecho();
	curs_set(0);
	erase();

	// get_files("./test", test_vec);
	/*for(unsigned int i = 0; i < test_vec.size(); i++) {
		test_str = test_vec[i];
		printw("%s\n", test_str.name.c_str());
	}*/
	interface_fm();
	/*for(unsigned int i = 0; i < test_vec.size(); i++) {
		test_str = test_vec[i];
		printw("%i %s %s\n", (int)test_str.name[0], test_str.name.c_str(), ctime(&test_str.mtime));
	}*/
	
	endwin();
	return 0;
}
