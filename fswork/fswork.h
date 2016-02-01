#ifndef FSWORK_H
#define FSWORK_H
	#include <vector>
	#include <string>
	struct FILESTR {
		std::string name;
	};
	bool FileExists(const std::string&);
	int get_files(std::string, std::vector<FILESTR>&);
	void files_sort_by(char/*SORT TYPE*/, std::vector<FILESTR>&);
	/* SORT TYPE
		n - name
	*/
#endif