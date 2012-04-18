#ifndef SURFACE_H
#define SURFACE_H

#define FIELD_SIZE 300
#define SIZE_X 20
#define SIZE_Y 15

#include "crystal.h"
#include <QMap>
#include <QSet>

#include <QPair>
#include <QPair>
#include <QVector>


class Surface
{

private:
    Crystal* _crystal;
    Reaction** _reactions;
    QSet<Carbon*> _activeCarbons;
    QSet<Carbon*> _hydroCarbons;
    map<Carbon*,Carbon*> _dimerBonds;

    void init() {
        _crystal->throughAllCarbonsIter(ref(*this));
    }
public:

    Surface(Crystal* crystal): _crystal(crystal) {
        init();
    }

    void operator() (Carbon* carbon) {
        if ( carbon->actives() > 0 ) _activeCarbons.insert(carbon);
        if ( carbon->hydrogens() > 0) _hydroCarbons.insert(carbon);
    }

    int numberOfSites();

    // адсорбция Н2
    void addHydrogen(Carbon* carbon) {
        carbon->addHydrogen();
        _hydroCarbons.insert(carbon);
        if (carbon->actives() == 0 ) _activeCarbons.remove(carbon);
    }

    // абсорбция Н2
    void removeHydrogen(Carbon* carbon) {
        carbon->absHydrogen();
        _activeCarbons.insert(carbon);
        if (carbon->hydrogens() == 0) _hydroCarbons.remove(carbon);
    }

    // Осаждение СН3
    void addCarbon(Carbon* carbon, Carbon* bottomFirst, Carbon* bottomSecond) {
        carbon->formBond();
        bottomFirst->formBond();
        bottomSecond->formBond();
    }

    // Травление СН2
    void removeCarbon(Carbon* carbon, Carbon* bottomFirst, Carbon* bottomSecond) {
        carbon->dropBond();
        bottomFirst->dropBond();
        bottomSecond->dropBond();
    }
    void moveCarbon(Carbon* carbon, int3 to, QPair<Carbon*, Carbon*> fromBasis, QPair<Carbon*, Carbon*> toBasis) {

    }

    void addDimer(Carbon* first, Carbon* second) {
        _dimerBonds[first] = second;
        _dimerBonds[second] = first;
        first->formBond();
        second->formBond();
    }
    void dropDimer(Carbon* first) {
        Carbon* second = _dimerBonds[first];
        second->dropBond();
        first->dropBond();
        _dimerBonds[first] = 0;
        _dimerBonds[second] = 0;
    }

};

#endif // surface_H
