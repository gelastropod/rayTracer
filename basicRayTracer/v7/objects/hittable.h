#ifndef HITTABLE_H
#define HITTABLE_H

#include "utility/common.h"

class Material;

struct HittableRecord {
    double t;
    vec3 hitPosition, normal;
    shared_ptr<Material> materialPtr;
    bool frontFace;

    // Check if fact is front or back fact, and set proper normal
    void setFaceNormal(const Ray& ray, const vec3& outwardsNormal) {
        frontFace = dot(ray.direction, outwardsNormal) < 0.0;
        normal = (frontFace ? outwardsNormal : -outwardsNormal);
    }
};

class Hittable {
public:
    virtual ~Hittable() = default;

    // Shoot the ray and check if it hits this, hit information stored in record
    virtual bool hit(const Ray& ray, const Interval& tInterval, HittableRecord& record) const = 0;
};

#endif