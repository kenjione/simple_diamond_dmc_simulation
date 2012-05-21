/*
 * configurator.h
 *
 *  Created on: 30.05.2011
 *      Author: newmen
 */

#ifndef CONFIGURATOR_H_
#define CONFIGURATOR_H_

#include <string>

#define DEFAULT_CONFIG_FILE "handbook.cnf"
#define DEFAULT_PREFIX "../dmc-results/000"
#define STEPS 500
#define ANY_STEP 1

class Configurator {
public:
	Configurator();
    virtual ~Configurator() { }

	void parseParams(int argc, char* argv[]);
    std::string help() const;

    const char* programName() const { return _program_name.c_str(); }
	bool needHelp() const { return _need_help; }
	const char* configFileName() const { return _config_file_name.c_str(); }
    int sizeX() const { return _sizeX; }
    int sizeY() const { return _sizeY; }
    unsigned int steps() const { return _steps; }
    unsigned int anyStep() const { return _any_step; }

    std::string outFileName(const char *suffix) const;

private:
	std::string _program_name;
	bool _need_help;
	std::string _config_file_name;
    int _sizeX, _sizeY;
    unsigned long long _steps, _any_step;
	std::string _prefix;
};

#endif /* CONFIGURATOR_H_ */
