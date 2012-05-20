#ifndef RUNNER_H
#define RUNNER_H

#include "configurator.h"
#include "handbook.h"

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
    Runner(const Configurator &configurator);
    ~Runner();

    void run();

private:
    void save();

    const Configurator &_configurator;
    Handbook _handbook;

    float _totalTime;
    Crystal *_crystal;
    Surface *_surface;
    Reactor *_reactor;
    ReactionsPool *_reactionsPool;
    Saver *_savers[3]; // TODO: циферка!!
};

#endif // RUNNER_H
