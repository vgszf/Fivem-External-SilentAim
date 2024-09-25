#pragma once

#include <cmath>

class Vector2D
{
public:
    // Members
    float x, y;

    // Construction/destruction:
    Vector2D(void) { }
    Vector2D(float X, float Y) { x = X; y = Y; }
    Vector2D(float* clr) { x = clr[0]; y = clr[1]; }

    Vector2D(const Vector2D& vOther)
    {
        x = vOther.x; y = vOther.y;
    }

    // Initialization
    void Init(float ix = 0.0f, float iy = 0.0f) { x = ix; y = iy; }

    // Got any nasty NAN's?
    bool IsValid() const
    {
        return !isinf(x) && !isinf(y);
    }

    void Invalidate();

    // array access...
    float operator[](int i) const
    {
        return ((float*)this)[i];
    }

    float& operator[](int i)
    {
        return ((float*)this)[i];
    }

    // Base address...
    float* Base()
    {
        return (float*)this;
    }

    float const* Base() const
    {
        return (float const*)this;
    }

    // Initialization methods
    void Random(float minVal, float maxVal)
    {
        x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
        y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
    }
    void Zero(); ///< zero out a vector

    // equality
    bool operator==(const Vector2D& src) const
    {
        return (src.x == x) && (src.y == y);
    }

    bool operator!=(const Vector2D& src) const
    {
        return (src.x != x) || (src.y != y);
    }

    // arithmetic operations
    Vector2D& operator+=(const Vector2D& v)
    {
        x += v.x; y += v.y;
        return *this;
    }

    Vector2D& operator-=(const Vector2D& v)
    {
        x -= v.x; y -= v.y;
        return *this;
    }

    Vector2D& operator*=(float fl)
    {
        x *= fl;
        y *= fl;
        return *this;
    }

    Vector2D& operator*=(const Vector2D& v)
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    Vector2D& operator/=(const Vector2D& v)
    {
        x /= v.x;
        y /= v.y;
        return *this;
    }

    // this ought to be an opcode.
    Vector2D& operator+=(float fl)
    {
        x += fl;
        y += fl;
        return *this;
    }

    // this ought to be an opcode.
    Vector2D& operator/=(float fl)
    {
        x /= fl;
        y /= fl;
        return *this;
    }

    Vector2D& operator-=(float fl)
    {
        x -= fl;
        y -= fl;
        return *this;
    }

    // negate the vector components
    void Negate()
    {
        x = -x; y = -y;
    }

    // Get the vector's magnitude.
    float Length() const
    {
        return (float)sqrt(this->x * this->x + this->y * this->y);
    }

    // Get the vector's magnitude squared.
    float LengthSqr(void) const
    {
        return (x * x + y * y);
    }

    // return true if this vector is (0,0,0) within tolerance
    bool IsZero(float tolerance = 0.01f) const
    {
        return (x > -tolerance && x < tolerance &&
            y > -tolerance && y < tolerance);
    }

    float NormalizeInPlace()
    {
        float l = this->Length();
        if (l != 0.0f) {
            *this /= l;
        }
        else {
            this->x = this->y = 0.0f;
        }
        return l;
    }

    bool IsLengthGreaterThan(float val) const
    {
        return LengthSqr() > val * val;
    }

    bool IsLengthLessThan(float val) const
    {
        return LengthSqr() < val * val;
    }

    // Get the distance from this vector to the other one squared.
    // NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' .  
    // may be able to tidy this up after switching to VC7
    float DistToSqr(const Vector2D& vOther) const
    {
        Vector2D delta;

        delta.x = x - vOther.x;
        delta.y = y - vOther.y;

        return delta.LengthSqr();
    }

    // Copy
    void CopyToArray(float* rgfl) const;

    // Multiply, add, and assign to this (ie: *this = a + b * scalar). This
    // is about 12% faster than the actual vector equation (because it's done per-component
    // rather than per-vector).
    void MulAdd(const Vector2D& a, const Vector2D& b, float scalar)
    {
        x = a.x + b.x * scalar;
        y = a.y + b.y * scalar;
    }

    // Dot product.
    float Dot(const Vector2D& vOther) const
    {
        return(this->x * vOther.x + this->y * vOther.y);
    }

    // assignment
    Vector2D& operator=(const Vector2D& vOther)
    {
        x = vOther.x; y = vOther.y;
        return *this;
    }

    // arithmetic operations
    Vector2D operator-(void) const
    {
        return Vector2D(-x, -y);
    }

    Vector2D operator+(const Vector2D& v) const
    {
        Vector2D res;
        res.x = this->x + v.x;
        res.y = this->y + v.y;
        return res;
    }
    Vector2D operator-(const Vector2D& v) const
    {
        Vector2D res;
        res.x = this->x - v.x;
        res.y = this->y - v.y;
        return res;
    }
    Vector2D operator*(const Vector2D& v) const
    {
        Vector2D res;
        res.x = this->x * v.x;
        res.y = this->y * v.y;
        return res;
    }
    Vector2D operator/(const Vector2D& v) const
    {
        Vector2D res;
        res.x = this->x / v.x;
        res.y = this->y / v.y;
        return res;
    }
    Vector2D operator*(float fl) const
    {
        Vector2D res;
        res.x = this->x * fl;
        res.y = this->y * fl;
        return res;
    }
    Vector2D operator/(float fl) const
    {
        Vector2D res;
        res.x = this->x / (1.0f / fl);
        res.y = this->y / (1.0f / fl);
        return res;
    }

    // Returns a vector with the min or max in X, Y, and Z.
    Vector2D Min(const Vector2D& vOther) const
    {
        return Vector2D(x < vOther.x ? x : vOther.x, y < vOther.y ? y : vOther.y);
    }

    Vector2D Max(const Vector2D& vOther) const
    {
        return Vector2D(x > vOther.x ? x : vOther.x, y > vOther.y ? y : vOther.y);
    }
};