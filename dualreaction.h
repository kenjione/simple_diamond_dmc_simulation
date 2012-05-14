#ifndef DUALREACTION_H
#define DUALREACTION_H

#include <vector>
#include <utility>
#include "reaction.h"
#include "carbon.h"

class DualReaction : public Reaction
{
public:
    double commonRate();
    void reset();

    virtual void seeAt(Carbon *first, Carbon *second) = 0;

protected:
    DualReaction(Surface *surface);

    std::vector<std::pair<Carbon*, Carbon*> > _sites;
};

#endif // DUALREACTION_H
