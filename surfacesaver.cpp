#include "surfacesaver.h"

SurfaceSaver::SurfaceSaver(const char *outFileName, Surface *surface) : Saver(outFileName), _surface(surface) {}

void SurfaceSaver::save() {}

// сохранение множеств
