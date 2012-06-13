#include "dualreaction.h"

DualReaction::DualReaction(Surface *surface, const char *paragraphName) : Reaction(surface, paragraphName) {}

double DualReaction::commonRate() {
    return coef() * _sites.size();
}

void DualReaction::reset() {
    _sites.clear();
}
