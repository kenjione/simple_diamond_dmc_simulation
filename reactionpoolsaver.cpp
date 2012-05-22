#include "reactionpoolsaver.h"

ReactionPoolSaver::ReactionPoolSaver(const char *outFileName, ReactionsPool *reactionPool) :
    TimeNumberCurvesSaver(outFileName), _reactionPool(reactionPool), _outFileName(outFileName) {}

void ReactionPoolSaver::save(double time) {
    _outFile.close();
    _outFile.open(_outFileName, std::ios::trunc);
    saveHeader(_reactionPool->reactionsNames());
    saveValuesLine(time, _reactionPool->reactionsTimes());
}
