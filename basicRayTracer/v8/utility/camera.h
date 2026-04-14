#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

class Camera {
public:
    double vfov, aspectRatio, focusAngle, focusDistance;
    vec3 origin, lookAt, up;

private:
    vec3 u, v, w;
    vec3 lowerLeftCorner, horizontal, vertical;
    double focusRadius;

public:
    Camera() {}
    
    // Set-up constants
    void setUp();

    // Generate a random ray offset
    vec3 genOffset() const;
    // Shoot a ray through an arbritrary pixel
    Ray getRay(double x, double y) const;
};

void Camera::setUp() {
    w = unitVector(origin - lookAt);
    u = unitVector(cross(up, w));
    v = cross(w, u);

    double tanTheta = tan(vfov / 2.0);
    double halfViewportHeight = tanTheta * focusDistance;
    double halfViewportWidth = halfViewportHeight * aspectRatio;

    horizontal = 2.0 * halfViewportWidth * u;
    vertical = 2.0 * halfViewportHeight * v;
    lowerLeftCorner = origin - focusDistance * w - 0.5 * (horizontal + vertical);

    double tanFocusAngle = tan(focusAngle / 2.0);
    focusRadius = focusDistance * tanFocusAngle;
}

vec3 Camera::genOffset() const {
    vec3 randomVec = randomInUnitDisk() * focusRadius;
    return randomVec[0] * u + randomVec[1] * v;
}

Ray Camera::getRay(double x, double y) const {
    vec3 rayOrigin = origin + genOffset();
    vec3 rayEnd = lowerLeftCorner + x * horizontal + y * vertical;
    return Ray(rayOrigin, rayEnd - rayOrigin);
}

#endif