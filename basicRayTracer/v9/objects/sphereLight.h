#ifndef SPHERELIGHT_H
#define SPHERELIGHT_H

#include "light.h"

class SphereLight: public Light {
private:
    vec3 center;
    double radius;
    Color emissionColor;

public:
    SphereLight() {}
    SphereLight(vec3 _center, double _radius, Color _emissionColor) : center(_center), radius(_radius), emissionColor(_emissionColor) {}

    // Sample a random point on the sphere, return emissionColor as emission
    void sampleLight(vec3& samplePoint, Color& emission) const override;
};

void SphereLight::sampleLight(vec3& samplePoint, Color& emission) const {
    samplePoint = center + radius * randomOnUnitSphere();
    emission = emissionColor;
}

#endif