#ifndef ADDCH2REACTION_H
#define ADDCH2REACTION_H

#include "dualreaction.h"
#include "crystal.h"

class AddCH2Reaction : public DualReaction
{
public:
    AddCH2Reaction(Surface *surface, Crystal *crystal);

    void seeAt(Carbon *first, Carbon *second);
    void doIt();
    void doItForDimerRow();
    void reset();

protected:
    double coef() const;

private:
    void makeAddCh2(size_t siteIndex);

    Crystal *_crystal;
    std::vector<int3> _positions;
};

#endif // ADDCH2REACTION_H
