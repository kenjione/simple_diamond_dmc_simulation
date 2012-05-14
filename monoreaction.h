#ifndef MONOREACTION_H
#define MONOREACTION_H

#include <vector>
#include "reaction.h"
#include "carbon.h"

class MonoReaction : public Reaction
{
public:
    double commonRate();
    void reset();

    virtual void seeAt(Carbon *carbon) = 0;

protected:
    MonoReaction(Surface *surface);

    std::vector<Carbon *> _sites;
};

#endif // MONOREACTION_H
