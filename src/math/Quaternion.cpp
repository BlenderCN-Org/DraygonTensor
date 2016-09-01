#include <cmath>
#include <cassert>

#include "Quaternion.h"

namespace ds_math
{
Quaternion::Quaternion(scalar x, scalar y, scalar z, scalar w)
    : x(x), y(y), z(z), w(w)
{
}

Quaternion::Quaternion(Vector3 vectorPart, scalar scalarPart)
    : x(vectorPart.x), y(vectorPart.y), z(vectorPart.z), w(scalarPart)
{
}

Quaternion::Quaternion(const Quaternion &other)
    : x(other.x), y(other.y), z(other.z), w(other.w)
{
}

const Quaternion &Quaternion::operator=(const Quaternion &other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;

    return (*this);
}

const Quaternion &Quaternion::operator*=(scalar factor)
{
    x *= factor;
    y *= factor;
    z *= factor;
    w *= factor;

    return (*this);
}

scalar &Quaternion::operator[](unsigned int index)
{
    assert(index < 4 && "Attempt to access index outside Quaternion bounds.");

    switch (index)
    {
    case 0:
        return x;
        break;
    case 1:
        return y;
        break;
    case 2:
        return z;
        break;
    case 3:
        return w;
        break;
    default:
        return x;
        break;
    }
}

const scalar &Quaternion::operator[](unsigned int index) const
{
    assert(index < 4 && "Attempt to access index outside Quaternion bounds.");

    switch (index)
    {
    case 0:
        return x;
        break;
    case 1:
        return y;
        break;
    case 2:
        return z;
        break;
    case 3:
        return w;
        break;
    default:
        return x;
        break;
    }
}

bool Quaternion::operator==(const Quaternion &other) const
{
    return (fabs(x - other.x) < FLOAT_ACCURACY &&
            fabs(y - other.y) < FLOAT_ACCURACY &&
            fabs(z - other.z) < FLOAT_ACCURACY &&
            fabs(w - other.w) < FLOAT_ACCURACY);
}

bool Quaternion::operator!=(const Quaternion &other) const
{
    return (!(*this == other));
}

scalar Quaternion::Magnitude() const
{
    return (Quaternion::Magnitude(*this));
}

void Quaternion::Normalize()
{
    *this = Quaternion::Normalize(*this);
}

void Quaternion::Invert()
{
    *this = Quaternion::Invert(*this);
}

void Quaternion::AddScaledVector(const Vector3 &vec, scalar scale)
{
    Quaternion q(vec.x * scale, vec.y * scale, vec.z * scale, (scalar)0.0);

    q = q * (*this);

    this->x += q.x * ((scalar)0.5);
    this->y += q.y * ((scalar)0.5);
    this->z += q.z * ((scalar)0.5);
    this->w += q.w * ((scalar)0.5);
}

scalar Quaternion::Magnitude(const Quaternion &q)
{
    return sqrt(Quaternion::Dot(q, q));
}

Quaternion Quaternion::Normalize(const Quaternion &q)
{
    scalar mag = Quaternion::Magnitude(q);

    assert(mag != 0 && "Attempted to normalize a vector with zero magnitude.");

    return (q * (((scalar)1.0f) / mag));
}

scalar Quaternion::Dot(const Quaternion &q1, const Quaternion &q2)
{
    return ((q1.x * q2.x) + (q1.y * q2.y) + (q1.z * q2.z) + (q1.w * q2.w));
}

Quaternion Quaternion::Invert(const Quaternion &q)
{
    // From
    // https://bitbucket.org/sinbad/ogre/src/3cbd67467fab/OgreMain/src/OgreQuaternion.cpp?at=default&fileviewer=file-view-default
    scalar norm = q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w;
    if (norm > 0.0)
    {
        scalar invNorm = 1.0f / norm;
        return Quaternion(-q.x * invNorm, -q.y * invNorm, -q.z * invNorm,
                          q.w * invNorm);
    }
    else
    {
        return Quaternion();
    }
}

Quaternion Quaternion::CreateFromAxisAngle(const Vector3 &axis, scalar angleRad)
{
    Vector3 axisNormalized = Vector3::Normalize(axis);

    axisNormalized *= sinf(angleRad / 2.0f);
    float scal = cosf(angleRad / 2.0f);

    Quaternion q = Quaternion(axisNormalized, scal);

    return (Quaternion::Normalize(q));
}

Quaternion operator*(const Quaternion &q1, const Quaternion &q2)
{
    return (Quaternion(q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
                       q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
                       q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x,
                       q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z));
}

Quaternion operator*(const Quaternion &q, scalar factor)
{
    Quaternion scaled = q;

    scaled *= factor;

    return scaled;
}

Quaternion operator*(scalar factor, const Quaternion &q)
{
    Quaternion scaled = q;

    scaled *= factor;

    return scaled;
}

Quaternion operator-(const Quaternion &q)
{
    return (Quaternion::Invert(q));
}

std::ostream &operator<<(std::ostream &out, const Quaternion &q)
{
    out << "{" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << "}";

    return out;
}
}
