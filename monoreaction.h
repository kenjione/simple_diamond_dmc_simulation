#ifndef MONOREACTION_H
#define MONOREACTION_H

#include "reaction.h"
#include "carbon.h"
#include <QVector>

class MonoReaction : public Reaction
{
protected:
    QVector<Carbon*> _sites;
    MonoReaction();
public:
    double commonRate();
    void reset();
    virtual void seeAt(Carbon* carbon) = 0;
};

#endif // MONOREACTION_H
