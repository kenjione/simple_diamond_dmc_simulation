#include "crystal.h"
#include <iostream>

Crystal::Crystal(int sizeX, int sizeY) : _sizeX(sizeX), _sizeY(sizeY), _completedLayers(0) {
//    std::cout << "CRYSTAL SIZE: " << _sizeX << "x" << _sizeY << std::endl;
    init();
}

void Crystal::init() {
    // инициализация первых двух слоев
    createLayer(0, 0);
    createLayer(1, 1);

    //createLayer();
    //addCarbon(new Carbon(int3(5,5,2),0,2));

    //createLayer();
    //addCarbon(new Carbon(int3(5,5,3),0,2));
}

void Crystal::createLayer() {
    _layers.push_back(Layer(_sizeX, _sizeY));
}

void Crystal::createLayer(int actives, int hydrogens) {
    createLayer();

    int currZ = _layers.size() - 1 + _completedLayers;
    auto layersIter = _layers.rbegin();
    for (int y = 0; y < _sizeY; y++) {
        for (int x = 0; x < _sizeX; x++) {
            layersIter->add(new Carbon(int3(x, y, currZ), actives, hydrogens), x, y);
        }
    }
}

void Crystal::throughAllCarbonsIter(std::function<void (Carbon *)> sf) {
    for (auto &layer : _layers) layer.throughAllCarbonsIter(sf);
}

bool Crystal::hasAbove(Carbon *first, Carbon *second) {
    int3 coords = topPosition(first, second);

    if ((size_t)coords.z <= _layers.size() - 1) return getLayer(coords.z)->carbon(coords.x, coords.y);
    else return false;
}

void Crystal::posMigrIter(Carbon *carbon, std::function<void (Carbon *, const int3 &,
                                                              Carbon *, Carbon *, Carbon *, Carbon *)> reaction) {
    const int3 &currentCoords = carbon->coords();
    int3 flatNeighboursCoords[4];
    for (int3 &neighbourCoords : flatNeighboursCoords) neighbourCoords = currentCoords;

    int less_x, more_x;
    torusCoordinate('x', currentCoords.x, less_x, more_x);

    int less_y, more_y;
    torusCoordinate('y', currentCoords.y, less_y, more_y);

    if (currentCoords.z % 2 == 0) {
        flatNeighboursCoords[0].y = less_y;
        flatNeighboursCoords[1].y = more_y;
        flatNeighboursCoords[2].x = less_x;
        flatNeighboursCoords[3].x = more_x;
    } else {
        flatNeighboursCoords[0].x = less_x;
        flatNeighboursCoords[1].x = more_x;
        flatNeighboursCoords[2].y = less_y;
        flatNeighboursCoords[3].y = more_y;
    }

    Carbon *currBasisCarbons[2];
    getBasisCarbons(carbon->coords(), currBasisCarbons);

    for (int3 &neighbourCoords : flatNeighboursCoords) {
        Carbon *toBasisCarbons[2];
        getBasisCarbons(neighbourCoords, toBasisCarbons);

        reaction(carbon, neighbourCoords, currBasisCarbons[0], currBasisCarbons[1], toBasisCarbons[0], toBasisCarbons[1]);
    }
}

void Crystal::posDimerIter(Carbon *carbon, std::function<void (Carbon *, Carbon *)> reaction) {

//    std::cout << "\n ------------ \ncall Crystal::posDimerIter\n";

  //  std::cout << "current carbon : {" << carbon->coords().x << carbon->coords().y << carbon->coords().z << "}";


    const int3 &currentCoords = carbon->coords();
    int3 directNeighboursCoords[2];
    for (int3 &neighbourCoords : directNeighboursCoords) neighbourCoords = currentCoords;

    if (currentCoords.z % 2 == 0) {
        int less_y, more_y;
        torusCoordinate('y', currentCoords.y, less_y, more_y);

        directNeighboursCoords[0].y = less_y;
        directNeighboursCoords[1].y = more_y;
    } else {
        int less_x, more_x;
        torusCoordinate('x', currentCoords.x, less_x, more_x);

        directNeighboursCoords[0].x = less_x;
        directNeighboursCoords[1].x = more_x;
    }

    for (int3 &neighbourCoords : directNeighboursCoords) {
       // std::cout << "\nneighb carbon : {" << neighbourCoords.x << neighbourCoords.y << neighbourCoords.z << "}";
        if (getLayer(neighbourCoords.z)->carbon(neighbourCoords.x, neighbourCoords.y) != 0)
            if (carbon->actives() < 4 && getLayer(neighbourCoords.z)->carbon(neighbourCoords.x, neighbourCoords.y)->actives() < 4)
                reaction(carbon, getLayer(neighbourCoords.z)->carbon(neighbourCoords.x, neighbourCoords.y));
    }

    // выполнить проверку на выход за границы!
//    int3 firstCarbonCoords = carbon->coords();

//    std::cout << "  fcc: {" << firstCarbonCoords.x << ", " << firstCarbonCoords.y << "}";

//    int dx = 0;
//    int dy = 0;

//    if ((firstCarbonCoords.z) % 2 == 0) dx = 1;
//    else dy = 1;

//    // проверка не выход за границу
//    if (firstCarbonCoords.x + dx == _x_size) firstCarbonCoords.x = 0;
//    if (firstCarbonCoords.y + dy == _y_size) firstCarbonCoords.y = 0;

//    std::cout << "  scc: {" << firstCarbonCoords.x + dx << ", " << firstCarbonCoords.y + dy << "}\n";
//    for (int i = 0; i < 2; ++i) {
//        reaction(carbon, getLayer(carbon->coords().z)->carbon(firstCarbonCoords.x + dx,
//                                                              firstCarbonCoords.y + dy));
//    }
}

void Crystal::getBasis(Carbon *carbon, std::function<void (Carbon *, Carbon *)> reaction) {
    if (carbon->coords().z == 0) return; // костыль для первого слоя

    Carbon *bottomCarbons[2];
    getBasisCarbons(carbon->coords(), bottomCarbons);
    reaction(bottomCarbons[0], bottomCarbons[1]);
}

void Crystal::addCarbon(Carbon *carbon) {
//    std::cout << "          ... _layers level = " << _layers.size() - 1 << ", z = " << carbon->coords().z << std::endl;
    if ((size_t)carbon->coords().z == _layers.size()) {
        createLayer();
   //     std::cout << "\nLAYER CREATED!!!! D:";
    }
    getLayer(carbon->coords().z)->add(carbon, carbon->coords().x, carbon->coords().y);


//    for (int f = 0; f < _layers.size(); f++)
//    {
//        std::cout << "\n ---- #" << f << " ----\n";
//        for (int i = 0; i < _y_size; i++)
//        {
//            for (int j = 0; j < _x_size; j++)
//                std::cout << _layers[f].carbon(j, i) << " ";
//            std::cout << std::endl;
//        }
//    }

}

void Crystal::removeCarbon(Carbon *carbon) {
    getLayer(carbon->coords().z)->remove(carbon->coords().x, carbon->coords().y);
}

void Crystal::move(Carbon *carbon, const int3 &to) {

    std::cout << "\nfrom : { " << carbon->coords().x << ", " << carbon->coords().y << ", " << carbon->coords().z << " }  to { "
              << to.x << ", " << to.y << ", " << to.z << " }\n";

    getLayer(carbon->coords().z)->move(carbon->coords().x, carbon->coords().y, to.x, to.y);
}

int3 Crystal::topPosition(Carbon *first, Carbon *second) {
    const int3 &coords1 = first->coords();
    const int3 &coords2 = second->coords();

    const int3 *sc1 = (coords1 < coords2) ? &coords1 : &coords2;
    const int3 *sc2 = (coords1 < coords2) ? &coords2 : &coords1;

    int3 topNeighbourCoords;
    topNeighbourCoords.z = sc1->z + 1;
    if (sc1->z % 2 == 1) topNeighbourCoords.y = sc1->y;
    else topNeighbourCoords.x = sc1->x;

    if (sc1->z % 4 == 3) {
        topNeighbourCoords.x = ((sc2->x - sc1->x) == 1) ? sc2->x : sc1->x;
    } else if (sc1->z % 4 == 2) {
        topNeighbourCoords.y = ((sc2->y - sc1->y) == 1) ? sc2->y : sc1->y;
    } else if (sc1->z % 4 == 1) {
        topNeighbourCoords.x = ((sc2->x - sc1->x) == 1) ? sc1->x : sc2->x;
    } else { // sc1->z % 4 == 0
        topNeighbourCoords.y = ((sc2->y - sc1->y) == 1) ? sc1->y : sc2->y;
    }

//    std::cout << "\n ...topPos() coords {" << topNeighbourCoords.x << ", " << topNeighbourCoords.y << ", " << topNeighbourCoords.z <<"}";
//    std::cout << "_layers.size() = " << _layers.size();
 //   if (getLayer(topNeighbourCoords.z)) std::cout << "sloi s nomerom " << topNeighbourCoords.z <<"EST"; else std::cout << "NET";
    return topNeighbourCoords;
}

// изменяет передаваемые bottomCarbons
void Crystal::getBasisCarbons(const int3 &currentCoords, Carbon *bottomCarbons[2]) {
    int3 bottomNeighboursCoords[2];
    for (int3 &bottomCoords : bottomNeighboursCoords) {
        bottomCoords = currentCoords;
        --bottomCoords.z;
    }

    int less_x, more_x;
    torusCoordinate('x', currentCoords.x, less_x, more_x);

    int less_y, more_y;
    torusCoordinate('y', currentCoords.y, less_y, more_y);

    if (currentCoords.z % 4 == 3) {
        bottomNeighboursCoords[0].y = less_y;
    } else if (currentCoords.z % 4 == 2) {
        bottomNeighboursCoords[1].x = more_x;
    } else if (currentCoords.z % 4 == 1) {
        bottomNeighboursCoords[1].y = more_y;
    } else { // current_coords.z % 4 == 0
        bottomNeighboursCoords[0].x = less_x;
    }

    for (int i = 0; i < 2; ++i) {
        bottomCarbons[i] = getLayer(bottomNeighboursCoords[i].z)->carbon(bottomNeighboursCoords[i].x, bottomNeighboursCoords[i].y);
    }
}

void Crystal::torusCoordinate(char coord, int current, int& less, int& more) const {
    int max;
    if (coord == 'x') max = _sizeX - 1;
    else max = _sizeY - 1;

    less = current - 1;
    if (less < 0) less = max;

    more = current + 1;
    if (more > max) more = 0;
}
