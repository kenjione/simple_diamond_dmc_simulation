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

    if (carbon->actives() == 0) _activeCarbons.erase(carbon);
    if (bottomFirst->actives() == 0) _activeCarbons.erase(bottomFirst);
    if (bottomSecond->actives() == 0) _activeCarbons.erase(bottomSecond);
}

void Surface::removeCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond) {
    carbon->dropBond(); // разрыв связи с первым
    carbon->dropBond(); // разрыв связи со вторым
    bottomFirst->dropBond();
    bottomSecond->dropBond();

    _activeCarbons.insert(carbon);
    _activeCarbons.insert(bottomFirst);
    _activeCarbons.insert(bottomSecond);
}

void Surface::addDimer(Carbon *first, Carbon *second) {
    _dimerBonds[first] = second;
    _dimerBonds[second] = first;

    first->formBond();
    second->formBond();

    if (first->actives() == 0) _activeCarbons.erase(first);
    if (second->actives() == 0) _activeCarbons.erase(second);
}

void Surface::dropDimer(Carbon *first) {
    Carbon *second = _dimerBonds[first];
    second->dropBond();
    first->dropBond();

    _dimerBonds.erase(first);
    _dimerBonds.erase(second);

    _activeCarbons.insert(first);
    _activeCarbons.insert(second);
}

int Surface::numberOfSites() {
    std::set<Carbon*> allSites;
    allSites.insert(_activeCarbons.begin(),_activeCarbons.end());
    allSites.insert(_hydroCarbons.begin(), _hydroCarbons.end());
    return allSites.size();
}
