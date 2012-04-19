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
    if (carbon->actives() == 0 ) _activeCarbons.remove(carbon);
}

void Surface::removeHydrogen(Carbon *carbon) {
    carbon->absHydrogen();
    _activeCarbons.insert(carbon);
    if (carbon->hydrogens() == 0) _hydroCarbons.remove(carbon);
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

    // TODO: тут нужно не нулям присваивать, а вообще удалять из map. см. метод erase
    _dimerBonds[first] = 0;
    _dimerBonds[second] = 0;
}
