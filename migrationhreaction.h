#ifndef MIGRATIONHREACTION_H
#define MIGRATIONHREACTION_H

#include "dualreaction.h"

class MigrationHReaction : public DualReaction
{
public:
    MigrationHReaction(Surface *surface, float r);

    double coef();
    void seeAt(Carbon *first, Carbon* second);
    void doIt() ;
private:
    float _r;
};

#endif // MIGRATIONHREACTION_H
