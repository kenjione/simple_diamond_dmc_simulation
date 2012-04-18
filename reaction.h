#ifndef REACTION_H
#define REACTION_H

#include "reactor.h"

class Surface;

class Reaction
{
protected:
    static Reactor __reactor;
    Surface* _surface;

    Reaction(Surface* surface): _surface(surface) {}
    virtual double coef() = 0;
public:
    virtual double commonRate() = 0;
    virtual void doIt() = 0;
    virtual void reset() = 0;
};

#endif // REACTION_H
