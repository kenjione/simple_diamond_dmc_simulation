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
    void operator() (Carbon *carbon);
    void separator();

    //
    void closer();

private:
    std::ofstream _outFile;
};

#endif // SAVER_H
