/*
	:DV company (c) 1997-2016
*/

#include <unistd.h>
#include <sys/stat.h>

#include "../../include/isca_alpha.h"

using namespace std;

int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");
	init_display();
	init_color();

	InitObjVec(test_obj_vec);

	InitWINOBJ(test_obj_conf);
	test_obj_conf.posX = 14;
	test_obj_conf.posY = 4;

	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_01", TEXT_WHITE_BLACK, &test_obj_conf);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_0", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_1", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_2", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_3", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_4", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_5", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_6", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_7", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_8", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_9", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_10", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_11", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_12", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_13", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_14", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_15", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_16", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_17", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_18", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_19", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_20", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_21", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_22", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_23", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_24", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_25", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_26", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_27", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_28", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_29", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_30", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_1", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_2", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_3", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_4", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_5", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_6", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_7", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_8", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_9", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_10", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_11", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_12", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_13", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_14", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_15", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_16", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_17", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_18", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_19", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_20", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_21", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_22", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_23", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_24", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_25", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_26", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_27", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_28", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_29", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_30", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_31", TEXT_WHITE_BLACK, NULL);
	add_to_win(test_obj_vec, WIN_BUTTON, "TEST_TEXT_32", TEXT_WHITE_BLACK, NULL);
	win(NULL, test_obj_vec, "TEST WIN", TEXT_WHITE_BLACK);

	endwin();
	return 0;
}