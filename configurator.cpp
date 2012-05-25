/*
 * configurator.cpp
 *
 *  Created on: 30.05.2011
 *      Author: newmen
 */

#include <boost/regex.hpp>
#include <sstream>

#include "configurator.h"
#include "parse_params_error.h"

Configurator::Configurator() : _need_help(false), _config_file_name(DEFAULT_CONFIG_FILE), _sizeX(0), _sizeY(0),
        _steps(STEPS), _any_step(ANY_STEP), _prefix(DEFAULT_PREFIX) {}

void Configurator::parseParams(int argc, char* argv[]) {
	_program_name = argv[0];

	boost::regex rx_help("-h|--help");
	boost::regex rx_config_file_name("(-c|--config)=([\\/\\w\\._-]+)");
	boost::regex rx_size_x("(-x|--size-x)=(\\d+)");
	boost::regex rx_size_y("(-y|--size-y)=(\\d+)");
    boost::regex rx_steps("(-st|--steps)=(\\d+)");
    boost::regex rx_any_step("(-as|--any-step)=(\\d+)");
	boost::regex rx_prefix("^([^-][\\S]*)$");

	for (int i = 1; i < argc; ++i) {
		std::string current_param = argv[i];
		boost::smatch matches;

		if (boost::regex_match(current_param, matches, rx_help)) _need_help = true;
		else if (boost::regex_match(current_param, matches, rx_config_file_name)) _config_file_name = matches[2];
        else if (boost::regex_match(current_param, matches, rx_size_x)) _sizeX = atoi(matches[2].str().c_str());
        else if (boost::regex_match(current_param, matches, rx_size_y)) _sizeY = atoi(matches[2].str().c_str());
        else if (boost::regex_match(current_param, matches, rx_steps)) {
            std::stringstream ss(matches[2].str());
            ss >> _steps;
        } else if (boost::regex_match(current_param, matches, rx_any_step)) {
            std::stringstream ss(matches[2].str());
            ss >> _any_step;
        } else if (i == argc - 1 && boost::regex_match(current_param, matches, rx_prefix)) _prefix = matches[1];
        else throw ParseParamsError("Undefined parameter", current_param.c_str());
	}
}

std::string Configurator::help() const {
	std::stringstream result;
    result << "Расчёт процесса роста кристалла алмаза CVD методом Динамическим методом Монте Карло\n"
            << "(c) 2012 РХТУ им. Д.И. Менделеева, каф. ИКТ, А.М.Чернышёв, Г.Ю.Аверчук\n"
			<< "\n"
			<< "Запуск программы:\n"
			<< "  " << _program_name << " [параметры] [префикс_выходных_файлов]\n"
			<< "\n"
			<< "Параметры:\n"
			<< "  -h, --help - эта справка\n"
			<< "\n"
			<< "  -c=конфигурационный_файл, --config=конфигурационный_файл - задаёт конфигурационный файл "
			<< "(по умолчанию "<< _config_file_name << ")\n"
			<< "\n"
            << "Размеры кристалла, заменяют указанные в конфигурационном файле\n"
			<< "  -x=число, --size-x=число - размер автомата по X\n"
			<< "  -y=число, --size-x=число - размер автомата по Y\n"
			<< "\n"
            << "  -st=число, --steps=число - число шагов по времени (по умолчанию " << _steps << ")\n"
            << "  -as=число, --any-step=число - вывод результатов, когда шаг кратен этому значению"
            << "(по умолчанию " << _any_step << ")" << std::endl;

    return result.str();
}

std::string Configurator::outFileName(const char *suffix) const {
    std::stringstream result;
    result << _prefix << "-" << suffix << ".txt";
    return result.str();
}
