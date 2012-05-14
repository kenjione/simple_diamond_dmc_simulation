#include "crystal.h"

Crystal::Crystal(int x_size, int y_size) : _x_size(x_size), _y_size(y_size), _completedLayers(0) {}
#include <iostream>

void Crystal::init() {
    // инициализация первых двух слоев

    _layers.push_back(Layer(_x_size, _y_size));

    std::cout << "LAYER 0: \n";

    for (int i = 0; i < _y_size; i++)
    {
        for (int j = 0; j < _x_size; j++)
            std::cout << _layers[0].carbon(j, i) << " ";
        std::cout << "\n";
    }

    // первый слой с чистыми карбонами

    for (int i = 0; i < _y_size; i++)
        for (int j = 0; j < _x_size; j++)
            _layers[0].add(new Carbon(int3(j,i,0),0,0), j, i);

    std::cout << "LAYER 1 : \n";

    for (int i = 0; i < _y_size; i++)
    {
        for (int j = 0; j < _x_size; j++)
            std::cout << _layers[0].carbon(j, i) << " ";
        std::cout << "\n";
    }

    // второй слой с *-с-Н

    _layers.push_back(Layer(_x_size, _y_size));

    for (int i = 0; i < _y_size; i++)
        for (int j = 0; j < _x_size; j++)       // 1, 1
            _layers[1].add(new Carbon(int3(j,i,1),2,0), j, i);

    std::cout << "LAYER 2 : \n";

    for (int i = 0; i < _y_size; i++)
    {
        for (int j = 0; j < _x_size; j++)
            std::cout << _layers[1].carbon(j, i) << " ";
        std::cout << "\n";
    }


    //_layers.push_back(Layer(_x_size, _y_size));
    //addCarbon(new Carbon(int3(5,5,2),0,2));

    //_layers.push_back(Layer(_x_size, _y_size));
    //addCarbon(new Carbon(int3(5,5,3),0,2));
}

void Crystal::throughAllCarbonsIter(std::function<void (Carbon *)> sf) {
    for (auto &layer : _layers) layer.throughAllCarbonsIter(sf);
}


void Crystal::posMigrIter(Carbon *carbon, std::function<void (Carbon *, const int3 &, Carbon *, Carbon *, Carbon *, Carbon *)> reaction) {
    // посмотрел по истории - ничего небыло тут.
}

void Crystal::posDimerIter(Carbon *carbon, std::function<void (Carbon *, Carbon *)> reaction) {

    // выполнить проверку на выход за границы!

    std::cout << "call Crystal::posMigrIter\n";
    int3 firstCarbonCoords = carbon->coords();

    std::cout << "  fcc: {" << firstCarbonCoords.x << ", " << firstCarbonCoords.y << "}";

    int dx = 0;
    int dy = 0;

    if ((firstCarbonCoords.z) % 2 == 0) dx = 1;
    else dy = 1;

    // проверка не выход за границу
    if (firstCarbonCoords.x + dx == _x_size) firstCarbonCoords.x = 0;
    if (firstCarbonCoords.y + dy == _y_size) firstCarbonCoords.y = 0;

    std::cout << "  scc: {" << firstCarbonCoords.x + dx << ", " << firstCarbonCoords.y + dy << "}\n";
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

    // TODO:
    // нужны поверки на выход за пределы

    firstBottomPos.z--;
    secondBottomPos.z--;

    Carbon *firstBottom = getLayer(firstBottomPos.z)->carbon(firstBottomPos.x, firstBottomPos.y);
    Carbon *secondBottom = getLayer(secondBottomPos.z)->carbon(secondBottomPos.x, secondBottomPos.y);
    reaction(firstBottom, secondBottom);
}

void Crystal::addCarbon(Carbon *carbon) {
    _layers.push_back(Layer(_x_size, _y_size));
    getLayer(carbon->coords().z)->add(carbon, carbon->coords().x, carbon->coords().y);
}

void Crystal::removeCarbon(Carbon *carbon) {
    getLayer(carbon->coords().z)->remove(carbon->coords().x, carbon->coords().y);
}

void Crystal::move(Carbon *carbon, const int3 &to) {
    getLayer(carbon->coords().z)->move(carbon->coords().x, carbon->coords().y, to.x, to.y);
}

int3 Crystal::topPosition(Carbon *first, Carbon *second) {

    // TODO: нужно от обоих карбонов!
    int3 topPos = first->coords();
    topPos.z++;

    if (topPos.z % 4 == 3) topPos.y--;
    else if (topPos.z % 4 == 2) ;
    else if (topPos.z % 4 == 1) topPos.x--;
    else {
        topPos.x--;
        topPos.y--;
    }


    return topPos;
}
