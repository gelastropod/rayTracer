#ifndef METAL_H
#define METAL_H

#include "material.h"

// Metal material (specular reflection)
class Metal: public Material {
    friend class Dielectric;

private:
    Color albedo;
    double gloss;

public:
    Metal() {}
    Metal(Color _albedo, double _gloss) : albedo(_albedo), gloss(_gloss) {}

private:
    // Reflects a vector given surface normal
    static vec3 reflect(const vec3& incident, const vec3& normal);

public:
    // Calculate perfect reflection, then add some noise to it
    bool scatter(const Ray& incident, const HittableRecord& record, Color& attenuation, Ray& scattered) const override;
};

vec3 Metal::reflect(const vec3& incident, const vec3& normal) {
    return incident - 2.0 * dot(incident, normal) * normal;
}

bool Metal::scatter(const Ray& incident, const HittableRecord& record, Color& attenuation, Ray& scattered) const {
    attenuation = albedo;

    vec3 reflected = reflect(incident.direction, record.normal);
    vec3 randomDirection = randomInUnitSphere();
    vec3 scatterDirection = unitVector(reflected) + (1.0 - gloss) * randomDirection;
    if (nearZero(scatterDirection)) {
        scatterDirection = record.normal;
    }
    
    scattered = Ray(record.hitPosition, scatterDirection);
    
    return true;
}

#endif