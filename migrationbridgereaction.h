#ifndef MIGRATIONBRIDGE_H
#define MIGRATIONBRIDGE_H

#include <vector>
#include <utility>
#include "migrationbridgeinfo.h"
#include "monoreaction.h"
#include "crystal.h"

class MigrationBridgeReaction : public MonoReaction
{
public:
    MigrationBridgeReaction(Surface *surface, Crystal *crystal, const char *paragraphName);

    void seeAt(Carbon *carbon);
    void doIt();
    void reset();
    void operator() (Carbon *carbon, const int3 &to,
                     Carbon *ffBasis, Carbon *fsBasis,
                     Carbon *tfBasis, Carbon *tsBasis);
                     //const std::pair<Carbon *, Carbon *> &fromBasis,
                     //const std::pair<Carbon *, Carbon *> &toBasis);

protected:
    double coef() const;
    bool checkConditions(Carbon *carbon) const;

    Crystal *_crystal;

private:
    std::vector<std::pair<Carbon *,  Carbon *> > _currBasis;
    std::vector<std::vector<MigrationBridgeInfo> > _infos;
};

#endif // MIGRATIONBRIDGE_H
