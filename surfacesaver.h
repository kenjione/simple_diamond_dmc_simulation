#ifndef SURFACESAVER_H
#define SURFACESAVER_H

#include "timenumbercurvessaver.h"
#include "surface.h"

class SurfaceSaver : public TimeNumberCurvesSaver
{
public:
    SurfaceSaver(const char *outFileName, Surface *surface);
    void save(float time);

private:
    Surface *_surface;
};

#endif // SURFACESAVER_H
