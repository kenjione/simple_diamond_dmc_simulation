#include "saver.h"
#include "parse_error.h"
#include <sstream>

Saver::Saver(const char *outFileName) : _outFile(outFileName) {
    if (!_outFile) {
        std::stringstream ss;
        ss << "File \"" << outFileName << "\" couldn't be created\n";
        throw ParseError(ss.str().c_str());
    }
}

Saver::~Saver() {
    _outFile.close();
}
