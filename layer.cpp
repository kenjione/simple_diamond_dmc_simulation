#include "layer.h"
#include <assert.h>
#include <cstddef>

#include <iostream>

Layer::Layer(int sizeX, int sizeY) : _sizeX(sizeX), _sizeY(sizeY), _carbons(0) {
    size_t total = _sizeX * _sizeY;
    _carbons = new Carbon *[total];
    for (size_t i = 0; i < total; i++) _carbons[i] = 0;
    std::cout << "          ... new layer init done\n"; //
}

Layer::~Layer() {
    for (int i = 0; i < _sizeX * _sizeY; i++) delete _carbons[i];
    delete [] _carbons;
}

void Layer::throughAllCarbonsIter(std::function<void (Carbon *)> sf) {
    for (int i = 0; i < (_sizeX * _sizeY); i++) {
        if (_carbons[i]) sf(_carbons[i]);
    }
}

Carbon *Layer::carbon(int x, int y) {
    return _carbons[_sizeX * y + x];
}

void Layer::add(Carbon *crb, int x, int y) {
//    if (crb) assert(!carbon(x, y)); // проверяем что там ещё нет (на этапе разработки)
    _carbons[_sizeX * y + x] = crb;
}

void Layer::remove(int x, int y) {
    assert(carbon(x, y)); // проверяем что там уже есть (на этапе разработки)
    delete carbon(x, y);
    add(0, x, y);
}

void Layer::move(int from_x, int from_y, int to_x, int to_y) {
    Carbon *targetCarbon = carbon(from_x, from_y);

    assert(targetCarbon); // проверяем откуда мигрируем (на этапе разработки)
    assert(!carbon(to_x, to_y)); // проверяем куда мигрируем (на этапе разработки)

    int3 newcoords = targetCarbon->coords();
    newcoords.x = to_x;
    newcoords.y = to_y;
    targetCarbon->move(newcoords);

    add(targetCarbon, to_x, to_y);
    add(0, from_x, from_y);
}
