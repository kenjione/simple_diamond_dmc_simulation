#include "addch2reaction.h"
#include <cmath>
#include <cstdlib>

#include <iostream> //

AddCH2Reaction::AddCH2Reaction(Surface *surface, Crystal *crystal) :
    DualReaction(surface), _crystal(crystal) {}

double AddCH2Reaction::coef() const {
    return 1 * 10e13 * __reactor->methylConcentration();
}

void AddCH2Reaction::seeAt(Carbon *first, Carbon *second) {

    std::cout << "call AddCH2Reaction::seeAt(f,s) \n";
    if (first && second) std::cout << "exist both\n";

    auto pushPair = [this](Carbon *first, Carbon *second) {
        _sites.push_back(std::pair<Carbon *, Carbon *> (first, second));
        _positions.push_back(_crystal->topPosition(first, second));

        std::cout << "check topPos:\n" << "   first coords { " << first->coords().x << ", " << first->coords().y << ", " << first->coords().z << "\n"
                  << second->coords().x << ", " << second->coords().y << ", " << second->coords().z << "\n";
        std::cout << "topPos = { " << _crystal->topPosition(first, second).x << ", "<< _crystal->topPosition(first, second).y << ", " << _crystal->topPosition(first, second).z << "\n\n";
        };

    if (first->actives() > 0) pushPair(first, second);
    else std::cout << "can't push coz hasn't actives\n";
    if (second->actives() > 0) pushPair(second, first);
    else std::cout << "can't push coz hasn't actives\n";
}

void AddCH2Reaction::doIt() {

    if  (_sites.size() == 0 ) {
        std::cout << "call AddCH2Reaction()::doIt is not availible. _sites is empty.\n";
        return;
    }
    int siteRandomIndex = rand() % _sites.size();
    _surface->addCarbon(new Carbon(_positions[siteRandomIndex], 0, 2),
                        _sites[siteRandomIndex].first,
                        _sites[siteRandomIndex].second);
}

void AddCH2Reaction::reset() {
    DualReaction::reset();
    _positions.clear();
}
