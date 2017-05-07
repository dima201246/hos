
#include "../include/isca_alpha.h"
#include "../include/stat_file.h"

#include <fstream>
#include <dirent.h>
#include <sys/types.h>
#include <time.h>
#include <cstring>


using namespace std;


bool makedir(string path) {
	/*if (mkdir(path.c_str(), 0777) != 0) {

	}*/
	return false;
}

bool rm_file(string path) {
	return remove(path.c_str());
}

/*inline - не работает с ним нихрена!!!*/bool FileExists(const string& path) {	
	return ifstream(path.c_str()).good();
}

void fv_in_strv_out(vector <FILEINFO> filevector, vector <string>& fileout) {
	FILEINFO temp;
	fileout.clear();
	for (unsigned int vec = 0; vec < filevector.size();vec++) {
		temp = filevector[vec];
		fileout.insert(fileout.end(), temp.name.c_str());
	}
}

void files_sort_by(char type_sort, vector<FILEINFO> &filevec) {
	if (filevec.size() < 2)
		return;

	FILEINFO temp_1, temp_2, temp_3;
	unsigned int k_cycle, itemp_1, itemp_2;
	for (unsigned int i = 0; i < filevec.size() - 1; i++) { // Сортировка методом пузырька
		for (unsigned int j = 0; j < filevec.size() - i - 1; j++) {
			temp_1 = filevec[j];
			temp_2 = filevec[j + 1];
			if (type_sort == 'n') { // Сортировка по имени
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
			if (type_sort == 't') { // Сортировка по времени
				if (temp_2.mtime < temp_1.mtime) {
					temp_3 = filevec[j];
					filevec[j] = filevec[j + 1];
					filevec[j + 1] = temp_3;		
				}
			}
		}	
	}
	return;
}

int get_files(string path, vector<FILEINFO> &filevec) {
	DIR *dir;
	if (llength(path) == 0) return -1;
	if (path[llength(path) - 1] != '/') path += "/"; // Подправка пути для нормальной загрузки файлов
	if ((dir=opendir(path.c_str())) == NULL)
		return -1;
	else {
		FILEINFO file_info;
		struct dirent *f_cur;
		string tmp;
		filevec.clear(); // Очистка вектора
		while ((f_cur=readdir(dir))!= NULL) {
			file_info.name = f_cur->d_name;
			tmp = path + (char *) f_cur -> d_name;		// Получаем полный адрес файла для stat()
			
			// stat(tmp.c_str(), &fs_cur); 				// Получение информации о файле 
			// file_info.mtime = fs_cur.st_mtime;			// Сохраняем время последней модификации

			file_info.mtime = stat_file(tmp.c_str());			// Сохраняем время последней модификации
			
			file_info.f_path = tmp;						// Saving of full path to file
			if ((file_info.name != "..") && (file_info.name != ".")) { 
				filevec.insert(filevec.end(), file_info);  // Костылей нет. p.s честно p.s.s ну почти...
			}
		}
		closedir(dir);
		return 0;
	}
}
