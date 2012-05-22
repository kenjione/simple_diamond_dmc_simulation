#ifndef REACTIONPOOLSAVER_H
#define REACTIONPOOLSAVER_H

#include <string>
#include "timenumbercurvessaver.h"
#include "reactionspool.h"

class ReactionPoolSaver : public TimeNumberCurvesSaver
{
public:
    ReactionPoolSaver(const char *outFileName, ReactionsPool *reactionPool);

    void save(double time);

private:
    ReactionsPool *_reactionPool;
    std::string _outFileName;
};

#endif // REACTIONPOOLSAVER_H
