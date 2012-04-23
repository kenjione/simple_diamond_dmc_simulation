#include "etchingreaction.h"

EtchingReaction::EtchingReaction(Surface *surface, Crystal *crystal) :
    MonoReaction(surface), _crystal(crystal) {}

double EtchingReaction::coef() {}

void EtchingReaction::seeAt(Carbon *carbon) {}

void EtchingReaction::doIt() {}

void EtchingReaction::operator() (Carbon *first, Carbon *second) {}
