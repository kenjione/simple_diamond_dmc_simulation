#ifndef MIGRATIONFRONTDOWN_H
#define MIGRATIONFRONTDOWN_H

#include "migrationbridgereaction.h"

class MigrationFrontDown : public MigrationBridgeReaction
{
public:
    MigrationFrontDown(Surface *surface, Crystal *crystal);

    void seeAt(Carbon *carbon);
};

#endif // MIGRATIONFRONTDOWN_H
