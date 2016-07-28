#include "../include/stat_file.h"

time_t stat_file(const char *path) { // Получение информации о файле 
	struct stat fs_cur; // Ну дибилы!!! Кто же называет структуру и функцию одним именем!?					
	stat(path, &fs_cur);
	return fs_cur.st_mtime;
}
