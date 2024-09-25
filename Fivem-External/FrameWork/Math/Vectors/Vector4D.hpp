#pragma once

#include <cmath>

class Vector4D
{
public:
    // Members
    float x, y, z, w;

    Vector4D(void) { }
    Vector4D(float X, float Y, float Z, float W) { x = X; y = Y; z = Z; w = W; }

    Vector4D operator + (const Vector4D& rhs) const { return Vector4D(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w); }
};