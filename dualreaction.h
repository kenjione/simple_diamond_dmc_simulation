#ifndef DUALREACTION_H
#define DUALREACTION_H

#include <QVector>
#include <QPair>

#include "crystal.h"
#include "reaction.h"
#include "carbon.h"

class DualReaction : public Reaction
{
protected:
    QVector<  QPair<Carbon*, Carbon*> >_sites;
    DualReaction();
public:
    double commonRate();
    void reset();
    virtual void seeAt(Carbon* carbon) = 0;
};

#endif // DUALREACTION_H
