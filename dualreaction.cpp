#include "dualreaction.h"


#include <iostream> //

DualReaction::DualReaction(Surface *surface) : Reaction(surface) {}

double DualReaction::commonRate() {
    std::cout << "call Dual::commonRate() ";
    std::cout << "\n sites.size() = " << _sites.size();
    std::cout << "\n numofsites() = " << _surface->numberOfSites() << std::endl;
    std::cout << "coef = " << coef() << std::endl;
    std::cout << "CommonRate = " << coef() * _sites.size() / (2 * _surface->numberOfSites());
    std::cout << std::endl;
    return coef() * _sites.size() / (2 * _surface->numberOfSites());
}

void DualReaction::reset() {
    _sites.clear();
}
