#ifndef ADDHREACTION_H
#define ADDHREACTION_H

#include "monoreaction.h"

class AddHReaction : public MonoReaction
{
public:
    AddHReaction(Surface *surface);

    void seeAt(Carbon *carbon);
    void doIt();
    void doItForAllActives();

protected:
    void makeAddH(size_t siteIndex);

    double coef() const;
};

#endif // ADDHREACTION_H
