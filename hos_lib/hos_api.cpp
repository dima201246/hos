#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#include "../include/screen.h"
#include "../include/hos_api.h"

pid_t	loading_title_pid;

void add_to_load_screen(std::vector<load_t> &text_on_title, unsigned int posX, unsigned int posY, std::string sometext)
{
	load_t	temp_str = {};

	temp_str.posX	= posX;
	temp_str.posY	= posY;
	temp_str.text	= sometext;

	text_on_title.push_back(temp_str);
}

void loading_title_start(std::vector<load_t> *text_on_title)
{
	pid_t loading_pid	= fork();

	if (loading_pid == 0)
	{
		unsigned int	maxX,
						maxY;

		int				state;

		state	= 0;

		init_display();
		init_color();

		if (text_on_title != NULL)
		{
			std::vector <load_t> text_on_title_temp	= *text_on_title;

			for (unsigned int	i = 0; i < text_on_title->size(); mvprintw(text_on_title_temp[i].posY, text_on_title_temp[i].posX, "%s", text_on_title_temp[i].text.c_str()), i++);
		}

		getmaxyx(stdscr, maxY, maxX);

		while (true)
		{
			switch (state)
			{
				case 0:		mvprintw(maxY / 2 - 1, maxX / 2 - 5, "Loading...");
							break;

				case 1:		coloron(TEXT_YELLOW_BLACK);
							mvprintw(maxY / 2 - 2, maxX / 2 - 5, "L      ");
							coloroff(TEXT_YELLOW_BLACK);
							mvprintw(maxY / 2 - 1, maxX / 2 - 5, " oading...");
							break;

				case 2:		coloron(TEXT_BLUE_BLACK);
							mvprintw(maxY / 2 - 2, maxX / 2 - 5, " o");
							coloroff(TEXT_BLUE_BLACK);
							mvprintw(maxY / 2 - 1, maxX / 2 - 5, "L ading...");
							break;

				case 3:		coloron(TEXT_GREEN_BLACK);
							mvprintw(maxY / 2 - 2, maxX / 2 - 5, "  a");
							coloroff(TEXT_GREEN_BLACK);
							mvprintw(maxY / 2 - 1, maxX / 2 - 5, "Lo ding...");
							break;

				case 4:		coloron(TEXT_RED_BLACK);
							mvprintw(maxY / 2 - 2, maxX / 2 - 5, "   d");
							coloroff(TEXT_RED_BLACK);
							mvprintw(maxY / 2 - 1, maxX / 2 - 5, "Loa ing...");
							break;

				case 5:		coloron(TEXT_MAGENTA_BLACK);
							mvprintw(maxY / 2 - 2, maxX / 2 - 5, "    i");
							coloroff(TEXT_MAGENTA_BLACK);
							mvprintw(maxY / 2 - 1, maxX / 2 - 5, "Load ng...");
							break;

				case 6:		coloron(TEXT_CYAN_BLACK);
							mvprintw(maxY / 2 - 2, maxX / 2 - 5, "     n");
							coloroff(TEXT_CYAN_BLACK);
							mvprintw(maxY / 2 - 1, maxX / 2 - 5, "Loadi g...");
							break;

				case 7:		coloron(TEXT_YELLOW_BLACK);
							mvprintw(maxY / 2 - 2, maxX / 2 - 5, "      g");
							coloroff(TEXT_YELLOW_BLACK);
							mvprintw(maxY / 2 - 1, maxX / 2 - 5, "Loadin ...");
							state	= 0;
							break;
			}

			refresh();
			usleep(250000);
			state++;
		}

		endwin();
		exit(0);
	}
	else
	{
		loading_title_pid	= loading_pid;
	}
}

void kill_loading_title()
{
	endwin();
	kill(loading_title_pid, SIGTERM);
	waitpid(loading_title_pid, NULL, WUNTRACED);
	init_display();
	init_color();
}