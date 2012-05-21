#ifndef CRYSTALSAVER_H
#define CRYSTALSAVER_H

#include "saver.h"
#include "crystal.h"

class CrystalSaver : public Saver
{
public:
    CrystalSaver(const char *outFileName, Crystal *crystal);
    void save(double time);
    void operator() (Carbon *carbon);

private:
    Crystal *_crystal;
    void separator();
};

#endif // CRYSTALSAVER_H
