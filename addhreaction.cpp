#include "addhreaction.h"
#include <cmath>
#include <cstdlib>

#include <iostream> //

AddHReaction::AddHReaction(Surface *surface) : MonoReaction(surface) {
    // _k = Handbook.instance()->value("addhreaction", "k");
}

double AddHReaction::coef() const {
    return 2e13 * __reactor->hydrogenConcentration();
    // return _k * __reactor->hydrogenConcentration();
}

void AddHReaction::seeAt(Carbon *carbon)  {
    _sites.push_back(carbon);
}

void AddHReaction::doIt() {
    _surface->addHydrogen(_sites[rand() % _sites.size()]);
}
