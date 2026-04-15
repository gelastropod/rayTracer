#ifndef LIGHT_H
#define LIGHT_H

#include "hittable.h"

class Light {
public:
    virtual ~Light() = default;

    // Samples a point on the light, returns emission
    virtual void sampleLight(vec3& samplePoint, Color& emission) const = 0;
};

#endif