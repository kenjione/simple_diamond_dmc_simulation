#include "dropdimerreaction.h"
#include "math.h"

DropDimerReaction::DropDimerReaction(Surface *surface) : DualReaction(surface) {}

double DropDimerReaction::coef() {
    return 4.79 * pow(10,13) * exp(-7196.8/__reactor->temperature());
}

void DropDimerReaction::seeAt(Carbon *first, Carbon *second) {
    _sites.push_back(std::pair<Carbon*, Carbon*> (first,second));
}

void DropDimerReaction::doIt() {
    int siteRandomIndex = rand() % _sites.size();
    _surface->dropDimer(_sites[siteRandomIndex].first);
}
