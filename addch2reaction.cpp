#include "addch2reaction.h"

AddCH2Reaction::AddCH2Reaction(Surface *surface, Crystal *crystal) :
    DualReaction(surface), _crystal(crystal) {}

double AddCH2Reaction::coef() {
    // return ...
}

void AddCH2Reaction::seeAt(Carbon *first, Carbon* second) {

}

void AddCH2Reaction::doIt() {}

void AddCH2Reaction::reset() {
    DualReaction::reset();
    _positions.clear();
}
