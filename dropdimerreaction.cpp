#include "dropdimerreaction.h"
#include <cmath>
#include <cstdlib>

#include <iostream> //

DropDimerReaction::DropDimerReaction(Surface *surface) : DualReaction(surface) {}

double DropDimerReaction::coef() const {
    return 4.79 * 1e13 * exp(-7196.8 / __reactor->temperature());
}

void DropDimerReaction::seeAt(Carbon *first, Carbon *second) {
    _sites.push_back(std::pair<Carbon *, Carbon *> (first, second));
}

void DropDimerReaction::doIt() {
    int siteRandomIndex = rand() % _sites.size();
    _surface->dropDimer(_sites[siteRandomIndex].first, _sites[siteRandomIndex].second);
}
