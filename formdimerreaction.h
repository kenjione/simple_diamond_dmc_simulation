#ifndef FORMDIMERREACTION_H
#define FORMDIMERREACTION_H

#include "dualreaction.h"
#include "crystal.h"

class FormDimerReaction : public DualReaction
{
public:
    FormDimerReaction(Surface *surface, Crystal *crystal);

    double coef();

    void seeAt(Carbon *first, Carbon *second);
    void reset();
    void doIt();
    void operator() (Carbon *first, Carbon *second);

private:
    Crystal *_crystal;
    std::set<Carbon *>  _pairs;
};

#endif // FORMDIMERREACTION_H
