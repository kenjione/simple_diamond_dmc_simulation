#include "migrationhreaction.h"
#include "math.h"

MigrationHReaction::MigrationHReaction(Surface *surface, float r) : DualReaction(surface), _r(r) {}

double MigrationHReaction::coef() {
    float R = 123.456;
    return 2.3 * pow(10,13) * exp(-51.1/(__reactor->temperature()*R));
}

void MigrationHReaction::seeAt(Carbon *first, Carbon *second) {
    if (first->hydrogens() > 0 && second->actives() > 0) {
        _sites.push_back(std::pair<Carbon*, Carbon*>(first, second));
    } else if (first->actives() > 0 && second->hydrogens() > 0) {
        _sites.push_back(std::pair<Carbon*, Carbon*>(second, first));
    }
}

void MigrationHReaction::doIt() {
    std::pair<Carbon*, Carbon*> &randomSite = _sites[rand() % _sites.size()];
    _surface->removeHydrogen(randomSite.first);
    _surface->addHydrogen(randomSite.second);
}
