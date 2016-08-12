#ifndef INTERNAL_WINDLG_H
#define INTERNAL_WINDLG_H

	#include <string>
	#include "../../include/screen.h"

	void draw_box(	int				mode,
					std::string		title,
					unsigned int	progressBarPos,
					unsigned int	x,
					unsigned int	y,
					unsigned int	end_x,
					unsigned int	end_y,
					color_t			win_color_local,
					color_t			win_color_selected);

	int	windlg_input(unsigned int	max_size, unsigned int	&firstItem,unsigned int	&lastItem, unsigned int	&selected, bool	progressBar);

#endif 