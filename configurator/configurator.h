#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

	#include <fstream>
	#include <vector>
	#include <string>
	#include <stdlib.h>

	std::string configurator(std::string /*Путь к файлу*/, std::string /*Искомый параметр*/, std::string /*Новое значение, если нужна перезапись*/, bool /*Перезапись значения или нет*/); // Поиск в файле нужного параметра и возврат его значения
	void add_to_file(std::string /*Путь к файлу*/, std::string /*Строка, которая будет добавлена*/); // Запись в конец файла
	std::string conf(std::string /*Искомый параметр*/, std::vector<std::string> /*вектор со значениями*/); //Поиск в векторе нужного параметра и возврат его значения
	bool load_to_vector(std::string /*Имя файла*/, std::vector<std::string>&  /*Ссылка на вектор*/); // Загрузка файла в вектор

#endif
