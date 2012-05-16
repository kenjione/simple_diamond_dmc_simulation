#ifndef CRYSTALSAVER_H
#define CRYSTALSAVER_H

#include "saver.h"
#include "crystal.h"

class CrystalSaver : public Saver
{
public:
    CrystalSaver(char *outFileName, Crystal *crystal);
    void operator ()(Carbon *carbon);
    void save();

private:
    Crystal *_crystal;
    void separator();
};

#endif // CRYSTALSAVER_H
