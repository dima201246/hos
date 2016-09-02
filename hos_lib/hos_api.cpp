// #include <sys/types>
#include <signal.h>

#include "../include/screen.h"
#include "../include/hos_api.h"

pid_t	loading_title_pid;

using namespace std;

void loading_title_start() {
	pid_t loading_pid	= fork();

	if (loading_pid == 0) {
		unsigned int	maxX,
						maxY;

		int				state;

		state	= 0;

		init_display();
		init_color();

		getmaxyx(stdscr, maxY, maxX);
		while (true) {
			switch (state) {
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
	} else {
		loading_title_pid	= loading_pid;
	}

}

void kill_loading_title() {
	endwin();
	kill(loading_title_pid, SIGTERM);
	init_display();
	init_color();
}