#ifndef SYSTEM_H
#define SYSTEM_H

	#include <string.h>

	#include "../windlg/windlg.h"
	#include "../lang/lang.h"
	#include "../screen/screen.h"

	#define MAIN_CONFIG "configs/system.conf"
	#define MAIN_SETFILE "configs/system.setfile"

	std::string hos_version();
	int action_parcer(std::string);

#endif