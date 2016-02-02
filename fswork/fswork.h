#ifndef FSWORK_H
#define FSWORK_H
	#include <vector>
	#include <string>
	struct FILEINFO {					
		std::string name;
		// ... информация о файле ... 
	};
	bool FileExists(const std::string&);
	int get_files(std::string, std::vector<FILEINFO>&);
	void files_sort_by(char/*SORT TYPE*/, std::vector<FILEINFO>&);
	/* SORT TYPE
		n - name
	*/
#endif
