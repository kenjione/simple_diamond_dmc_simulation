#include "surface.h"

Surface::Surface(Crystal *crystal) : _crystal(crystal) {
    init();
}

void Surface::init() {
    _crystal->throughAllCarbonsIter(std::ref(*this));

    // далее инитим реакции, и реактор
}

void Surface::operator() (Carbon *carbon) {
    if (carbon->actives() > 0 ) _activeCarbons.insert(carbon);
    if (carbon->hydrogens() > 0) _hydroCarbons.insert(carbon);
}

void Surface::addHydrogen(Carbon *carbon) {
    carbon->addHydrogen();
    _hydroCarbons.insert(carbon);
    if (carbon->actives() == 0) _activeCarbons.erase(carbon);
}

void Surface::removeHydrogen(Carbon *carbon) {
    carbon->absHydrogen();
    _activeCarbons.insert(carbon);
    if (carbon->hydrogens() == 0) _hydroCarbons.erase(carbon);
}

void Surface::addCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond) {
    _crystal->addCarbon(carbon);

    bottomFirst->formBond();
    bottomSecond->formBond();

    _hydroCarbons.insert(carbon);
    if (bottomFirst->actives() == 0) _activeCarbons.erase(bottomFirst);
    if (bottomSecond->actives() == 0) _activeCarbons.erase(bottomSecond);
}

void Surface::removeCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond) {
    _crystal->removeCarbon(carbon);

    bottomFirst->dropBond();
    bottomSecond->dropBond();

    _hydroCarbons.erase(carbon); // т.к. только те, что с водородами могут отлетать (проверка внутри реакции)
    _activeCarbons.insert(bottomFirst);
    _activeCarbons.insert(bottomSecond);
}

void Surface::addDimer(Carbon *first, Carbon *second) {
    _dimerBonds[first] = second;
//    _dimerBonds[second] = first;

    first->formBond();
    second->formBond();

    if (first->actives() == 0) _activeCarbons.erase(first);
    if (second->actives() == 0) _activeCarbons.erase(second);
}

void Surface::dropDimer(Carbon *first, Carbon *second) {
    auto it = _dimerBonds.find(first);
    if (it == _dimerBonds.end()) {
        // если не нашли по first, ищем по second
        it = _dimerBonds.find(second);
    }

    _dimerBonds.erase(it); // удаляем димер из хеша

    second->dropBond();
    first->dropBond();

    _activeCarbons.insert(first);
    _activeCarbons.insert(second);
}

int Surface::numberOfSites() {
    std::set<Carbon*> allSites;
    allSites.insert(_activeCarbons.begin(),_activeCarbons.end());
    allSites.insert(_hydroCarbons.begin(), _hydroCarbons.end());

    return allSites.size();
}
