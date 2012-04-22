#ifndef REACTION_H
#define REACTION_H

#include "reactor.h"
#include "surface.h"
#include <stdlib.h>


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
    Reaction(Surface *surface) : _surface(surface) {}
    static Reactor *__reactor;
    Surface *_surface;

    virtual double coef() = 0;
};


/* если раскомментить эту строчку, ругается на
"multiple definition of `Reaction::__reactor` во всех классах-реакциях",
причем ругается в разных методах .. где-то в coef(), а где-то в reset(); */

Reactor *Reaction::__reactor = 0;

#endif // REACTION_H
