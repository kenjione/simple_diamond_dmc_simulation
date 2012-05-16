#include "monoreaction.h"

#include <iostream> //

MonoReaction::MonoReaction(Surface *surface) : Reaction(surface) {}

double MonoReaction::commonRate()  {
    std:: cout << "siteSize: " << _sites.size() << "\n";
    return coef() * _sites.size();
}

void MonoReaction::reset() {
    _sites.clear();
}
