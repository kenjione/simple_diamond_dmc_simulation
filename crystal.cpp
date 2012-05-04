#include "crystal.h"
#include "surface.h"

Crystal::Crystal(int x_size, int y_size) : _x_size(x_size), _y_size(y_size), _completedLayers(0), _surface(0) {}

Crystal::~Crystal() {
    delete _surface;
}

void Crystal::init() {
    _surface = new Surface(this);
    _surface->init();

    // далее со слоями..
}

void Crystal::throughAllCarbonsIter(std::function<void (Carbon *)> sf) {
    for (auto &layer : _layers) layer.throughAllCarbonsIter(sf);
}

void Crystal::posDimerIter(Carbon *carbon, std::function<void (Carbon *, Carbon *)> reaction) {
    int3 firstCarbonCoords = carbon->coords();
    int dx = 0;
    int dy = 0;

    if ((firstCarbonCoords.z + 1) % 2 == 0) dx = 1;
    else dy = 1;

    for (int i = 0; i < 2; ++i) {
        reaction(carbon, getLayer(carbon->coords().z)->carbon(firstCarbonCoords.x + dx,
                                                              firstCarbonCoords.y + dy));
    }
}

void Crystal::getBasis(Carbon *carbon, std::function<void (Carbon *, Carbon *)> reaction) {
    int3 topPos = carbon->coords();
    int3 firstBottomPos = carbon->coords();
    int3 secondBottomPos = carbon->coords();

    if ((topPos.z + 1) % 4 == 0) {
        firstBottomPos.y++;
    } else if ((topPos.z + 1) % 3 == 0) {
        firstBottomPos.x++;
    } else if ((topPos.z + 1) % 2 == 0) {
        firstBottomPos.y--;
    } else {
        firstBottomPos.x--;
    }

    // нужны проверки на выход за пределы, и взятие с другой стороны, т.к. по x и y - какбе тор

    firstBottomPos.z--;
    secondBottomPos.z--;

    Carbon *firstBottom = getLayer(firstBottomPos.z)->carbon(firstBottomPos.x, firstBottomPos.y);
    Carbon *secondBottom = getLayer(secondBottomPos.z)->carbon(secondBottomPos.x, secondBottomPos.y);
    reaction(firstBottom, secondBottom);
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

int3 Crystal::topPosition(Carbon *first, Carbon *second) {

    // нужно от обоих карбонов

    int3 topPos = first->coords();
    if ((topPos.z + 1) % 4 == 0) topPos.y--;
    else if ((topPos.z + 1) % 3 == 0) topPos.x--;
    else if ((topPos.z + 1) % 2 == 0) topPos.y++;
    else topPos.x++;

    topPos.z++;
    return topPos;
}
