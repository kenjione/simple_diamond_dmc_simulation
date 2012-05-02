#ifndef REACTION_H
#define REACTION_H

#include <cmath>
#include <cstdlib>
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

    Surface *_surface;

    virtual double coef() = 0;
};

#endif // REACTION_H
