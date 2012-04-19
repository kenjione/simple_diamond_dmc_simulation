#ifndef FORMDIMERREACTION_H
#define FORMDIMERREACTION_H

#include "monoreaction.h"
#include "crystal.h"

class FormDimerReaction : public MonoReaction
{
public:
    FormDimerReaction(Crystal *crystal);

    double coef();

    void reset();

    void seeAt(Carbon *carbon);
    void doIt();
    void operator() (Carbon *first, Carbon *second);

private:
    Crystal *_crystal;
    std::set<Carbon *>  _pairs;
};

#endif // FORMDIMERREACTION_H
