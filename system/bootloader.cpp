/*
	:DV company (c) 1997-2016
*/

#include "../include/apps_starter.h"
#include "../include/isca_alpha.h"
#include "../include/desktop.h"
#include "../include/system_defines.h"

using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	init_display();
	init_color();

	/*TEST WINDOWS*/
	vector<list_of_objects> obj_list;

	InitWINOBJ(test_button);
	test_button.posX	= 12;
	test_button.posY	= 13;

	add_to_win(obj_list, WIN_BUTTON, "TEST", TEXT_BLUE_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST1", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST2", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST3", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST4", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST5", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST6", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST7", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST8", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST9", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST10", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST11", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST12", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST13", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST14", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST15", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST16", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST17", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST18", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST19", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST20", TEXT_GREEN_BLACK, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST21", TEXT_GREEN_BLACK, NULL);
	// add_to_win(obj_list, WIN_BUTTON, "TEST215", TEXT_RED_BLACK, &test_button);

	
	InitWINOBJ(window);
	window.posX		= 1;
	window.posY		= 1;
	window.posXmax	= 20;
	win(&window, obj_list, "TEST WIN", RED_WIN);
	endwin();
	return 0;
	/*TEST WINDOWS*/

	init_signals();
	apps_vect.clear();

	if (!load_to_vector(MAIN_CONFIG, main_config_base)) {
		DLGSTR	failwin	= {}; // Только так!!!
		failwin.line	= "Can't load main configuration file!!!";
		failwin.style	= RED_WIN;
		msg_win(failwin);
		endwin();
		return 32;
	}

	get_normal_inv_color(conf("system_color", main_config_base), main_system_color, main_system_color_selection);

	if (conf("alpha_warning_on_start", main_config_base) != "0") {
		DLGSTR teststr = {}; // Только так!!!
		teststr.title = "Pre pre pre ... Alpha";
		teststr.style = RED_WIN;
		teststr.line = "Dear user, it's not full version of OS!/nThis is just an example of how might look this OS.";
		msg_win(teststr);
	}

	if ((conf("start_boot_indexing", main_config_base) == "1") && (FileExists(MAIN_APPS_FILE))) {
		if (!rm_file(MAIN_APPS_FILE)) {
			DLGSTR	failwin	= {}; // Только так!!!
			failwin.line	= "Can't load main configuration file!!!";
			failwin.style	= RED_WIN;
			msg_win(failwin);
		}
	}

	main_desktop("user_name");
	endwin();
	return 0;
}