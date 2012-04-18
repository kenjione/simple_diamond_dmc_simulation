#ifndef FORMDIMERREACTION_H
#define FORMDIMERREACTION_H

#include "monoreaction.h"
#include "crystal.h"
#include <QSet>

class FormDimerReaction : public MonoReaction
{
private:
    Crystal* _crystal;
    QSet<Carbon*>  _pairs;
public:
    FormDimerReaction();

    void operator()(Carbon* first, Carbon* second) {}

    double coef() {
    }

    void reset();
    void seeAt(Carbon *carbon);
    void doIt();
};

#endif // FORMDIMERREACTION_H
