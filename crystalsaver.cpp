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
    int state = -1;


    if (!carbon->isDimer()) {
        if (carbon->actives() == 0) {
            if (carbon->hydrogens() == 0) state = 1;    // серый     >C<
            if (carbon->hydrogens() == 1) state = 2;    // желтый    CH
            if (carbon->hydrogens() == 2) state = 3;    // зеленый   CH2
        } else if (carbon->actives() == 1) {
            if (carbon->hydrogens() == 0) state = 4;    // розовый   *C
            if (carbon->hydrogens() == 1) state = 5;    // голубой   *CH
        } else if (carbon->actives() == 2) state = 6;   // красный   *C*
    } else {
        if (carbon->actives() == 0 && carbon->hydrogens() == 1) state = 7;      // синий      HC--
        else if (carbon->actives() == 1 && carbon->hydrogens() == 0) state = 8; // оранжевый  *C--
        else if (carbon->actives() == 0 && carbon->hydrogens() == 0) state = 9; // белый      >C--
    }

    _outFile << state << " " << coords.x << " " << coords.y << " " << coords.z << "\n";

}
