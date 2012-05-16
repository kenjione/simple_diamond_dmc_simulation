#ifndef REACTIONSPOOL_H
#define REACTIONSPOOL_H

#include "abshreaction.h"
#include "addch2reaction.h"
#include "addhreaction.h"
#include "formdimerreaction.h"
#include "dropdimerreaction.h"
#include "etchingreaction.h"
#include "migrationbridgereaction.h"
#include "migrationhreaction.h"


class ReactionsPool
{
public:
    ReactionsPool(Surface *surface, Crystal *crystal);
    void seeAtActives(std::set<Carbon *> activeCarbons);
    void seeAtHydrogens(std::set<Carbon *> hydroCarbons);
    void seeAtDimer(std::map<Carbon *, Carbon *> dimers);

    float doReaction();
    void reset();

private:
    AbsHReaction _absH;
    AddHReaction _addH;
    FormDimerReaction _formDimer;
    DropDimerReaction _dropDimer;
    AddCH2Reaction _addCH2;
    EtchingReaction _etching;
    MigrationBridgeReaction _migrationBridge;
    MigrationHReaction _migrationH;

    MonoReaction *_mono[4];
    DualReaction *_dual[4];

    Reaction *_reactions[8];

    Surface *_surface;
    Crystal *_crystal;

    double totalRate();
};

#endif // REACTIONSPOOL_H
