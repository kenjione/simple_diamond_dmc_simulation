#include "crystal.h"
#include <iostream>

Crystal::Crystal(int sizeX, int sizeY) : _sizeX(sizeX), _sizeY(sizeY), _completedLayers(0) {
//    std::cout << "CRYSTAL SIZE: " << _sizeX << "x" << _sizeY << std::endl;
    init();
}

Crystal::~Crystal() {
    for (Layer *layer : _layers) delete layer;
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
    _layers.push_back(new Layer(_sizeX, _sizeY));
}

void Crystal::createLayer(int actives, int hydrogens) {
    createLayer();

    int currZ = _layers.size() - 1 + _completedLayers;
    auto layersIter = _layers.rbegin();
    for (int y = 0; y < _sizeY; y++) {
        for (int x = 0; x < _sizeX; x++) {
            int3 coords(x, y, currZ);
            Carbon *carbon = new Carbon(coords, actives, hydrogens);
            (*layersIter)->add(carbon, x, y);
        }
    }
}

void Crystal::throughAllCarbonsIter(std::function<void (Carbon *)> sf) {
    for (auto layer : _layers) layer->throughAllCarbonsIter(sf);
}

bool Crystal::hasAbove(Carbon *first, Carbon *second) {
    int3 coords = topPosition(first, second);

    if ((size_t)coords.z - _completedLayers <= _layers.size() - 1) return getLayer(coords.z)->carbon(coords.x, coords.y);
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
        if (getLayer(neighbourCoords.z)->carbon(neighbourCoords.x, neighbourCoords.y)) continue;

        Carbon *toBasisCarbons[2];
        getBasisCarbons(neighbourCoords, toBasisCarbons);
        if (!toBasisCarbons[0] || !toBasisCarbons[1]) continue;

        reaction(carbon, neighbourCoords, currBasisCarbons[0], currBasisCarbons[1], toBasisCarbons[0], toBasisCarbons[1]);
    }
}

void Crystal::posDimerIter(Carbon *carbon, std::function<void (Carbon *, Carbon *)> reaction) {
    Carbon *frontCarbons[2];
    getFrontDirectionCarbons(carbon->coords(), frontCarbons);

    for (Carbon *neighbourCarbon : frontCarbons) {
        if (!neighbourCarbon) continue;
        reaction(carbon, neighbourCarbon);
    }
}

void Crystal::getBasis(Carbon *carbon, std::function<void (Carbon *, Carbon *, Carbon *)> reaction) {
    // пропускаем, если вокруг рассматриваемого карбона имеются другие карбоны
    for (int tz = 0; tz < 2; tz++) {
        Carbon *aroundCarbons[2];
        getAroundCarbons(tz, carbon->coords(), aroundCarbons);
        for (Carbon *neighbourCarbon : aroundCarbons) {
            if (neighbourCarbon) return;
        }
    }

    Carbon *bottomCarbons[2];
    getBasisCarbons(carbon->coords(), bottomCarbons);
    reaction(carbon, bottomCarbons[0], bottomCarbons[1]);
}

void Crystal::addCarbon(Carbon *carbon) {
    if ((size_t)carbon->coords().z - _completedLayers == _layers.size()) {
        createLayer();
    }
    getLayer(carbon->coords().z)->add(carbon, carbon->coords().x, carbon->coords().y);
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

void Crystal::getAroundCarbons(int targetZMod, const int3 &currentCoords, Carbon *frontCarbons[]) {
    int3 directNeighboursCoords[2];
    for (int3 &neighbourCoords : directNeighboursCoords) neighbourCoords = currentCoords;

    if (currentCoords.z % 2 == targetZMod) {
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

    for (int i = 0; i < 2; i++) {
        const int3 &neighbourCoords = directNeighboursCoords[i];
        frontCarbons[i] = getLayer(neighbourCoords.z)->carbon(neighbourCoords.x, neighbourCoords.y);
    }
}

void Crystal::getFrontDirectionCarbons(const int3 &currentCoords, Carbon *frontCarbons[2]) {
    getAroundCarbons(0, currentCoords, frontCarbons);
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
