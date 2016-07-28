#include <string>

#include "settings.h"

using namespace std;

string hos_version() {
	return _HOS_VERSION;
}

void about_hos() {
	timeout(-1);
	erase();
	printw(":DV company 2016\n\n");

	printw("HOS version: %s\n", hos_version().c_str());
	printw("Date build: %s %s\n", __DATE__, __TIME__);

	printw("\nThe authors:\n");
	printw("    Dmitriy Volchenko (dima201246@gmail.com)\n");
	printw("    Viktor Ohotnikov  (viktorokh96@mail.ru)\n");

	printw("\nBig thanks:\n");
	printw("    Mariya Quesada\n");

	printw("\nSites:\n");
	printw("    https://github.com/dima201246/hos\n");
	printw("    http://dv-company.ru.com\n");


	printw("\nPress any key...");
	getch();
}

void system_info() { // Пока не работает
	erase();
	timeout(-1);
	FILE	*logf;
	char	log_out[256];

	logf		= fopen("/proc/cpuinfo", "r");

	while (fgets(log_out,sizeof(log_out),logf)) {
		printw("%s", log_out);
	}

	fclose(logf);
	getch();
}

int action_parcer(string line) {
	string				command, // Переменная для содержания команды
						action, // Переменная для содержания названия вызываемого объекта
						temp;

	unsigned int		lenth_line,
						i;

	bool				get_action;

	line				+= ' '; // Для остановки и корретного чтения
	lenth_line			= llength(line);
	get_action			= false;
	temp.clear();
	action.clear();
	command.clear();

	for (i	= 0; i < lenth_line; i++) {
		if ((line[i] == ' ') && (!get_action)) {
			command		= temp;
			get_action	= true;
			temp.clear();
			continue;
		}

		if ((line[i] == ' ') && (get_action)) {
			action		= temp;
			temp.clear();
			continue;
		}

		temp	+= line[i];
	}

	if (command == "about_hos") {
		about_hos();
		return 0;
	}

	if (command == "system_info") {
		system_info();
		return 0;
	}

	if (command == "settings") {
		settings(action);
		return 0;
	}


	DLGSTR	failwin	= {};
	failwin.style	= RED_WIN;
	failwin.line	= "Not found " + line;
	msg_win(failwin);

	return -1;
}