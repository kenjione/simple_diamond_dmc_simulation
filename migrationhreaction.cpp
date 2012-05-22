#include "migrationhreaction.h"
#include <cmath>
#include <cstdlib>

//#include <iostream> //

MigrationHReaction::MigrationHReaction(Surface *surface) : DualReaction(surface) {}

double MigrationHReaction::coef() const {
            // 13
    return 2.3e5 * exp(-51100 / (__reactor->temperature() * R));
}

void MigrationHReaction::seeAt(Carbon *first, Carbon *second) {
    if (first->hydrogens() > 0 && second->actives() > 0) {
        _sites.push_back(std::pair<Carbon *, Carbon *>(first, second));
    } else if (first->actives() > 0 && second->hydrogens() > 0) {
        _sites.push_back(std::pair<Carbon *, Carbon *>(second, first));
    }
}

void MigrationHReaction::doIt() {
    std::pair<Carbon*, Carbon*> &randomSite = _sites[rand() % _sites.size()];
    _surface->removeHydrogen(randomSite.first);
    _surface->addHydrogen(randomSite.second);
}
