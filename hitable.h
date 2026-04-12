#ifndef HITABLE_H
#define HITABLE_H

#include "common.h"

class Material;

struct HitRecord {
    double t;
    vec3 p, n;
    bool frontFace;
    Material *matPtr;

    void setFaceNormal(const Ray& r, const vec3& outwardNormal) {
        frontFace = dot(r.direction(), outwardNormal) < 0.0;
        n = (frontFace ? outwardNormal : -outwardNormal);
    }
};

class Hitable {
public:
    virtual ~Hitable() = default;

    virtual bool hit(const Ray& r, Interval rayT, HitRecord& record) const = 0;
};

#endif