#ifndef SAVER_H
#define SAVER_H

#include <fstream>
#include "carbon.h"

class Saver
{
public:
    Saver(const char *outFileName);
    virtual ~Saver();

    virtual void save(float time) = 0;

protected:
    std::ofstream _outFile;
};

#endif // SAVER_H
