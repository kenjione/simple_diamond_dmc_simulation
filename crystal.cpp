#include "crystal.h"

Crystal::Crystal(int x_size, int y_size) : _x_size(x_size), _y_size(y_size) {}

void Crystal::throughAllCarbonsIter(std::function<void (Carbon *)> sf) {
    for (auto &layer : _layers) layer.throughAllCarbonsIter(sf);
}

void Crystal::addCarbon(Carbon *carbon) {
    getLayer(carbon->coords().z)->add(carbon, carbon->coords().x, carbon->coords().y);
}

void Crystal::removeCarbon(Carbon *carbon) {
    getLayer(carbon->coords().z)->remove(carbon->coords().x, carbon->coords().y);
}

void Crystal::move(Carbon *carbon, const int3 &to) {
    getLayer(carbon->coords().z)->move(carbon->coords().x, carbon->coords().y, to.x, to.y);
}

