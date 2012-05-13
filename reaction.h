#ifndef REACTION_H
#define REACTION_H

#include "reactor.h"
#include "surface.h"


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
    static float R;

    Reaction(Surface *surface) : _surface(surface) {}

    virtual double coef() = 0;

    Surface *_surface;
};

#endif // REACTION_H
