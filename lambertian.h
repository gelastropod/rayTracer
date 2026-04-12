#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

class Lambertian: public Material {
public:
    Color albedo;

    Lambertian(const Color& _albedo) { albedo = _albedo; }
    virtual bool scatter(const Ray& incident, const HitRecord& record, Color& attenuation, Ray& scattered) const {
        vec3 target = record.p + record.n + randomInUnitSphere();
        scattered = Ray(record.p, target - record.p);
        attenuation = albedo;
        return true;
    }
};

#endif