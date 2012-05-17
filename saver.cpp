#include "saver.h"
#include <iostream> //

Saver::Saver(const char *outFileName) : _outFile(outFileName) {
    if (!_outFile) {
        std::cerr << outFileName << " file not created!\n";
    } else {
        std::cout << "   ...file created!\n";
    }
}

Saver::~Saver() {
    _outFile.close();
}
