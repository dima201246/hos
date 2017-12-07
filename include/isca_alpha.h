#ifndef ISCA_ALPHA_H
#define ISCA_ALPHA_H

	typedef int color_t;

	#include <time.h>
	#include <ncurses.h>
	#include <unistd.h>
	#include <string>
	#include <vector>
	#include <stdlib.h>

	#include "timework.h"
	#include "configurator.h"
	#include "fswork.h"
	#include "lang.h"
	#include "screen.h"
	#include "windlg.h"
	#include "windows_api.h"
	#include "settings.h"
	#include "hos_api.h"
	#include "hos_video.h"

	#define H_KEY_ESC		27
	#define H_KEY_BACKSPACE	127
	#define H_KEY_TAB		9
	#define H_KEY_ENTER		'\n'
	#define H_KEY_CtrlF1	289
	#define H_KEY_DEL		330

#endif