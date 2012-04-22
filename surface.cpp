#include "surface.h"

Surface::Surface(Crystal *crystal) : _crystal(crystal) {
    init();
}

void Surface::init() {
    _crystal->throughAllCarbonsIter(ref(*this));
}

void Surface::operator ()(Carbon *carbon) {
    if ( carbon->actives() > 0 ) _activeCarbons.insert(carbon);
    if ( carbon->hydrogens() > 0) _hydroCarbons.insert(carbon);
}

void Surface::addHydrogen(Carbon *carbon) {
    carbon->addHydrogen();
    _hydroCarbons.insert(carbon);
    if (carbon->actives() == 0 ) _activeCarbons.erase(carbon);
}

void Surface::removeHydrogen(Carbon *carbon) {
    carbon->absHydrogen();
    _activeCarbons.insert(carbon);
    if (carbon->hydrogens() == 0) _hydroCarbons.erase(carbon);
}

void Surface::addCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond) {
    carbon->formBond();
    bottomFirst->formBond();
    bottomSecond->formBond();
}

void Surface::removeCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond) {
    carbon->dropBond();
    bottomFirst->dropBond();
    bottomSecond->dropBond();
}

void Surface::addDimer(Carbon *first, Carbon *second) {
    _dimerBonds[first] = second;
    _dimerBonds[second] = first;
    first->formBond();
    second->formBond();
}

void Surface::dropDimer(Carbon *first) {
    Carbon *second = _dimerBonds[first];
    second->dropBond();
    first->dropBond();
    _dimerBonds.erase(first);
    _dimerBonds.erase(second);
}

int Surface::numberOfSites() {
    // посчитать количество уникальных карбонов в каждом сете
    // и return sum
}
