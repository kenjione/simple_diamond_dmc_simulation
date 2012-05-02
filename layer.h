#ifndef LAYER_H
#define LAYER_H

#include <functional>
#include "carbon.h"

class Layer
{
public:
    Layer(int size_x, int size_y);
    ~Layer();

    Carbon *carbon(int x, int y);
    void throughAllCarbonsIter(std::function<void (Carbon *)> sf);
    void add(Carbon *carbon, int x, int y);
    void remove(int x, int y);
    void move(int from_x, int from_y, int to_x, int to_y);

private:
    Layer();

    int _x_size, _y_size;
    Carbon** _carbons;
};

#endif // LAYER_H
