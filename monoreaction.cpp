#include "monoreaction.h"

MonoReaction::MonoReaction(Surface *surface, const char *paragraphName) :
    Reaction(surface, paragraphName) {}

double MonoReaction::commonRate()  {
    return coef() * _sites.size();
}

void MonoReaction::reset() {
    _sites.clear();
}
