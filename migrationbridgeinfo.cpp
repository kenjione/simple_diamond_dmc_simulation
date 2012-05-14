#include "migrationbridgeinfo.h"

MigrationBridgeInfo::MigrationBridgeInfo(int3 position, std::pair<Carbon *, Carbon *> toBasis) :
    _position(position), _toBasis(toBasis)
{
}

std::pair MigrationBridgeInfo::toBasis() {
    return _toBasis;
}

int3 MigrationBridgeInfo::position() {
    return _position;
}
