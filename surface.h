#ifndef SURFACE_H
#define SURFACE_H

#include <deque>
#include <string>
#include <map>
#include <set>

#include "crystal.h"

class Reaction;
class ReactionsPool;

class Surface
{
public:
    Surface(Crystal *crystal);
    ~Surface();

    std::deque<std::string> setsNames() const;
    std::deque<int> setsNumbers() const;

    void init();
    void operator() (Carbon *carbon);

//    int numberOfSites(); // TODO: этот метод используется?

    void addHydrogen(Carbon *carbon);
    void removeHydrogen(Carbon *carbon);

    void addCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond);
    void removeCarbon(Carbon *carbon, Carbon *bottomFirst, Carbon *bottomSecond);
    void moveCarbon(Carbon *carbon, const int3 &to,
                    const std::pair<Carbon *, Carbon *> &fromBasis,
                    const std::pair<Carbon *, Carbon *> &toBasis);

    void addDimer(Carbon *first, Carbon *second);
    void dropDimer(Carbon *first, Carbon *second);

    double doReaction(ReactionsPool *reactionPool);

private:
    void formBondsFor(Carbon *first, Carbon *second);
    void dropBondsFor(Carbon *first, Carbon *second);
    void removeFromDimersHash(Carbon *first, Carbon *second);

    Crystal *_crystal;

    std::set<Carbon *> _activeCarbons, _hydroCarbons;
    std::map<Carbon *,Carbon *> _dimerBonds;
};

#endif // surface_H
