#ifndef METAL_H
#define METAL_H

#include "material.h"

class Metal: public Material {
public:
    Color albedo;
    double matte;

    Metal(const Color& _albedo, double _matte = 0.0) { albedo = _albedo, matte = std::min(_matte, 1.0); }
    virtual bool scatter(const Ray& incident, const HitRecord& record, Color& attenuation, Ray& scattered) const {
        vec3 reflected = reflect(unitVector(incident.direction()), record.n);
        scattered = Ray(record.p, reflected + matte * randomInUnitSphere());
        attenuation = albedo;
        return (dot(scattered.direction(), record.n) > 0.0);
    }
};

#endif