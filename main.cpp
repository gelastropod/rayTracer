#include <iostream>

#include "vec3.h"

int main() {
    int nx = 200, ny = 100;
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    for (int y = ny - 1; y >= 0; y--) {
        for (int x = 0; x < nx; x++) {
            vec3 col(float(x) / float(nx), float(y) / float(ny), 0.2);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}