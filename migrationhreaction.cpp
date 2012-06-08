#include "migrationhreaction.h"
#include <cmath>
#include <cstdlib>

//#include <iostream> //

MigrationHReaction::MigrationHReaction(Surface *surface) : DualReaction(surface) {
    _k = Handbook::instance()->value("Migration H reaction", "k");
    _E = Handbook::instance()->value("Migration H reaction", "E");
}

double MigrationHReaction::coef() const {
            // 13
    return 2.3e5 * exp(-51100 / (__reactor->temperature() * R));
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
