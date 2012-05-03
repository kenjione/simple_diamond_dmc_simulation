#include "abshreaction.h"
#include <cmath>
#include <cstdlib>

AbsHReaction::AbsHReaction(Surface *surface) : MonoReaction(surface) {}

double AbsHReaction::coef() {
    return 5.2 * 10e3 * __reactor->hydrogenConcentration() * exp(-3360 / __reactor->temperature());
}

void AbsHReaction::seeAt(Carbon *carbon) {
     _sites.push_back(carbon);
}

void AbsHReaction::doIt() {
    _surface->removeHydrogen(_sites[rand() % _sites.size()]);
}
