#ifndef CRYSTAL_H
#define CRYSTAL_H

#include <deque>
#include "layer.h"

using namespace std;

class Crystal
{
public:
    Crystal(int x_size, int y_size);

    void throughAllCarbonsIter(std::function<void (Carbon *)> sf);

    void posDimerIter(Carbon *carbon, std::function<void (Carbon *, Carbon *)> reaction) {
//        for (/* по позициям для димера в зависимости от  z */) {
//            reaction(carbon, currentLayer(carbon)->carbon(dimer_indexes));
//          }
    }
    void posMigrIter(Carbon *carbon, std::function<void (Carbon *, const int3 &, Carbon *, Carbon *)> reaction);
    void getBasis(Carbon *carbon, std::function<void (Carbon *, Carbon *)> reaction);
    int3 topPosition(Carbon *first, Carbon* second);

    void addCarbon(Carbon *carbon);
    void removeCarbon(Carbon *carbon);
    void move(Carbon *carbon, const int3 &to);

    void dropCompletedLayers();

private:
    Crystal();

    void init();

    Layer *getLayer(int z) {
        return &_layers[z - _completedLayers];
    }

    int _x_size, _y_size;

    std::deque<Layer> _layers;
    int _completedLayers;
};

#endif // CRYSTAL_H
