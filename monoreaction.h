#ifndef MONOREACTION_H
#define MONOREACTION_H

#include <vector>
#include "reaction.h"
#include "carbon.h"

class MonoReaction : public Reaction
{
public:
    double commonRate();

    virtual void seeAt(Carbon *carbon) = 0;

    void reset();

protected:
    MonoReaction();

    std::vector<Carbon *> _sites;
};

#endif // MONOREACTION_H
