#include "crystalsaver.h"

CrystalSaver::CrystalSaver(char *outFileName, Crystal *crystal) :
    Saver(outFileName), _crystal(crystal) {
    _outFile.open(outFileName, std::ios_base::out);
    //if (_outFile == NULL) std::cout << "    ...file not created..\n"; else std::cout << "   ...file created!\n"; //
}

void CrystalSaver::save() {
    _crystal->throughAllCarbonsIter(std::ref(*this));
    separator();
}

void CrystalSaver::separator() {
    _outFile << "0 0 0 0" << std::endl;
}

void CrystalSaver::operator ()(Carbon *carbon) {

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

    if (carbon->isDimer()) state = 6;
    _outFile << state << " " << coords.x << " " << coords.y << " " << coords.z << std::endl;

}
