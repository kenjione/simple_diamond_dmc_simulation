#ifndef DROPDIMERREACTION_H
#define DROPDIMERREACTION_H

#include "dualreaction.h"

class DropDimerReaction : public DualReaction
{
public:
    DropDimerReaction(Surface *surface);

    double coef();
    void seeAt(Carbon *first, Carbon* second);
    void doIt();
};

#endif // DROPDIMERREACTION_H
