#ifndef MIGRATIONBRIDGE_H
#define MIGRATIONBRIDGE_H

#include "monoreaction.h"
#include "crystal.h"

class MigrationBridgeReaction : public MonoReaction
{
private:
    Crystal* _crystal;
    QVector<int3> _positions;
    QVector<QPair<Carbon*,  Carbon*> > _currBasis;
    QVector<QPair<Carbon*,  Carbon*> > _toBasis;
public:
    MigrationBridgeReaction();
    double coef() {}
    void seeAt(Carbon *carbon);
    void operator() (int3 to, QPair<Carbon*, Carbon*> fromBasis, QPair<Carbon*, Carbon*> toBasis);
    void doIt();
    void reset();

};

#endif // MIGRATIONBRIDGE_H
