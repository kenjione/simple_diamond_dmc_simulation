#include "runner.h"
#include <iostream>

Runner::Runner() {
    _crystal = new Crystal(8, 8); // 25 15
    _surface = new Surface(_crystal);
    _reactor = new Reactor(1200, 1e-9, 1e-10); // TODO: забрать из Handbook
    Reaction::setReactor(_reactor); // t=1200K, [H]=10e-9, [CH2]=10e-10 mol/cm3
    _saver = new Saver("/home/alex/Monte-Carlo/ohmygodkillme.txt");
}

Runner::~Runner() {
    delete _crystal;
    delete _surface;
    delete _reactor;
    delete _saver;
}

void Runner::run() {
    for (int i = 0; i < 10000; i++)
    {
        std::cout << "___________________________ " << i << " ___________________________\n\n";
        _surface->doReaction();
        save();
    }

    // ...
    _saver->closer();

}

void Runner::save() {
    _crystal->throughAllCarbonsIter(std::ref(*_saver));
    _saver->separator();
}

