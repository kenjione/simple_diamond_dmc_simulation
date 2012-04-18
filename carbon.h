#ifndef CARBON_H
#define CARBON_H

#include <iostream>
#include <QDebug>
#include <QVector>

using namespace std;

struct int3 {
    int x, y, z;
};


class Carbon
{
private:

    int _activities;
    int _hydrogens;
    int3 _coords;

public:

    Carbon() {
        _activities = rand()%3;
        _hydrogens = 2 - _activities;
    }

    void addHydrogen()
    {
        _activities--;
        _hydrogens++;
    }

    void absHydrogen()
    {
        _activities++;
        _hydrogens--;
    }

    void formBond() { _activities--; }
    void dropBond() { _activities++; }

    int actives() const {
        return _activities;
    }
    int hydrogens() const {
        return _hydrogens;
    }
    bool isTop() {}

    void move(const int3 &to) {
        _coords.x = to.x;
        _coords.y = to.y;
        _coords.z = to.z;
    }

    int3 coords() const {
        return _coords;
    }
};

#endif // CARBON_H
