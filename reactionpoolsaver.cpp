#include "reactionpoolsaver.h"

ReactionPoolSaver::ReactionPoolSaver(const char *outFileName, ReactionsPool *reactionPool) :
    TimeNumberCurvesSaver(outFileName), _reactionPool(reactionPool), _totalTime(0)
{
    saveHeader(_reactionPool->reactionsNames());
}

ReactionPoolSaver::~ReactionPoolSaver() {
    saveValuesLine(_totalTime, _reactionsTimes);
}

void ReactionPoolSaver::save(double time) {
    _totalTime = time;
    _reactionsTimes = _reactionPool->reactionsTimes();
}
