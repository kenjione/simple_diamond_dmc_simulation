#ifndef ADDHREACTION_H
#define ADDHREACTION_H

#include "monoreaction.h"

class AddHReaction : public MonoReaction
{
public:
    AddHReaction(Surface *surface);

    double coef();
    void seeAt(Carbon *carbon);
    void doIt();
};

#endif // ADDHREACTION_H
