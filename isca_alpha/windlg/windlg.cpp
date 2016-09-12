#include <unistd.h>
#include <stdio.h>

#include "../../include/system_defines.h"
#include "../../include/isca_alpha.h"
#include "internal_windlg.h"

// МОЖНО УДАЛИТЬ ДРЕВНИЙ ЛОГ?

#define DEBUG 0
#define WINDOWS_XP_SIMULATION 0

#define BACKSPACE_KEY 127
#define DEL_KEY 330
#define TAB_KEY 9
#define CtrlF1 289

using namespace std;

const string win_ver = "0.2";

unsigned int count_lines(string line, unsigned int maxX) { // Счётчик кол-ва строк через знак новой строки
	// ДИСТИЛЯТОР ИОНИЗИРОВАННОЙ ПЛАЗМАТИЧЕСКОЙ РЕГЕНИРАТИВНОЙ СУБСТАНЦИИ
	unsigned int count = 0, count_chars = 0;
	if (line.length() != 0) count++;
	bool continue_stat = false;
	for (unsigned int i = 0; i < line.length(); i++) {
		if (continue_stat) {continue_stat = false; continue;}
		if ((line[i] == '/') && (line[i + 1] == 'n')) {count++; count_chars = 0; continue_stat = true; continue;}
		count_chars++;
		if (count_chars >= (maxX - 4)) {count++; count_chars = 0;}
	}
	return count;
}

// ПРОСТО LOAD_ARRAY И ИСПОЛЬЗУЙ КАК ХОШ
void load_array(string *array, unsigned int all_lines, string line, unsigned int& max_line, unsigned int maxX) {
	unsigned int	count			= 0,
					count_chars		= 0;

	bool			continue_stat	= false;

	string			temp;

	temp.clear();

	for (unsigned int	i	= 0; i < line.length(); i++) {

		if (continue_stat) {
			continue_stat = false;
			continue;
		}

		if ((line[i] == '/') && (line[i + 1] == 'n')) {
			array[count]	= temp;
			temp.clear();

			if (max_line < (array[count].length()))
				max_line	= array[count].length();
			
			count++;
			count_chars		= 0;
			continue_stat	= true;
			continue;
		}

		count_chars++;

		if (count_chars == (maxX - 4)) {
			array[count]	= temp;
			temp.clear();
			count++;
			count_chars		= 0;
			max_line		= maxX - 4;
		}

		temp	+= line[i];
	}

	array[count]	= temp;

	if (max_line < (array[count].length()))
		max_line	= array[count].length();
}

// ПРОЧИТАЛ КАК OUTLAST!!! ОШИБСЯ, немного
string out_line(string line, unsigned pos/*Позиция указателя*/, unsigned right_pos/*На сколько сдвинута строка вправо*/, unsigned int maxX) {

	if (right_pos != 0) { // Обрезка строки с конца
		for (unsigned int	i	= 0; i <= right_pos; i++)
			line.erase(0, 1);

		line.insert(0, "&");
	}

	if ((line.length()) > maxX) { // Обрезка строки с начала

		while ((line.length()) > maxX)
			line.erase(line.length() - 1, 1);

		line.erase(line.length() - 1, 1);
		line	+= "&";
	}

	return line;
}

string get_ver_windlg() {	// ТОЛЬКО ИЗБРАННЫЕ МОГУТ НАЗЫВАТЬ ТАК СТРУКТУРЫ И БОЛЬШЕ НИКТО!!!!
	return win_ver;
}

void info_win() { 		// ВИНОВНИКИ ТОРЖЕСТВА
	erase();
	printw(":DV company 2016 (c)\n\n");
	printw("Standart windows library HOS\n\n");
	printw("Autor: Dmitriy Volchenko (dima201246)\n\n");
	printw("Ver.%s", win_ver.c_str());
	getch();
}

int search_max_vectro(vector<string> items, string title) { // ЭТА ФУНКЦИЯ ОЧЕНЬ НЕОБХОДИМА!!!! ПРАВДА!!!
	unsigned int	max	= llength(title);

	string			temp;

	for (unsigned int	i	= 0; i < items.size(); i++) {
		temp	= items[i];
		
		if (max < llength(temp))
			max 	= llength(temp);
	}

	return max;
}

void menu_win_old(DLGSTR& dlgcfg, vector<string>& items) {  // ВСЁ НОВОЕ - ЭТО ХОРОШО ПРОПИТОЕ СТАРОЕ!!!
	DLGSTR local_cfg		= dlgcfg;

	if (dlgcfg.selected == 0)
		dlgcfg.selected = 1;

	unsigned int	max_x	= search_max_vectro(items, local_cfg.title), // Получение длины самого длинного элемента
			// ПОЛУЧЕНИЕ ВЫСОТЫ САМОГО ВЫСОГО ЗДАНИЯ!!!!
					max_y	= items.size(), // Получение длины списка
					min_y	= 0,
					maxX,
					maxY,
					pointer_position; // Позиция вывода указателя прогресса

	int		fix_border		= 0,
			fix_title		= 0,
			color_selected; // Цвет выделения

	bool	vert_scrollbar	= false; // Выводить ли с боку прогрессбар прокрутки
	// АЛИ НЕ ВВОДИТЬ...

	getmaxyx(stdscr, maxY, maxX);

	dlgcfg.second_border	= items.size();

	if (local_cfg.border_menu)
		fix_border = 2;

	if (llength(local_cfg.title))
		fix_title = 1;

	dlgcfg.yreturn	= 0; // Онуление возврата по Y
	// ОНУЛЕНИЕ НАШЕ ВСЁ!!!!!!!

	if (local_cfg.ymax != 0)
		max_y = local_cfg.ymax; // Присвоение размера менюшки

	if ((local_cfg.ypos + max_y + fix_border + fix_title) >= maxY) { // Проверка на "влезание" в экран
		// ПРОВЕРКА УРОВНЯ АЛГОГОЛЯ В КРОВИ ПРОГРАММИСТА.................LOADING...............
		if (((local_cfg.ypos + max_y + fix_border + fix_title) - maxY) <= local_cfg.ypos) {
			local_cfg.ypos -= ((local_cfg.ypos + max_y + fix_border + fix_title) - maxY); // Сдвиг окошка вверх, если не хватает места
		} else {
			local_cfg.keys = 1;
			local_cfg.style = 1;
			local_cfg.title.clear();
			local_cfg.line = "Ooops... I can't find free space for menu!";
//............................L...O....A...D...I...N....G...... УРОВЕНЬ АЛКОГОЛЯ ЗАШКАЛИВАЕТ!!!!!!!
			msg_win(local_cfg);
			return;
		}
	}

	if (local_cfg.xmax != 0)
		max_x = local_cfg.xmax;

	if ((local_cfg.xpos + max_x + fix_border) >= maxX) {
		if (((local_cfg.xpos + max_x + fix_border) - maxX) <= local_cfg.xpos) {
			local_cfg.xpos -= ((local_cfg.xpos + max_x + fix_border) - maxX); // Сдвиг окошка влево, если не хватает места
			// А СЛЕВА ГРАЖДАНЕ ПРОТИВ НЕ БУДУТ????
		} else {
			local_cfg.keys = 1;
			local_cfg.style = 1;
			local_cfg.title.clear();
			local_cfg.line = "Ooops... I can't find free space for menu!";
			msg_win(local_cfg);
			return;
		}
	}

	if ((items.size() > max_y) && (!local_cfg.not_view_scrollbar))
		vert_scrollbar = true;

	if (local_cfg.selected == 0)
		local_cfg.selected = 1;
	
	if (local_cfg.selected > items.size())
		local_cfg.selected = items.size(); 

	if (max_y < local_cfg.selected) { // Если нужно сжать окошко
		// СЖАТЬ, РАЗЖАТЬ.... ХМ... ZIP ПРОТОКОЛ АГА!
		dlgcfg.yreturn = max_y; // Чтобы новое окно, если что, не уехало вниз
		// ЕСЛИ ЧТО!!!!!!!!!!!!!!!!! КАРЛ!!!!!!!!!
		min_y = local_cfg.selected - max_y; // Чтобы элементы, которые выше видимой области не выводились
		local_cfg.selected = max_y + min_y; // Исправление выбора
		// ТУТ БЫЛ БАГ!! НО БОЛЬШЕ ЕГО НЕТ!!!! ЭТО НАДО ОТМЕТИТЬ!!! ЧТО БЫ ВСЕ ЗНАЛИ!!!
	}

	switch (local_cfg.style) { // Цветовая схема окна
		case RED_WIN:		local_cfg.style	= TEXT_RED_BLACK;
							color_selected	= TEXT_BLACK_RED;
							break;

		case GREEN_WIN:		local_cfg.style = TEXT_GREEN_BLACK;
							color_selected	= TEXT_BLACK_GREEN;
							break;

		case BLUE_WIN: 		local_cfg.style = TEXT_BLUE_BLACK;
							color_selected	= TEXT_BLACK_BLUE;
							break;

		case YELLOW_WIN: 	local_cfg.style = TEXT_YELLOW_BLACK;
							color_selected	= TEXT_BLACK_YELLOW;
							break;

		case MAGENTA_WIN: 	local_cfg.style = TEXT_MAGENTA_BLACK;
							color_selected	= TEXT_BLACK_MAGENTA;
							break;

		case CYAN_WIN: 		local_cfg.style = TEXT_CYAN_BLACK;
							color_selected	= TEXT_BLACK_CYAN;
							break;

		default:			local_cfg.style = TEXT_WHITE_BLACK;
							color_selected	= TEXT_BLACK_WHITE;
							color_selected	= TEXT_BLACK_WHITE;
							break;
	}

	attron(COLOR_PAIR(local_cfg.style) | A_BOLD);

	if (local_cfg.border_menu) { // Вывод границ, если они нужны
		// МНЕ НЕ НУЖНЫ ГРАНИЦЫ!!! Я АНАРХИСТ!!!!

		for (unsigned int i = 0; i < (max_x + 2); i++) { // Вывод верхней и нижней границы
			mvprintw(local_cfg.ypos, local_cfg.xpos + i, "-");
			mvprintw((local_cfg.ypos + max_y + 1 + fix_title), local_cfg.xpos + i, "-");
		}

		local_cfg.xpos++; // Смещение текста
		local_cfg.ypos++;

		for (unsigned int i = 0; i < max_y; i++) {
			mvprintw(local_cfg.ypos + i + fix_title, local_cfg.xpos + max_x, "|"); // Вывод правой границы
			mvprintw(local_cfg.ypos + i + fix_title, local_cfg.xpos - 1, "|"); // Вывод левой границы
		}

		pointer_position = (((local_cfg.selected - 1) * max_y) / items.size()) + local_cfg.ypos + fix_title;
		mvprintw(pointer_position, local_cfg.xpos - 1, "]"); // Вывод Указателя
		// ВВОД АЛКОГОЛЯЯЯ!!!
	}

	if ((vert_scrollbar) && (!local_cfg.border_menu)) { // Вывод границы слева, если нужна прокрутка
		for (unsigned int i = 0; i < max_y; i++) {
				mvprintw(local_cfg.ypos + i  + fix_title, local_cfg.xpos, "|"); // Вывод левой границы
		}
		pointer_position = (((local_cfg.selected - 1) * max_y) / items.size()) + local_cfg.ypos + fix_title;
		mvprintw(pointer_position, local_cfg.xpos - 1, "]"); // Вывод Указателя

		local_cfg.xpos++; // Смещение текста
	}

	local_cfg.ypos	+= fix_title; // Добавление заголовка

	if (llength(local_cfg.title) > max_x) { // Обрезка слишком длинного заголовка
		local_cfg.title.erase(max_x - 3, llength(local_cfg.title));
		local_cfg.title	+= "...";
	}

	if (fix_title) { // Использование int как bool, 0 == false, >0 == true

		if (local_cfg.border_menu) {
			mvprintw(local_cfg.ypos - 1, local_cfg.xpos + max_x, "|"); // Вывод правой границы
			mvprintw(local_cfg.ypos - 1, local_cfg.xpos - 1, "|"); // Вывод левой границы
		}


		attron(COLOR_PAIR(color_selected));
		for (unsigned int spaces = 0; spaces < max_x - 1; spaces++, mvprintw(local_cfg.ypos - 1, local_cfg.xpos + spaces, " ")); // Заливка заголовка
		mvprintw(local_cfg.ypos - 1, local_cfg.xpos, "%s", local_cfg.title.c_str()); // Вывод заголовка
		attroff(COLOR_PAIR(color_selected));
	}

	attroff(COLOR_PAIR(local_cfg.style) | A_BOLD);
	
	string	temp;

	unsigned int	i; // Вынес для заполнения оставшейся части пробелами, дабы изображение не залипало 
	
	for (i = min_y; i < items.size(); i++) {
		if (i >= max_y + min_y)
			continue;
		
		temp	= items[i];
		
		if ((local_cfg.selected - 1) == i) {
			attron(COLOR_PAIR(color_selected)/* | A_BOLD*/); // Выделение пункта
		} else {
			attron(COLOR_PAIR(local_cfg.style) | A_BOLD);
		}

		if (llength(temp) > max_x) { // Обрезка слишком длинных строк
			temp.erase(max_x - 3, llength(temp));
			temp	+= "...";
		}

		mvprintw(local_cfg.ypos + i - min_y, local_cfg.xpos, "%s", temp.c_str()); // Вывод элемента

		if (llength(temp) < max_x) { // Если не хватает пробелов до границы
			unsigned int	length_temp	= llength(temp);
			
			for (unsigned int j = 0; j < (max_x - length_temp); j++) { // Добавление пробелов
				temp	+= " ";
				mvprintw(local_cfg.ypos + i - min_y, local_cfg.xpos + length_temp + j, " ");
			}
			items[i]	= temp; // Сохранение пробелов в векторе
		}

		if ((local_cfg.selected - 1) == i) {
			attroff(COLOR_PAIR(color_selected)/* | A_BOLD*/); // Выделение пункта
			dlgcfg.xreturn	= local_cfg.xpos + max_x;
		
			if (dlgcfg.yreturn == 0)
				dlgcfg.yreturn	= local_cfg.ypos + i;
		} else {
			attroff(COLOR_PAIR(local_cfg.style) | A_BOLD);
		}
	}

	if (i < (max_y)) { // Если осталось пустое место
		string eraser;
		eraser.clear();
		for (unsigned int es = 0; es < max_x; es++, eraser += " "); // Создание строки с пробелами
		for (unsigned int es = 0; es < (max_y - i); es++, mvprintw(local_cfg.ypos + i + es - fix_title, local_cfg.xpos, "%s", eraser.c_str())); // Заполнение пробелами 
	}

	#if WINDOWS_XP_SIMULATION == 1 // Just for fan :)
	if (dlgcfg.border_menu) {
		dlgcfg.xpos++; // Смещение текста
		dlgcfg.ypos++;
	}
	#endif

	return;
}

int msg_win(DLGSTR dlgcfg) {
	if (dlgcfg.line.length() == 0)
		return 0;

	timeout(-1);

	unsigned int	maxX,
					maxY;

	getmaxyx(stdscr, maxY, maxX); // Получение размера терминала

	if (maxY < 10)
		return -1;
	
	unsigned int	all_lines	= count_lines(dlgcfg.line, maxX), // Размер по y
					max_line	= 0, // Размер по x
					color_selected; // Цвет выделения

	if (dlgcfg.keys > 3)
		dlgcfg.keys	= 3;

	if (dlgcfg.keys < 0)
		dlgcfg.keys	= 1;

	if ((dlgcfg.keys == 1) || (dlgcfg.keys == 0)) {
		dlgcfg.keys	= 1;

		if (dlgcfg.f_button.length() == 0)
			dlgcfg.f_button = "OK";

		max_line	+= dlgcfg.f_button.length() + 4; // Размер кнопок, расстояние до границ и пропуск между кнопками
		// РАССТОЯНИЕ ДО ГРАНИЦ МОЖНО НАЙТИ НА GOOGLE MAPS!!!!!
	}

	if (dlgcfg.keys == 2) {
		if (dlgcfg.f_button.length() == 0)
			dlgcfg.f_button	= "OK";

		if (dlgcfg.s_button.length() == 0)
			dlgcfg.s_button	= "Cancel";

		max_line	+= dlgcfg.f_button.length() + dlgcfg.s_button.length() + 5; // Размер кнопок, расстояние до границ и пропуск между кнопками
	}

	if (dlgcfg.keys == 3) {
		if (dlgcfg.f_button.length() == 0)
			dlgcfg.f_button	= "Yes";

		if (dlgcfg.s_button.length() == 0)
			dlgcfg.s_button	= "No";

		if (dlgcfg.t_button.length() == 0)
			dlgcfg.t_button	= "Cancel";

		max_line	+= dlgcfg.f_button.length() + dlgcfg.s_button.length() + dlgcfg.t_button.length() + 8; // Размер кнопок, расстояние до границ и пропуск между кнопками
	}

	switch (dlgcfg.style) { // Цветовая схема окна
		case RED_WIN:		dlgcfg.style	= TEXT_RED_BLACK;
							color_selected	= TEXT_BLACK_RED;
							break;

		case GREEN_WIN:		dlgcfg.style = TEXT_GREEN_BLACK;
							color_selected	= TEXT_BLACK_GREEN;
							break;

		case BLUE_WIN: 		dlgcfg.style = TEXT_BLUE_BLACK;
							color_selected	= TEXT_BLACK_BLUE;
							break;

		case YELLOW_WIN: 	dlgcfg.style = TEXT_YELLOW_BLACK;
							color_selected	= TEXT_BLACK_YELLOW;
							break;

		case MAGENTA_WIN: 	dlgcfg.style = TEXT_MAGENTA_BLACK;
							color_selected	= TEXT_BLACK_MAGENTA;
							break;

		case CYAN_WIN: 		dlgcfg.style = TEXT_CYAN_BLACK;
							color_selected	= TEXT_BLACK_CYAN;
							break;

		default:			dlgcfg.style = TEXT_WHITE_BLACK;
							color_selected	= TEXT_BLACK_WHITE;
							break;
	}

	string *array	= new string[all_lines];
	load_array(array, all_lines, dlgcfg.line, max_line, maxX);
	
	unsigned int	i, // Основная позиционная переменная!
	// И САМАЯ ГЛАВНАЯ ПОЗИЦИОННАЯ ПЕРЕМЕННАЯ!!! НИКТО НЕ СМЕЕТ ОБИЖАТЬ САМУЮ ГЛАВНУЮ ПОЗИЦИОННУЮ ПЕРЕМЕННУЮ!!!! НИКТО!!
					cn,
					s_key_pos,
					left_border_x,
					right_border_x;

	int				fix				= 0, // Фикс для четного и нечетного кол-ва знаков в строке
					active_input	= 1, // Номер выделенной кнопки
					title_fix		= 0; // Сдвиг строки текста вниз, для красоты, когда активирован заголовок

	bool			cycle			= true;
	
	string			line_out,
					free_space, // Очиститель области
					banka;

	max_line	+= 4; // Границы и пропуск до границ

	if ((dlgcfg.selected > 0) && (dlgcfg.selected <= (unsigned)dlgcfg.keys))
		active_input	= dlgcfg.selected; // Изменение стандартно выделенной кнопки

	if ((max_line % 2) == 0)
		fix	= 1;

	s_key_pos		= (((maxX / 2 - max_line / 2) + (dlgcfg.f_button.length() + 3)) + ((maxX / 2 + max_line / 2 - fix) - (dlgcfg.t_button.length() + 3))) / 2;
	right_border_x	= maxX / 2 + (max_line / 2) - fix;
	left_border_x	= maxX / 2 - (max_line / 2);

	dlgcfg.line.clear();
	free_space.clear();

	line_out	= "|";

	if (dlgcfg.title.length() != 0)
			title_fix	= 1;

	for (i	= 0; i < max_line; i++) {
		attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
		mvprintw(0, left_border_x + i, "="); // Верхняя граница окна
		free_space += " ";
		mvprintw(all_lines + 4 + title_fix, left_border_x + i, "="); // Нижняя граница окна
		attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			
		if ((i <= (max_line - 2)) && (dlgcfg.title.length() != 0)) { // Залитие заголовка цветом 
			attron(COLOR_PAIR(color_selected) | A_BOLD);
			mvprintw(1, left_border_x + 1 + i, " ");
			attroff(COLOR_PAIR(color_selected) | A_BOLD);
		}
	}


	for (i	= (dlgcfg.title.length() == 0) ? 0 : 1; i < all_lines + 3 + title_fix; i++, mvprintw(i, left_border_x, "%s", free_space.c_str())); // Зачистка области

	if (dlgcfg.title.length() > (max_line - 2)) {
		dlgcfg.title.erase(max_line - 5, dlgcfg.title.length());
		dlgcfg.title	+= "...";
	}

	if (dlgcfg.title.length() != 0) { // Вывод или не вывод заголовка
		attron(COLOR_PAIR(color_selected) | A_BOLD);
		mvprintw(1, left_border_x + 1, "%s", dlgcfg.title.c_str());
		attroff(COLOR_PAIR(color_selected) | A_BOLD);
	}

	attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
	mvprintw(1, left_border_x, "|"); // Левая граница
	mvprintw(1, right_border_x, "|"); // Правая граница

	for (i = 0; i < all_lines; i++) { // Вывод текста и границ
		mvprintw(i + 2 + title_fix, maxX / 2 - (array[i].length() / 2), "%s", array[i].c_str()); // Вывод текста
	}

	for (int k = 0; k <= 3 + title_fix; k++) { // Вывод оставшихся границ окна
		mvprintw(i + k, left_border_x, "|");
		mvprintw(i + k, right_border_x, "|");
	}

	attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);

	while (cycle) {
		#if DEBUG == 1
		mvprintw(0, 0, "cn: %i", cn);
		mvprintw(all_lines + 7, 0, "max_line: %i\nMaxX: %i\nMaxY: %i", max_line, maxX, maxY);
		#endif

		if (active_input == 1)
			attron(COLOR_PAIR(color_selected) | A_BOLD);

		if (active_input != 1)
			attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);

		if (dlgcfg.keys > 1) {
			mvprintw(i + 3 + title_fix, left_border_x + 2, " %s ", dlgcfg.f_button.c_str()); // Первая кнопка
		} else {
			mvprintw(i + 3 + title_fix, maxX / 2 - (dlgcfg.f_button.length() / 2) - 1, " %s ", dlgcfg.f_button.c_str()); // Центровка первой кнопки (Если она одна)
		}

		if (active_input != 1)
			attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);		

		if (active_input == 1)
			attroff(COLOR_PAIR(color_selected) | A_BOLD);

		if (dlgcfg.keys  == 2) {
			if (active_input == 2)
				attron(COLOR_PAIR(color_selected) | A_BOLD);

			if (active_input != 2)
				attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);

			mvprintw(i + 3 + title_fix, maxX / 2 + (max_line / 2) - dlgcfg.s_button.length() - 3 - fix, " %s ", dlgcfg.s_button.c_str()); // Вторая кнопка

			if (active_input != 2)
				attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);

			if (active_input == 2)
				attroff(COLOR_PAIR(color_selected) | A_BOLD);
		}

		if (dlgcfg.keys  == 3) {
			if (active_input == 2)
				attron(COLOR_PAIR(color_selected) | A_BOLD);

			// ГДЕ ЧЁРТОВ ОАЗИС?!?!?!?! ТУТ ОДНИ if-Ы !!!!!!!!! 

			if (active_input != 2)
				attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);

			mvprintw(i + 3 + title_fix, s_key_pos - dlgcfg.s_button.length() / 2, " %s ", dlgcfg.s_button.c_str()); // Вторая кнопка

			if (active_input != 2)
				attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);

			if (active_input == 2)
				attroff(COLOR_PAIR(color_selected) | A_BOLD);

			if (active_input == 3)
				attron(COLOR_PAIR(color_selected) | A_BOLD);

			if (active_input != 3)
				attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);

			mvprintw(i + 3 + title_fix, maxX / 2 + (max_line / 2) - dlgcfg.t_button.length() - 3 - fix, " %s ", dlgcfg.t_button.c_str()); // Вторая кнопка

			if (active_input != 3)
				attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);

			if (active_input == 3)
				attroff(COLOR_PAIR(color_selected) | A_BOLD);
		}

		cn	= getch();
		switch (cn) {
			case CtrlF1:	info_win();
							break;

			case KEY_LEFT:	if (active_input != 1)
								active_input--;
							break;

			case KEY_RIGHT:	if (active_input != dlgcfg.keys)
								active_input++;
							break;

			case TAB_KEY:	if (active_input != dlgcfg.keys) {
								active_input++;
							} else {
								active_input = 1;
							}
							break;

			case 27:		delete [] array;
							return 0;
							break;

			case '\n':		if (active_input != 0) {
								delete [] array;
								return active_input;
							}
							break;
		}

	}

	delete [] array;
	return 0;
}

int dlg_win(DLGSTR dlgcfg, string& out_put) {
	if (dlgcfg.line.length() == 0)
		return 0;

	timeout(-1);				// У ТЕБЯ ВЫШЛО ВРЕМЯ!!! ХАКЕР!!!

	unsigned int	maxX,
					maxY;

	getmaxyx(stdscr, maxY, maxX); // Получение размера терминала

	if (maxY < 10)
		return -1;

	unsigned int	all_lines	= count_lines(dlgcfg.line, maxX), // Размер по y
					max_line	= 0; // Размер по x

	if (dlgcfg.keys > 3)
		dlgcfg.keys	= 3;

	if (dlgcfg.keys < 0)
		dlgcfg.keys	= 1;

	if ((dlgcfg.keys == 1) || (dlgcfg.keys == 0)) {
		dlgcfg.keys	= 1;
		
		if (dlgcfg.f_button.length() == 0)
			dlgcfg.f_button	= "OK";

		max_line	+= dlgcfg.f_button.length() + 4; // Размер кнопок, расстояние до границ и пропуск между кнопками
	}

	if (dlgcfg.keys == 2) {
		if (dlgcfg.f_button.length() == 0)
			dlgcfg.f_button	= "OK";

		if (dlgcfg.s_button.length() == 0)
			dlgcfg.s_button	= "Cancel";

		max_line	+= dlgcfg.f_button.length() + dlgcfg.s_button.length() + 5; // Размер кнопок, расстояние до границ и пропуск между кнопками
	}

	if (dlgcfg.keys == 3) {
		if (dlgcfg.f_button.length() == 0)
			dlgcfg.f_button	= "Yes";

		if (dlgcfg.s_button.length() == 0)
			dlgcfg.s_button	= "No";

		if (dlgcfg.t_button.length() == 0)
			dlgcfg.t_button	= "Cancel";

		max_line	+= dlgcfg.f_button.length() + dlgcfg.s_button.length() + dlgcfg.t_button.length() + 8; // Размер кнопок, расстояние до границ и пропуск между кнопками
	}

	int	color_selected; // Цвет выделения

	switch (dlgcfg.style) { // Цветовая схема окна
		case RED_WIN:		dlgcfg.style	= TEXT_RED_BLACK;
							color_selected	= TEXT_BLACK_RED;
							break;

		case GREEN_WIN:		dlgcfg.style = TEXT_GREEN_BLACK;
							color_selected	= TEXT_BLACK_GREEN;
							break;

		case BLUE_WIN: 		dlgcfg.style = TEXT_BLUE_BLACK;
							color_selected	= TEXT_BLACK_BLUE;
							break;

		case YELLOW_WIN: 	dlgcfg.style = TEXT_YELLOW_BLACK;
							color_selected	= TEXT_BLACK_YELLOW;
							break;

		case MAGENTA_WIN: 	dlgcfg.style = TEXT_MAGENTA_BLACK;
							color_selected	= TEXT_BLACK_MAGENTA;
							break;

		case CYAN_WIN: 		dlgcfg.style = TEXT_CYAN_BLACK;
							color_selected	= TEXT_BLACK_CYAN;
							break;

		default:			dlgcfg.style = TEXT_WHITE_BLACK;
							color_selected	= TEXT_BLACK_WHITE;
							break;
	}

	string *array	= new string[all_lines];		// ДА ТЫ ИГРАЕШЬ В ОПАСНЫЕ ИГРЫ!!!!
	// ПРОСТО ARRAY - ЭТО ТАК ИНФОРМАТИВНО!!!! 
	load_array(array, all_lines, dlgcfg.line, max_line, maxX);

	unsigned int	i, // Основная позиционная переменная!
	// ДАК КАК ТЫ ПОСМЕЛ ПОСМОТРЕТЬ НА НЕЁ?!?!?!? ОНА БОГИНЯ!!! ТЫ НЕ ДОСТОЕН ДАЖЕ ПРОСТОГО ВЗГЛЯДА НА
	// ПОЗИЦИОННУЮ ПЕРЕМЕННУЮ! НИКТО НЕ ДОСТОЕН!!! НИКТО!!!!
					cn,
					pos				= 0,
					right_pos		= 0,
					s_key_pos,
					left_border_x,
					right_border_x;

	int				fix				= 0, // Фикс для четного и нечетного кол-ва знаков в строке
					active_input	= 0,
					title_fix;

	bool			cycle			= true;

	string			line_out,
					banka;

	max_line += 4; // Границы и пропуск до границ
	
	if ((dlgcfg.selected > 0) && (dlgcfg.selected <= (unsigned)dlgcfg.keys))
		active_input	= dlgcfg.selected; // Изменение стандартной позиции выделения

	if ((max_line % 2) == 0)
		fix	= 1;
	
	dlgcfg.line.clear();
	
	line_out		= "|";
	s_key_pos		= (((maxX / 2 - max_line / 2) + (dlgcfg.f_button.length() + 3)) + ((maxX / 2 + max_line / 2 - fix) - (dlgcfg.t_button.length() + 3))) / 2;
	left_border_x	= maxX / 2 - (max_line / 2);
	right_border_x	= maxX / 2 + (max_line / 2) - fix;
	title_fix		= 0; // Сдвиг строки текста вниз, для красоты, когда активирован заголовок
	
	if (dlgcfg.title.length() != 0)
		title_fix	= 1;

	while (cycle) {
		erase();

		#if DEBUG == 1
		mvprintw(0, 0, "cn: %i", cn);
		mvprintw(all_lines + 7, 0, "max_line: %i\nMaxX: %i\nMaxY: %i", max_line, maxX, maxY);
		#endif

		for (i	= 0; i < max_line; i++) {
			attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			mvprintw(0, left_border_x + i, "="); // Верхняя граница окна
			mvprintw(all_lines + 6 + title_fix, left_border_x + i, "="); // Нижняя граница окна
			attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			
			if ((i <= (max_line - 2)) && (dlgcfg.title.length() != 0)) { // Залитие заголовка цветом 
				attron(COLOR_PAIR(color_selected) | A_BOLD);
				mvprintw(1, left_border_x + 1 + i, " ");
				attroff(COLOR_PAIR(color_selected) | A_BOLD);
				// ATTROFFИРУЙ МНЕ МОЗГ ПАРЕНЬ! 
			}
		}

		if (dlgcfg.title.length() > (max_line - 2)) {
			dlgcfg.title.erase(max_line - 5, dlgcfg.title.length());
			dlgcfg.title	+= "...";
		}

		if (dlgcfg.title.length() != 0) { // Вывод или не вывод заголовка
			attron(COLOR_PAIR(color_selected) | A_BOLD);
			mvprintw(1, left_border_x + 1, "%s", dlgcfg.title.c_str());
			attroff(COLOR_PAIR(color_selected) | A_BOLD);
		}
		
		attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
		mvprintw(1, left_border_x, "|"); // Левая граница
		mvprintw(1, right_border_x, "|"); // Правая граница

		for (i	= 0; i < all_lines; i++) // Вывод текста и границ
			mvprintw(i + 2 + title_fix, maxX / 2 - (array[i].length() / 2), "%s", array[i].c_str()); // Вывод текста

		for (int	k	= 0; k <= 5 + title_fix; k++) { // Вывод оставшихся границ окна
			mvprintw(i + k, left_border_x, "|");
			mvprintw(i + k, right_border_x, "|");
		}

		attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);

		if (active_input == 1)
			attron(COLOR_PAIR(color_selected) | A_BOLD);		

		if (active_input != 1)
			attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);		

		if (dlgcfg.keys > 1) {
			mvprintw(i + 5 + title_fix, left_border_x + 2, " %s ", dlgcfg.f_button.c_str()); // Первая кнопка
		} else {
			mvprintw(i + 5 + title_fix, maxX / 2 - (dlgcfg.f_button.length() / 2) - 1, " %s ", dlgcfg.f_button.c_str()); // Центровка первой кнопки (Если она одна)
		}

		if (active_input != 1)
			attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);		

		if (active_input == 1)
			attroff(COLOR_PAIR(color_selected) | A_BOLD);

		if (dlgcfg.keys  == 2) {
			if (active_input == 2)
				attron(COLOR_PAIR(color_selected) | A_BOLD);

			if (active_input != 2)
				attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);

			mvprintw(i + 5 + title_fix, maxX / 2 + (max_line / 2) - dlgcfg.s_button.length() - 3 - fix, " %s ", dlgcfg.s_button.c_str()); // Вторая кнопка

			if (active_input != 2)
				attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);

			if (active_input == 2)
				attroff(COLOR_PAIR(color_selected) | A_BOLD);
		}

		if (dlgcfg.keys  == 3) {

			if (active_input == 2)
				attron(COLOR_PAIR(color_selected) | A_BOLD);

			if (active_input != 2)
				attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);

			mvprintw(i + 5 + title_fix, s_key_pos - dlgcfg.s_button.length() / 2, " %s ", dlgcfg.s_button.c_str()); // Вторая кнопка

			if (active_input != 2)
				attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);

			if (active_input == 2)
				attroff(COLOR_PAIR(color_selected) | A_BOLD);

			if (active_input == 3)
				attron(COLOR_PAIR(color_selected) | A_BOLD);

			if (active_input != 3)
				attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);

			mvprintw(i + 5 + title_fix, maxX / 2 + (max_line / 2) - dlgcfg.t_button.length() - 3 - fix, " %s ", dlgcfg.t_button.c_str()); // Вторая кнопка

			// У ТЕБЯ 2 ВТОРЫХ КНОПКИ!!!!!! АААААААААААА! ТЫ ПРОСТО ЛЮТЫЙ!!!! 
			// IF-Ы ЗАХВАТЯТ МИР!!!!! ИИ БУДЕТ СОЗДАН НА IF-АХ!!!!!!!!!1!11!!1!!!!!
			if (active_input != 3)
				attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);

			if (active_input == 3)
				attroff(COLOR_PAIR(color_selected) | A_BOLD);
		}

		if (active_input == 0)
			attron(COLOR_PAIR(color_selected) | A_BOLD);

		if (active_input != 0)
			attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);

		if (active_input == 0)
			for (unsigned int j = 0; j < max_line - 4; j++)
				mvprintw(i + 3 + title_fix, left_border_x + j + 2, " "); // Заливка фоном поля длятекста

		mvprintw(i + 3 + title_fix, left_border_x + 2, "%s", out_line(line_out, pos, right_pos, max_line - 4)/*Обрезка текста и тд*/.c_str()); // Вывод текста

		if (active_input != 0)
			attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);

		if (active_input == 0)
			attroff(COLOR_PAIR(color_selected) | A_BOLD);
		
		cn	= getch();

		switch (cn) {
			case CtrlF1:	info_win();
							break;

			case KEY_LEFT:	if (active_input == 0) {
								if (pos != 0) {
									line_out.erase(pos, 1);
									line_out.insert(pos - 1, "|");
									pos--;
									if ((right_pos != 0) && ((pos - right_pos) == 0))
										right_pos--;
								}
							} else {
								if (active_input != 1) {
									active_input--;
								}
							}
							break;

			case KEY_RIGHT:	if (active_input == 0) {
								if (pos < (line_out.length() - 1)) {
									line_out.erase(pos, 1);
									line_out.insert(pos + 1, "|");
									pos++;
									if ((pos - right_pos) >= (max_line - 4)) right_pos++;
									// ААААААААААААДДДДДДДД!!!!
								}
							} else {
								if (active_input != dlgcfg.keys) {
									active_input++;
								}
							}
							break;

			case KEY_UP:	if (active_input > 0)
								active_input	= 0;
							break;

			case KEY_DOWN:	if (active_input == 0)
								active_input	= 1;
							break;

			case BACKSPACE_KEY:
							if (active_input != 0)
								break;
							if (pos != 0) {
								line_out.erase(pos - 1, 1);
								pos--;
								if ((right_pos != 0) && ((pos - 1 - right_pos) /*<*/== 0))
								right_pos--;
							}
							break;

			case TAB_KEY:	if (active_input != dlgcfg.keys) {
								active_input++;
							} else {
								active_input = 0;
							}
							break;

			case DEL_KEY:	if (active_input != 0)
								break;
							
							if (pos !=  (line_out.length() - 1))
								line_out.erase(pos + 1, 1);
							break;

			case 27:		delete [] array;
							return 0;
							break;

			case '\n':		if (active_input != 0) {
								line_out.erase(pos, 1);
								out_put	= line_out;
								delete [] array;
								return active_input;
							}
							break;

			default:		if (active_input != 0)
								break;
							if (((cn < 97) || (cn > 122)) && ((cn < 65) || (cn > 90)) && ((cn < 48) || (cn > 57)))
								break;

							banka	= (char)cn;
							line_out.insert(pos, banka);
							pos++;
							if ((pos - right_pos) >= max_line - 4)
								right_pos++;
							break;
		}

	}

	delete [] array;
	return 0;
}

/*WINDLG 2.0*/
void windlg_ver() {
	erase();
	printw("|WinDLG API----------------------|\n");
	printw("|Version:                     2.0|\n");
	printw("|                                |\n");
	printw("|Autor:         Dmitriy Volchenko|\n");
	printw("|E-mail:     dima201246@gmail.com|\n");
	printw("|                                |\n");
	printw("|                                |\n");
	printw("|Build date: %s %s|\n", __DATE__, __TIME__);
	printw("|--------------------------------|\n");
	getch();
}

unsigned int	line_length(string	line) {	// Подсчёт колличества элементов в строке без учёта специальных символов
	unsigned int	count,
					continue_count;

	count	= continue_count	= 0;

	for (unsigned int	i	= 0; i < line.length(); i++) {

		if (continue_count) {
			continue_count--;
			continue;
		}

		if ((line[i] == '%') && ((i == 0) || ((i > 0) && (line[i - 1] != '\\'))))
			continue_count	= 2;

		if ((line[i] == '/') && (line[i + 1] == '/'))
			continue;

		if ((line[i] == '/') && (line[i + 1] == '\''))
			continue;

		if ((line[i] == '\'') && ((i == 0) || ((i > 0) && (line[i - 1] != '/'))))
			continue;

		if (continue_count)
			continue;

		count++;
	}

	return count;
}

int	windlg_input(unsigned int	max_size, unsigned int	&firstItem,unsigned int	&lastItem, unsigned int	&selected, bool	progressBar) {

	int	key_pressed	= getch();

	switch (key_pressed) {
		case KEY_UP:			if (selected != 0)
									selected--;
								if ((progressBar) && (selected + 1 == firstItem)) {
									firstItem--;
									lastItem--;
								}
								return KEY_UP;
								break;

		case KEY_DOWN:			if (selected != (max_size - 1))
									selected++;
								if ((progressBar) && (selected == lastItem)) {
									firstItem++;
									lastItem++;
								}
								return KEY_DOWN;
								break;

		case H_KEY_CtrlF1:		windlg_ver();
								break;

		default:				return key_pressed;
								break;
	}

	return 0;
}

void mvprintw_l(unsigned int	y, unsigned int	x, string line, color_t	win_color_local, color_t	win_color_selected, bool	selected) {
	if (selected) {
		attron(COLOR_PAIR(win_color_selected) | A_BOLD);
	} else {
		attron(COLOR_PAIR(win_color_local) | A_BOLD);
	}

	unsigned int	next_sign,			// Позиция следующего знака на экране
					state;				// Состояние
					// operation_count;

	int				continue_count;		// Счётчик количества пропусков

	bool			always_read,
					// found_first_sign,
					color_ok;			// Если было использовано залитие

	color_t			write_color;		// Цвет залития

	state				= 0;
	next_sign			= 0;
	always_read			= false;
	// found_first_sign	= false;
	color_ok			= false;
	write_color			= TEXT_WHITE_BLACK;
	continue_count		= 0;

	for (unsigned int	i	= 0; i < llength(line); i++) {
		if (continue_count) {
			continue_count--;
			continue;
		}

		if ((line[i] == '/') && (line[i + 1] == '/'))	// Пропуск экранировки знака экранирования
			continue;

		if ((line[i] == '/') && (line[i + 1] == '\''))	// Пропуск экранировки ковычки
			continue;

		if ((line[i] == '\'') && ((i == 0) || ((i > 0) && (line[i - 1] != '/')))) {
			if (always_read) {
				always_read	= false;
				attroff(COLOR_PAIR(write_color) | A_BOLD);

				if (selected) {
					attron(COLOR_PAIR(win_color_selected) | A_BOLD);
				} else {
					attron(COLOR_PAIR(win_color_local) | A_BOLD);
				}

				color_ok	= false;
				state		= 0;
			} else {
				always_read	= true;
			}

			continue;
		}

		if ((line[i] == '%') && ((i == 0) || ((i > 0) && (line[i - 1] != '\\'))))	// Если обнаружен неэкранированный специальный знак
			state	= 0;

		switch (state) {
			case 0:		if ((line[i] == '%') && ((i == 0) || ((i > 0) && (line[i - 1] != '\\')))) {
							switch (line[i + 1]) {
								case 'c':							// Цвет
											continue_count	= 2;	// Пропуск вывод 2-х знаков +1
											state			= 1;

											if (color_ok)
												attroff(COLOR_PAIR(write_color) | A_BOLD);	// Сброс цвета, если до этого он был задан

											switch (line[i + 2]) {	// Каким цветом заливать
												case 'w':	if (selected) {
																write_color	= get_color_on_color(TEXT_WHITE_BLACK, win_color_local);
															} else {
																write_color	= TEXT_WHITE_BLACK;
															}
															break;

												case 'y':	if (selected) {
																write_color	= get_color_on_color(TEXT_YELLOW_BLACK, win_color_local);
															} else {
																write_color	= TEXT_YELLOW_BLACK;
															}
															break;

												case 'b':	if (selected) {
																write_color	= get_color_on_color(TEXT_BLUE_BLACK, win_color_local);
															} else {
																write_color	= TEXT_BLUE_BLACK;
															}
															break;

												case 'g':	if (selected) {
																write_color	= get_color_on_color(TEXT_GREEN_BLACK, win_color_local);
															} else {
																write_color	= TEXT_GREEN_BLACK;
															}
															break;

												case 'r':	if (selected) {
																write_color	= get_color_on_color(TEXT_RED_BLACK, win_color_local);
															} else {
																write_color	= TEXT_RED_BLACK;
															}
															break;

												case 'm':	if (selected) {
																write_color	= get_color_on_color(TEXT_MAGENTA_BLACK, win_color_local);
															} else {
																write_color	= TEXT_MAGENTA_BLACK;
															}
															break;

												case 'c':	if (selected) {
																write_color	= get_color_on_color(TEXT_CYAN_BLACK, win_color_local);
															} else {
																write_color	= TEXT_CYAN_BLACK;
															}
															break;


												default:	state			= 0;	// Сброс, если не обнаружен известный знак
														// САМОУБИЙСТВО ЕСЛИ НЕ ОБНАРУЖЕ МОЗГ!!!!!!!!!!!!!!!!!!! ГДЕ КНОПКА САМОУНИЧТОЖЕНИЯ?!?!?!?! 
															continue_count	= 0;
						
															break;

											}

											if (state == 1) {
												if (!color_ok) {
													if (selected) {
														attroff(COLOR_PAIR(win_color_selected) | A_BOLD);
													} else {
														attroff(COLOR_PAIR(win_color_local) | A_BOLD);
													}
												}

												attron(COLOR_PAIR(write_color) | A_BOLD);
												color_ok	= true;
											}
											break;

								case 'l':	// Позиция
											break;

							}
						}
						break;

			case 1:		if ((line[i] == ' ') && (!always_read)) {	// Если обнаружен пробел, то остановить заливку
					// ЕСЛИ ОБНАРУЖЕН ТО ПОБЕЖДЁН!!!
							attroff(COLOR_PAIR(write_color) | A_BOLD);
							if (selected) {
								attron(COLOR_PAIR(win_color_selected) | A_BOLD);
							} else {
								attron(COLOR_PAIR(win_color_local) | A_BOLD);
							}

							color_ok	= false;
							state		= 0;
						}
						break;
		}

		if (continue_count)
			continue;

		mvprintw(y, x + next_sign, "%c", line[i]);
		next_sign++;
	}

	if (color_ok) {
		attroff(COLOR_PAIR(write_color) | A_BOLD);
	} else if (selected) {
		attroff(COLOR_PAIR(win_color_selected) | A_BOLD);
	} else {
		attroff(COLOR_PAIR(win_color_local) | A_BOLD);
	}

}

void draw_box(	int				mode,
		// ТОЛЬКО СВОИ ВЕЛОСИепДЫ ТОЛЬКО ХАРДКОР!!!! АААА!!! 
		// ПОФИГ ЧТО ЕСТЬ ФУНКЙИЯ box()!!!!!!!
				string			title,
				unsigned int	progressBarPos,
				unsigned int	x,
				unsigned int	y,
				unsigned int	end_x,
				unsigned int	end_y,
				color_t			win_color_local,
				color_t			win_color_selected) {

	if (mode == 1) {	// Рисование рамки
		unsigned int	x_i,
						y_i;

		string			emptySpace;

		emptySpace.clear();

		attron(COLOR_PAIR(win_color_local) | A_BOLD);

		for (x_i	= 0; x_i < (end_x - 1); mvprintw(y, (x + x_i), "-"), mvprintw((y + end_y), (x + x_i), "-"), emptySpace	+= " ", x_i++);	// Верхняя и нижняя границы

		for (y_i	= 0; y_i <= end_y; mvprintw((y + y_i), x, "|"), mvprintw((y + y_i), (x + x_i), "|"), y_i++) {	// Левая и правая граница
			if ((y_i != 0) && (y_i != end_y))
				mvprintw((y + y_i), x + 1, "%s", emptySpace.c_str());	// Зачистка области
		}

		if (progressBarPos)
			mvprintw(progressBarPos, x, "]");	// Вывод прогресс-бара

		attroff(COLOR_PAIR(win_color_local) | A_BOLD);

		attron(COLOR_PAIR(win_color_selected) | A_BOLD);

		if (!title.empty()) {					// Вывод заголовка
			if (title.length() > (end_x - 3)) {
				title.erase((end_x - 6), title.length());
				title	+= "...";
			}

			mvprintw(y, x + 2, "%s", title.c_str());
		}

		attroff(COLOR_PAIR(win_color_selected) | A_BOLD);
	}

	if (mode == 2) {	// Обновление прогресс-бара
		unsigned int	y_i;

		attron(COLOR_PAIR(win_color_local) | A_BOLD);

		for (y_i	= 0; y_i <= end_y; mvprintw((y + y_i), x, "|"), y_i++);	// Левая граница

		if (progressBarPos)
			mvprintw(progressBarPos, x, "]");

		attroff(COLOR_PAIR(win_color_local) | A_BOLD);
	}
}

void balance_vector(vector <string>	&items, unsigned int	max_l) {
	string			temp_item;

	for (unsigned int	i	= 0; i < items.size(); i++) {	// Добавление пробелов в конец для выравнивания
		temp_item	= items[i];

		if (line_length(temp_item) < max_l) {
			while (max_l != line_length(temp_item))
				temp_item += " ";
		} else if (line_length(temp_item) > max_l) {
			temp_item.erase(max_l - 3, line_length(temp_item));
			temp_item	+= "...";
		}

		items[i]	= temp_item;
	}
}

unsigned int find_max_length(vector <string>	&items) {	// Поиск самой длиной строки в векторе
	// О ДААААААААААААААААААААААААААААААААААААААААААААААААААААА!!!!!!!!!!!!!!!!!!!!1
	unsigned int	max_l;

	string			temp_item;

	max_l			= 0;

	for (unsigned int	i	= 0; i < items.size(); i++) {	// Поиск самой длинной строки
		temp_item	= items[i];

		if (max_l < line_length(temp_item))
			max_l	= line_length(temp_item);
	}

	return max_l;
}

#ifdef _DEBUG
void fill_field() {
	unsigned int	maxX,
					maxY,
					es;

	string			fill_str;

	fill_str.clear();

	getmaxyx(stdscr, maxY, maxX);	// Получение размеров экрана

	for (es	= 0; es <= maxX; fill_str	+= " ", es++);

	attron(COLOR_PAIR(TEXT_BLACK_GREEN) | A_BOLD);

	for (es	= 0; es <= maxY; mvprintw(es, 0, "%s", fill_str.c_str()), es++);

	attroff(COLOR_PAIR(TEXT_BLACK_GREEN) | A_BOLD);
}
#endif

unsigned int menu_win(MENSTR*	menu_conf, string	title, vector <string>	items, color_t	win_color_local) {

	unsigned int	posX,
					posY,
					posXmax,			// Ограничение размера окошка
					posYmax,
					maxX,				// Размеры экрана
					maxY,
					firstItem,			// Если не лезет в экран, то с какого элемента выводить
					lastItem,			// Если не лезет в экран, то до какого элемента выводить
					// ЕСЛИ НЕ ЛЕЗЕТ - НЕ ЕШЬ!
					selected,			// Выбранный элемент
					maxItemLenght,		// Максимальная длина строки
					i,
					j,
					animation_delay;

	bool			progressBar,		// Выводить ли прогресс-бар
					cycle,
					already_fix,
					redraw_window;		// Если нужно только перерисовать окно

	int				key_pressed,
					border_fix,
					border_fix_x;

	color_t			win_color_selected;

	string			tempItem,
					emptySpace;			// Для очистки области окна

	vector <string>	orig_items;

	orig_items		= items;

	getmaxyx(stdscr, maxY, maxX);	// Получение размеров экрана

	if (menu_conf == NULL) {
		getmaxyx(stdscr, posY, posX);

		if (items.size() < posY)	// Чтобы окошко было посередине
			posY 			= (posY / 2) - (items.size() / 2);

		unsigned int	temp_max	= find_max_length(items);
		
		if (temp_max < posX)
			posX 			= (posX / 2) - (temp_max / 2);

		posXmax			= 0;
		posYmax			= 0;
		border_fix		= 2;	// Если включены границы окна, то добавить ещё две строки
		// ААААА?!?!?! ПОЧЕМУ ДВЕ?! ГДЕ ВЕЛИКИЙ ЗАМЫСЕЛ?!!?! ПОЧЕМУ нЕ  42 ???!?!?!
		animation_delay	= 0;	// Отключение анимации
		// ДОЛОЙ АНИМАЦИЮ!!!!
		redraw_window	= false;
		selected		= 0;
	} else {
		if (menu_conf->no_border) {
			border_fix	= 0;
		} else {
			border_fix	= 2;
		}

		posX			= menu_conf->posX;
		posY			= menu_conf->posY;
		posXmax			= menu_conf->posXmax;
		posYmax			= menu_conf->posYmax;
		animation_delay	= menu_conf->animation_delay;
		redraw_window	= menu_conf->redraw;

		if (menu_conf->std_selected > items.size()) {
			selected		= items.size() - 1;
		} else {
			if (menu_conf->std_selected != 0) {
				selected	= menu_conf->std_selected - 1;
			} else {
				selected	= 0;
			}
		}
	}

	if ((border_fix == 0) && (!title.empty()))
		border_fix	= 1;

	progressBar			= false;
	already_fix			= false;
	firstItem			= 0;
	lastItem			= items.size();
	win_color_selected	= get_inv_color(win_color_local);

	if ((posYmax != 0) && (posYmax < items.size())) {	// Если элементов больше, чем фиксированный размер окна
		// ЕЛСИ КИТАЙЦЕВ БОЛЬШЕ - ТО ДОСТАТЬ МИНИГАН!!!
		lastItem	= posYmax;
		progressBar	= true;
	}

	/*Влезание по Y начало*/
	// РОЖДЕНИЕ ЛЕГЕНДЫ!!!! НАЧАЛО!!!!!!
	if (((posYmax != 0) && ((posY + posYmax + border_fix) >= maxY)) || ((posYmax == 0) && ((posY + items.size() + border_fix) >= maxY))) {
		if (posYmax != 0) {
			if (((posY + border_fix)  >= maxY) && ((posYmax + border_fix) < maxY)) {
				posY			= maxY - (posYmax + border_fix);
			}

			if (((posY + border_fix)  >= maxY) && ((posYmax + border_fix) >= maxY)) {
				posY			= 0;
				posYmax			= maxY - border_fix;

				if (posYmax < items.size()) {
					lastItem	= posYmax;
					progressBar	= true;
				}
			}

			if (((posY + border_fix)  < maxY) && ((posYmax + border_fix) >= maxY)) {
				posYmax			= maxY - (posY + border_fix);

				if (posYmax < items.size()) {
					lastItem	= posYmax;
					progressBar	= true;
				}
			}

			if ((posY + posYmax + border_fix) >= maxY) {
				posY			= maxY - (posYmax + border_fix);
			}

		} else {
			if (((posY + border_fix)  >= maxY) && ((items.size() + border_fix) < maxY)) {
				posY			= maxY - (items.size() + border_fix);
			}

			if (((posY + border_fix)  >= maxY) && ((items.size() + border_fix) >= maxY)) {
				posY			= 0;
				posYmax			= maxY - border_fix;
				lastItem		= posYmax;
				progressBar		= true;
			}

			if (((posY + border_fix)  < maxY) && ((items.size() + border_fix) >= maxY)) {
				posYmax			= maxY - (posY + border_fix);
				lastItem		= posYmax;
				already_fix		= true;
				progressBar		= true;
			}

			if (((posY + items.size() + border_fix) >= maxY) && (!already_fix)) {
				posY			= maxY - (items.size() + border_fix);
			}
		}
	}
	/*Влезание по Y конец*/
	// КОНЕЦ ЛЕГЕНДЫ!!!!!!!!!!

	cycle			= true;
	key_pressed		= KEY_UP;

	if (posXmax == 0) {
		maxItemLenght	= find_max_length(items);
	} else {
		maxItemLenght	= posXmax;
	}

	/*Влезание по X начало*/
	if (border_fix == 2) {
		border_fix_x	= 2;
	} else {
		border_fix_x	= 0;
	}

	if (((posX + posXmax + border_fix_x) >= maxX) || ((posX + maxItemLenght + border_fix_x) >= maxX)) {
		if (posXmax != 0) {
			if (((posX + border_fix_x)  >= maxX) && ((posXmax + border_fix_x) < maxX)) {
				posX			= maxX - (posXmax + border_fix_x);
			}

			if (((posX + border_fix_x)  >= maxX) && ((posXmax + border_fix_x) >= maxX)) {
				posX			= 0;
				posXmax			= maxX - border_fix_x;
			}

			if (((posX + border_fix_x) < maxX) && ((posXmax + border_fix_x) >= maxX)) {
				posXmax			= maxX - (posX + border_fix_x);
			}

			if ((posX + posXmax + border_fix_x) >= maxX) {
				posX			= maxX - (posXmax + border_fix_x);
			}

		} else {
			if (((posX + border_fix_x)  >= maxX) && ((maxItemLenght + border_fix_x) < maxX)) {
				posX			= maxX - (maxItemLenght + border_fix_x);
			}

			if (((posX + border_fix_x)  >= maxX) && ((maxItemLenght + border_fix_x) >= maxX)) {
				posX	= 0;
				maxItemLenght	= maxX - border_fix_x;
			}

			if (((posX + border_fix_x) < maxX) && ((maxItemLenght + border_fix_x) >= maxX)) {
				maxItemLenght	= maxX - (posX + border_fix_x);
			}

			if ((posX + maxItemLenght + border_fix_x) >= maxX) {
				posX			= maxX - (maxItemLenght + border_fix_x);
			}
		}
	}
	/*Влезание по X конец*/

	balance_vector(items, maxItemLenght);

	emptySpace.clear();

	timeout(-1);	// Задержка чтения кнопки с клавиатуры
	// ДЕЛАЕМ ИЗ КОМПА - ДАУНА!!!!

	#ifdef _DEBUG
	fill_field();
	#endif

	if (border_fix == 2) {
		draw_box(1, title, (progressBar == true ? (((selected * posYmax) / items.size()) + (posY + 1)) : 0), posX, posY, (maxItemLenght + border_fix), (posYmax == 0 ? (items.size() + 1) : (posYmax + 1)), win_color_local, win_color_selected);
		posX++;
		posY++;
	}

	if ((selected > lastItem) && (progressBar)) {	// Смещение вывода, если была задана позиция выделения заранее
		lastItem	= selected + 1;
		firstItem	= selected - posYmax + 1;
	}

	while (cycle) {
		if (animation_delay)
			refresh();

		if ((key_pressed == KEY_UP) || (key_pressed == KEY_DOWN)) {		// Обновлять экран только при нажатии этих кнопок
			// А ПРИ НАЖАТИИ ДРУГИХ КНОПОК - ВЫКЛЮЧАЕМ КОМП!!!!!!!!!!!!!!!!!!!!!!
			j	= 0;

			for (i	= firstItem; i < lastItem; i++, j++) {
				tempItem	= items[i];

				mvprintw_l(posY + j, posX, tempItem, win_color_local, win_color_selected, (i == selected ? true : false));	// Вывод строки на экран

				if (animation_delay) {	// Анимация
					usleep(animation_delay * 1000);
					timeout(0);

					if (getch() != -1) {	// Если обнаружена любая нажатая кнопка, то остановить анимацию
						animation_delay	= 0;
						timeout(-1);
					}
				}

				if (animation_delay)
					refresh();
			}

			if (animation_delay) {
				animation_delay	= 0;
				timeout(-1);
			}

			// items.size()	=	posYmax - Формула, по которой находится позиция прогресс-бара
			// selected		=	???
			// ААА?!?!?!?! ВАТ?!
			if (progressBar)
				draw_box(2, title, (((selected * posYmax) / items.size()) + posY), (posX - 1), posY, 0, (posYmax == 0 ? items.size() : posYmax), win_color_local, win_color_selected);
		}

		if (!redraw_window)
			key_pressed = windlg_input(items.size(), firstItem, lastItem, selected, progressBar);

		if (menu_conf != NULL)
			menu_conf->returned_key	= key_pressed;

		if (key_pressed == H_KEY_ENTER) {
			cycle	= false;
		} else if ((key_pressed != KEY_UP) && (key_pressed != KEY_DOWN)) {
			if (menu_conf != NULL)
				menu_conf->returned_selected	= selected;

			return 0;
		}

		if (redraw_window)
			cycle	= false;
	}

	if (menu_conf != NULL) {
		menu_conf->returned_x	= posX + maxItemLenght;
		menu_conf->returned_y	= posY + (selected - firstItem);
		menu_conf->returned_selected	= selected;
	}

	return selected + 1;

	return 0;
}
/*WINDLG 2.0*/
