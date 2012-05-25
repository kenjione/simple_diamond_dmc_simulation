/*
 * configurator.cpp
 *
 *  Created on: 30.05.2011
 *      Author: newmen
 */

#include <boost/regex.hpp>
#include <sstream>
#include <cstdlib>

#include "configurator.h"
#include "parse_params_error.h"

Configurator::Configurator() : _need_help(false), _config_file_name(DEFAULT_CONFIG_FILE), _sizeX(0), _sizeY(0),
        _steps(STEPS), _any_step(ANY_STEP), _full_time(FULL_TIME), _any_time(ANY_TIME),
        _prefix(DEFAULT_PREFIX) {}

void Configurator::parseParams(int argc, char* argv[]) {
    _program_name = argv[0];

    boost::regex rx_help("-h|--help");
    boost::regex rx_config_file_name("(-c|--config)=([\\/\\w\\._-]+)");
    boost::regex rx_size_x("(-x|--size-x)=(\\d+)");
    boost::regex rx_size_y("(-y|--size-y)=(\\d+)");
    boost::regex rx_steps("(-st|--steps)=(\\d+)");
    boost::regex rx_any_step("(-as|--any-step)=(\\d+)");
    boost::regex rx_full_time("(-ft|--full-time)=([\\d\\.]+)");
    boost::regex rx_any_time("(-at|--any-time)=([\\d\\.]+)");
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
        } else if (boost::regex_match(current_param, matches, rx_full_time)) _full_time = atof(matches[2].str().c_str());
        else if (boost::regex_match(current_param, matches, rx_any_time)) _any_time = atof(matches[2].str().c_str());
        else if (i == argc - 1 && boost::regex_match(current_param, matches, rx_prefix)) _prefix = matches[1];
        else throw ParseParamsError("Неизвестный парамер", current_param.c_str());
    }

    if ((_steps != STEPS || _any_step != ANY_STEP) && !isSteps()) {
        throw ParseError("Нельзя использовать одновременно параметры установки частоты сохранения, из разных пар.");
    }
}

std::string Configurator::help() const {
    std::stringstream result;
    result << "Расчёт процесса роста кристалла алмаза CVD методом Динамическим методом Монте Карло\n"
            << "(c) 2012 РХТУ им. Д.И. Менделеева, каф. ИКТ, А.М. Чернышёв, Г.Ю. Аверчук\n" // TODO: можно и отчества указать ;)
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
            << "(по умолчанию " << _any_step << ")\n\n"
            << "  -ft=число, --full-time=число - количество рассчитываемых секунд процесса "
            << "(по умолчанию " << _full_time << ")\n"
            << "  -at=число, --any-time=число - вывод результатов, когда время кратно этому значению секунд; "
            << "если этот параметр равен нулю, то сохраняется каждый шаг (по умолчанию " << _any_time << ")\n\n"
            << "  Параметры устанавливающие ограничения на количество шагов расчёта - могут использоваться только попарно. "
            << "Если не использовать ни один из ключей частоты сохранения, то по умолчанию будет использоваться пара ключей, "
            << "отвечаюих количеству шагов.\n"
            << std::endl;

    return result.str();
}

bool Configurator::isSteps() const {
    auto mulAndRound = [](float number) {
        return (int)(1000000000 * number + 0.5); // билятский костыль, потому что 1e-5 != 1e-5 :(
    };
    return !(mulAndRound(_full_time) != mulAndRound(FULL_TIME) || _any_time != ANY_TIME);
}

std::string Configurator::outFileName(const char *suffix) const {
    std::stringstream result;
    result << _prefix << "-" << suffix << ".txt";
    return result.str();
}
