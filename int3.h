#ifndef INT3_H
#define INT3_H

struct int3 {
    int x, y, z;

    int3(int x, int y, int z) : x(x), y(y), z(z) {}

    bool operator< (const int3& oi) const {
        return (z < oi.z || y < oi.y || x < oi.x);
    }
};

#endif // INT3_H
