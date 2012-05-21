#include "layer.h"
#include <assert.h>
#include <cstddef>

#include <iostream>

Layer::Layer(int size_x, int size_y): _x_size(size_x), _y_size(size_y) {
    size_t total = _x_size * _y_size;
    _carbons = new Carbon*[total];
    for (size_t i = 0; i < total; i++) _carbons[i] = 0;
    std::cout << "          ... new layer init done\n"; //
}

Layer::~Layer() {
    for (int i = 0; i < _x_size * _y_size; i++)
        delete _carbons[i];
}

void Layer::throughAllCarbonsIter(std::function<void (Carbon *)> sf) {
    for (int i = 0; i < (_x_size * _y_size); i++) {
        if (_carbons[i]) sf(_carbons[i]);
    }
}

Carbon *Layer::carbon(int x, int y) {
    //if (_carbons[_x_size * y  + x] == 0) return false;
    return _carbons[_x_size * y  + x];
}

void Layer::add(Carbon *carbon, int x, int y) {
    //assert(_carbons[_x_size * y + x]); // проверяем что там ещё нет (на этапе разработки)
    _carbons[_x_size * y + x] = carbon;
}

void Layer::remove(int x, int y) {
    //assert(!_carbons[_x_size * y + x]); // проверяем что там уже есть (на этапе разработки)

    _carbons[_x_size * y + x] = 0;
}

void Layer::move(int from_x, int from_y, int to_x, int to_y) {
    //assert(_carbons[_x_size * to_y + to_x]); // проверяем что там ещё нет (на этапе разработки)

    int3 newcoords = _carbons[_x_size * from_y + from_x]->coords();
    newcoords.x = to_x;
    newcoords.y = to_y;
    _carbons[_x_size * from_y + from_x]->move(newcoords);
    _carbons[_x_size * to_y + to_x] = _carbons[_x_size * from_y + from_x];
    _carbons[_x_size * from_y + from_x] = 0;
}

