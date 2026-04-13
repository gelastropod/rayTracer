#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "vec3.h"

// Helper function for color
using Color = vec3;

void printColor(std::ostream& os, const Color& color) {
    int ir = 255.99 * color[0];
    int ig = 255.99 * color[1];
    int ib = 255.99 * color[2];

    os << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif