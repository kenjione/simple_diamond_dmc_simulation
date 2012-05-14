#include "saver.h"
#include <stdio.h> //
#include <iostream> //

Saver::Saver(const char *outFileName)
{
    std::cout << "call Saver::Saver()\n"; //
    _outFile.open(outFileName, std::ios_base::out);
    if (_outFile == NULL) std::cout << "not exist..\n"; else std::cout << "EXIST!\n"; //
}

void Saver::operator ()(Carbon *carbon) {
    //std::cout << "call Saver::operator()\n"; //
    int3 coords = carbon->coords();
    int state = -333;

    switch (carbon->hydrogens())
    {
    case 0:
        state = (carbon->actives() == 0) ? 1 : 2;
        break;
    case 1:
        state = 3;
        break;
    case 2:
        state = 4;
        break;
    }

    if (carbon->isDimer()) state = 5;
    _outFile << state << " " << coords.x << " " << coords.y << " " << coords.z << std::endl;
}

void Saver::separator() {
    std::cout << "call Saver::separator()\n"; //
    _outFile << "0 0 0 0" << std::endl;
}


// без этого метода пока не выдумал как файлик закрывать
void Saver::closer() {
    _outFile.close();
}
