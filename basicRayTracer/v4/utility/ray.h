#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
public:
    vec3 origin, direction;

    Ray() {}
    Ray(vec3 _origin, vec3 _direction) : origin(_origin), direction(_direction) {}

    inline vec3 operator()(double t) const;
};

inline vec3 Ray::operator()(double t) const {
    return origin + t * direction;
}

#endif