#include "etchingreaction.h"
#include <cmath>
#include <cstdlib>

#define ETCHING_PARAGRAPH_NAME "Etching reaction"

EtchingReaction::EtchingReaction(Surface *surface, Crystal *crystal) :
    MonoReaction(surface, ETCHING_PARAGRAPH_NAME), _crystal(crystal)
{
    _coef = Handbook::instance()->value(ETCHING_PARAGRAPH_NAME, "coef");
}

double EtchingReaction::coef() const {
    // TODO: надо прочекать всю формулу и чётко проверить размерности. проверить __reactor->temperature() на равенство нулю %)

//    double first = 35.345 - 7.2873 * 1e8 * __reactor->hydrogenConcentration() +
//            3.4063 * 1e16 * __reactor->hydrogenConcentration() * __reactor->hydrogenConcentration();

//    double second = (38.931 - 1.2038 * 1e9 * __reactor->hydrogenConcentration() + 5.9123 * 1e16 *
//                     __reactor->hydrogenConcentration() * __reactor->hydrogenConcentration()) / __reactor->temperature();

//    double degree = first - second;

    //return pow(2.72, degree);

    return _coef;
}

void EtchingReaction::seeAt(Carbon *carbon) {
    if (carbon->actives() > 0 || carbon->coords().z == 0 || carbon->isDimer()) return;

    _crystal->getBasis(carbon, std::ref(*this));
}

void EtchingReaction::doIt() {
    int siteRandomIndex = rand() % _sites.size();
    _surface->removeCarbon(_sites[siteRandomIndex],
                           _basis[siteRandomIndex].first,
                           _basis[siteRandomIndex].second);
}

void EtchingReaction::reset() {
    MonoReaction::reset();
    _basis.clear();
}

void EtchingReaction::operator() (Carbon *carbon, Carbon *first, Carbon *second) {
    _sites.push_back(carbon);
    _basis.push_back(std::pair<Carbon *, Carbon *> (first, second));
}
