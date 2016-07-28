/*
	:DV company (c) 1997-2016
*/

#include "../include/apps_starter.h"
#include "../include/configurator.h"
#include "../include/windlg.h"
#include "../include/desktop.h"
#include "../include/fswork.h"
#include "../include/screen.h"
#include "../include/system_defines.h"

using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	init_display();
	init_color();

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
		
	}

	main_desktop("user_name");
	endwin();
	return 0;
}