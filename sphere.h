#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class Sphere: public Hitable {
public:
    vec3 C;
    double R;
    Material *matPtr;

    Sphere() {}
    Sphere(vec3 c, double r, Material *_matPtr) { C = c, R = r, matPtr = _matPtr; }
    bool hit(const Ray& r, Interval rayT, HitRecord& record) const override {
        vec3 A = r.direction(), B = r.origin() - C;
        double a = dot(A, A), b = dot(A, B), c = dot(B, B) - R * R;
        double disc = b * b - a * c;
        if (disc > 0.0) {
            double t1 = (-b - sqrt(disc)) / a, t2 = (-b + sqrt(disc)) / a;
            double root;
            if (rayT.surrounds(t1)) {
                root = t1;
            }
            else if (rayT.surrounds(t2)) {
                root = t2;
            }
            else return false;
            record.t = root;
            record.p = r.at(root);
            vec3 outwardNormal = (record.p - C) / R;
            record.setFaceNormal(r, outwardNormal);
            return true;
        }
        return false;
    }
};

#endif