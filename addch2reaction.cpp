#include "addch2reaction.h"
#include <cmath>
#include <cstdlib>

AddCH2Reaction::AddCH2Reaction(Surface *surface, Crystal *crystal) :
    DualReaction(surface), _crystal(crystal) {}

double AddCH2Reaction::coef() {
    return 1 * 10e13 * __reactor->methylConcentration();
}

void AddCH2Reaction::seeAt(Carbon *first, Carbon *second) {
    auto pushPair = [this](Carbon *first, Carbon *second) {
        _sites.push_back(std::pair<Carbon *, Carbon *> (first, second));
        _positions.push_back(_crystal->topPosition(first, second));
    };

    if (first->actives() > 0) pushPair(first, second);
    if (second->actives() > 0) pushPair(second, first);
}

void AddCH2Reaction::doIt() {
    int siteRandomIndex = rand() % _sites.size();
    _surface->addCarbon(new Carbon(_positions[siteRandomIndex], 0, 2),
                        _sites[siteRandomIndex].first,
                        _sites[siteRandomIndex].second);
}

void AddCH2Reaction::reset() {
    DualReaction::reset();
    _positions.clear();
}
