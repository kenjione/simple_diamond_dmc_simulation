#include "reactionpoolsaver.h"

ReactionPoolSaver::ReactionPoolSaver(const char *outFileName, ReactionsPool *reactionPool) :
    Saver(outFileName), _reactionPool(reactionPool) {}

void ReactionPoolSaver::save() {
    _outFile << "[reaction#] = [times]\n";

    for (int i = 0; i < REACTIONS_NUM; i++) {
        _outFile << "reaction #" << i+1 <<  " = " << _reactionPool->reactionTimes()[i] << std::endl;
    }
}
