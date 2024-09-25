#pragma once

#include <cmath>

class Vector3D
{
public:
    // Members
    float x, y, z;

    Vector3D(void) { }
    Vector3D(float X, float Y, float Z) { x = X; y = Y; z = Z; }

    Vector3D operator + (const Vector3D& rhs) const { return Vector3D(x + rhs.x, y + rhs.y, z + rhs.z); }
    Vector3D operator * (const Vector3D& rhs) const { return Vector3D(x * rhs.x, y * rhs.y, z * rhs.z); }
    Vector3D operator * (float fl) const { return Vector3D(x * fl, y * fl, z * fl); }

    float DistTo(const Vector3D& vOther) const
    {
        Vector3D delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;
        delta.z = z - vOther.z;

        return delta.Length();
    }

    float Length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    float LengthSqr(void) const
    {
        return (x * x + y * y + z * z);
    }

    float Length2D() const
    {
        return sqrt(x * x + y * y);
    }

    Vector3D Cross(const Vector3D& v) const
    {
        return Vector3D(
            this->y * v.z - this->z * v.y,
            this->z * v.x - this->x * v.z,
            this->x * v.y - this->y * v.x
        );
    }
};