#include "../../configurator/configurator.h"
#include "../../fswork/fswork.h"
#include "menu_apps.h"

#define APPS_FILE "./apps/apps.list"

using namespace std;

int get_apps_list(vector<string> names) {
	if (!FileExists(APPS_FILE)) {
		/*To future...*/
		return 0;
	}
	return 0;
}