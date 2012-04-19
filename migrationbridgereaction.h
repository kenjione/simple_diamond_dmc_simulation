#ifndef MIGRATIONBRIDGE_H
#define MIGRATIONBRIDGE_H

#include <vector>
#include <utility>
#include "monoreaction.h"
#include "crystal.h"

class MigrationBridgeReaction : public MonoReaction
{
public:
    MigrationBridgeReaction(Crystal *crystal);

    double coef();

    void reset();
    void seeAt(Carbon *carbon);
    void doIt();
    void operator() (const int3 &to,
                     const std::pair<Carbon *, Carbon *> &fromBasis,
                     const std::pair<Carbon *, Carbon *> &toBasis);

private:
    Crystal *_crystal;
    std::vector<int3> _positions;
    std::vector<std::pair<Carbon *,  Carbon *>> _currBasis;
    std::vector<std::pair<Carbon *,  Carbon *>> _toBasis;
};

#endif // MIGRATIONBRIDGE_H
