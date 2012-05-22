#include "runner.h"
#include <iostream>
#include <cstring>


Runner::Runner(const Configurator &configurator)
    : _configurator(configurator), _handbook(configurator.configFileName()), _totalTime(0),
      _crystal(0), _surface(0), _reactor(0), _reactionsPool(0)
{
    int sizeX, sizeY;
    if (_configurator.sizeX() > 0 && _configurator.sizeY() > 0) {
        sizeX = _configurator.sizeX();
        sizeY = _configurator.sizeY();
    } else {
        sizeX = _handbook.sizeX();
        sizeY = _handbook.sizeY();
    }
    _crystal = new Crystal(sizeX, sizeY); // 25 15
    _surface = new Surface(_crystal);

    _reactor = new Reactor();
    _reactionsPool = new ReactionsPool(_surface, _crystal);
    Reaction::setReactor(_reactor); // t=1200K, [H]=10e-9, [CH2]=10e-10 mol/cm3

    //char outFileName[] = "/home/alex/Monte-Carlo/";

    _savers[0] = new ReactionPoolSaver(_configurator.outFileName("reactions").c_str(), _reactionsPool);
    _savers[1] = new SurfaceSaver(_configurator.outFileName("species").c_str(), _surface);
    _savers[2] = new CrystalSaver(_configurator.outFileName("crystal").c_str(), _crystal);
}

Runner::~Runner() {
    for (int i = 0; i < 3; i++) delete _savers[i];
    delete _reactionsPool;
    delete _reactor;
    delete _surface;
    delete _crystal;
}

void Runner::run() {
    for (size_t i = 0; i < _configurator.steps() + 1; i++) {
//        std::cout << "___________________________ " << i << " ___________________________\n\n";
        _totalTime += _surface->doReaction(_reactionsPool);
        if (i % _configurator.anyStep() == 0) {
            std::cout << ((double)i * 100 / _configurator.steps()) << "%" << std::endl;
            save();
        }
    }
}

void Runner::save() {
     for (int i = 0; i < 3; i++) _savers[i]->save(_totalTime);
}
