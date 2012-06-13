#include "migrationhreaction.h"
#include <cmath>
#include <cstdlib>

MigrationHReaction::MigrationHReaction(Surface *surface, const char *paragraphName) :
    DualReaction(surface, paragraphName) {
}

double MigrationHReaction::coef() const {
    return _k * exp(_E / (__reactor->temperature() * R));
}

void MigrationHReaction::seeAt(Carbon *first, Carbon *second) {
    auto savePairLambda = [this](Carbon *first, Carbon *second) {
        _sites.push_back(std::pair<Carbon *, Carbon *>(first, second));
    };

    if (first->hydrogens() > 0 && second->actives() > 0) {
        savePairLambda(first, second);
    } else if (first->actives() > 0 && second->hydrogens() > 0) {
        savePairLambda(second, first);
    }
}

void MigrationHReaction::doIt() {
    std::pair<Carbon*, Carbon*> &randomSite = _sites[rand() % _sites.size()];
    _surface->removeHydrogen(randomSite.first);
    _surface->addHydrogen(randomSite.second);
}
