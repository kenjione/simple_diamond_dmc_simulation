#include "surfacesaver.h"

SurfaceSaver::SurfaceSaver(char *outFileName, Surface *surface) :
    Saver(outFileName), _surface(surface) {}

void SurfaceSaver::save() {}

// сохранение множеств
