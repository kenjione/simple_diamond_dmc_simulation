#ifndef ETCHINGREACTION_H
#define ETCHINGREACTION_H

#include "monoreaction.h"
#include "crystal.h"


class EtchingReaction : public MonoReaction
{
public:
    EtchingReaction(Surface *surface, Crystal *crystal);

    void seeAt(Carbon *carbon);
    void doIt();

    void operator() (Carbon *carbon, Carbon *first, Carbon *second);

protected:
    double coef() const;

private:
    Crystal *_crystal;
    std::vector<std::pair<Carbon*, Carbon*> >  _basis;
};

#endif // ETCHINGREACTION_H
