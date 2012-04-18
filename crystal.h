#ifndef CRYSTAL_H
#define CRYSTAL_H

#include  <QQueue>
#include "layer.h"
#include "reaction.h"

using namespace std;

class Crystal
{
private:
    int _x_size;
    int _y_size;
    int _completedLayers;

    QQueue<Layer> _layers;

public:
    Crystal() {
    }

    Crystal(int x_size, int y_size):_x_size(x_size), _y_size(y_size)  {
    }

    void throughAllCarbonsIter(std::function<void (Carbon*)> sf) {
        for (int i = 0; i<_layers.size(); i++)
            for (int j = 0; j < SIZE_X*SIZE_Y; j++)
                if (_layers[i].carbon(j)) sf(_layers[i].carbon(j));
    }


    void posDimerIter(Carbon* carbon, std::function<void (Carbon*, Carbon*)> reaction) {}
    void posMigrIter(Carbon* carbon, std::function<void (Carbon*, int3, Carbon*, Carbon*)> reaction) {}
    void getBasis(Carbon* carbon, std::function<void (Carbon*, Carbon*)> reaction) {}
    int3 topPosition(Carbon* first, Carbon* second) {}

    void addCarbon(Carbon* carbon) {
        int deq_index = carbon->coords().z - _completedLayers;
        _layers[deq_index].add(carbon, carbon->coords().x, carbon->coords().y);
    }

    void removeCarbon(Carbon* carbon) {
        int deq_index = carbon->coords().z - _completedLayers;
        _layers[deq_index].remove(carbon->coords().x, carbon->coords().y);
    }
    void move(Carbon* carbon, int3 to) {    // WTF?
        int deq_index = carbon->coords().z - _completedLayers;
        const int3& from = carbon->coords();
        _layers[deq_index].move(from.x, from.y, to.x, to.y);
    }


    void dropCompletedLayers() {

    }

private:
    void init();
    Layer* getLayer(int z) {
        return &_layers[z - _completedLayers];
    }
};

#endif // CRYSTAL_H
