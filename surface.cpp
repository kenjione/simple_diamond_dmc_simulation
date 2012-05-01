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

    if (_activeCarbons.find(carbon) != _activeCarbons.end()) _activeCarbons.insert(carbon);
    if (_activeCarbons.find(bottomFirst) != _activeCarbons.end())_activeCarbons.insert(bottomFirst);
    if (_activeCarbons.find(bottomSecond) != _activeCarbons.end())_activeCarbons.insert(bottomSecond);
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

    if (_activeCarbons.find(first) != _activeCarbons.end()) _activeCarbons.insert(first);
    if (_activeCarbons.find(second) != _activeCarbons.end()) _activeCarbons.insert(second);
}

int Surface::numberOfSites() {
    std::set<Carbon*> allSites;
    allSites.insert(_activeCarbons.begin(),_activeCarbons.end());
    for (std::set<Carbon*>::iterator i = _hydroCarbons.begin(); i != _hydroCarbons.end(); ++i)
        if (_activeCarbons.find(*i) == _activeCarbons.end()) allSites.insert(*i);
    return allSites.size();
}
