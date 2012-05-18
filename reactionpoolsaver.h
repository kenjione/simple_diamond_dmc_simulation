#ifndef REACTIONPOOLSAVER_H
#define REACTIONPOOLSAVER_H

#include "timenumbercurvessaver.h"
#include "reactionspool.h"

class ReactionPoolSaver : public TimeNumberCurvesSaver
{
public:
    ReactionPoolSaver(const char *outFileName, ReactionsPool *reactionPool);
    void save(float time);

private:
    ReactionsPool *_reactionPool;
};

#endif // REACTIONPOOLSAVER_H
