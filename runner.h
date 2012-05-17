#ifndef RUNNER_H
#define RUNNER_H

#include "reactor.h"
#include "reaction.h"
#include "surface.h"
#include "saver.h"

#include "reactionpoolsaver.h"
#include "surfacesaver.h"
#include "crystalsaver.h"

class Runner
{
public:
    Runner();
    ~Runner();

    void run();

private:
    float _totalTime;
    Crystal *_crystal;
    Surface *_surface;
    Reactor *_reactor;
    ReactionsPool *_reactionsPool;
    Saver *_savers[3]; // TODO: циферка!!

    void save();
};

#endif // RUNNER_H
