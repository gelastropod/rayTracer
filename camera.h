#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class Camera {
public:
    vec3 origin, horizontal, vertical, lowerLeftCorner;
    vec3 u, v, w;
    double lensRadius;

    Camera(vec3 lookFrom, vec3 lookAt, vec3 vUp, double vfov, double aspect, double aperture, double focusDist) {
        lensRadius = aperture / 2.0;
        double theta = vfov * M_PI / 180.0;
        double halfHeight = tan(theta / 2.0);
        double halfWidth = aspect * halfHeight;
        origin = lookFrom,
        w = unitVector(lookFrom - lookAt),
        u = unitVector(cross(vUp, w)),
        v = cross(w, u);
        horizontal = 2.0 * halfWidth * focusDist * u,
        vertical = 2.0 * halfHeight * focusDist * v,
        lowerLeftCorner = origin - focusDist * (halfWidth * u + halfHeight * v + w);
    }

    Ray getRay(double s, double t) {
        vec3 randomInDisk = lensRadius * randomInUnitDisk();
        vec3 offset = randomInDisk[0] * u + randomInDisk[1] * v;
        return Ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset);
    }
};

#endif