#ifndef ETCHINGREACTION_H
#define ETCHINGREACTION_H

#include "crystal.h"

#include "monoreaction.h"

class EtchingReaction : public MonoReaction
{
private:
    Crystal* _crystal;
    QSet<Carbon*>  _basis;
public:
    EtchingReaction();

    void operator()(Carbon* first, Carbon* second) {}

    double coef() {
    }

    void reset();
    void seeAt(Carbon *carbon);
    void doIt();
};

#endif // ETCHINGREACTION_H
