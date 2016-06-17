#ifndef APPS_STARTER_H
#define APPS_STARTER_H

	#include <wait.h>
	#include <stdlib.h>
	#include <stdio.h>
	#include <unistd.h>

	#include "../lang/lang.h"
	#include "../configurator/configurator.h"
	#include "../windlg/windlg.h"
	#include "../screen/screen.h"

	#define APPS_FILE "./apps/apps.list"
	#define APPS_DIR "./apps/" // Внимание, всегда должна оканчиваться слешем!!!

	int app_start(int, const char*);

#endif