#include "../../configurator/configurator.h"
#include "../../fswork/fswork.h"
#include "../../lang/lang.h"
#include "../../apps_starter/apps_starter.h"
#include "menu_apps.h"

#include <stdlib.h>

using namespace std;

int get_apps_list(vector<string>& names) {
	names.clear();
	unsigned int count = 0;
	if (!FileExists(APPS_FILE)) {
		vector <FILEINFO> apps_vec;
		get_files(APPS_DIR, apps_vec); // Получение списка папок с (предполагается) приложениями 
		files_sort_by('n', apps_vec); // Сортировка по имени
		for (unsigned int i = 0; i < apps_vec.size(); i++) {
			if ((FileExists(APPS_DIR + apps_vec[i].name + "/app.config")) && (configurator(APPS_DIR + apps_vec[i].name + "/app.config", "type", "", false) == "app")) {
				count++;
				add_to_file(APPS_FILE, str(count) + "_app_package_name = \"" + configurator(APPS_DIR + apps_vec[i].name + "/app.config", "name_package", "", false) + "\"");
				add_to_file(APPS_FILE, str(count) + "_app_path = \"" + APPS_DIR + apps_vec[i].name + "\"");
				add_to_file(APPS_FILE, str(count) + "_app_launcher = \"" + configurator(APPS_DIR + apps_vec[i].name + "/app.config", "launcher", "", false) + "\"");
			}
		}
		add_to_file(APPS_FILE, "all_apps = " + str(count));
		for (unsigned int i = 1; i <= count; i++)
			names.insert(names.end(), configurator(APPS_FILE, str(i) + "_app_package_name", "", false));
	} else {
		count = atoi(configurator(APPS_FILE, "all_apps", "", false).c_str());
		for (unsigned int i = 1; i <= count; i++)
			names.insert(names.end(), configurator(APPS_FILE, str(i) + "_app_package_name", "", false));
	}
	return 0;
}