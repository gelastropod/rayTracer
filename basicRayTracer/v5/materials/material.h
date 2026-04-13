#ifndef MATERIAL_H
#define MATERIAL_H

#include "objects/hittable.h"

class Material {
public:
    virtual ~Material() = default;

    // Scatter the incident ray according to the HittableRecord, imparting a certain color to it, and scattering it
    virtual bool scatter(const Ray& incident, const HittableRecord& record, Color& attenuation, Ray& scattered) const = 0;
};

#endif