#include "test.h"

using namespace std;

void button_obj(WINOBJ *button_conf, string text, color_t color_button) {

	printw("In button_obj: %p\nPoint in button: %p\n", &button_obj, button_conf);

	if (button_conf != NULL) {
		printw("posX:   %d\n", button_conf->posX);
		printw("posY:   %d\n", button_conf->posY);
		printw("posXmax:   %d\n", button_conf->posXmax);
		printw("posYmax:   %d\n", button_conf->posYmax);
		printw("Redraw: %d\n\n", (button_conf->redraw ? 1 : 0));
	}
	getch();
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
		WINOBJ *temp_objstr	= new WINOBJ;
		temp_objstr->redraw			= true;
		temp_value.point_to_struct	= temp_objstr;
		temp_value.memory_leak		= true;
	} else {
		point_to_conf->redraw		= true;
		temp_value.point_to_struct	= point_to_conf;
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

			if (first_write) {
				temp_item.point_to_struct->redraw	= false;
				obj_list[i]	= temp_item;
			}

		}
		if (!first_write)
			cycle		= false;

		first_write	= false;
	}

	
	for (unsigned int	i	= 0; i < obj_list.size(); i++) {	// От утечки памяти
		temp_item	= obj_list[i];

		if (temp_item.memory_leak)
			delete temp_item.point_to_struct;
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