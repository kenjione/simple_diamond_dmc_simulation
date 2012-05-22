#include <iostream>
#include <cmath>
#include "surface.h"
#include "reactionspool.h"
#include <assert.h>

Surface::Surface(Crystal *crystal) : _crystal(crystal) {
    init();
}

Surface::~Surface() {
}

std::deque<std::string> Surface::setsNames() const {
    std::deque<std::string> names;
    names.push_back("Hydrocarbons");
    names.push_back("Active carbons");
    names.push_back("Dimers");
    return names;
}

std::deque<int> Surface::setsNumbers() const {
    std::deque<int> numbers;
    numbers.push_back(_hydroCarbons.size());
    numbers.push_back(_activeCarbons.size());
    numbers.push_back(_dimerBonds.size());
    return numbers;
}

void Surface::init() {
    _crystal->throughAllCarbonsIter(std::ref(*this));
}

void Surface::operator() (Carbon *carbon) {
    if (carbon->actives() > 0) _activeCarbons.insert(carbon);
    if (carbon->hydrogens() > 0) _hydroCarbons.insert(carbon);
}

double Surface::doReaction(ReactionsPool *reactionPool) {
    reactionPool->reset();
    reactionPool->seeAtActives(_activeCarbons);
    reactionPool->seeAtHydrogens(_hydroCarbons);
    reactionPool->seeAtDimer(_dimerBonds);

    return reactionPool->doReaction();
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
    _hydroCarbons.insert(carbon);

    removeFromDimersHash(bottomFirst, bottomSecond);
}

void Surface::removeCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond) {
    _crystal->removeCarbon(carbon);
    _hydroCarbons.erase(carbon); // т.к. только те, что с водородами могут отлетать (проверка внутри реакции)

    dropBondsFor(bottomFirst, bottomSecond);
}

void Surface::moveCarbon(Carbon *carbon, const int3 &to,
                         const std::pair<Carbon *, Carbon *> &fromBasis,
                         const std::pair<Carbon *, Carbon *> &toBasis)
{
    _crystal->move(carbon, to);

    Carbon *first = fromBasis.first;
    Carbon *second = fromBasis.second;
    dropBondsFor(first, second);

    // удаление из димеров
    first = toBasis.first;
    second = toBasis.second;
    auto it = _dimerBonds.find(first);
    if (it == _dimerBonds.end()) {
        it = _dimerBonds.find(second);
    }

    if (it != _dimerBonds.end()) {
        _dimerBonds.erase(it);

        first->setAsNotDimer();
        second->setAsNotDimer();
    } else {
        // может мигрировать не только на димеры, но и на активные атомы
        formBondsFor(first, second);
    }
}


void Surface::addDimer(Carbon *first, Carbon *second) {
    _dimerBonds[first] = second;
//    _dimerBonds[second] = first;

    formBondsFor(first, second);

    first->setAsDimer();
    second->setAsDimer();
}

void Surface::dropDimer(Carbon *first, Carbon *second) {
    removeFromDimersHash(first, second);
    dropBondsFor(first, second);
}

void Surface::formBondsFor(Carbon *first, Carbon *second) {
    first->formBond();
    second->formBond();

    if (first->actives() == 0) _activeCarbons.erase(first);
    if (second->actives() == 0) _activeCarbons.erase(second);
}

void Surface::dropBondsFor(Carbon *first, Carbon *second) {
    second->dropBond();
    first->dropBond();

    _activeCarbons.insert(first);
    _activeCarbons.insert(second);
}

void Surface::removeFromDimersHash(Carbon *first, Carbon *second) {
    auto it = _dimerBonds.find(first);
    if (it == _dimerBonds.end()) {
        // если не нашли по first, ищем по second
        it = _dimerBonds.find(second);
    }

    assert(it == _dimerBonds.end());
    _dimerBonds.erase(it); // удаляем димер из хеша

    first->setAsNotDimer();
    second->setAsNotDimer();
}

//int Surface::numberOfSites() {
//    std::set<Carbon*> allSites;
//    allSites.insert(_activeCarbons.begin(),_activeCarbons.end());
//    allSites.insert(_hydroCarbons.begin(), _hydroCarbons.end());

//    return allSites.size();
//}
