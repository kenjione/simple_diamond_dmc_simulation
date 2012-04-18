#ifndef LAYER_H
#define LAYER_H

#define SIZE_X 25
#define SIZE_Y 15

#include "carbon.h"

#include <functional>


class Layer
{
private:
    int _x_size;
    int _y_size;
    Carbon** _carbon;
public:
    Layer();
    ~Layer() {
        delete [] _carbon;
    }
    Layer(int size_x, int size_y): _x_size(size_x), _y_size(size_y) {
        _carbon = new Carbon*[size_x * size_y];
        for (int i = 0; i < (_x_size * _y_size) ; i++)
            _carbon[i] = 0;
        // обращение к элементу через carbon[size_x * y + x]
    }

    Carbon* carbon(int x, int y) {
        return _carbon[_x_size * y  + x];
    }

    Carbon* carbon(int index) {
        return _carbon[index];
    }

    void add(Carbon* carbon, int x, int y) {
        _carbon[_x_size * y + x] = carbon;
    }

    void remove(int x, int y) {
        _carbon[_x_size * y + x] = 0;
    }

    void move(int from_x, int from_y, int to_x, int to_y) {
        _carbon[_x_size * to_y + to_x] = _carbon[_x_size * from_y + from_x];
        _carbon[_x_size * from_y + from_x] = 0;
    }


    //void throughAllCarbonsIter(std::function<void (Carbon*)> sf) {}  // нужно ли?
};

#endif // LAYER_H
