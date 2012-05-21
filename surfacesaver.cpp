#include "surfacesaver.h"

SurfaceSaver::SurfaceSaver(const char *outFileName, Surface *surface)
    : TimeNumberCurvesSaver(outFileName), _surface(surface)
{
    saveHeader(_surface->setsNames());
}

void SurfaceSaver::save(double time) {
    saveValuesLine(time, _surface->setsNumbers());
}
