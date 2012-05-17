#include "etchingreaction.h"
#include <cmath>
#include <cstdlib>

#include <iostream> //

EtchingReaction::EtchingReaction(Surface *surface, Crystal *crystal) :
    MonoReaction(surface), _crystal(crystal) {}

double EtchingReaction::coef() const {
    // TODO: надо прочекать всю формулу и чётко проверить размерности. проверить __reactor->temperature() на равенство нулю %)

    /*
    return pow(2, ((35.345 * 7.2873 * 10e8 * __reactor->hydrogenConcentration() + 3.4063 *
                 10e16 * pow(__reactor->hydrogenConcentration(), 2)) -
                (38.931  - 1.2038 * 10e9 * __reactor->hydrogenConcentration() +
                 5.9123 * 10e16 * pow(__reactor->hydrogenConcentration(), 2)) / __reactor->temperature()));
    */ // не считает скорость. Вернее считает но результат получается inf
                 //10
    return 2.6 * 1e3; // поставил вручную просто для проверки
}

void EtchingReaction::seeAt(Carbon *carbon) {
    if ((carbon->actives() > 0) || carbon->isDimer()) return;

    _sites.push_back(carbon);
    _crystal->getBasis(carbon, std::ref(*this));
}

void EtchingReaction::doIt() {
    int siteRandomIndex = rand() % _sites.size();
    _surface->removeCarbon(_sites[siteRandomIndex],
                           _basis[siteRandomIndex].first,
                           _basis[siteRandomIndex].second);
}

void EtchingReaction::operator() (Carbon *first, Carbon *second) {
    _basis.push_back(std::pair<Carbon *, Carbon *> (first, second));
}
