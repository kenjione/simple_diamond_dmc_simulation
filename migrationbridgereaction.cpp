#include "migrationbridgereaction.h"
#include <cmath>
#include <cstdlib>

#include <iostream>

MigrationBridgeReaction::MigrationBridgeReaction(Surface *surface, Crystal *crystal, const char *paragraphName) :
    MonoReaction(surface, paragraphName), _crystal(crystal)
{}

double MigrationBridgeReaction::coef() const {
    return _k * exp (-_E / (R * __reactor->temperature()));
}

bool MigrationBridgeReaction::checkConditions(Carbon *carbon) const {
    return ((carbon->actives() + carbon->hydrogens() <= 1) || carbon->coords().z == 0 || carbon->isDimer());
}

void MigrationBridgeReaction::seeAt(Carbon *carbon) {
    // на первых итерациях лезет искать bottomNeighbours у карбонов на первом слое (т.е пытается применить getLayer для z = -1)
    if (checkConditions(carbon)) return;
    _crystal->posMigrIter(carbon, std::ref(*this));
}

void MigrationBridgeReaction::operator() (Carbon *carbon, const int3 &to,
                                           Carbon *ffBasis, Carbon *fsBasis,
                                           Carbon *tfBasis, Carbon *tsBasis)
{
    // проверяем куда мигрируем
    if (!(_surface->isDimer(tfBasis, tsBasis) || (!tfBasis) || (!tsBasis) || (tfBasis->actives() > 0 && tsBasis->actives() > 0))) return;

    auto migrationInfoLambda = [this, &to, &tfBasis, &tsBasis]() {
        _infos[_infos.size() - 1].push_back(MigrationBridgeInfo(to, std::pair<Carbon *, Carbon *>(tfBasis, tsBasis)));
    };

    // проверка на наличие мостовой группы в _sites
    if (_sites.size() > 0 && _sites[_sites.size() - 1] == carbon) {
        migrationInfoLambda();
    } else {
        _sites.push_back(carbon);
        _currBasis.push_back(std::pair<Carbon *, Carbon *> (ffBasis, fsBasis));
        _infos.push_back(std::vector<MigrationBridgeInfo>());
        migrationInfoLambda();
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
    _currBasis.clear();
    _infos.clear();
}

