#include "reactionpoolsaver.h"

ReactionPoolSaver::ReactionPoolSaver(const char *outFileName, ReactionsPool *reactionPool) :
    TimeNumberCurvesSaver(outFileName), _reactionPool(reactionPool)
{
    saveHeader(_reactionPool->reactionsNames());
}

void ReactionPoolSaver::save(float time) {
    saveValuesLine(time, _reactionPool->reactionsTimes());
}
