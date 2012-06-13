#include <iostream>
#include <cmath>
#include "surface.h"
#include "reactionspool.h"
#include <assert.h>

Surface::Surface(Crystal *crystal) : _crystal(crystal) {
}

Surface::~Surface() {}

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

void Surface::init(ReactionsPool *reactionPool) {
    _crystal->throughAllCarbonsIter(std::ref(*this));
    initDimerLayer(reactionPool);
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
    auto it = findDimer(first, second);

    if (iteratorIsDimer(it, first, second)) {
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

bool Surface::isDimer(Carbon *first, Carbon *second) const {
    auto it = findDimer(first, second);
    return iteratorIsDimer(it, first, second);
}

std::map<Carbon *,Carbon *>::const_iterator Surface::findDimer(Carbon *first, Carbon *second) const {
    std::map<Carbon *,Carbon *>::const_iterator it = _dimerBonds.find(first);
    if (it == _dimerBonds.cend()) {
        // если не нашли по first, ищем по second
        it = _dimerBonds.find(second);
    }

    return it;
}

bool Surface::iteratorIsDimer(const std::map<Carbon *, Carbon *>::const_iterator &it, Carbon *first, Carbon *second) const {
    if (it == _dimerBonds.cend()) return false;
    if ((it->first == first && it->second == second) || (it->second == first && it->first == second)) {
        return true;
    }

    return false;
}

void Surface::initDimerLayer(ReactionsPool *reactionPool) {
    FormDimerReaction &formDimer = reactionPool->formDimerReaction();
    for (Carbon *carbon : _activeCarbons) {
        formDimer.seeAt(carbon, 0);
    }
    formDimer.initDimerLayer();
}

void Surface::formBondsFor(Carbon *first, Carbon *second) {
    auto formBondLambda = [this](Carbon *c) {
        c->formBond();
        if (c->actives() == 0) _activeCarbons.erase(c);
    };

    formBondLambda(first);
    formBondLambda(second);
}

void Surface::dropBondsFor(Carbon *first, Carbon *second) {
    auto dropBondLambda = [this](Carbon *c) {
        c->dropBond();
        _activeCarbons.insert(c);
    };

    dropBondLambda(first);
    dropBondLambda(second);
}

void Surface::removeFromDimersHash(Carbon *first, Carbon *second) {
    auto it = findDimer(first, second);

    assert(it != _dimerBonds.cend());
    _dimerBonds.erase(it); // удаляем димер из хеша

    first->setAsNotDimer();
    second->setAsNotDimer();
}
