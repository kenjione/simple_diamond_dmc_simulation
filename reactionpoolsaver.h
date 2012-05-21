#ifndef REACTIONPOOLSAVER_H
#define REACTIONPOOLSAVER_H

#include "timenumbercurvessaver.h"
#include "reactionspool.h"

class ReactionPoolSaver : public TimeNumberCurvesSaver
{
public:
    ReactionPoolSaver(const char *outFileName, ReactionsPool *reactionPool);
    ~ReactionPoolSaver();

    void save(double time);

private:
    ReactionsPool *_reactionPool;

    double _totalTime;
    std::deque<int> _reactionsTimes;
};

#endif // REACTIONPOOLSAVER_H
