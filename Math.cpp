#pragma once
#include <cmath>

namespace math
{
    auto distanceToMeters =[](float distance) -> double
    {
        const float INCHES_IN_METER = 39.3701f;
        return distance / INCHES_IN_METER;
    };

        auto calculateDistance = [](float x1, float y1, float z1, float x2, float y2, float z2) -> double
    {
        float dx = (x1 - x2);
        float dy = (y1 - y2);
        float dz = (z1 - z2);
        return sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
    };

    auto calculateDistanceInMeters = [](float x1, float y1, float z1, float x2, float y2, float z2) -> double
    {
        return distanceToMeters(calculateDistance(x1, y1, z1, x2, y2, z2));
    };

        auto calculateDistance2D = [](float x1, float y1, float x2, float y2) -> double
    {
        float dx = (x1 - x2);
        float dy = (y1 - y2);
        return sqrt(pow(dx, 2) + pow(dy, 2));
    };
}

