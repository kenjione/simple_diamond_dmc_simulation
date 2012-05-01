#include "addhreaction.h"
#include "math.h"

AddHReaction::AddHReaction(Surface *surface) : MonoReaction(surface) {}

double AddHReaction::coef() {
    return 2 * pow(10,13) * __reactor->hydrogenConcentration();
}

void AddHReaction::seeAt(Carbon *carbon)  {
    _sites.push_back(carbon);
}

void AddHReaction::doIt() {
    _surface->addHydrogen(_sites[rand() % _sites.size()]);
}
