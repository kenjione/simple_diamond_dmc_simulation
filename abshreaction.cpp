#include "abshreaction.h"
#include <cmath>
#include <cstdlib>


#include <iostream> //


AbsHReaction::AbsHReaction(Surface *surface) : MonoReaction(surface)
{
    _k = Handbook::instance()->value("Abs H reaction", "k");
    _E = Handbook::instance()->value("Abs H reaction", "E");
}

double AbsHReaction::coef() const {
    //             13
    //return 5.2 * 1e10 * __reactor->hydrogenConcentration() * exp(-3360 / __reactor->temperature());

    return _k * __reactor->hydrogenConcentration() * exp(-_E / R /__reactor->temperature());
}

void AbsHReaction::seeAt(Carbon *carbon) {
     _sites.push_back(carbon);
}

void AbsHReaction::doIt() {
    _surface->removeHydrogen(_sites[rand() % _sites.size()]);
}
