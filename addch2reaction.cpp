#include "addch2reaction.h"
#include <cmath>
#include <cstdlib>

#include <iostream> //

AddCH2Reaction::AddCH2Reaction(Surface *surface, Crystal *crystal) :
    DualReaction(surface), _crystal(crystal) {}

double AddCH2Reaction::coef() const {
    // 1e13 * [CH3];
    return 1e13 * __reactor->methylConcentration();
}

void AddCH2Reaction::seeAt(Carbon *first, Carbon *second) {
    auto pushPair = [this](Carbon *first, Carbon *second) {
        _sites.push_back(std::pair<Carbon *, Carbon *> (first, second));
        _positions.push_back(_crystal->topPosition(first, second));
    };

    if (first->actives() > 0) pushPair(first, second);
    //else std::cout << "         ...addch2::seeAt message: can't push first coz hasn't actives\n";
    if (second->actives() > 0) pushPair(second, first);
    //else std::cout << "         ...addch2::seeAt message: can't push second coz hasn't actives\n";
}

void AddCH2Reaction::doIt() {
    int siteRandomIndex = rand() % _sites.size();

//    std::cout << "    ...addch2::doIt message: new positions: { " << _positions[siteRandomIndex].x << ", " << _positions[siteRandomIndex].y << ", " << _positions[siteRandomIndex].z << " } \n";
    makeAddCh2(siteRandomIndex);
    //    std::cout << "\n    ...addCh2::doIt message:    add Ch2 done!\n";
}

void AddCH2Reaction::doItForDimerRow()
{
    for (int i = 0; i < _sites.size(); i++) {
        if (_sites[i].first->isDimer() && _sites[i].second->isDimer()) {
            makeAddCh2(i);
        }
    }
}

void AddCH2Reaction::reset() {
    DualReaction::reset();
    _positions.clear();
}

void AddCH2Reaction::makeAddCh2(size_t siteIndex)
{
    _surface->addCarbon(new Carbon(_positions[siteIndex], 0, 2),
                        _sites[siteIndex].first,
                        _sites[siteIndex].second);
}
