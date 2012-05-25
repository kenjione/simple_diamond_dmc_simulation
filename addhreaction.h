#ifndef ADDHREACTION_H
#define ADDHREACTION_H

#include "monoreaction.h"

class AddHReaction : public MonoReaction
{
public:
    AddHReaction(Surface *surface);

    void seeAt(Carbon *carbon);
    void doIt();

protected:
    double coef() const;
};

#endif // ADDHREACTION_H
