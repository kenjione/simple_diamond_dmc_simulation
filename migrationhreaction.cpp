#include "migrationhreaction.h"

MigrationHReaction::MigrationHReaction(Surface *surface):
    MigrationHReaction::DualReaction(surface) {}

double MigrationHReaction::coef() {
    // return ...
}

void MigrationHReaction::seeAt(Carbon *first, Carbon *second) {
    if (first->hydrogens() > 0 && second->actives() > 0)
        _sites.push_back(std::pair<Carbon*, Carbon*>(first, second));
    else if (first->actives() > 0 && second->hydrogens() > 0)
        _sites.push_back(std::pair<Carbon*, Carbon*>(second, first));
}

void MigrationHReaction::doIt() {
    std::pair<Carbon*, Carbon*> random_site = _sites[rand()%_sites.size()];
    _surface->removeHydrogen(random_site.first);
    _surface->addHydrogen(random_site.second);
}
