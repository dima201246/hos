/*
	Данный код не распространяется свободно

	:DV company 2016
*/

// VERSION: 0.29.0
// LAST UPDATE: 26.05.2016
#include <ncurses.h>
#include "configurator.h"

using namespace std;

bool always_read = false, edit_found_value = false;

bool save_commit(unsigned int first_pos,string line) {
	for (unsigned int j = first_pos; j < line.length(); j++) {
		if ((line[j] == '#') && (line[j - 1] != '\\')) return true;
		if (line[j] != ' ') return false;
	}
	return false;
}

int search_comment(unsigned int first_pos, string line) {
	for (unsigned int	j	= first_pos; j < line.length(); j++) {
		printw("%c\n", line[j]);
		if ((line[j] == '#') && (line[j - 1] != '\\'))
			return j;
	}
	return 0;
}

bool search_value(string line, string parametr, string new_value, bool edit, string &returned_value) {
	bool	only_read		= true /*Пока ищется параметр*/,
			continue_stat	= false,
			find_first_char	= false,
			not_found		= true;

	string	temp_line,
			temp_return,
			comment;

	int		sh;

	temp_line.clear();
	temp_return.clear();
	comment.clear();

	for (unsigned int i = 0; i < line.length(); i++) {
		if ((only_read) && (!always_read)) { // Чтение, пока не найдено равно или не активно постоянное чтение
			if (line[i] == ' ')
				continue;

			if (line[i] == '\t')
				continue;

			if (line[i] == '=') {
				if (temp_line == parametr) { // Если найденный параметр совпал с искомым
					not_found	= false;
					only_read	= false;

					if ((edit) && ((i + 1) == line.length())) { // Если сразу за знаком равно пустота
						edit_found_value	= true;
						returned_value		= line + " " + new_value;
						return true;
					}

					continue; // Пропуск, чтобы не добавлять равно в ответ
				} else if (edit) {
						returned_value	= line;
						return true;	
					} else {
						return false;
					}
			}

			temp_line	= temp_line + line[i]; // Накопление параметра
		} else {
			if (edit) {
				edit_found_value	= true;

				for (unsigned int	j	= i; j < line.length(); j++) {
					if ((line[j] == '\"') && (line[j - 1] != '\\')) {
						if (always_read) {
							always_read	= false;
							return false;
						} else {
							always_read	= true;
							line.erase(i, line.length());
							returned_value	= line + new_value;
							return false;
						}
					}
				}

				if (always_read)
					return false;

				if ((sh	= search_comment(0, line)) > 0) { // Сохранение комментария в изменённом параметре
					comment	= line;
					comment.erase(0, sh);
					comment.insert(0, " ");
				}

				line.erase(i, line.length());

				returned_value	= line + " " + new_value + comment;
				return true;
			} else {
				if ((!find_first_char) && ((line[i] == ' ') || (line[i] == '\t'))) {
					continue; // Если обнаружены пробелы в самом начале
				} else {
					find_first_char	= true;
				}

				if (continue_stat) { // Если надо что-то пропустить
					continue_stat	= false;
					continue;
				}

				if (line[i] == ' ') {
					if (save_commit(i, line)) {
						break; // Если обнаружен пробел и за ним следует комментарий, то закончить
					}
				}

				if (line[i] == '\\') { // Если обнаружен знак экранирования
					if (line[i + 1] == '#') {
						temp_return		= temp_return + line[i + 1];
						continue_stat	= true;
						continue;
					}

					if (line[i + 1] == '\"') {
						temp_return		= temp_return + line[i + 1];
						continue_stat	= true;
						continue;
					}

					if (line[i + 1] == '%') {
						temp_return		= temp_return + line[i + 1];
						continue_stat	= true;
						continue;
					}
				}

				if (line[i] == '#')
					break;

				if (line[i] == '%') {
					temp_return	= temp_return + " ";
					continue;
				}

				if (line[i] == '\"') { // Если обнаружены кавычки
					if (always_read) { // Если это вторые кавычки
						always_read = false;
						returned_value = temp_return;
						return true;
					} else {
						always_read = true;
						continue;
					}
				}

				temp_return	= temp_return + line[i]; // Накопление результата
			}
		}
	}

	if (edit) {
		returned_value	= line;
		return true;
	}

	returned_value	= temp_return;

	if (not_found) {
		return false; // Если искомый параметр не был найден
	}

	return true;
}

string configurator(string link_to_file, string parametr, string new_value, bool edit) {
	always_read			= false;
	edit_found_value	= false;

	if ((fopen(link_to_file.c_str(), "r")) == NULL)
		return("0x0"); // файл не найден

	string				readText,
						returned_value,
						always_read_temp;

	bool				found_result,
						always_read_bool;

	vector<string>		base;

	returned_value.clear();
	always_read_temp.clear();
	found_result		= false;
	always_read_bool	= false;

	ifstream i(link_to_file.c_str()); // Открытие файла

	while(true) {
		getline(i, readText);
		if (i) {
			if (edit) {
				if ((search_value(readText, parametr, new_value, true, returned_value)) && (!always_read)) {
					base.insert(base.end(), returned_value);
				} else {
					if ((always_read) && (!returned_value.empty())) {
						base.insert(base.end(), returned_value);
					}
				}
			} else {
				if (always_read) {
					always_read_bool = true;
				} else {
					always_read_bool = false;
				}

				if ((search_value(readText, parametr, new_value, false, returned_value)) && (!always_read)) {
					found_result = true;
					if (always_read_bool) {
						return always_read_temp + returned_value;
					} else {
						return returned_value;
					}
				} else
					if (always_read) {
						always_read_temp = always_read_temp + returned_value;
					}
			}
		} else {
			break;
		}
	}

	i.close(); // Закрытие файла

	if ((edit) && (edit_found_value)) {
		ofstream o(link_to_file.c_str()); // Открытие файла для записи

		for (unsigned int i = 0; i < base.size(); i++)
			o << base[i] << endl; // Запись

		o.close(); // Закрыть файл для записи
		return "0x2"; // Изменение завершено
	} else {
		return "0x1"; // Параметр не найден
	}

	if (!found_result) {
		return "0x1"; // Параметр не найден
	} else {
		return returned_value;
	}

	return "0x1";
}

string conf(string parametr, vector<string> conf_base) {
	always_read = false;
	string returned_value, always_read_temp;
	returned_value.clear(); always_read_temp.clear();
	bool found_result = false, always_read_bool = false;
	for (unsigned int i = 0; i < conf_base.size(); i++) {
		if (always_read) always_read_bool = true;
		else always_read_bool = false;
		if ((search_value(conf_base[i], parametr, "", false, returned_value)) && (!always_read)) {
			found_result = true;
			if (always_read_bool) return always_read_temp + returned_value;
			else return returned_value;
		} else if (always_read) always_read_temp = always_read_temp + returned_value;
	}
	if (!found_result) return "0x1"; // Параметр не найден
	else return returned_value;
}


void add_to_file(string link_to_file, string parametr) { // Запись в файл
	FILE		*file;
	file		= fopen(link_to_file.c_str(), "a");
	fprintf(file, "%s\n", parametr.c_str());
	fclose(file);
	return;
}

bool load_to_vector(string link_to_file, vector <string>& list) {
	if ((fopen(link_to_file.c_str(), "r")) != NULL) {
		list.clear();
		string readText;
		ifstream i(link_to_file.c_str()); // Открытие файла
		while(true) {
			getline(i, readText);
			if (i)
				list.insert(list.end(), readText);
			else break;
		}
		i.close(); // Закрытие файла
		return true;
	}
	return false;
}