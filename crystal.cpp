#include "crystal.h"
#include <iostream>

#include "migrationbridgereaction.h"
#include "migrationfrontdown.h"

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
    createTopLayer();
}

void Crystal::createLayer() {
    _layers.push_back(new Layer(_sizeX, _sizeY));
}

void Crystal::createLayerByCarbonLambda(std::function<Carbon * (const int3 &)> carbonLambda) {
    createLayer();

    int currZ = _layers.size() - 1 + _completedLayers;
    auto layersIter = _layers.rbegin();
    for (int y = 0; y < _sizeY; y++) {
        for (int x = 0; x < _sizeX; x++) {
            int3 coords(x, y, currZ);
            Carbon *carbon = carbonLambda(coords);
            (*layersIter)->add(carbon, x, y);
        }
    }
}

void Crystal::createLayer(int actives, int hydrogens) {
    createLayerByCarbonLambda([&actives, &hydrogens](const int3 &coords) {
        return new Carbon(coords, actives, hydrogens);
    });
}

void Crystal::createTopLayer() {
    createLayerByCarbonLambda([](const int3 &coords) {
        int actives, hydrogens;
        if (coords.x % 3 == 0) {
            actives = 0;
            hydrogens = 2;
        } else {
            actives = 1;
            hydrogens = 1;
        }
        return new Carbon(coords, actives, hydrogens);
    });
}


void Crystal::throughAllCarbonsIter(std::function<void (Carbon *)> sf) {
    for (auto layer : _layers) layer->throughAllCarbonsIter(sf);
}

bool Crystal::hasAbove(Carbon *first, Carbon *second) {
    int3 coords = topPosition(first, second);

    if ((size_t)coords.z - _completedLayers <= _layers.size() - 1) return getLayer(coords.z)->carbon(coords.x, coords.y);
    else return false;
}

void Crystal::posMigrIter(Carbon *carbon, MigrationBridgeReaction &reaction)
{
    int3 flatNeighboursCoords[4];
    getFlatNeighbourCoords(carbon->coords(), flatNeighboursCoords);

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

void Crystal::posMigrDownFrontIter(Carbon *carbon, MigrationFrontDown &reaction)
{
    Carbon *currBasisCarbons[2];
    getBasisCarbons(carbon->coords(), currBasisCarbons);

    for (int i = 0; i < 2; ++i) {
//        if (!currBasisCarbons[i]) return;

//        if (currBasisCarbons[i]->actives() == 0) continue;

        int3 frontNeighbourCoords[2];
        getFrontDirectionCoords(currBasisCarbons[i]->coords(), frontNeighbourCoords);

        int anotherBaseIndex = 1 - i;
        int3 &toCoord = (currBasisCarbons[anotherBaseIndex]->coords() == frontNeighbourCoords[0]) ?
                    frontNeighbourCoords[1] : frontNeighbourCoords[0];
        if (getLayer(toCoord.z)->carbon(toCoord.x, toCoord.y)) continue;

        Carbon *toLowBasisCarbons[2];
        getBasisCarbons(toCoord, toLowBasisCarbons);
        if (!toLowBasisCarbons[0] || !toLowBasisCarbons[1]) continue;

        reaction(carbon, toCoord,
                 currBasisCarbons[0], currBasisCarbons[1],
                 toLowBasisCarbons[0], toLowBasisCarbons[1]);
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
    const int3 &from = carbon->coords();
    if (to.z == from.z) {
        getLayer(from.z)->move(from.x, from.y, to.x, to.y);
    } else {
        assert(carbon); // проверяем откуда мигрируем (на этапе разработки)
        assert(!getLayer(to.z)->carbon(to.x, to.y)); // проверяем куда мигрируем (на этапе разработки)

        getLayer(from.z)->add(0, from.x, from.y);
        carbon->move(to);
        getLayer(to.z)->add(carbon, to.x, to.y);
    }
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

void Crystal::getAroundCarbons(int targetZMod, const int3 &currentCoords, Carbon *frontCarbons[2]) {
    int3 directNeighboursCoords[2];
    getAroundCoords(targetZMod, currentCoords, directNeighboursCoords);

    for (int i = 0; i < 2; i++) {
        const int3 &neighbourCoords = directNeighboursCoords[i];
        frontCarbons[i] = getLayer(neighbourCoords.z)->carbon(neighbourCoords.x, neighbourCoords.y);
    }
}

void Crystal::getFrontDirectionCarbons(const int3 &currentCoords, Carbon *frontCarbons[2]) {
    getAroundCarbons(0, currentCoords, frontCarbons);
}

void Crystal::getAroundCoords(int targetZMod, const int3 &currentCoords, int3 aroundCoords[2]) {
    for (int i = 0; i < 2; ++i) aroundCoords[i] = currentCoords;

    if (currentCoords.z % 2 == targetZMod) {
        int less_y, more_y;
        torusCoordinate('y', currentCoords.y, less_y, more_y);

        aroundCoords[0].y = less_y;
        aroundCoords[1].y = more_y;
    } else {
        int less_x, more_x;
        torusCoordinate('x', currentCoords.x, less_x, more_x);

        aroundCoords[0].x = less_x;
        aroundCoords[1].x = more_x;
    }
}

void Crystal::getFrontDirectionCoords(const int3 &currentCoords, int3 frontCoords[2]) {
    getAroundCoords(0, currentCoords, frontCoords);
}

void Crystal::getCrossDirectionCoords(const int3 &currentCoords, int3 crossCoords[2]) {
    getAroundCoords(1, currentCoords, crossCoords);
}

void Crystal::getFlatNeighbourCoords(const int3 &currentCoords, int3 neighbourCoords[4]) {
    getFrontDirectionCoords(currentCoords, neighbourCoords);
    getCrossDirectionCoords(currentCoords, neighbourCoords + 2);
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
