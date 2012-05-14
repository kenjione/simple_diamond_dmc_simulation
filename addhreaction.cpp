#include "addhreaction.h"
#include <cmath>
#include <cstdlib>

AddHReaction::AddHReaction(Surface *surface) : MonoReaction(surface) {}

double AddHReaction::coef() const {
    return 2 * 10e13 * __reactor->hydrogenConcentration();
}

void AddHReaction::seeAt(Carbon *carbon)  {
    _sites.push_back(carbon);
}

void AddHReaction::doIt() {
    _surface->addHydrogen(_sites[rand() % _sites.size()]);
}
