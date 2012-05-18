#ifndef REACTIONPOOLSAVER_H
#define REACTIONPOOLSAVER_H

#include "saver.h"
#include "reactionspool.h"

class ReactionPoolSaver : public Saver
{
public:
    ReactionPoolSaver(const char *outFileName, ReactionsPool *reactionPool);
    void save();

private:
    ReactionsPool *_reactionPool;
};

#endif // REACTIONPOOLSAVER_H
