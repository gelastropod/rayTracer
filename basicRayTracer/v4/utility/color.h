#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "vec3.h"

// Helper function for color
using Color = vec3;

// Apply sqrt transformation to color
Color normalise(const Color& color) {
    return Color(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));
}

void printColor(std::ostream& os, const Color& color) {
    int ir = 255.99 * color[0];
    int ig = 255.99 * color[1];
    int ib = 255.99 * color[2];

    os << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif