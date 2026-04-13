#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

class Camera {
private:
    vec3 origin, lowerLeftCorner, horizontal, vertical;

public:
    Camera() {}
    Camera(vec3 _origin, vec3 _lowerLeftCorner, vec3 _horizontal, vec3 _vertical) :
        origin(_origin), lowerLeftCorner(_lowerLeftCorner), horizontal(_horizontal), vertical(_vertical) {}

    // Shoot a ray through an arbritrary pixel
    Ray getRay(double x, double y) const;
};

Ray Camera::getRay(double x, double y) const {
    return Ray(origin, lowerLeftCorner + x * horizontal + y * vertical - origin);
}

#endif