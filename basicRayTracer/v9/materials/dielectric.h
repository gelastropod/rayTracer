#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"
#include "metal.h"

// Dielectric material, like glass (refraction etc.)
class Dielectric: public Material {
private:
    double nRatio;
    Color absorbtion;

public:
    Dielectric() {}
    Dielectric(double _nRatio, Color _absorbtion) : nRatio(_nRatio), absorbtion(_absorbtion) {}

private:
    // Refracts a vector given surface normal and ratio of refractive indices
    static vec3 refract(const vec3& incident, const vec3& normal, double nRatio);
    // Calculates reflection chance from cosine theta and ratio of refractive indices
    static double schlick(double cosTheta, double nRatio);

public:
    // Calculate reflection probability, then apply total internal reflection if applicable, else refraction
    bool scatter(const Ray& incident, const HittableRecord& record, Color& attenuation, Ray& scattered) const override;
    // Return attenuation
    bool trace(const Ray& shadowRay, const HittableRecord& record, Color& attenuation) const override;
    // Should not trace shadow rays
    bool traceShadowRays() const override;
};

vec3 Dielectric::refract(const vec3& incident, const vec3& normal, double nRatio) {
    double cosTheta = std::fmin(-dot(incident, normal), 1.0);
    vec3 refractedPerp = nRatio * (incident + cosTheta * normal);
    vec3 refractedPara = -sqrt(1.0 - refractedPerp.squaredLength()) * normal;
    return refractedPerp + refractedPara;
}

double Dielectric::schlick(double cosTheta, double nRatio) {
    double r0 = pow((nRatio - 1.0) / (nRatio + 1.0), 2.0);
    return r0 + (1.0 - r0) * pow(1.0 - cosTheta, 5.0);
}

bool Dielectric::scatter(const Ray& incident, const HittableRecord& record, Color& attenuation, Ray& scattered) const {
    attenuation = (record.frontFace ? absorbtion : Color(1.0, 1.0, 1.0));

    double usedRatio = (record.frontFace ? 1.0 / nRatio : nRatio);
    vec3 unitDirection = unitVector(incident.direction);

    double cosTheta = -dot(unitDirection, record.normal);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
    double reflectionChance = (sinTheta < 1.0 / usedRatio ? schlick(cosTheta, usedRatio) : 1.0);

    vec3 scatteredDirection;
    if (randDouble() < reflectionChance) {
        scatteredDirection = Metal::reflect(unitDirection, record.normal);
    }
    else {
        scatteredDirection = refract(unitDirection, record.normal, usedRatio);
    }
    scattered = Ray(record.hitPosition, scatteredDirection);

    return true;
}

bool Dielectric::trace(const Ray& shadowRay, const HittableRecord& record, Color& attenuation) const {
    attenuation = absorbtion;

    return true;
}

bool Dielectric::traceShadowRays() const {
    return false;
}

#endif