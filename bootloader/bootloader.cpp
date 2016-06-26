/*
	:DV company (c) 1997-2016
*/

#include <unistd.h>
#include <curses.h>
#include <vector>
#include <sys/stat.h>

#include "../apps_starter/apps_starter.h"
#include "../configurator/configurator.h"
#include "../windlg/windlg.h"
#include "../desktop/desktop.h"
#include "../fswork/fswork.h"
#include "../screen/screen.h"
#include "../system/system_defines.h"

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

	main_desktop("user_name");
	endwin();
	return 0;
}