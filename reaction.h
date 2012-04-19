#ifndef REACTION_H
#define REACTION_H

#include "reactor.h"

class Surface;

class Reaction
{
public:
    static void setReactor(Reactor *reactor) {
        __reactor = reactor;
    }

    virtual double commonRate() = 0;
    virtual void doIt() = 0;
    virtual void reset() = 0;

protected:
    static Reactor *__reactor;
    Surface *_surface;

    Reaction(Surface *surface) : _surface(surface) {}

    virtual double coef() = 0;
};

Reactor *Reaction::__reactor = 0;

#endif // REACTION_H
