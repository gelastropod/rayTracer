#ifndef VEC3_H
#define VEC3_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

class vec3 {
public:
    double v[3];

    vec3() {}
    vec3(double v1, double v2, double v3) { v[0] = v1, v[1] = v2, v[2] = v3; }
    inline void cp(const vec3& other) { v[0] = other.v[0], v[1] = other.v[1], v[2] = other.v[2]; }

    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]); }
    inline double operator[](int i) const { return v[i]; }
    inline double& operator[](int i) { return v[i]; }

    inline vec3& operator+=(const vec3& other);
    inline vec3& operator-=(const vec3& other);
    inline vec3& operator*=(const vec3& other);
    inline vec3& operator/=(const vec3& other);
    inline vec3& operator*=(const double c);
    inline vec3& operator/=(const double c);

    inline double squaredLength() const;
    inline double length() const;
    inline void makeUnitVector();
};

inline std::istream& operator>>(std::istream& is, vec3& vec) {
    return is >> vec.v[0] >> vec.v[1] >> vec.v[2];
}

inline std::ostream& operator<<(std::ostream& os, const vec3& vec) {
    return os << vec.v[0] << " " << vec.v[1] << " " << vec.v[2];
}

inline vec3 operator+(const vec3& v1, const vec3& v2) {
    return vec3(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1], v1.v[2] + v2.v[2]);
}

inline vec3 operator-(const vec3& v1, const vec3& v2) {
    return v1 + -v2;
}

inline vec3 operator*(const vec3& v1, const vec3& v2) {
    return vec3(v1.v[0] * v2.v[0], v1.v[1] * v2.v[1], v1.v[2] * v2.v[2]);
}

inline vec3 operator/(const vec3& v1, const vec3& v2) {
    return vec3(v1.v[0] / v2.v[0], v1.v[1] / v2.v[1], v1.v[2] / v2.v[2]);
}

inline vec3 operator*(const vec3& vec, double t) {
    return vec3(vec.v[0] * t, vec.v[1] * t, vec.v[2] * t);
}

inline vec3 operator*(double t, const vec3& vec) {
    return vec * t;
}

inline vec3 operator/(const vec3& vec, double t) {
    return vec * (1.0 / t);
}

inline double dot(const vec3& v1, const vec3& v2) {
    return v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2];
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3(
        (v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1]),
        (v1.v[2] * v2.v[0] - v1.v[0] * v2.v[2]),
        (v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0])
    );
}

inline vec3& vec3::operator+=(const vec3& other) {
    cp(*this + other);
    return *this;
}

inline vec3& vec3::operator-=(const vec3& other) {
    cp(*this - other);
    return *this;
}

inline vec3& vec3::operator*=(const vec3& other) {
    cp(*this * other);
    return *this;
}

inline vec3& vec3::operator/=(const vec3& other) {
    cp(*this / other);
    return *this;
}

inline vec3& vec3::operator*=(const double c) {
    cp(*this * c);
    return *this;
}

inline vec3& vec3::operator/=(const double c) {
    cp(*this / c);
    return *this;
}

inline double vec3::squaredLength() const {
    return dot(*this, *this);
}

inline double vec3::length() const {
    return sqrt(squaredLength());
}

inline vec3 unitVector(vec3 vec) {
    return vec / vec.length();
}

inline void vec3::makeUnitVector() {
    cp(unitVector(*this));
}

inline double randDouble() {
    return static_cast<double>(rand()) / (RAND_MAX + 1.0);
}

inline vec3 randVec3() {
    return vec3(randDouble(), randDouble(), randDouble());
}

vec3 randomInUnitSphere() {
    vec3 p;
    do {
        p = 2.0 * randVec3() - vec3(1.0, 1.0, 1.0);
    } while (p.squaredLength() >= 1.0);
    return p;
}

vec3 randomInUnitDisk() {
    vec3 p;
    do {
        p = 2.0 * randVec3() * vec3(1.0, 1.0, 0.0) - vec3(1.0, 1.0, 0.0);
    } while (p.squaredLength() >= 1.0);
    return p;
}

inline bool chance(double c) {
    return randDouble() < c;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2 * dot(v, n) * n;
}

bool refract(const vec3& v, const vec3& n, double nRatio, vec3& refracted) {
    vec3 uv = unitVector(v);
    double cosThetaI = dot(uv, n);
    double sin2ThetaI = 1.0 - cosThetaI * cosThetaI;
    double sin2ThetaR = nRatio * nRatio * sin2ThetaI;
    double cos2ThetaR = 1.0 - sin2ThetaR;
    if (cos2ThetaR > 0.0) {
        refracted = nRatio * (uv - cosThetaI * n) - sqrt(cos2ThetaR) * n;
        if (abs(refracted[0]) < 1e-100) std::cout << v << ' ' << n << ' ' << nRatio << '\n';
        return true;
    }
    else return false;
}

#endif