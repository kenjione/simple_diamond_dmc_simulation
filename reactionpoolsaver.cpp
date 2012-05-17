#include "reactionpoolsaver.h"

ReactionPoolSaver::ReactionPoolSaver(const char *outFileName, ReactionsPool *reactionPool) :
    Saver(outFileName), _reactionPool(reactionPool) {}

void ReactionPoolSaver::save() {

}
