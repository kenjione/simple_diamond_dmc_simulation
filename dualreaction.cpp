#include "dualreaction.h"


#include <iostream> //

DualReaction::DualReaction(Surface *surface) : Reaction(surface) {}

double DualReaction::commonRate() {
 //   std:: cout << "siteSize: " << _sites.size() << "\n";
    return coef() * _sites.size();
}

void DualReaction::reset() {
    _sites.clear();
}
