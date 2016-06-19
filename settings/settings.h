#ifndef SETTINGS_H
#define SETTINGS_H

	#include "../lang/lang.h"
	#include "../screen/screen.h"
	#include "../configurator/configurator.h"
	#include "../fswork/fswork.h"
	#include "../windlg/windlg.h"

	#define WAIT_START 10
	#define WAIT_END 5

	int settings(std::string/*путь к файлу настроек*/);

#endif