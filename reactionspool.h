#ifndef REACTIONSPOOL_H
#define REACTIONSPOOL_H

#include <deque>
#include <string>

#include "abshreaction.h"
#include "addch2reaction.h"
#include "addhreaction.h"
#include "formdimerreaction.h"
#include "dropdimerreaction.h"
#include "etchingreaction.h"
#include "migrationbridgereaction.h"
#include "migrationhreaction.h"


#define REACTIONS_NUM 8


class ReactionsPool
{
public:
    ReactionsPool(Surface *surface, Crystal *crystal);

    std::deque<std::string> reactionsNames() const;
    std::deque<int> reactionsTimes() const;

    void seeAtActives(std::set<Carbon *> activeCarbons);
    void seeAtHydrogens(std::set<Carbon *> hydroCarbons);
    void seeAtDimer(std::map<Carbon *, Carbon *> dimers);

    double doReaction();
    void reset();

private:
    double totalRate();

    AbsHReaction _absH;
    AddHReaction _addH;
    FormDimerReaction _formDimer;
    DropDimerReaction _dropDimer;
    AddCH2Reaction _addCH2;
    EtchingReaction _etching;
    MigrationBridgeReaction _migrationBridge;
    MigrationHReaction _migrationH;

    Reaction *_reactions[REACTIONS_NUM];

    Surface *_surface;

};

#endif // REACTIONSPOOL_H
