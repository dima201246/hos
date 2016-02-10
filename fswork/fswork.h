#ifndef FSWORK_H
#define FSWORK_H
	#include <vector>
	#include <string>
	#include <time.h>
	struct FILEINFO {					
		std::string name;		// Имя файла
		time_t mtime;			// Переменная, содержащая прошедшее время с момента создания
		bool d_type; 			//Папка или нет
		std::string f_path;		// Full path to this file 
		// ... информация о файле ... 
	};
	bool FileExists(const std::string&);
	int get_files(std::string, std::vector<FILEINFO>&);
	void files_sort_by(char/*SORT TYPE*/, std::vector<FILEINFO>&);
	/* SORT TYPE
		n - name
	*/
#endif  
