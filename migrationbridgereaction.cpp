#include "migrationbridgereaction.h"


MigrationBridgeReaction::MigrationBridgeReaction(Surface *surface, Crystal *crystal) :
    MonoReaction(surface), _crystal(crystal) {}

double MigrationBridgeReaction::coef() {
    return 6.13 * (10e13) * exp(-18.269/__reactor->temperature());
}

void MigrationBridgeReaction::seeAt(Carbon *carbon) {

}

void MigrationBridgeReaction::operator ()(const int3 &to,
                                          const std::pair<Carbon *, Carbon *> &fromBasis,
                                          const std::pair<Carbon *, Carbon *> &toBasis) {}

void MigrationBridgeReaction::doIt() {}

void MigrationBridgeReaction::reset() {
    MonoReaction::reset();
    _positions.clear();
    _currBasis.clear();
    _toBasis.clear();
}

