/*	#include "../include/configurator.h"
	#include "../include/fswork.h"
	#include "../include/lang.h"
	#include "../include/apps_starter.h"
*/
#include "../include/isca_alpha.h"
#include "../include/system_defines.h"
#include "../include/menu_apps.h"

using namespace std;

int get_apps_list(vector<string>& names) {
	names.clear();
	unsigned int count = 0;
	vector <string> apps_file_vec;
	if (!FileExists(MAIN_APPS_FILE)) {
		vector <FILEINFO> apps_vec;
		get_files(MAIN_APPS_DIR, apps_vec); // Получение списка папок с (предполагается) приложениями 
		files_sort_by('n', apps_vec); // Сортировка по имени
		for (unsigned int i = 0; i < apps_vec.size(); i++) {
			if ((FileExists(MAIN_APPS_DIR + apps_vec[i].name + "/app.config")) && ((configurator(MAIN_APPS_DIR + apps_vec[i].name + "/app.config", "type", "", false) == "app") || (configurator(MAIN_APPS_DIR + apps_vec[i].name + "/app.config", "type", "", false) == "link_app"))) {
				count++;
				
				load_to_vector(MAIN_APPS_DIR + apps_vec[i].name + "/app.config", apps_file_vec); // Загрузка файла с описанием приложения
				
				add_to_file(MAIN_APPS_FILE, str(count) + "_app_type = \"" + conf("type", apps_file_vec) + "\"");
				add_to_file(MAIN_APPS_FILE, str(count) + "_app_package_name = \"" + conf("name_package", apps_file_vec) + "\"");
				add_to_file(MAIN_APPS_FILE, str(count) + "_app_path = \"" + MAIN_APPS_DIR + apps_vec[i].name + "\"");
				add_to_file(MAIN_APPS_FILE, str(count) + "_app_launcher = \"" + conf("launcher", apps_file_vec) + "\"");
			}
		}
		add_to_file(MAIN_APPS_FILE, "all_apps = " + str(count));
		
	}

	load_to_vector(MAIN_APPS_FILE, apps_file_vec); // Загрузка файла со списком приложений
	count = atoi(conf("all_apps", apps_file_vec).c_str()); // Сколько всего приложений
	for (unsigned int i = 1; i <= count; i++)
		names.insert(names.end(), conf(str(i) + "_app_package_name", apps_file_vec));

	return 0;
}