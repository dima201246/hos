#ifndef ISCA_ALPHA_H
#define ISCA_ALPHA_H

	#include <string>
	#include <vector>
	#include <time.h>
	#include <ncurses.h>
	#include <unistd.h>

	/*TIME START*/

	struct local_time {
		int	hours,
			min,
			sec,
			mon,
			day,
			year;
	};

	local_time		get_time_now();

	/*TIME END*/

	/*CONFIGURATOR START*/

	extern	std::vector <std::string>	main_config_base;

	std::string		configurator(std::string /*Путь к файлу*/, std::string /*Искомый параметр*/, std::string /*Новое значение, если нужна перезапись*/, bool /*Перезапись значения или нет*/); // Поиск в файле нужного параметра и возврат его значения
	void			add_to_file(std::string /*Путь к файлу*/, std::string /*Строка, которая будет добавлена*/); // Запись в конец файла
	std::string		conf(std::string /*Искомый параметр*/, std::vector<std::string> /*вектор со значениями*/); //Поиск в векторе нужного параметра и возврат его значения
	bool			load_to_vector(std::string /*Имя файла*/, std::vector<std::string>&  /*Ссылка на вектор*/); // Загрузка файла в вектор

	/*CONFIGURATOR END*/

	/*FSWORK START*/

	struct FILEINFO {
		std::string	name;		// Имя файла
		time_t		mtime;		// Переменная, содержащая прошедшее время с момента создания
		bool		d_type;		//Папка или нет
		std::string	f_path;		// Full path to this file 
		// ... информация о файле ... 
	};

	bool			FileExists(const std::string&);
	bool			rm_file(std::string);
	int				get_files(std::string, std::vector<FILEINFO>&);
	void			files_sort_by(char/*SORT TYPE*/, std::vector<FILEINFO>&);

	/* SORT TYPE
		n - name
	*/

	/*FSWORK END*/

	/*LANG START*/

	unsigned int	llength(std::string);
	std::string		str(int);

	/*LANG END*/

	/*SCREEN START*/

	/*Types*/
	typedef int	color_t;

	void			init_display();
	void			init_color();
	void			get_normal_inv_color(std::string /*Строка с названием цвета*/, color_t&/*Код цвета*/, color_t&/*Инвертированный цвет*/);
	color_t			get_inv_color(color_t);
	color_t			get_color_on_color(color_t, color_t);


	/*Colors*/
	#define TEXT_WHITE_BLACK	0
	#define TEXT_YELLOW_BLACK	1
	#define TEXT_BLUE_BLACK		2
	#define TEXT_GREEN_BLACK	3
	#define TEXT_RED_BLACK		4
	#define TEXT_MAGENTA_BLACK	5
	#define TEXT_CYAN_BLACK		6

	#define TEXT_BLACK_WHITE	7
	#define TEXT_YELLOW_WHITE	8
	#define TEXT_BLUE_WHITE		9
	#define TEXT_GREEN_WHITE	10
	#define TEXT_RED_WHITE		11
	#define TEXT_MAGENTA_WHITE	12
	#define TEXT_CYAN_WHITE		13

	#define TEXT_WHITE_YELLOW	14
	#define TEXT_BLACK_YELLOW	15
	#define TEXT_BLUE_YELLOW	16
	#define TEXT_GREEN_YELLOW	17
	#define TEXT_RED_YELLOW		18
	#define TEXT_MAGENTA_YELLOW	19
	#define TEXT_CYAN_YELLOW	20

	#define TEXT_WHITE_BLUE		21
	#define TEXT_BLACK_BLUE		22
	#define TEXT_YELLOW_BLUE	23
	#define TEXT_GREEN_BLUE		24
	#define TEXT_RED_BLUE		25
	#define TEXT_MAGENTA_BLUE	26
	#define TEXT_CYAN_BLUE		27

	#define TEXT_WHITE_GREEN	28
	#define TEXT_BLACK_GREEN	29
	#define TEXT_YELLOW_GREEN	30
	#define TEXT_BLUE_GREEN		31
	#define TEXT_RED_GREEN		32
	#define TEXT_MAGENTA_GREEN	33
	#define TEXT_CYAN_GREEN		34

	#define TEXT_WHITE_RED		35
	#define TEXT_BLACK_RED		36
	#define TEXT_YELLOW_RED		37
	#define TEXT_BLUE_RED		38
	#define TEXT_GREEN_RED		39
	#define TEXT_MAGENTA_RED	40
	#define TEXT_CYAN_RED		41

	#define TEXT_WHITE_MAGENTA	42
	#define TEXT_BLACK_MAGENTA	43
	#define TEXT_YELLOW_MAGENTA	44
	#define TEXT_BLUE_MAGENTA	45
	#define TEXT_GREEN_MAGENTA	46
	#define TEXT_RED_MAGENTA	47
	#define TEXT_CYAN_MAGENTA	48

	#define TEXT_WHITE_CYAN		49
	#define TEXT_BLACK_CYAN		50
	#define TEXT_YELLOW_CYAN	51
	#define TEXT_BLUE_CYAN		52
	#define TEXT_GREEN_CYAN		53
	#define TEXT_RED_CYAN		54
	#define TEXT_MAGENTA_CYAN	55

	/*SCREEN END*/

	/*WINDLG START*/

	/*Styles*/
	#define WHITE_WIN	TEXT_WHITE_BLACK
	#define RED_WIN		TEXT_RED_BLACK
	#define GREEN_WIN	TEXT_GREEN_BLACK
	#define BLUE_WIN	TEXT_BLUE_BLACK
	#define YELLOW_WIN	TEXT_YELLOW_BLACK
	#define MAGENTA_WIN	TEXT_MAGENTA_BLACK
	#define CYAN_WIN	TEXT_CYAN_BLACK

	struct DLGSTR {
		std::string title,			// Title
		line,						// Text
		f_button,					// Text on first button (maybe empty)
		s_button,					// Text on second button (maybe empty)
		t_button;					// Text on third button (maybe empty)
		int num_of_chars,			// Maximum number of input characters (not work)
		type_input,					// TYPE INPUT (not work)
		style,						// STYLE
		keys,						// Number of keys (1 - 3)
		fix_size;					// Unknown
		unsigned int xpos, ypos,
		xmax, ymax,
		selected;					// Initial choice
		unsigned int xreturn, yreturn, second_border;
		bool border_menu, active_menu, not_view_scrollbar;
	};

	struct MENSTR {
		bool					no_border,			// Если не нужны границы окна !!!НЕИСПОЛЬЗОВАТЬ!!!
								redraw;				// Если нужно только перерисовать вывод

		int						returned_key;		// Возврат нажатой кнопки

		unsigned int			posX,				// Позиция окна
								posY,
								posXmax,			// Максимальные размеры окна
								posYmax,
								returned_x,			// Возвращаемая позиция выделения
								returned_y,
								animation_delay,	// Время анимации
								std_selected;		// Позиция выделения
	};

	#define Init_MENSTR(var_name) MENSTR var_name = {};

	unsigned int	menu_win(MENSTR*, std::string, std::vector <std::string>, color_t);
	int				dlg_win(DLGSTR, std::string&);
	int				msg_win(DLGSTR);
	void			menu_win_old(DLGSTR&, std::vector<std::string>&);

	/*WINDLG END*/

	/*SETTINGS START*/

	int				settings(std::string/*путь к файлу настроек*/);

	/*SETTINGS END*/

#endif