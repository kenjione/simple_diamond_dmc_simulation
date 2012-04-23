#include "abshreaction.h"

AbsHReaction::AbsHReaction(Surface *surface) : MonoReaction(surface) {}

double AbsHReaction::coef() {
    //return ...
}

void AbsHReaction::seeAt(Carbon *carbon) {
     _sites.push_back(carbon);
}

void AbsHReaction::doIt() {
    _surface->removeHydrogen(_sites[rand()%_sites.size()]);
}
