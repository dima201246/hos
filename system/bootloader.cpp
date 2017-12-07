/*
	:DV company (c) 1997-2017
*/

#include "../include/apps_starter.h"
#include "../include/isca_alpha.h"
#include "../include/desktop.h"
#include "../include/system_defines.h"

#include "./include/video_buf.h"

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");
	video_init();
	// init_signals();
	// apps_vect.clear();
	// sleep(2);
	// screen_init();

	for (;;)
	{
		sleep(1);
	}


	// main_desktop("user_name");
	end_video();
	exit(0);


	// while (true);
	// end_video();
/*
	init_display();
	init_color();

	InitLOAD_T(loading_info);		// ЧТО ЗДЕСЬ ТОБОЙ ДВИГАЛО???

	std::string	hos_ver	= _HOS_VERSION; 

	add_to_load_screen(loading_info, 0, 0, "HOS version: " + hos_ver);
	add_to_load_screen(loading_info, 0, 1, "WINDLG version: " + get_ver_windlg());
	add_to_load_screen(loading_info, 0, 2, "Windows API version: " + get_ver_winapi());

	loading_title_start(&loading_info);	// Вывод загрузочного экрана

	init_signals();
	apps_vect.clear();

	usleep(2500000);				// ВАЖНО!

	kill_loading_title();			// Закрытие загрузочного экрана

	if (!load_to_vector(MAIN_CONFIG, main_config_base))	// АБСТРАКЦИИ, ПОЛИМОРФИЗМ, КОСВЕННЫЙ ДОСТУП... ЗААААЧЧЧЕЕЕЕМ?
	{
		DLGSTR	failwin	= {};		// Только так!!! ЭТО ФИЧА!
		failwin.line	= "Can't load main configuration file!!!";
		failwin.style	= RED_WIN;
		msg_win(failwin);
		endwin();
		return 32;
	}

	get_normal_inv_color(conf("system_color", main_config_base), main_system_color, main_system_color_selection);

	if (conf("alpha_warning_on_start", main_config_base) != "0")
	{
		DLGSTR teststr = {};		// Только так!!!
		teststr.title = "Pre pre pre ... Alpha";	// Aaa??
		teststr.style = RED_WIN;	// КРАСНЫЙ КАК КРОВЬ!!!
		teststr.line = "Dear user, it's not full version of OS!/nThis is just an example of how might look this OS.";
		msg_win(teststr);
	}

	if ((conf("start_boot_indexing", main_config_base) == "1") && (FileExists(MAIN_APPS_FILE)))
	{
		if (!rm_file(MAIN_APPS_FILE))
		{
			DLGSTR	failwin	= {};	// Только так!!!
			failwin.line	= "Can't load main configuration file!!!";
			failwin.style	= RED_WIN;
			msg_win(failwin);		// ТЫ ЗАФЕЙЛИЛ, МУДИЛА
		}
	}

	main_desktop("user_name");		// ВИНОВНИК ТОРЖЕСТВА
	endwin();						// КОНЕЦ СТРАДАНИЯМ
	return 0;*/
}