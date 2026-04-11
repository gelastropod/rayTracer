#include <math.h>
#include <iostream>

class vec3 {
public:
    double v[3];

    vec3() {}
    vec3(double v1, double v2, double v3) { v[0] = v1, v[1] = v2, v[2] = v3; }
    inline void cp(const vec3& other) { v[0] = other.v[0], v[1] = other.v[1], v[2] = other.v[2]; }

    inline double x() const { return v[0]; }
    inline double y() const { return v[1]; }
    inline double z() const { return v[2]; }
    inline double r() const { return v[0]; }
    inline double g() const { return v[1]; }
    inline double b() const { return v[2]; }

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

    inline double squared_length() const;
    inline double length() const;
    inline void make_unit_vector();
};

inline std::istream& operator>>(std::istream& is, vec3& vec) {
    return is >> vec.v[0] >> vec.v[1] >> vec.v[2];
}

inline std::ostream& operator<<(std::ostream& os, vec3& vec) {
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
}

inline vec3& vec3::operator-=(const vec3& other) {
    cp(*this - other);
}

inline vec3& vec3::operator*=(const vec3& other) {
    cp(*this * other);
}

inline vec3& vec3::operator/=(const vec3& other) {
    cp(*this / other);
}

inline vec3& vec3::operator*=(const double c) {
    cp(*this * c);
}

inline vec3& vec3::operator/=(const double c) {
    cp(*this / c);
}

inline double vec3::squared_length() const {
    return dot(*this, *this);
}

inline double vec3::length() const {
    return sqrt(squared_length());
}

inline vec3 unit_vector(vec3 vec) {
    return vec / vec.length();
}

inline void vec3::make_unit_vector() {
    cp(unit_vector(*this));
}