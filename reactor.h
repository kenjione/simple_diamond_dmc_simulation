#ifndef REACTOR_H
#define REACTOR_H

class Reactor
{
public:
    Reactor(float temperature, float hydroConcentration, float methylConcentration)
        : _temperature(temperature), _hydrogenConcentration(hydroConcentration), _methylConcentration(methylConcentration) {}

    float temperature() const { return _temperature; }
    float hydrogenConcentration() const { return _hydrogenConcentration; }
    float methylConcentration() const { return _methylConcentration; }

private:
    float _temperature;
    float _hydrogenConcentration;
    float _methylConcentration;
};

#endif // REACTOR_H
