#include "test.h"

using namespace std;

void button_obj(/*BUTSTR*/ void *button_conf_point, string text, color_t color_button) {
	BUTSTR	*button_conf	= (BUTSTR *)button_conf_point;

	printw("\nIn button_obj: %p\nPoint in button: %p\n", &button_obj, button_conf);

	if (button_conf != NULL) {
		printw("posX:   %d\n", button_conf->posX);
		printw("posY:   %d\n\n", button_conf->posY);
		printw("Redraw: %d\n", (button_conf->redraw ? 1 : 0));
	}

	return;
}

void add_to_win(vector<list_of_objects> &obj_list, win_object object_type, std::string text_on_object, color_t color_obj, void* point_to_conf) {
	list_of_objects	temp_value	= {};

	switch (object_type) {
		case WIN_BUTTON:	temp_value.point_to_function	= &button_obj;
							temp_value.type_obj				= WIN_BUTTON;

							if (point_to_conf == NULL) {
								BUTSTR	temp_button	= {};
								temp_button.redraw	= true;
								temp_value.point_to_struct		= &temp_button;
							} else {
								BUTSTR	*temp_button	= (BUTSTR *)point_to_conf;
								temp_button->redraw	= true;
								temp_value.point_to_struct		= temp_button;
							}

							break;
	}

	temp_value.text					= text_on_object;
	temp_value.color_object			= color_obj;
	obj_list.push_back(temp_value);
}

returned_str win(WINSTR* win_conf, std::vector<list_of_objects> obj_list) {
	returned_str		returned_value;

	list_of_objects		temp_item;

	for (unsigned int	i	= 0; i < obj_list.size(); i++) {
		erase();
		temp_item	= obj_list[i];
		printw("Item number: %d\n", i);
		printw("Function point: %p\n", temp_item.point_to_function);
		printw("Struct point: %p\n", temp_item.point_to_struct);
		printw("Text: %s\n", temp_item.text.c_str());
		temp_item.point_to_function(temp_item.point_to_struct, temp_item.text, temp_item.color_object);	// Вызов нужной функции
		getch();
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

	BUTSTR	test_button	= {};
	test_button.posX	= 12;
	test_button.posY	= 13;

	add_to_win(obj_list, WIN_BUTTON, "TEST", 13, NULL);
	add_to_win(obj_list, WIN_BUTTON, "TEST2", 14, &test_button);
	win(NULL, obj_list);

	endwin();
	return 0;
}