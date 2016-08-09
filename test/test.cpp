#include "test.h"

using namespace std;

void button_obj(/*BUTSTR*/ void *button_conf, string text, color_t color_button) {
	return;
}

void add_to_win(vector<list_of_objects> &obj_list, win_object object_type, std::string text_on_object, color_t color_obj, void* point_to_conf) {
	list_of_objects	temp_value	= {};

	switch (object_type) {
		case WIN_BUTTON:	temp_value.point_to_function	= &button_obj;
							break;
	}

	temp_value.point_to_struct		= point_to_conf;
	temp_value.text					= text_on_object;
	temp_value.color_object			= color_obj;
	obj_list.push_back(temp_value);
}

int main() {
	return 0;
}

returned_str win(WINSTR* win_conf, std::vector<list_of_objects> obj_list) {
	returned_str		returned_value;

}