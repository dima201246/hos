#ifndef HOS_API_H
#define HOS_API_H

	#include <unistd.h>
	#include <vector>

	struct load_t {
		std::string		text;
		unsigned int	posX,
						posY;
	};

	#define InitLOAD_T(vec_name) std::vector<load_t> vec_name

	extern	pid_t	loading_title_pid;

	void add_to_load_screen(std::vector<load_t> &, unsigned int, unsigned int, std::string);
	void loading_title_start(std::vector<load_t> *);
	void kill_loading_title();

#endif