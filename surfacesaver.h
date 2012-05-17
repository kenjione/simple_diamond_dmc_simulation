#ifndef SURFACESAVER_H
#define SURFACESAVER_H

#include "saver.h"
#include "surface.h"

class SurfaceSaver : public Saver
{
public:
    SurfaceSaver(const char *outFileName, Surface *surface);
    void save();

private:
    Surface *_surface;
};

#endif // SURFACESAVER_H
