#ifndef CRYSTAL_H
#define CRYSTAL_H

#include <deque>
#include "layer.h"

class Crystal
{
public:
    Crystal(int sizeX, int sizeY);
    ~Crystal();

    void init();

    void throughAllCarbonsIter(std::function<void (Carbon *)> sf);

    void posDimerIter(Carbon *carbon, std::function<void (Carbon *, Carbon *)> reaction);
    void posMigrIter(Carbon *carbon, std::function<void (Carbon *, const int3 &, Carbon *, Carbon *, Carbon *, Carbon *)> reaction);
    void getBasis(Carbon *carbon, std::function<void (Carbon *, Carbon *, Carbon *)> reaction);
    int3 topPosition(Carbon *first, Carbon* second);

    void addCarbon(Carbon *carbon);
    void removeCarbon(Carbon *carbon);
    void move(Carbon *carbon, const int3 &to);

    bool hasAbove(Carbon *first, Carbon *second);
    void dropCompletedLayers(); // т.к. на Layer выделяем память через new необходимо не забыть отчистить эту память!

private:
    Crystal();

    Layer *getLayer(int z) { return _layers[z - _completedLayers]; }
    void createLayer();
    void createLayer(int actives, int hydrogens);

    void getBasisCarbons(const int3 &currentCoords, Carbon *bottomCarbons[]);
    void getAroundCarbons(int targetZMod, const int3 &currentCoords, Carbon *frontCarbons[]);
    void getFrontDirectionCarbons(const int3 &currentCoords, Carbon *frontCarbons[]);
    void torusCoordinate(char coord, int current, int &less, int &more) const;

    int _sizeX, _sizeY;
    std::deque<Layer *> _layers;
    int _completedLayers;
};

#endif // CRYSTAL_H
