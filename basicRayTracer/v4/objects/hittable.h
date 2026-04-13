#ifndef HITTABLE_H
#define HITTABLE_H

#include "utility/common.h"

struct HittableRecord {
    double t;
    vec3 hitPosition, normal;
};

class Hittable {
public:
    virtual ~Hittable() = default;

    // Shoot the ray and check if it hits this, hit information stored in record
    virtual bool hit(const Ray& ray, const Interval& tInterval, HittableRecord& record) const = 0;
};

#endif