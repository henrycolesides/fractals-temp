// VectorMath.cpp
// Provides definitions for classes and functions for mathematical calculations
// See VectorMath.h for definitions

#include <cmath>
#include <math.h>
#include <iostream>
#include "VectorMath.h"

const float  PI = 3.14159265358979f;

Vec3::Vec3() : values{ 0 } { return; }

Vec3::Vec3(const float x, const float y, const float z)
{
    values[0] = x;
    values[1] = y;
    values[2] = z;
}

void Vec3::set(const char dimension, const float value)
{
    switch (dimension)
    {
    case X:
        values[0] = value;
        break;
    case Y:
        values[1] = value;
        break;
    case Z:
        values[2] = value;
        break;
    default:
        throw(false);
        break;
    }
    return;
}
float Vec3::get(const char dimension) const
{
    switch (dimension)
    {
    case X:
        return values[0];
        break;
    case Y:
        return values[1];
        break;
    case Z:
        return values[2];
        break;
    default:
        throw(false);
        break;
    }
}

float Vec3::get(const int dimension) const
{
    if(dimension < 0 || dimension > 2) return 0.0;
    return values[dimension];
}

float Vec3::length() const
{
    return std::sqrt((values[0] * values[0]) + (values[1] * values[1]) + (values[2] * values[2]));
}

void Vec3::normalize()
{
    float m = length();
    values[0] = values[0] / m;
    values[1] = values[1] / m;
    values[2] = values[2] / m;
}

void Vec3::rotate_about_y(const float radians)
{
//    std::cout << "angle: " << angle << '\n';
    float temp_x = values[0];
    float temp_z = values[2];
    float angle = radians * PI / 180.0;
   /// values[0] = (temp_x * std::cosf(angle)) + (temp_z * std::sinf(angle));
   /// values[2] = (temp_x * std::sinf(angle)) + (temp_z * std::cosf(angle));
    values[0] = (temp_x * cosf(angle)) + (temp_z * sinf(angle));
    values[2] = (-temp_x * sinf(angle)) + (temp_z * cosf(angle));
}

void Vec3::rotate_about_z(const float degrees)
{
    float temp_x = values[0];
    float temp_y = values[1];
    float angle = degrees * PI / 180.0;
    
    values[0] = (temp_x * cosf(angle)) + (-temp_y * sinf(angle));
    values[1] = (temp_x * sinf(angle)) + (temp_y * cosf(angle));
}

void Vec3::rotate_about_x(const float radians)
{
    float temp_y = values[1];
    float temp_z = values[2];
    float angle = radians * PI / 180.0;
    
    values[1] = (temp_y * cosf(angle)) + (-temp_z * sinf(angle));
    values[2] = (temp_y * sinf(angle)) + (temp_z * cosf(angle));
}

Vec3 Vec3::operator-() const
{
    return Vec3(-values[0], -values[1], -values[2]);
}

float Vec3::operator*(const Vec3& op2) const
{
    return (values[0] * op2.values[0])
        + (values[1] * op2.values[1])
        + (values[2] * op2.values[2]);
}

Vec3& Vec3::operator*=(const float op2)
{
    values[0] *= op2;
    values[1] *= op2;
    values[2] *= op2;
    return *this;
}

Vec3& Vec3::operator/=(const float op2)
{
    values[0] /= op2;
    values[1] /= op2;
    values[2] /= op2;
    return *this;
}

Vec3 Vec3::operator+(const Vec3& op2) const
{
    Vec3 temp = Vec3();
    temp.values[0] = values[0] + op2.values[0];
    temp.values[1] = values[1] + op2.values[1];
    temp.values[2] = values[2] + op2.values[2];
    return temp;
}

Vec3& Vec3::operator+=(const Vec3& op2)
{
    values[0] += op2.values[0];
    values[1] += op2.values[1];
    values[2] += op2.values[2];
    return *this;
}

Vec3 Vec3::operator-(const Vec3& op2) const
{
    Vec3 temp = Vec3();
    temp.values[0] = values[0] - op2.values[0];
    temp.values[1] = values[1] - op2.values[1];
    temp.values[2] = values[2] - op2.values[2];
    return temp;
}

Vec3& Vec3::operator-=(const Vec3& op2)
{
    values[0] -= op2.values[0];
    values[1] -= op2.values[1];
    values[2] -= op2.values[2];
    return *this;
}

bool Vec3::operator==(const Vec3& op2) const
{
    return (values[0] == op2.values[0]
        && values[1] == op2.values[1]
        && values[2] == op2.values[2]);
}

bool Vec3::operator!=(const Vec3& op2) const
{
    return (values[0] != op2.values[0]
        || values[1] != op2.values[1]
        || values[2] != op2.values[2]);
}

// Friend operators
Vec3 cross(const Vec3& op1, const Vec3& op2)
{
    return Vec3((op1.values[1] * op2.values[2]) - (op1.values[2] * op2.values[1]),
        (op1.values[2] * op2.values[0]) - (op1.values[0] * op2.values[2]),
        (op1.values[0] * op2.values[1]) - (op1.values[1] * op2.values[0]));
}


Vec3 operator*(const Vec3& op1, const float op2)
{
    Vec3 temp = Vec3(op1.values[0] * op2, op1.values[1] * op2, op1.values[2] * op2);
    return temp;
}

Vec3 operator*(const float op1, const Vec3& op2)
{
    Vec3 temp = Vec3(op2.values[0] * op1, op2.values[1] * op1, op2.values[2] * op1);
    return temp;
}

Vec3 operator/(const Vec3& op1, const float op2)
{
    Vec3 temp = Vec3(op1.values[0] / op2, op1.values[1] / op2, op1.values[2] / op2);
    return temp;
}

Vec3 operator/(const float op1, const Vec3& op2)
{
    Vec3 temp = Vec3(op2.values[0] / op1, op2.values[1] / op1, op2.values[2] / op1);
    return temp;
}

std::ostream & operator<<(std::ostream & out, const Vec3& op2)
{
    out << "(" << op2.values[0] << ", " << op2.values[1] << ", " << op2.values[2] << ")";
    return out;
}


void Vec3::transform(const Vec3 & i, const Vec3 & j, const Vec3 & k)
{
    float x = values[0];
    float y = values[1];
    float z = values[2];
    values[0] = (x * i.get(X)) + (y * j.get(X)) + (z * k.get(X));
    values[1] = (x * i.get(Y)) + (y * j.get(Y)) + (z * k.get(Y));
    values[2] = (x * i.get(Z)) + (y * j.get(Z)) + (z * k.get(Z));
}

void Vec3::scale(const Vec3 & scale)
{
    values[0] *= scale.values[0];
    values[1] *= scale.values[1];
    values[2] *= scale.values[2];
}


Matrix3x3 mmultiply(const Matrix3x3 a, const Matrix3x3 b)
{
    Matrix3x3 result;
    Vec3 a_x = Vec3(a.i.get(X), a.j.get(X), a.k.get(X));
    Vec3 a_y = Vec3(a.i.get(Y), a.j.get(Y), a.k.get(Y));
    Vec3 a_z = Vec3(a.i.get(Z), a.j.get(Z), a.k.get(Z));

    result.i = Vec3(a_x * b.i, a_y * b.i, a_z * b.i);
    result.j = Vec3(a_x * b.j, a_y * b.j, a_z * b.j);
    result.k = Vec3(a_x * b.k, a_y * b.k, a_z * b.k);
    return result;
}


