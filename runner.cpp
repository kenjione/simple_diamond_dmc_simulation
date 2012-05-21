#include "runner.h"
#include <iostream>
#include <cstring>

Runner::Runner() {
    _crystal = new Crystal(8, 8); // 25 15
    _surface = new Surface(_crystal);
    _reactor = new Reactor(1200, 1e-9, 1e-10); // TODO: забрать из Handbook
    _reactionsPool = new ReactionsPool(_surface, _crystal);

    Reaction::setReactor(_reactor); // t=1200K, [H]=10e-9, [CH2]=10e-10 mol/cm3

    //char outFileName[] = "/home/alex/Monte-Carlo/";

    _savers[0] = new ReactionPoolSaver("../dmc-results/ReactionsSaver.txt", _reactionsPool);
    _savers[1] = new SurfaceSaver("../dmc-results/SurfaceSaver.txt", _surface);
    _savers[2] = new CrystalSaver("../dmc-results/CrystalSaver.txt", _crystal);
}

Runner::~Runner() {
    delete _crystal;
    delete _surface;
    delete _reactor;
    for (int i = 0; i < 3; i++) delete _savers[i];
}

void Runner::run() {
    for (int i = 0; i < 1000; i++)
    {
        std::cout << "___________________________ " << i << " ___________________________\n\n";
        _surface->doReaction(_reactionsPool);
        save();
    }
}

void Runner::save() {
     for (int i = 0; i < 3; i++) _savers[i]->save(_totalTime);
}
