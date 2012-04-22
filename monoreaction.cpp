#include "monoreaction.h"

MonoReaction::MonoReaction(Surface *surface): MonoReaction::Reaction(surface) {}

double MonoReaction::commonRate()  {
    return coef() * _sites.size() / _surface->numberOfSites();
}

void MonoReaction::reset() { _sites.clear(); }
