#ifndef ABSHREACTION_H
#define ABSHREACTION_H

#include "monoreaction.h"

class AbsHReaction : public MonoReaction
{
public:
    AbsHReaction(Surface *surface);

    double coef();
    void seeAt(Carbon *carbon);
    void doIt();
};

#endif // ABSHREACTION_H
