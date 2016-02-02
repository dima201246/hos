#include <fstream>
// #include <sys/types.h>
// #include <unistd.h>
// #include <string>
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
#include <dirent.h> // !!!
#include <vector>
#include "../lang/lang.h"
#include "../configurator/configurator.h"
#include "fswork.h"
#include <curses.h>

using namespace std;

bool makedir(string path) {
	/*if (mkdir(path.c_str(), 0777) != 0) {

	}*/
	return false;
}

inline bool FileExists(const string& path) {	
	return ifstream(path.c_str()).good();
}

void files_sort_by(char type_sort, vector<FILEINFO> &filevec) {
	FILEINFO temp_1, temp_2, temp_3;
	unsigned int k_cycle, itemp_1, itemp_2;
	for (unsigned int i = 0; i < filevec.size() - 1; i++) { // Сортировка методом пузырька
		for (unsigned int j = 0; j < filevec.size() - i - 1; j++) {
			if (type_sort == 'n') { // Сортировка по имени
				temp_1 = filevec[j];
				temp_2 = filevec[j + 1];
				if (llength(temp_1.name) >= llength(temp_2.name)) k_cycle = llength(temp_2.name); // Взятие длины наименьшего
				else k_cycle = llength(temp_1.name);
				for (unsigned int k = 0; k < k_cycle; k++) { // Чтобы сортировка шла не только по первым буквам, но и по остальным, если они одинаковые
					if (((int)temp_1.name[k] >= 97) && ((int)temp_1.name[k] <= 122)) itemp_1 = (int)temp_1.name[k] - 32; // Исправление маленьких букв на большие
					else itemp_1 = (int)temp_1.name[k];
					if (((int)temp_2.name[k] >= 97) && ((int)temp_2.name[k] <= 122)) itemp_2 = (int)temp_2.name[k] - 32;
					else itemp_2 = (int)temp_2.name[k];
					if (itemp_1 == itemp_2) continue; // Обработать следующие буквы, если эти одинаковые
					if (itemp_1 > itemp_2) { // Поменять местами
						temp_3 = filevec[j];
						filevec[j] = filevec[j + 1];
						filevec[j + 1] = temp_3;
						break;
					} else break; // Иначе остановиться и перейти к следующим элементам
				}

			}
		}	
	}
	return;
}

int get_files(string path, vector<FILEINFO> &filevec) {
	DIR *dir;
	if ((dir=opendir(path.c_str())) == NULL)
		return -1;
	else {
		FILEINFO file_info;
		struct dirent *f_cur;
		while ((f_cur=readdir(dir))!= NULL) {
			file_info.name = f_cur->d_name;
			if ((file_info.name != "..") && (file_info.name != ".")) {
				filevec.insert(filevec.end(), file_info);
			}
		}
		closedir(dir);
		return 0;
	}
}
