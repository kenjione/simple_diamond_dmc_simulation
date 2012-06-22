#include "dropdimerreaction.h"
#include <cmath>
#include <cstdlib>

DropDimerReaction::DropDimerReaction(Surface *surface) : DualReaction(surface, "Drop dimer reaction")
{}

double DropDimerReaction::coef() const {
    return _k * exp(-_E / R / __reactor->temperature());
}

void DropDimerReaction::seeAt(Carbon *first, Carbon *second) {
    _sites.push_back(std::pair<Carbon *, Carbon *> (first, second));
}

void DropDimerReaction::doIt() {
    int siteRandomIndex = rand() % _sites.size();
    _surface->dropDimer(_sites[siteRandomIndex].first, _sites[siteRandomIndex].second);
}
