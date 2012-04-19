#ifndef CARBON_H
#define CARBON_H

#include "int3.h"

class Carbon
{
public:
    Carbon(const int3 &coords, int actives, int hydrogens)
        : _coords(coords), _actives(actives), _hydrogens(hydrogens) {}

    bool isTop();
    int actives() const { return _actives; }
    int hydrogens() const { return _hydrogens; }

    void addHydrogen() {
        --_actives;
        ++_hydrogens;
    }

    void absHydrogen() {
        ++_actives;
        --_hydrogens;
    }

    void formBond() { --_actives; }
    void dropBond() { ++_actives; }

    int3 coords() const { return _coords; }
    void move(const int3 &to) { _coords = to; }

private:
    int3 _coords;
    int _actives, _hydrogens;
};

#endif // CARBON_H
