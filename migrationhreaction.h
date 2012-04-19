#ifndef MIGRATIONHREACTION_H
#define MIGRATIONHREACTION_H

#include "dualreaction.h"

class MigrationHReaction : public DualReaction
{
public:
    MigrationHReaction();

    double coef();

    void seeAt(Carbon *carbon);
    void doIt();
};

#endif // MIGRATIONHREACTION_H
