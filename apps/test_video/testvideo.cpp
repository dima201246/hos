#include "../../include/isca_alpha.h"

using namespace std;

unsigned int	shiftX = 11,
				shiftY = 6,
				count = 0;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "");

	setVideoBufName("app2");
	screen_init();

	for (unsigned char i = 0; i < 10; ++i)
	{
		mvprint(shiftY, shiftX + i, "*");
		mvprint(shiftY + 5, shiftX + i, "*");
	}

	for (unsigned char i = 0; i < 5; ++i)
	{
		mvprint(shiftY + i, shiftX, "|");
		mvprint(shiftY + i, shiftX + 10, "|");
	}

	for(;;)
	{
		sleep(1);
		count++;
		mvprint(shiftY + 1, shiftX + 1, "%d", count);
		write_display();
	}

	return 0;
}
