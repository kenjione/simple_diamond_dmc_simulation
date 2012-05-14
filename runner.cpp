#include "runner.h"
#include <iostream>

Runner::Runner() {
    _crystal = new Crystal(8, 8); // 25 15
    _surface = new Surface(_crystal);
    _reactor = new Reactor(1200, 0.5, 0.05); //
    _saver = new Saver("/home/alex/Monte-Carlo/ohmygodkillme.txt");
}

Runner::~Runner() {
    delete _crystal;
    delete _surface;
    delete _reactor;
    delete _saver;
}

void Runner::run() {
    std::cout << "call Runner::run()\n";
    _surface->doReaction();
    save();
}

void Runner::save() {
    std::cout << "call Runner::save()\n";
    _crystal->throughAllCarbonsIter(std::ref(*_saver));
    _saver->closer();
}

