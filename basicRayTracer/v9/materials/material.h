#ifndef MATERIAL_H
#define MATERIAL_H

#include "objects/hittable.h"

class Material {
public:
    virtual ~Material() = default;

    // Scatter the incident ray according to the HittableRecord, imparting a certain color to it, and scattering it
    virtual bool scatter(const Ray& incident, const HittableRecord& record, Color& attenuation, Ray& scattered) const = 0;
    // Trace shadow ray through material
    virtual bool trace(const Ray& shadowRay, const HittableRecord& record, Color& attenuation) const = 0;
    // Return if should trace shadow rays
    virtual bool traceShadowRays() const = 0;
};

#endif