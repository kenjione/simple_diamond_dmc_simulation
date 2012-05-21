#include "saver.h"
#include <iostream> //

Saver::Saver(const char *outFileName) : _outFile(outFileName) {
    if (!_outFile) {
        std::cerr << " file \"" << outFileName << "\" NOT created!\n";
    } else {
        std::cout << "   ...file \"" << outFileName << "\" created!\n";
    }
}

Saver::~Saver() {
    _outFile.close();
}
