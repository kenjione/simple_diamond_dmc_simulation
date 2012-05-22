#include "formdimerreaction.h"
#include <cmath>
#include <cstdlib>

#include <iostream> //

FormDimerReaction::FormDimerReaction(Surface *surface, Crystal *crystal) :
    DualReaction(surface), _crystal(crystal) {}

void FormDimerReaction::operator() (Carbon *first, Carbon *second) {

   // std::cout << "\nCALL OPERATOR() FORMDIM; HAS ABOVE?! : " << _crystal->hasAbove(first, second);
    if ((_pairs.find(first) != _pairs.end()) || _crystal->hasAbove(first, second)) return;

    if (!first->isDimer() && !second->isDimer()) {
        _sites.push_back(std::pair<Carbon *, Carbon *> (first, second));
        _pairs.insert(second);
    }
}

double FormDimerReaction::coef() const {
    return 1e5 * exp(-352.3 / __reactor->temperature());
}


void FormDimerReaction::seeAt(Carbon *first, Carbon *second) {
    _crystal->posDimerIter(first, std::ref(*this));
}

void FormDimerReaction::doIt() {
    int siteRandomIndex = rand() % _sites.size();
    Carbon *first = _sites[siteRandomIndex].first;
    Carbon *second = _sites[siteRandomIndex].second;
    _surface->addDimer(first, second);
}

void FormDimerReaction::reset() {
    DualReaction::reset();
    _pairs.clear();
}
