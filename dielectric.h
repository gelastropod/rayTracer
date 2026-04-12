#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"

double schlick(double cosine, double nRatio) {
    double r0 = (1.0 - nRatio) / (1.0 + nRatio);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow((1.0 - cosine), 5.0);
}

class Dielectric: public Material {
public:
    double n;

    Dielectric(double _n) { n = _n; }
    virtual bool scatter(const Ray& incident, const HitRecord& record, Color& attenuation, Ray& scattered) const {
        vec3 outwardNormal;
        vec3 reflected = reflect(incident.direction(), record.n);
        double nRatio, reflectProb, cosine;
        attenuation = Color(1.0, 1.0, 1.0);
        vec3 refracted;
        if (dot(incident.direction(), record.n) > 0.0) {
            outwardNormal = -record.n;
            nRatio = n;
            cosine = nRatio * dot(unitVector(incident.direction()), record.n);
        }
        else {
            outwardNormal = record.n;
            nRatio = 1.0 / n;
            cosine = -dot(unitVector(incident.direction()), record.n);
        }
        if (refract(incident.direction(), outwardNormal, nRatio, refracted)) {
            reflectProb = schlick(cosine, nRatio);
        }
        else {
            reflectProb = 1.0;
        }
        if (chance(reflectProb)) {
            scattered = Ray(record.p, reflected);
        }
        else {
            scattered = Ray(record.p, refracted);
        }
        return true;
    }
};

#endif