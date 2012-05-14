#ifndef RUNNER_H
#define RUNNER_H

#include "reactor.h"
#include "surface.h"
#include "saver.h"
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
    Saver *_saver;

    void save();
};

#endif // RUNNER_H
