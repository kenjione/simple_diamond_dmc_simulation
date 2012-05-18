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

    void incTimes() { _times++; }
    int times() const { return _times; }

protected:
    static Reactor *__reactor;
    static float R;

    Reaction(Surface *surface) : _surface(surface), _times(0) {}

    virtual double coef() const = 0;

    Surface *_surface;
    int _times;
};

#endif // REACTION_H
