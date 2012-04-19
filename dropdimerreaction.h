#ifndef DROPDIMERREACTION_H
#define DROPDIMERREACTION_H

#include "dualreaction.h"

class DropDimerReaction : public DualReaction
{
public:
    DropDimerReaction();

    double coef();

    void seeAt(Carbon *carbon);
    void doIt();
};

#endif // DROPDIMERREACTION_H
