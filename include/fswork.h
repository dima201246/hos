#ifndef FSWORK_H
#define FSWORK_H

	#include <vector>
	#include <string>
	#include <time.h>

	struct FILEINFO
	{
		std::string name;		// Имя файла
		time_t mtime;			// Переменная, содержащая прошедшее время с момента создания
		bool d_type; 			//Папка или нет
		std::string f_path;		// Full path to this file 
		// ... информация о файле ... 
	};

	int get_files(std::string, std::vector <FILEINFO> &);
	bool rm_file(std::string);
	bool FileExists(const std::string &);
	void files_sort_by(char/*SORT TYPE*/, std::vector<FILEINFO> &);
	void fv_in_strv_out(std::vector <FILEINFO>, std::vector <std::string> &);	// Имена файлов из вектора с типом FILEINFO в вектор с типом STRING

	/* SORT TYPE
		n - name
	*/

#endif