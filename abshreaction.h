#ifndef ABSHREACTION_H
#define ABSHREACTION_H

#include "monoreaction.h"

class AbsHReaction : public MonoReaction
{
public:
    AbsHReaction(Surface *surface, const char *paragraphName);

    void seeAt(Carbon *carbon);
    void doIt();

protected:
    double coef() const;
};

#endif // ABSHREACTION_H
