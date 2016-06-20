#ifndef DESKTOP_H
#define DESKTOP_H
	#include <string>
	#include <unistd.h>
	#include <stdlib.h>

	#include "../windlg/windlg.h"
	#include "../fswork/fswork.h"
	#include "../apps_starter/apps_starter.h"
	#include "../time/time.h"
	#include "../screen/screen.h"
	#include "../settings/settings.h"

	#include "header/menu_apps.h"

	#define DESKTOP_SETTINGS_FILE "configs/system.setfile"

	int main_desktop(std::string);
#endif
