#ifndef SKYBOX_H
#define SKYBOX_H

#include "utility/common.h"

class Skybox {
private:
    Color bottomColor, topColor;

public:
    Skybox() {}
    Skybox(Color _bottomColor, Color _topColor) : bottomColor(_bottomColor), topColor(_topColor) {}

    // Returns skybox color based on ray
    Color getColor(const Ray& ray) const;
};

Color Skybox::getColor(const Ray& ray) const {
    vec3 unitDirection = unitVector(ray.direction);
    double t = 0.5 * (unitDirection[1] + 1.0);
    return lerp(t, bottomColor, topColor);
}

#endif