#ifndef DUALREACTION_H
#define DUALREACTION_H

#include <vector>
#include <utility>
#include <stdlib.h> //
#include "reaction.h"
#include "carbon.h"

class DualReaction : public Reaction
{
public:
    double commonRate();
    virtual void seeAt(Carbon *carbon) = 0;
    virtual void doIt() = 0;
    void reset();

protected:
    DualReaction(Surface *surface);

    std::vector<std::pair<Carbon*, Carbon*> > _sites;
};

#endif // DUALREACTION_H
