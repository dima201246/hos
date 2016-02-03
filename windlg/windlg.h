#ifndef WINDLG_H
#define WINDLG_H
	#include <string>
	#include <vector>
	struct DLGSTR {
		std::string title, // Title
		line, // Text
		f_button, // Text on first button (maybe empty)
		s_button, // Text on second button (maybe empty)
		t_button; // Text on third button (maybe empty)
		int num_of_chars, // Maximum number of input characters (not work)
		type_input, // TYPE INPUT (not work)
		style, // STYLE
		keys, // Number of keys (1 - 3)
		fix_size; // Unknown
		unsigned int xpos, ypos,
		xmax, ymax,
		selected; // Initial choice
		unsigned int xreturn, yreturn, second_border;
		bool border_menu, avtive_menu;
	};
	
	int dlg_win(DLGSTR, std::string&);
	int msg_win(DLGSTR);
	void menu_win(DLGSTR&, std::vector<std::string>&);
	
	/* TYPE INPUT:
	0 - any signs
	1 - only numbers
	2 - only signs, not numbers
	3 - only letters, not special symbols, not numbers
	*/
	
	/* STYLE:
	0 - classic, white text
	1 - red text
	2 - green text
	3 - blue text
	4 - yellow text
	*/
#endif
