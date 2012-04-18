#ifndef REACTOR_H
#define REACTOR_H

class Reactor
{
private:
    float _temperature;
    float _hydrogenConcentration;
    float _methylConcentration;
public:
    Reactor(float t, float hydroC, float methylC) :_temperature(t),
                                                   _hydrogenConcentration(hydroC),
                                                   _methylConcentration(methylC) {}

    float temperature() {
        return _temperature;
    }

    float hydrogenConcentration() {
        return _hydrogenConcentration;
    }

    float methylConcentration() {
        return _methylConcentration;
    }

};

#endif // REACTOR_H
