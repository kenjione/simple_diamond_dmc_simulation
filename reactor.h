#ifndef REACTOR_H
#define REACTOR_H

#include "handbook.h"

class Reactor
{
public:
    Reactor() {
        const Handbook *hb = Handbook::instance();
        _temperature = hb->value("reactor", "T");
        _hydrogenConcentration = hb->value("reactor", "C(H)");
        _methylConcentration = hb->value("reactor", "C(CH3)");
    }

    float temperature() const { return _temperature; }
    float hydrogenConcentration() const { return _hydrogenConcentration; }
    float methylConcentration() const { return _methylConcentration; }

private:
    float _temperature;
    float _hydrogenConcentration;
    float _methylConcentration;
};

#endif // REACTOR_H
