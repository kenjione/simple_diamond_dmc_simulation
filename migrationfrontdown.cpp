#include "migrationfrontdown.h"

MigrationFrontDown::MigrationFrontDown(Surface *surface, Crystal *crystal) :
    MigrationBridgeReaction(surface, crystal, "Migration down front reaction")
{}

void MigrationFrontDown::seeAt(Carbon *carbon) {
    if (checkConditions(carbon)) return;
    _crystal->posMigrDownFrontIter(carbon, std::ref(*this));
}
