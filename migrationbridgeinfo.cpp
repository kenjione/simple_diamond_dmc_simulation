#include "migrationbridgeinfo.h"

MigrationBridgeInfo::MigrationBridgeInfo(const int3 &position, const std::pair<Carbon *, Carbon *> &toBasis) :
    _position(position), _toBasis(toBasis)
{
}

std::pair<Carbon *, Carbon *> MigrationBridgeInfo::toBasis() {
    return _toBasis;
}

int3 MigrationBridgeInfo::position() {
    return _position;
}
