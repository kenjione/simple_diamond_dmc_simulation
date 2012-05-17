#include "abshreaction.h"
#include <cmath>
#include <cstdlib>


#include <iostream> //


AbsHReaction::AbsHReaction(Surface *surface) : MonoReaction(surface) {}

double AbsHReaction::coef() const {
    //             13
    return 5.2 * 1e20 * __reactor->hydrogenConcentration() * exp(-3360 / __reactor->temperature());
}

void AbsHReaction::seeAt(Carbon *carbon) {
     _sites.push_back(carbon);
}

void AbsHReaction::doIt() {
    _surface->removeHydrogen(_sites[rand() % _sites.size()]);
}
