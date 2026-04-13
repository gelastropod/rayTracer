#include <chrono>
#include <ctime>
#include <fstream>
#include <cstdio>

#include "utility/render.h"

int main() {
    // Output file temp.ppm
    std::ofstream outFile("temp.ppm");

    // Parameters of renderer
    Renderer renderer(500, 250, 400, 2.0);

    // Create world and pass to renderer
    HittableList world = HittableList();
    world.add(make_shared<Sphere>(vec3(0.0, 0.0, -1.0), 0.5));
    world.add(make_shared<Sphere>(vec3(0.0, -100.5, -1.0), 100.0));
    renderer.setWorld(make_shared<HittableList>(world));

    renderer.render(outFile);
}