#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

// Lambertian material (diffuse reflection)
class Lambertian: public Material {
private:
    Color albedo;

public:
    Lambertian() {}
    Lambertian(Color _albedo) : albedo(_albedo) {}
    
    // Scatter in random direction, using albedo as attenuation
    bool scatter(const Ray& incident, const HittableRecord& record, Color& attenuation, Ray& scattered) const override;
    // Does not pass through, return false
    bool trace(const Ray& shadowRay, const HittableRecord& record, Color& attenuation) const override;
    // Should trace shadow rays
    bool traceShadowRays() const override;
};

bool Lambertian::scatter(const Ray& incident, const HittableRecord& record, Color& attenuation, Ray& scattered) const {
    attenuation = albedo;

    vec3 randomDirection = randomInUnitSphere();
    vec3 scatterDirection = randomDirection + record.normal;
    if (nearZero(scatterDirection)) {
        scatterDirection = record.normal;
    }
    
    scattered = Ray(record.hitPosition, scatterDirection);
    
    return true;
}

bool Lambertian::trace(const Ray& shadowRay, const HittableRecord& record, Color& attenuation) const {
    return false;
}

bool Lambertian::traceShadowRays() const {
    return true;
}

#endif