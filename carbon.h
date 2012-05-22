#ifndef CARBON_H
#define CARBON_H

#include <assert.h>
#include "int3.h"

class Carbon
{
public:
    Carbon(const int3 &coords, int actives, int hydrogens)
        : _coords(coords), _actives(actives), _hydrogens(hydrogens), _isDimer(false) {}

    int actives() const { return _actives; }
    int hydrogens() const { return _hydrogens; }
    bool isDimer() { return _isDimer; }

    void addHydrogen() {
        --_actives;
        ++_hydrogens;
        assert(_actives >= 0 && _hydrogens <= 2);
    }

    void absHydrogen() {
        ++_actives;
        --_hydrogens;
        assert(_actives <= 2 && _hydrogens >= 0);
    }

    void formBond() {
        --_actives;
        assert(_actives >= 0);
    }

    void dropBond() {
        ++_actives;
        assert(_actives <= 2);
    }

    void setAsDimer() { _isDimer = true; }
    void setAsNotDimer() { _isDimer = false; }

    const int3 &coords() const { return _coords; }
    void move(const int3 &to) { _coords = to; }

private:
    int3 _coords;
    int _actives, _hydrogens;
    bool _isDimer;
};

#endif // CARBON_H
