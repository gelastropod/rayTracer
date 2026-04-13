#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "color.h"
#include "interval.h"
#include "ray.h"

using std::shared_ptr;
using std::make_shared;

// Random double in [0.0, 1.0)
double randDouble() {
    return (double)(rand()) / (RAND_MAX + 1.0);
}

// Random vec3 with components in [0.0, 1.0)
vec3 randVec3() {
    return vec3(randDouble(), randDouble(), randDouble());
}

// Random vec3 in/on unit sphere
vec3 randomInUnitSphere() {
    vec3 candidate;
    do {
        candidate = 2.0 * randVec3() - vec3(1.0, 1.0, 1.0);
    } while (candidate.squaredLength() > 1.0);
    return candidate;
}

vec3 randomOnUnitSphere() {
    return unitVector(randomInUnitSphere());
}

// Random vec3 in/on unit disk
vec3 randomInUnitDisk() {
    vec3 candidate;
    do {
        candidate = 2.0 * randVec3() * vec3(1.0, 1.0, 0.0) - vec3(1.0, 1.0, 0.0);
    } while (candidate.squaredLength() > 1.0);
    return candidate;
}

vec3 randomOnUnitDisk() {
    return unitVector(randomInUnitDisk());
}

// Returns if vector is close to 0
bool nearZero(const vec3& v) {
    double epsilon = 1e-10;
    return (fabs(v[0]) < epsilon) && (fabs(v[1]) < epsilon) && (fabs(v[2]) < epsilon);
}

#endif