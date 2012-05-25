#include "formdimerreaction.h"
#include <cmath>
#include <cstdlib>

#include <iostream> //

FormDimerReaction::FormDimerReaction(Surface *surface, Crystal *crystal) :
    DualReaction(surface), _crystal(crystal) {}

void FormDimerReaction::operator() (Carbon *first, Carbon *second) {
    if (_pairs.find(first) != _pairs.end() || _crystal->hasAbove(first, second)) return;

    if (!first->isDimer() && !second->isDimer() && second->actives() > 0) {
        _sites.push_back(std::pair<Carbon *, Carbon *> (first, second));
        _pairs.insert(second);
    }
}

double FormDimerReaction::coef() const {
           //12
    return 1e5 * exp(-352.3 / __reactor->temperature());
}

void FormDimerReaction::seeAt(Carbon *first, Carbon *second) {
    _crystal->posDimerIter(first, std::ref(*this));
}

void FormDimerReaction::doIt() {
    size_t siteRandomIndex = rand() % _sites.size();
    makeDimer(siteRandomIndex);
}

void FormDimerReaction::initDimerLayer() {
    for (size_t i = 0; i < _sites.size(); i++) {
        if (!_sites[i].first->isDimer() && !_sites[i].second->isDimer()) {
            makeDimer(i);
        }
    }
}

void FormDimerReaction::reset() {
    DualReaction::reset();
    _pairs.clear();
}

void FormDimerReaction::makeDimer(size_t siteIndex) {
    _surface->addDimer(_sites[siteIndex].first, _sites[siteIndex].second);
}
