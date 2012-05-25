//#define NDEBUG // убрать в релизной версии
#include <assert.h>
#include <iostream>
#include "configurator.h"
#include "parse_params_error.h"
#include "runner.h"
#include "handbookerror.h"

int main(int argc, char *argv[])
{
    Configurator configurator;
    try {
        configurator.parseParams(argc, argv);
    } catch(const ParseError &e) {
        std::cerr << e.getMessage() << '\n'
                << "См. " << configurator.programName() << " --help" << std::endl;
        return 1;
    }

    if (configurator.needHelp()) {
        std::cout << configurator.help() << std::endl;
        return 0;
    }

    // чтобы программа запускалась в Qt Creator, сделай в папке, которую создаёт Creator такую штуку
    // ln -s ../#{папка_с_текущим_проектом}/handbook.cnf .

    srand(time(NULL));
    try {
        Runner runner(configurator);
        runner.run();
    } catch(const ParseError &e) {
        std::cerr << e.getMessage() << std::endl;
        return 1;
    }

    return 0;
}
