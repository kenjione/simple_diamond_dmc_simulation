#ifndef FORMDIMERREACTION_H
#define FORMDIMERREACTION_H

#include "monoreaction.h"
#include "crystal.h"

class FormDimerReaction : public MonoReaction
{
public:
    FormDimerReaction(Surface *surface, Crystal *crystal);
    double coef() {}
    void seeAt(Carbon *carbon);
    void reset();
    void doIt();
    void operator() (Carbon *first, Carbon *second);

private:
    Crystal *_crystal;
    std::set<Carbon *>  _pairs;
};

#endif // FORMDIMERREACTION_H
