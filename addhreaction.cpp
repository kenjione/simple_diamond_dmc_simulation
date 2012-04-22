#include "addhreaction.h"

AddHReaction::AddHReaction(Surface *surface):
    AddHReaction::MonoReaction(surface) {}

double AddHReaction::coef() {
    //return ...
}

void AddHReaction::seeAt(Carbon *carbon)  {
    _sites.push_back(carbon);
}

void AddHReaction::doIt() {
    _surface->addHydrogen(_sites[rand()%_sites.size()]);
}
