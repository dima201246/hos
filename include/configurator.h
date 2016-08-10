#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

	#include <vector>
	#include <string>
	#include <fstream>

	extern	std::vector <std::string>	main_config_base;

	std::string configurator(std::string /*Путь к файлу*/, std::string /*Искомый параметр*/, std::string /*Новое значение, если нужна перезапись*/, bool /*Перезапись значения или нет*/); // Поиск в файле нужного параметра и возврат его значения
	void add_to_file(std::string /*Путь к файлу*/, std::string /*Строка, которая будет добавлена*/); // Запись в конец файла

	template <typename InputT>
	void add_to_file(std::string link_to_file, InputT parametr) { // Запись в файл
		std::ofstream out_file;
		out_file.open(link_to_file.c_str(), std::ios::out | std::ios::app);
		out_file << parametr << std::endl;
		out_file.close();
	}

	void add_to_filef(std::string, std::string fmt, ...);	// ISCA_Log by Viktor Ohotnikov  (viktorokh96@mail.ru)

	std::string conf(std::string /*Искомый параметр*/, std::vector<std::string> /*вектор со значениями*/); //Поиск в векторе нужного параметра и возврат его значения
	bool load_to_vector(std::string /*Имя файла*/, std::vector<std::string>&  /*Ссылка на вектор*/); // Загрузка файла в вектор
	// #define log_write(line)	add_to_file(MAIN_LOGFILE, line);

#endif