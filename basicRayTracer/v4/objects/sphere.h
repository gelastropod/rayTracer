#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class Sphere: public Hittable {
public:
    vec3 origin;
    double radius;

    Sphere() {}
    Sphere(vec3 _origin, double _radius) : origin(_origin), radius(_radius) {}

    bool hit(const Ray& ray, const Interval& tInterval, HittableRecord& record) const override;
};

// Solve a quadratic based on origin and ray information
bool Sphere::hit(const Ray& ray, const Interval& tInterval, HittableRecord& record) const {
    vec3 toOrigin = ray.origin - origin;
    double a = dot(ray.direction, ray.direction), b = dot(ray.direction, toOrigin),
           c = dot(toOrigin, toOrigin) - radius * radius;
    double disc = b * b - a * c;

    if (disc > 0.0) {
        double t1 = (-b - sqrt(disc)) / a, t2 = (-b + sqrt(disc)) / a;
        if (tInterval.contains(t1)) {
            record.t = t1;
        }
        else if (tInterval.contains(t2)) {
            record.t = t2;
        }
        else {
            return false;
        }

        record.hitPosition = ray(record.t);
        record.normal = (record.hitPosition - origin) / radius;

        return true;
    }

    return false;
}

#endif