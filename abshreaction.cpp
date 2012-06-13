#include "abshreaction.h"
#include <cmath>
#include <cstdlib>

AbsHReaction::AbsHReaction(Surface *surface, const char *paragraphName) : MonoReaction(surface, paragraphName)
{}

double AbsHReaction::coef() const {
    return _k * __reactor->hydrogenConcentration() * exp(-_E / R /__reactor->temperature());
}

void AbsHReaction::seeAt(Carbon *carbon) {
     _sites.push_back(carbon);
}

void AbsHReaction::doIt() {
    _surface->removeHydrogen(_sites[rand() % _sites.size()]);
}
