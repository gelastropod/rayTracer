#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

using Color = vec3;

void writeColor(std::ostream& out, const Color& pixelColor) {
    auto r = pixelColor[0],
         g = pixelColor[1],
         b = pixelColor[2];
    
    int rByte = static_cast<int>(255.99 * r),
        gByte = static_cast<int>(255.99 * g),
        bByte = static_cast<int>(255.99 * b);
    
    out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}

#endif