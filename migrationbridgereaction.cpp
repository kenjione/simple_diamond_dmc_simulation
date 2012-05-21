#include "migrationbridgereaction.h"
#include <cmath>
#include <cstdlib>

#include <iostream> //

MigrationBridgeReaction::MigrationBridgeReaction(Surface *surface, Crystal *crystal) :
    MonoReaction(surface), _crystal(crystal) {}

double MigrationBridgeReaction::coef() const {
    return 6.13 * 1e13 * exp(-18.269 / __reactor->temperature());
}

void MigrationBridgeReaction::seeAt(Carbon *carbon) {
    // на первых итерациях лезет искать bottomNeighbours у карбонов на первом слое (т.е пытается применить getLayer для z = -1)
    if ((carbon->actives() + carbon->hydrogens() <= 1) || carbon->isDimer()) return;
    _crystal->posMigrIter(carbon, std::ref(*this));
}

void MigrationBridgeReaction::operator() (Carbon *carbon, const int3 &to,
                                           Carbon *ffBasis, Carbon *fsBasis,
                                           Carbon *tfBasis, Carbon *tsBasis)
{
    // проверяем куда мигрируем
    if (!(tfBasis->isDimer() && tsBasis->isDimer()) && !(tfBasis->actives() > 0 && tsBasis->actives() > 0)) return;

    auto migrationInfoLambda = [&to, &tfBasis, &tsBasis]() {
        return MigrationBridgeInfo(to, std::pair<Carbon *, Carbon *>(tfBasis, tsBasis));
    };

    bool exist = false;

    // проверка на наличие мостовой группы в _sites
    for (size_t i = 0; i < _sites.size(); i++) {
        if (_sites[i] == carbon) {
            exist = true;
            _infos[i].push_back(migrationInfoLambda());
            break;
        }
    }

    if (!exist) {
        _sites.push_back(carbon);
        _currBasis.push_back(std::pair<Carbon *, Carbon *> (ffBasis, fsBasis));
        _infos.push_back(std::vector<MigrationBridgeInfo>());
        _infos[_infos.size() - 1].push_back(migrationInfoLambda());
    }
}

void MigrationBridgeReaction::doIt() {
    int siteRandomIndex = rand() % _sites.size();
    Carbon *carbon = _sites[siteRandomIndex];
    MigrationBridgeInfo &info = _infos[siteRandomIndex][rand() % _infos[siteRandomIndex].size()];
    _surface->moveCarbon(carbon, info.position(), _currBasis[siteRandomIndex], info.toBasis());
}

void MigrationBridgeReaction::reset() {
    MonoReaction::reset();
    _infos.clear();
    _currBasis.clear();
}

