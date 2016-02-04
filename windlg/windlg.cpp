#include <unistd.h>
#include <stdio.h>
#include <curses.h>

#include "windlg.h"
#include "../lang/lang.h"

/*BUGS

- Длинные строки роняют систему (26.01.16) {!!!} - Исправленно
	Добавлено 26.01.16 01:48 - Ошибка где-то в ф-ции count_lines, скорее всего не правильно сносит строку
	Добавлено 26.01.16 02:03 - Вылет при длинной строке удалён, проблема была, в том, что ф-ция count_lines не знала maxX,
								осталось только понять почему окно не редактирует размер. Статус ошибки понижен {!}
	Добавлено 26.01.16 10:18 - Ошибка полностью исправлена (max_line = maxX; >> max_line = maxX - 4; #66)
*/

/*Tips
- Вынести все вычисления из цикла - Выполненно
*/

#define DEBUG 0
#define WINDOWS_XP_SIMULATION 0

#define BACKSPACE_KEY 127
#define DEL_KEY 330
#define TAB_KEY 9
#define CtrlF1 289

using namespace std;

const string win_ver = "0.1";

unsigned int count_lines(string line, unsigned int maxX) { // Счётчик кол-ва строк через знак новой строки
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

void load_array(string *array, unsigned int all_lines, string line, unsigned int& max_line, unsigned int maxX) {
	unsigned int count = 0, count_chars = 0;
	string temp;
	temp.clear();
	bool continue_stat = false;
	for (unsigned int i = 0; i < line.length(); i++) {
		if (continue_stat) {continue_stat = false; continue;}
		if ((line[i] == '/') && (line[i + 1] == 'n')) {
			array[count] = temp;
			temp.clear();
			if (max_line < (array[count].length())) max_line = array[count].length();
			count++;
			count_chars = 0;
			continue_stat = true;
			continue;
		}
		count_chars++;
		if (count_chars == (maxX - 4)) {
			array[count] = temp;
			temp.clear();
			count++;
			count_chars = 0;
			max_line = maxX - 4;
		}
		temp += line[i];
	}
	array[count] = temp;
	if (max_line < (array[count].length())) max_line = array[count].length();
	return;
}

string out_line(string line, unsigned pos/*Позиция указателя*/, unsigned right_pos/*На сколько сдвинута строка вправо*/, unsigned int maxX) {
	if (right_pos != 0) { // Обрезка строки с конца
		for (unsigned i = 0; i <= right_pos; i++)
			line.erase(0, 1);
		line.insert(0, "&");
	}
	if ((line.length()) > maxX) { // Обрезка строки с начала
		while ((line.length()) > maxX)
			line.erase(line.length() - 1, 1);
		line.erase(line.length() - 1, 1);
		line += "&";
	}
	return line;
}

void info_win() {
	erase();
	printw(":DV company 2016 (c)\n\n");
	printw("Standart windows library HOS\n\n");
	printw("Autor: Dmitriy Volchenko (dima201246)\n\n");
	printw("Ver.%s", win_ver.c_str());
	getch();
}

int search_max_vectro(vector<string> items, string title) {
	unsigned int max = llength(title);
	string temp;
	for (unsigned int i = 0; i < items.size(); i++) {
		temp = items[i];
		if (max < llength(temp)) max = llength(temp);
	}
	return max;
}

void menu_win(DLGSTR& dlgcfg, vector<string>& items) {
	DLGSTR local_cfg = dlgcfg;
	unsigned int max_x = search_max_vectro(items, local_cfg.title), // Получение длины самого длинного элемента
				max_y = items.size(), // Получение длины списка
				min_y = 0, maxX, maxY;
	int fix_border = 0, fix_title = 0;
	bool vert_scrollbar = false/*Выводить ли с боку прогрессбар прокрутки*/, past_pointer = false;/*Чтобы указатели прогресса не уходили вниз*/
	getmaxyx(stdscr, maxY, maxX);
	dlgcfg.second_border = items.size();
	if (local_cfg.border_menu) fix_border = 2;
	if (llength(local_cfg.title)) fix_title = 1;
	dlgcfg.yreturn = 0; // Онуление возврата по Y
	if (local_cfg.ymax != 0) max_y = local_cfg.ymax; // Присвоение размера менюшки
	if ((local_cfg.ypos + max_y + fix_border + fix_title) >= maxY) { // Проверка на "влезание" в экран
		if (((local_cfg.ypos + max_y + fix_border + fix_title) - maxY) <= local_cfg.ypos) local_cfg.ypos -= ((local_cfg.ypos + max_y + fix_border + fix_title) - maxY); // Сдвиг окошка вверх, если не хватает места
		else {
			local_cfg.keys = 1;
			local_cfg.style = 1;
			local_cfg.title.clear();
			local_cfg.line = "Ooops... I can't find free space for menu!";
			msg_win(local_cfg);
			return;
		}
	}
	if (local_cfg.xmax != 0) max_x = local_cfg.xmax;
	if ((local_cfg.xpos + max_x + fix_border) >= maxX) {
		if (((local_cfg.xpos + max_x + fix_border) - maxX) <= local_cfg.xpos) local_cfg.xpos -= ((local_cfg.xpos + max_x + fix_border) - maxX); // Сдвиг окошка влево, если не хватает места
		else {
			local_cfg.keys = 1;
			local_cfg.style = 1;
			local_cfg.title.clear();
			local_cfg.line = "Ooops... I can't find free space for menu!";
			msg_win(local_cfg);
			return;
		}
	}
	if ((items.size() > max_y) && (!local_cfg.not_view_scrollbar)) vert_scrollbar = true;
	if (local_cfg.selected == 0) local_cfg.selected = 1;
	if (local_cfg.selected > items.size()) local_cfg.selected = items.size(); 
	if (max_y < local_cfg.selected) { // Если нужно сжать окошка
		dlgcfg.yreturn = max_y; // Чтобы новое окно, если что, не уехало вниз
		min_y = local_cfg.selected - max_y; // Чтобы элементы, которые выше видимой области не выводились
		local_cfg.selected = max_y + min_y; // Исправление выбора
	}
	switch (local_cfg.style) { // Цветовая схема окна
		case 1: local_cfg.style = 2; break; // RED
		case 2: local_cfg.style = 4; break; // GREEN
		case 3: local_cfg.style = 6; break; // BLUE
		case 4: local_cfg.style = 8; break; // YELLOW
		default: local_cfg.style = 0; break;
	}
	attron(COLOR_PAIR(local_cfg.style) | A_BOLD);
	if (local_cfg.border_menu) { // Вывод границ, если они нужны
		for (unsigned int i = 0; i < (max_x + 2); i++) { // Вывод верхней и нижней границы
			mvprintw(local_cfg.ypos, local_cfg.xpos + i, "-");
			mvprintw((local_cfg.ypos + max_y + 1 + fix_title), local_cfg.xpos + i, "-");
		}
		local_cfg.xpos++; // Смещение текста
		local_cfg.ypos++;
		for (unsigned int i = 0; i < max_y; i++) {
			mvprintw(local_cfg.ypos + i + fix_title, local_cfg.xpos + max_x, "|"); // Вывод правой границы
			if ((vert_scrollbar) && (!past_pointer) && ((100 / max_y * (i + 1)) >= (local_cfg.selected * 100 / items.size()))) { // Очень крутая формула вывода прогресса спуска в списке
				past_pointer = true; // Чтобы указатели прогресса не уходили вниз
				mvprintw(local_cfg.ypos + i + fix_title, local_cfg.xpos - 1, "]"); // Вывод Указателя
			} else mvprintw(local_cfg.ypos + i + fix_title, local_cfg.xpos - 1, "|"); // Вывод левой границы
		}
	}
	if ((vert_scrollbar) && (!local_cfg.border_menu)) { // Вывод границы слева, если нужна прокрутка
		for (unsigned int i = 0; i < max_y; i++) {
			if ((!past_pointer) && ((100 / max_y * (i + 1)) >= (local_cfg.selected * 100 / items.size()))) { // Очень крутая формула вывода прогресса спуска в списке
				past_pointer = true; // Чтобы указатели прогресса не уходили вниз
				mvprintw(local_cfg.ypos + i + fix_title, local_cfg.xpos, "]"); // Вывод Указателя
			} else mvprintw(local_cfg.ypos + i  + fix_title, local_cfg.xpos, "|"); // Вывод левой границы
		}
		local_cfg.xpos++; // Смещение текста
	}
	local_cfg.ypos += fix_title; // Добавление заголовка
	if (llength(local_cfg.title) > max_x) { // Обрезка слишком длинного заголовка
		local_cfg.title.erase(max_x - 3, llength(local_cfg.title));
		local_cfg.title += "...";
	}
	if (fix_title) { // Использование int как bool, 0 == false, >0 == true
		if (local_cfg.border_menu) {
			mvprintw(dlgcfg.ypos + 1, local_cfg.xpos + max_x, "|"); // Вывод правой границы
			mvprintw(dlgcfg.ypos + 1, local_cfg.xpos - 1, "|"); // Вывод левой границы
		}
		attron(COLOR_PAIR(local_cfg.style + 1) | A_BOLD);
		for (unsigned int spaces = 0; spaces < max_x; spaces++, mvprintw(dlgcfg.ypos + local_cfg.border_menu, max_x - spaces + local_cfg.border_menu, " ")); // Заливка заголовка
		mvprintw(dlgcfg.ypos + local_cfg.border_menu, local_cfg.xpos, "%s", local_cfg.title.c_str()); // Вывод заголовка
		attroff(COLOR_PAIR(local_cfg.style + 1) | A_BOLD);
	}
	attroff(COLOR_PAIR(local_cfg.style) | A_BOLD);
	string temp;
	for (unsigned int i = min_y; i < items.size(); i++) {
		if (i >= max_y + min_y) continue;
		temp = items[i];
		if ((local_cfg.selected - 1) == i) attron(COLOR_PAIR(local_cfg.style + 1)/* | A_BOLD*/); // Выделение пункта
		else attron(COLOR_PAIR(local_cfg.style) | A_BOLD);
		if (llength(temp) > max_x) { // Обрезка слишком длинных строк
			temp.erase(max_x - 3, llength(temp));
			temp += "...";
		}
		mvprintw(local_cfg.ypos + i - min_y, local_cfg.xpos, "%s", temp.c_str()); // Вывод элемента
		if (llength(temp) < max_x) { // Если не хватает пробелов до границы
			unsigned int length_temp = llength(temp);
			for (unsigned int j = 0; j < (max_x - length_temp); j++) { // Добавление пробелов
				temp += " ";
				mvprintw(local_cfg.ypos + i - min_y, local_cfg.xpos + length_temp + j, " ");
			}
			items[i] = temp; // Сохранение пробелов в векторе
		}
		if ((local_cfg.selected - 1) == i) {
			attroff(COLOR_PAIR(local_cfg.style + 1)/* | A_BOLD*/); // Выделение пункта
			dlgcfg.xreturn = local_cfg.xpos + max_x;
			if (dlgcfg.yreturn == 0)
				dlgcfg.yreturn = local_cfg.ypos + i;
		} else attroff(COLOR_PAIR(local_cfg.style) | A_BOLD);
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
	if (dlgcfg.line.length() == 0) return 0;
	timeout(-1);
	unsigned int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX); // Получение размера терминала
	if (maxY < 10) return -1;
	unsigned int all_lines = count_lines(dlgcfg.line, maxX)/*размер по y*/;
	unsigned int max_line = 0/*Размер по x*/;
	if (dlgcfg.keys > 3) dlgcfg.keys = 3;
	if (dlgcfg.keys < 0) dlgcfg.keys = 1;
	if ((dlgcfg.keys == 1) || (dlgcfg.keys == 0)) {
		dlgcfg.keys = 1;
		if (dlgcfg.f_button.length() == 0) dlgcfg.f_button = "OK";
		max_line += dlgcfg.f_button.length() + 4; // Размер кнопок, расстояние до границ и пропуск между кнопками
	}
	if (dlgcfg.keys == 2) {
		if (dlgcfg.f_button.length() == 0) dlgcfg.f_button = "OK";
		if (dlgcfg.s_button.length() == 0) dlgcfg.s_button = "Cancel";
		max_line += dlgcfg.f_button.length() + dlgcfg.s_button.length() + 5; // Размер кнопок, расстояние до границ и пропуск между кнопками
	}
	if (dlgcfg.keys == 3) {
		if (dlgcfg.f_button.length() == 0) dlgcfg.f_button = "Yes";
		if (dlgcfg.s_button.length() == 0) dlgcfg.s_button = "No";
		if (dlgcfg.t_button.length() == 0) dlgcfg.t_button = "Cancel";
		max_line += dlgcfg.f_button.length() + dlgcfg.s_button.length() + dlgcfg.t_button.length() + 8; // Размер кнопок, расстояние до границ и пропуск между кнопками
	}

	switch (dlgcfg.style) { // Цветовая схема окна
		case 1: dlgcfg.style = 2; break; // RED
		case 2: dlgcfg.style = 4; break; // GREEN
		case 3: dlgcfg.style = 6; break; // BLUE
		case 4: dlgcfg.style = 8; break; // YELLOW
		default: dlgcfg.style = 0; break;
	}

	string *array = new string[all_lines];
	load_array(array, all_lines, dlgcfg.line, max_line, maxX);
	unsigned int i; // Основная позиционная переменная!
	int fix = 0; // Фикс для четного и нечетного кол-ва знаков в строке
	max_line += 4; // Границы и пропуск до границ
	bool cycle = true;
	int active_input = 1;
	if ((dlgcfg.selected > 0) && (dlgcfg.selected <= (unsigned)dlgcfg.keys)) active_input = dlgcfg.selected; // Изменение стандартной позиции выделения
	if ((max_line % 2) == 0) fix = 1;
	unsigned int cn;
	string line_out, banka;
	dlgcfg.line.clear();
	line_out = "|";
	int s_key_pos = (((maxX / 2 - max_line / 2) + (dlgcfg.f_button.length() + 3)) + ((maxX / 2 + max_line / 2 - fix) - (dlgcfg.t_button.length() + 3))) / 2;
	int left_border_x = maxX / 2 - (max_line / 2),
		right_border_x = maxX / 2 + (max_line / 2) - fix;
	int title_fix = 0; // Сдвиг строки текста вниз, для красоты, когда активирован заголовок
	if (dlgcfg.title.length() != 0) title_fix = 1;
	while (cycle) {
		erase();
		#if DEBUG == 1
		mvprintw(0, 0, "cn: %i", cn);
		mvprintw(all_lines + 7, 0, "max_line: %i\nMaxX: %i\nMaxY: %i", max_line, maxX, maxY);
		#endif
		for (i = 0; i < max_line; i++) {
			attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			mvprintw(0, left_border_x + i, "="); // Верхняя граница окна
			mvprintw(all_lines + 4	 + title_fix, left_border_x + i, "="); // Нижняя граница окна
			attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			if ((i <= (max_line - 2)) && (dlgcfg.title.length() != 0)) { // Залитие заголовка цветом 
				attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
				mvprintw(1, left_border_x + 1 + i, " ");
				attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
			}
		}
		if (dlgcfg.title.length() > (max_line - 2)) {
			dlgcfg.title.erase(max_line - 5, dlgcfg.title.length());
			dlgcfg.title += "...";
		}
		if (dlgcfg.title.length() != 0) { // Вывод или не вывод заголовка
			attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
			mvprintw(1, left_border_x + 1, "%s", dlgcfg.title.c_str());
			attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
		}
		
		attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
		mvprintw(1, left_border_x, "|"); // Левая граница
		mvprintw(1, right_border_x, "|"); // Правая граница
		for (i = 0; i < all_lines; i++) // Вывод текста и границ
			mvprintw(i + 2 + title_fix, maxX / 2 - (array[i].length() / 2), "%s", array[i].c_str()); // Вывод текста

		for (int k = 0; k <= 3 + title_fix; k++) { // Вывод оставшихся границ окна
			mvprintw(i + k, left_border_x, "|");
			mvprintw(i + k, right_border_x, "|");
		}
		attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);

		if (active_input == 1) attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);		
		if (active_input != 1) attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);		
		if (dlgcfg.keys > 1)
			mvprintw(i + 3 + title_fix, left_border_x + 2, " %s ", dlgcfg.f_button.c_str()); // Первая кнопка
		else mvprintw(i + 3 + title_fix, maxX / 2 - (dlgcfg.f_button.length() / 2) - 1, " %s ", dlgcfg.f_button.c_str()); // Центровка первой кнопки (Если она одна)
		if (active_input != 1) attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);		
		if (active_input == 1) attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);

		if (dlgcfg.keys  == 2) {
			if (active_input == 2) attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
			if (active_input != 2) attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			mvprintw(i + 3 + title_fix, maxX / 2 + (max_line / 2) - dlgcfg.s_button.length() - 3 - fix, " %s ", dlgcfg.s_button.c_str()); // Вторая кнопка
			if (active_input != 2) attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			if (active_input == 2) attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
		}

		if (dlgcfg.keys  == 3) {
			if (active_input == 2) attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
			if (active_input != 2) attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			mvprintw(i + 3 + title_fix, s_key_pos - dlgcfg.s_button.length() / 2, " %s ", dlgcfg.s_button.c_str()); // Вторая кнопка
			if (active_input != 2) attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			if (active_input == 2) attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
			if (active_input == 3) attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
			if (active_input != 3) attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			mvprintw(i + 3 + title_fix, maxX / 2 + (max_line / 2) - dlgcfg.t_button.length() - 3 - fix, " %s ", dlgcfg.t_button.c_str()); // Вторая кнопка
			if (active_input != 3) attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			if (active_input == 3) attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
		}

		cn = getch();
		switch (cn) {
			case CtrlF1: info_win(); break;
			case KEY_LEFT: if (active_input != 1) active_input--; break;
			case KEY_RIGHT: if (active_input != dlgcfg.keys) active_input++; break;
			case TAB_KEY:
					if (active_input != dlgcfg.keys) active_input++;
					else active_input = 1; break;
			// case 27: out_put.clear(); delete [] array; return 0; break;
			case '\n': if (active_input != 0) {
							delete [] array;
							switch (active_input) {
								case 1: return 1; break;
								case 2: return 2; break;
								case 3: return 3; break;
							}
						} break;
		}

	}
	delete [] array;
	return 0;
}

int dlg_win(DLGSTR dlgcfg, string& out_put) {
	if (dlgcfg.line.length() == 0) return 0;
	timeout(-1);
	unsigned int maxX, maxY;
	getmaxyx(stdscr, maxY, maxX); // Получение размера терминала
	if (maxY < 10) return -1;
	unsigned int all_lines = count_lines(dlgcfg.line, maxX)/*размер по y*/;
	unsigned int max_line = 0/*Размер по x*/;
	if (dlgcfg.keys > 3) dlgcfg.keys = 3;
	if (dlgcfg.keys < 0) dlgcfg.keys = 1;
	if ((dlgcfg.keys == 1) || (dlgcfg.keys == 0)) {
		dlgcfg.keys = 1;
		if (dlgcfg.f_button.length() == 0) dlgcfg.f_button = "OK";
		max_line += dlgcfg.f_button.length() + 4; // Размер кнопок, расстояние до границ и пропуск между кнопками
	}
	if (dlgcfg.keys == 2) {
		if (dlgcfg.f_button.length() == 0) dlgcfg.f_button = "OK";
		if (dlgcfg.s_button.length() == 0) dlgcfg.s_button = "Cancel";
		max_line += dlgcfg.f_button.length() + dlgcfg.s_button.length() + 5; // Размер кнопок, расстояние до границ и пропуск между кнопками
	}
	if (dlgcfg.keys == 3) {
		if (dlgcfg.f_button.length() == 0) dlgcfg.f_button = "Yes";
		if (dlgcfg.s_button.length() == 0) dlgcfg.s_button = "No";
		if (dlgcfg.t_button.length() == 0) dlgcfg.t_button = "Cancel";
		max_line += dlgcfg.f_button.length() + dlgcfg.s_button.length() + dlgcfg.t_button.length() + 8; // Размер кнопок, расстояние до границ и пропуск между кнопками
	}

	switch (dlgcfg.style) { // Цветовая схема окна
		case 1: dlgcfg.style = 2; break; // RED
		case 2: dlgcfg.style = 4; break; // GREEN
		case 3: dlgcfg.style = 6; break; // BLUE
		case 4: dlgcfg.style = 8; break; // YELLOW
		default: dlgcfg.style = 0; break;
	}

	string *array = new string[all_lines];
	load_array(array, all_lines, dlgcfg.line, max_line, maxX);
	unsigned int i; // Основная позиционная переменная!
	int fix = 0; // Фикс для четного и нечетного кол-ва знаков в строке
	max_line += 4; // Границы и пропуск до границ
	bool cycle = true;
	int active_input = 0;
	if ((dlgcfg.selected > 0) && (dlgcfg.selected <= (unsigned)dlgcfg.keys)) active_input = dlgcfg.selected; // Изменение стандартной позиции выделения
	if ((max_line % 2) == 0) fix = 1;
	unsigned int cn, pos = 0, right_pos = 0;
	string line_out, banka;
	dlgcfg.line.clear();
	line_out = "|";
	int s_key_pos = (((maxX / 2 - max_line / 2) + (dlgcfg.f_button.length() + 3)) + ((maxX / 2 + max_line / 2 - fix) - (dlgcfg.t_button.length() + 3))) / 2;
	int left_border_x = maxX / 2 - (max_line / 2),
		right_border_x = maxX / 2 + (max_line / 2) - fix;
	int title_fix = 0; // Сдвиг строки текста вниз, для красоты, когда активирован заголовок
	if (dlgcfg.title.length() != 0) title_fix = 1;
	while (cycle) {
		erase();
		#if DEBUG == 1
		mvprintw(0, 0, "cn: %i", cn);
		mvprintw(all_lines + 7, 0, "max_line: %i\nMaxX: %i\nMaxY: %i", max_line, maxX, maxY);
		#endif
		for (i = 0; i < max_line; i++) {
			attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			mvprintw(0, left_border_x + i, "="); // Верхняя граница окна
			mvprintw(all_lines + 6 + title_fix, left_border_x + i, "="); // Нижняя граница окна
			attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			if ((i <= (max_line - 2)) && (dlgcfg.title.length() != 0)) { // Залитие заголовка цветом 
				attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
				mvprintw(1, left_border_x + 1 + i, " ");
				attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
			}
		}
		if (dlgcfg.title.length() > (max_line - 2)) {
			dlgcfg.title.erase(max_line - 5, dlgcfg.title.length());
			dlgcfg.title += "...";
		}
		if (dlgcfg.title.length() != 0) { // Вывод или не вывод заголовка
			attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
			mvprintw(1, left_border_x + 1, "%s", dlgcfg.title.c_str());
			attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
		}
		
		attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
		mvprintw(1, left_border_x, "|"); // Левая граница
		mvprintw(1, right_border_x, "|"); // Правая граница
		for (i = 0; i < all_lines; i++) // Вывод текста и границ
			mvprintw(i + 2 + title_fix, maxX / 2 - (array[i].length() / 2), "%s", array[i].c_str()); // Вывод текста

		for (int k = 0; k <= 5 + title_fix; k++) { // Вывод оставшихся границ окна
			mvprintw(i + k, left_border_x, "|");
			mvprintw(i + k, right_border_x, "|");
		}
		attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);

		if (active_input == 1) attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);		
		if (active_input != 1) attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);		
		if (dlgcfg.keys > 1)
			mvprintw(i + 5 + title_fix, left_border_x + 2, " %s ", dlgcfg.f_button.c_str()); // Первая кнопка
		else mvprintw(i + 5 + title_fix, maxX / 2 - (dlgcfg.f_button.length() / 2) - 1, " %s ", dlgcfg.f_button.c_str()); // Центровка первой кнопки (Если она одна)
		if (active_input != 1) attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);		
		if (active_input == 1) attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);

		if (dlgcfg.keys  == 2) {
			if (active_input == 2) attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
			if (active_input != 2) attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			mvprintw(i + 5 + title_fix, maxX / 2 + (max_line / 2) - dlgcfg.s_button.length() - 3 - fix, " %s ", dlgcfg.s_button.c_str()); // Вторая кнопка
			if (active_input != 2) attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			if (active_input == 2) attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
		}

		if (dlgcfg.keys  == 3) {
			if (active_input == 2) attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
			if (active_input != 2) attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			mvprintw(i + 5 + title_fix, s_key_pos - dlgcfg.s_button.length() / 2, " %s ", dlgcfg.s_button.c_str()); // Вторая кнопка
			if (active_input != 2) attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			if (active_input == 2) attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
			if (active_input == 3) attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
			if (active_input != 3) attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			mvprintw(i + 5 + title_fix, maxX / 2 + (max_line / 2) - dlgcfg.t_button.length() - 3 - fix, " %s ", dlgcfg.t_button.c_str()); // Вторая кнопка
			if (active_input != 3) attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);
			if (active_input == 3) attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
		}

		if (active_input == 0) attron(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
		if (active_input != 0) attron(COLOR_PAIR(dlgcfg.style) | A_BOLD);
		if (active_input == 0) for (unsigned int j = 0; j < max_line - 4; j++) mvprintw(i + 3 + title_fix, left_border_x + j + 2, " "); // Заливка фоном поля длятекста
		mvprintw(i + 3 + title_fix, left_border_x + 2, "%s", out_line(line_out, pos, right_pos, max_line - 4)/*Обрезка текста и тд*/.c_str()); // Вывод текста
		if (active_input != 0) attroff(COLOR_PAIR(dlgcfg.style) | A_BOLD);
		if (active_input == 0) attroff(COLOR_PAIR(dlgcfg.style + 1) | A_BOLD);
		
		cn = getch();
		switch (cn) {
			case CtrlF1: info_win(); break;
			case KEY_LEFT: if (active_input == 0) {
								if (pos != 0) {
									line_out.erase(pos, 1);
									line_out.insert(pos - 1, "|");
									pos--;
									if ((right_pos != 0) && ((pos - right_pos) == 0)) right_pos--;
								}
							} else {
								if (active_input != 1) active_input--;
							} break;
			case KEY_RIGHT: if (active_input == 0) {
								if (pos < (line_out.length() - 1)) {
									line_out.erase(pos, 1);
									line_out.insert(pos + 1, "|");
									pos++;
									if ((pos - right_pos) >= (max_line - 4)) right_pos++;
								}
							} else {
								if (active_input != dlgcfg.keys) active_input++;
							} break;
			case KEY_UP: if (active_input > 0) active_input = 0; break;
			case KEY_DOWN: if (active_input == 0) active_input = 1; break;
			case BACKSPACE_KEY:
					if (active_input != 0) break;
					if (pos != 0) {
						line_out.erase(pos - 1, 1);
						pos--;
						if ((right_pos != 0) && ((pos - 1 - right_pos) /*<*/== 0)) right_pos--;
					} break;
			case TAB_KEY:
					if (active_input != dlgcfg.keys) active_input++;
					else active_input = 0;
			case DEL_KEY:
					if (active_input != 0) break;
					if (pos !=  (line_out.length() - 1)) line_out.erase(pos + 1, 1);
					break;
			// case 27: out_put.clear(); delete [] array; return 0; break;
			case '\n': if (active_input != 0) {
							line_out.erase(pos, 1);
							out_put = line_out;
							delete [] array;
							switch (active_input) {
								case 1: return 1; break;
								case 2: return 2; break;
								case 3: return 3; break;
							}
						} break;
			default:
					if (active_input != 0) break;
					if (((cn < 97) || (cn > 122)) && ((cn < 65) || (cn > 90)) && ((cn < 48) || (cn > 57))) break;
					banka = (char)cn;
					line_out.insert(pos, banka);
					pos++;
					if ((pos - right_pos) >= max_line - 4) right_pos++;
					break;
		}

	}
	delete [] array;
	return 0;
}
