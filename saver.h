#ifndef SAVER_H
#define SAVER_H

//#include <iostream>
#include <fstream>
//#include <ostream>
#include "carbon.h"

class Saver
{
public:
    Saver(char *outFileName);
    virtual void save() = 0;
    //
    void closer();

protected:
    std::ofstream _outFile;
};

#endif // SAVER_H
