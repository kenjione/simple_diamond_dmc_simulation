#include "monoreaction.h"

#include <iostream> //

MonoReaction::MonoReaction(Surface *surface) : Reaction(surface) {}

double MonoReaction::commonRate()  {

    std::cout << "call MonoR::commonRate() ";
    std::cout << "\n sites.size() = " << _sites.size();
    std::cout << "\n numofsites() = " << _surface->numberOfSites() << std::endl;
    std::cout << "coef -> " << coef();
    return 2;
    //return coef() * _sites.size() / _surface->numberOfSites();
}

void MonoReaction::reset() {
    _sites.clear();
}
