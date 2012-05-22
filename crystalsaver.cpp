#include "crystalsaver.h"

CrystalSaver::CrystalSaver(const char *outFileName, Crystal *crystal) : Saver(outFileName), _crystal(crystal) {}

void CrystalSaver::save(double time) {
    _crystal->throughAllCarbonsIter(std::ref(*this));
    separator();
}

void CrystalSaver::separator() {
    _outFile << "0 0 0 0" << std::endl;
}

void CrystalSaver::operator() (Carbon *carbon) {

    int3 coords = carbon->coords();
    int state = -333;


    if (!carbon->isDimer()) {
        if (carbon->actives() == 0) {
            if (carbon->hydrogens() == 0) state = 1;
            if (carbon->hydrogens() == 1) state = 2;
            if (carbon->hydrogens() == 2) state = 3;
        } else if (carbon->actives() == 1) {
            if (carbon->hydrogens() == 0) state = 4;
            if (carbon->hydrogens() == 1) state = 5;
        } else /* actives == 2 */ state = 6;
    } else {
        if (carbon->actives() == 0) state = 7;
        else state = 8;  /* hydrogens = 0 */
    }

    _outFile << state << " " << coords.x << " " << coords.y << " " << coords.z << "\n";

}
