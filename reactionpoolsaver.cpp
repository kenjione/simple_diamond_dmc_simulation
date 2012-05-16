#include "reactionpoolsaver.h"

ReactionPoolSaver::ReactionPoolSaver(char *outFileName, ReactionsPool *reactionPool) :
    Saver(outFileName), _reactionPool(reactionPool) {}

void ReactionPoolSaver::save() {

}
