#ifndef FORMDIMERREACTION_H
#define FORMDIMERREACTION_H

#include "dualreaction.h"
#include "crystal.h"

class FormDimerReaction : public DualReaction
{
public:
    FormDimerReaction(Surface *surface, Crystal *crystal);

    void seeAt(Carbon *first, Carbon *second);
    void reset();
    void doIt();
    void initDimerLayer();
    void operator() (Carbon *first, Carbon *second);

protected:
    double coef() const;

private:
    Crystal *_crystal;
    std::set<Carbon *>  _pairs;
};

#endif // FORMDIMERREACTION_H
