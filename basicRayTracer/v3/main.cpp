#include <chrono>
#include <ctime>
#include <fstream>
#include <cstdio>

#include "render.h"

#define DEBUG 0

int main() {
    // Output file temp.ppm
    std::ofstream outFile("temp.ppm");

    // Parameters of renderer. Can be changed using DEBUG
#if DEBUG
    Renderer renderer(200, 100, 2.0);
#else
    Renderer renderer(1000, 500, 2.0);
#endif

    renderer.render(outFile);
}