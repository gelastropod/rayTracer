#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

// Class for 3-dimensional vectors
class vec3 {
public:
    double v[3];

    vec3() {}
    vec3(double v1, double v2, double v3);

    inline void cp(const vec3& other);

    inline double operator[](size_t i) const;
    inline vec3 operator-() const;
    
    inline vec3 operator+(const vec3& other) const;
    inline vec3 operator-(const vec3& other) const;
    inline vec3 operator*(const vec3& other) const;
    inline vec3 operator/(const vec3& other) const;
    inline vec3 operator*(double c) const;
    inline vec3 operator/(double c) const;

    inline void operator+=(const vec3& other);
    inline void operator-=(const vec3& other);
    inline void operator*=(const vec3& other);
    inline void operator/=(const vec3& other);
    inline void operator*=(double c);
    inline void operator/=(double c);

    inline double squaredLength() const;
    inline double length() const;
    inline vec3 makeUnitVector() const;
};

vec3::vec3(double v1, double v2, double v3) {
    v[0] = v1, v[1] = v2, v[2] = v3;
}

inline void vec3::cp(const vec3& other) {
    v[0] = other[0], v[1] = other[1], v[2] = other[2];
}

inline double vec3::operator[](size_t i) const {
    return v[i];
}

inline vec3 vec3::operator-() const {
    return vec3(-v[0], -v[1], -v[2]);
}

inline vec3 vec3::operator+(const vec3& other) const {
    return vec3(v[0] + other[0], v[1] + other[1], v[2] + other[2]);
}

inline vec3 vec3::operator-(const vec3& other) const {
    return vec3(v[0] - other[0], v[1] - other[1], v[2] - other[2]);
}

inline vec3 vec3::operator*(const vec3& other) const {
    return vec3(v[0] * other[0], v[1] * other[1], v[2] * other[2]);
}

inline vec3 vec3::operator/(const vec3& other) const {
    return vec3(v[0] / other[0], v[1] / other[1], v[2] / other[2]);
}

inline vec3 vec3::operator*(double c) const {
    return vec3(v[0] * c, v[1] * c, v[2] * c);
}

inline vec3 operator*(double c, const vec3& v) {
    return vec3(v[0] * c, v[1] * c, v[2] * c);
}

inline vec3 vec3::operator/(double c) const {
    return vec3(v[0] / c, v[1] / c, v[2] / c);
}

inline void vec3::operator+=(const vec3& other) {
    cp(*this + other);
}

inline void vec3::operator-=(const vec3& other) {
    cp(*this - other);
}

inline void vec3::operator*=(const vec3& other) {
    cp(*this * other);
}

inline void vec3::operator/=(const vec3& other) {
    cp(*this / other);
}

inline void vec3::operator*=(double c) {
    cp(*this * c);
}

inline void vec3::operator/=(double c) {
    cp(*this / c);
}

inline double vec3::squaredLength() const {
    return (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);
}

inline double vec3::length() const {
    return sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
}

inline double dot(const vec3& v1, const vec3& v2) {
    return (v1[0] * v2[0]) + (v1[1] * v2[1]) + (v1[2] * v2[2]);
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3(
        (v1[1] * v2[2]) - (v1[2] * v2[1]),
        (v1[2] * v2[0]) - (v1[0] * v2[2]),
        (v1[0] * v2[1]) - (v1[1] * v2[0])
    );
}

inline vec3 unitVector(const vec3& v) {
    return v / v.length();
}

inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
    return os << v[0] << ' ' << v[1] << ' ' << v[2];
}

#endif