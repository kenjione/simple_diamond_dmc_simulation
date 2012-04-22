#include "dropdimerreaction.h"

DropDimerReaction::DropDimerReaction(Surface *surface):
    DropDimerReaction::DualReaction(surface) {}

double DropDimerReaction::coef() {
    // return ...
}

void DropDimerReaction::seeAt(Carbon *first, Carbon *second) {
    _sites.push_back(std::pair<Carbon*, Carbon*> (first,second));
}

void DropDimerReaction::doIt() {
    int site = rand()%_sites.size();
    _surface->dropDimer(_sites[site].first);
}
