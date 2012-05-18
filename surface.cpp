#include <iostream>
#include <cmath>
#include "surface.h"
#include "reactionspool.h"

Surface::Surface(Crystal *crystal) : _crystal(crystal) {
    init();
}

Surface::~Surface() {
}

void Surface::init() {

    _crystal->init();
    _crystal->throughAllCarbonsIter(std::ref(*this));

    std::cout << "\n----------------\n";
    std::cout << "hydrocarbons: " << this->_hydroCarbons.size() << std::endl;
    std::cout << "active carbons: " << this->_activeCarbons.size() << std::endl;
    std::cout << "dimers: " << this->_dimerBonds.size() << std::endl;
    std::cout << "----------------\n\n";
}

float Surface::doReaction(ReactionsPool *reactionPool) {

    reactionPool->reset();
    reactionPool->seeAtActives(_activeCarbons);
    reactionPool->seeAtHydrogens(_hydroCarbons);
    reactionPool->seeAtDimer(_dimerBonds);

    return reactionPool->doReaction();
}

void Surface::operator() (Carbon *carbon) {

    //std::cout << "call Surface::operator()\n";
    //std::cout << "this carbon properties: \n  actives: " << carbon->actives() << "\n  hydro: " << carbon->hydrogens() << "\n\n";
    if (carbon->actives() > 0) _activeCarbons.insert(carbon);
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

    // надо ли? и так же связь остается у каждого.
    // bottomFirst->formBond();
    // bottomSecond->formBond();

    // а вот из множества димеров их исключить наверное следовало бы
    auto it = _dimerBonds.find(bottomFirst);
    if (it == _dimerBonds.end()) {
        // если не нашли по first, ищем по second
        it = _dimerBonds.find(bottomSecond);
    }

    _dimerBonds.erase(it); // удаляем димер из хеша

    bottomFirst->setAsNotDimer();
    bottomSecond->setAsNotDimer();


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

void Surface::moveCarbon(Carbon *carbon, const int3 &to,
                         const std::pair<Carbon *, Carbon *> &fromBasis,
                         const std::pair<Carbon *, Carbon *> &toBasis)
{
    _crystal->move(carbon, to);

    /*
        надо разорвать димер так чтобы у него не было активных связей,
        т.к димерная связь идет на мостовую группу. Аналогичная ситуация
        и с образованием димера после перемещения мостовой группы.
    */

    // добавление к димерам
    // TODO: димер не образуется автоматически, при миграции мостовой группы, образуются просто активные связи
    Carbon *first = fromBasis.first;
    first->dropBond();
    _activeCarbons.insert(first);
    Carbon *second = fromBasis.second;
    fromBasis.second->dropBond();
    _activeCarbons.insert(second);
//    _dimerBonds[first] = second;



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
        first->formBond();
        second->formBond();
    }
}


void Surface::addDimer(Carbon *first, Carbon *second) {
    _dimerBonds[first] = second;
//    _dimerBonds[second] = first;

    first->formBond();
    second->formBond();

    first->setAsDimer();
    second->setAsDimer();

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

    first->setAsNotDimer();
    second->setAsNotDimer();

    _activeCarbons.insert(first);
    _activeCarbons.insert(second);
}

int Surface::numberOfSites() {
    std::set<Carbon*> allSites;
    allSites.insert(_activeCarbons.begin(),_activeCarbons.end());
    allSites.insert(_hydroCarbons.begin(), _hydroCarbons.end());

    return allSites.size();
}
