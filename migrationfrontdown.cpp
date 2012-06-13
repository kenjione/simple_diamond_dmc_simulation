#include "migrationfrontdown.h"

MigrationFrontDown::MigrationFrontDown(Surface *surface, Crystal *crystal, const char *paragraphName) :
    MigrationBridgeReaction(surface, crystal, paragraphName)
{}

void MigrationFrontDown::seeAt(Carbon *carbon) {
    if (checkConditions(carbon)) return;
    _crystal->posMigrDownFrontIter(carbon, std::ref(*this));
}
