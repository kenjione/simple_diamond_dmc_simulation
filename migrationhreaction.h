#ifndef MIGRATIONHREACTION_H
#define MIGRATIONHREACTION_H

#include "dualreaction.h"

class MigrationHReaction : public DualReaction
{
public:
    MigrationHReaction(Surface *surface);

    void seeAt(Carbon *first, Carbon* second);
    void doIt() ;

protected:
    double coef() const;
};

#endif // MIGRATIONHREACTION_H
