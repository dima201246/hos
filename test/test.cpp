#include "test.h"

using namespace std;

void button_obj(WINOBJ *button_conf, string text, color_t color_button) {

	printw("\nIn button_obj: %p\nPoint in button: %p\n", &button_obj, button_conf);

	if (button_conf != NULL) {
		printw("posX:   %d\n", button_conf->posX);
		printw("posY:   %d\n\n", button_conf->posY);
		printw("Redraw: %d\n", (button_conf->redraw ? 1 : 0));
	}

	return;
}

void add_to_win(vector<list_of_objects> &obj_list, win_object object_type, std::string text_on_object, color_t color_obj, WINOBJ* point_to_conf) {
	list_of_objects	temp_value	= {};

	switch (object_type) {
		case WIN_BUTTON:	temp_value.point_to_function	= &button_obj;
							temp_value.type_obj				= WIN_BUTTON;


							break;
	}

	if (point_to_conf == NULL) {
		WINOBJ	temp_button	= {};
		temp_button.redraw	= true;
		temp_value.point_to_struct	= &temp_button;
	} else {
		point_to_conf->redraw		= true;
	}

	temp_value.text					= text_on_object;
	temp_value.color_object			= color_obj;
	obj_list.push_back(temp_value);
}

returned_str win(WINOBJ* win_conf, std::vector<list_of_objects> obj_list) {
	returned_str		returned_value;

	list_of_objects		temp_item;


	bool 				cycle,
						first_write;


	cycle				= true;
	first_write			= true;

	while (cycle) {
		for (unsigned int	i	= 0; i < obj_list.size(); i++) {
			temp_item	= obj_list[i];

			#ifdef DEBUG
			log_write("Object number: " + str(i));
			log_write("Function point: 0x" + str(temp_item.point_to_function));
			log_write("Struct point: 0x" + str(temp_item.point_to_struct));
			log_write("Text: " + temp_item.text);
			#endif

			temp_item.point_to_function(temp_item.point_to_struct, temp_item.text, temp_item.color_object);	// Вызов нужного объекта

/*			if (first_write) {
				InitWINOBJ(temp_winobj);
				win_object	= temp_item.point_to_struct;
				win_object.redraw	= false;
				obj_list[i]	= temp_item;
			}*/

		}

		first_write	= false;
		cycle		= false;
	}
}

int main() {
	initscr();
	start_color();
	keypad (stdscr, true);
	noecho();
	curs_set(0);
	erase();

	vector<list_of_objects> obj_list;

	InitWINOBJ(test_button);
	test_button.posX	= 12;
	test_button.posY	= 13;

	add_to_win(obj_list, WIN_BUTTON, "TEST", 13, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST2", 14, &test_button);
	win(NULL, obj_list);

	endwin();
	return 0;
}