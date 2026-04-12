#ifndef RAY_H
#define RAY_H

#include <iostream>

#include "vec3.h"

class Ray {
public:
    vec3 O, D;
    
    Ray() {}
    Ray(const vec3& o, const vec3& d) { O = o, D = d; }

    vec3 origin() const { return O; }
    vec3 direction() const { return D; }
    vec3 at(double t) const { return O + t * D; }
};

inline std::ostream& operator<<(std::ostream& os, const Ray& ray) {
    return os << "Ray(" << ray.origin() << ", " << ray.direction() << ")";
}

#endif