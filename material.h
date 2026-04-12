#ifndef MATERIAL_H
#define MATERIAL_H

#include "hitable.h"

class Material {
public:
    virtual bool scatter(const Ray& incident, const HitRecord& record, Color& attenuation, Ray& scattered) const = 0;
};

#endif