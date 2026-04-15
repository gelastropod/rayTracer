#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "interval.h"
#include "vec3.h"

// Helper function for color
using Color = vec3;

// Apply sqrt transformation to color
Color normalise(const Color& color) {
    return Color(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));
}

// Output a color to an ostream
void printColor(std::ostream& os, const Color& color) {
    Interval intensityBounds(0.0, 0.999);
    int ir = 256 * intensityBounds.clamp(color[0]);
    int ig = 256 * intensityBounds.clamp(color[1]);
    int ib = 256 * intensityBounds.clamp(color[2]);

    os << ir << ' ' << ig << ' ' << ib << '\n';
}

#endif