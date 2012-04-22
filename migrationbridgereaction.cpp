#include "migrationbridgereaction.h"

MigrationBridgeReaction::MigrationBridgeReaction(Surface *surface, Crystal *crystal) :
    MonoReaction::MonoReaction(surface),_crystal(crystal) {}


double MigrationBridgeReaction::coef() {
    // return ...
}
void MigrationBridgeReaction::seeAt(Carbon *carbon) {}
void MigrationBridgeReaction::doIt() {}
void MigrationBridgeReaction::reset() {
    _sites.clear();
    _positions.clear();
    _currBasis.clear();
    _toBasis.clear();
}

