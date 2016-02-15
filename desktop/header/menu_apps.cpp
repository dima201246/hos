#include "../../configurator/configurator.h"
#include "../../fswork/fswork.h"
#include "menu_apps.h"

#define APPS_FILE "./apps/apps.list"
#define APPS_DIR "./apps/" // Внимание, всегда должна оканчиваться слешем!!!

using namespace std;

int get_apps_list(vector<string>& names) {
	names.clear();
	if (!FileExists(APPS_FILE)) {
		vector <FILEINFO> apps_vec;
		get_files(APPS_DIR, apps_vec); // Получение списка папок с (предполагается) приложениями 
		for (unsigned int i = 0; i < apps_vec.size(); i++) {
			if ((FileExists(APPS_DIR + apps_vec[i].name + "/app.config")) && (configurator(APPS_DIR + apps_vec[i].name + "/app.config", "type", "", false) == "app")) {
				add_to_file(APPS_FILE, configurator(APPS_DIR + apps_vec[i].name + "/app.config", "name_package", "", false));
			}
		}
		load_to_vector(APPS_FILE, names);
	} else load_to_vector(APPS_FILE, names);
	return 0;
}