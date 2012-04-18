#ifndef ADDCH2REACTION_H
#define ADDCH2REACTION_H

#include "dualreaction.h"

class AddCH2Reaction : public DualReaction
{
private:
    Crystal* _crystal;
    QVector<int3> _positions;
public:
    AddCH2Reaction(Crystal* crystal): _crystal(crystal) {}
    double coef() {
    }

    void seeAt(Carbon *carbon);
    void doIt();
};

#endif // ADDCH2REACTION_H
