#ifndef ETCHINGREACTION_H
#define ETCHINGREACTION_H

#include "monoreaction.h"
#include "crystal.h"

class EtchingReaction : public MonoReaction
{
public:
    EtchingReaction(Crystal *crystal);

    double coef();

    void reset();

    void seeAt(Carbon *carbon);
    void doIt();
    void operator() (Carbon *first, Carbon *second);

private:
    Crystal *_crystal;
    std::set<Carbon*>  _basis;
};

#endif // ETCHINGREACTION_H
