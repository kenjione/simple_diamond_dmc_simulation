#ifndef DROPDIMERREACTION_H
#define DROPDIMERREACTION_H

#include "dualreaction.h"

class DropDimerReaction : public DualReaction
{
public:
    DropDimerReaction(Surface *surface);

    void seeAt(Carbon *first, Carbon* second);
    void doIt();

protected:
    double coef() const;
};

#endif // DROPDIMERREACTION_H
