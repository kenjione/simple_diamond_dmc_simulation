#include "formdimerreaction.h"
#include "math.h"

FormDimerReaction::FormDimerReaction(Surface *surface, Crystal *crystal) :
    DualReaction(surface), _crystal(crystal) {}

void FormDimerReaction::operator() (Carbon *first, Carbon *second) {
    if (_pairs.find(first)!=_pairs.end()) return;
    _sites.push_back(std::pair<Carbon*, Carbon*> (first,second));
    _pairs.insert(second);
}

double FormDimerReaction::coef() {
    return 1 * pow(10,12) * exp(-352.3/__reactor->temperature());
}


void FormDimerReaction::seeAt(Carbon *carbon) {
    _crystal->posDimerIter(carbon, ref(*this));
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
