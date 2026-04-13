#include <fstream>

#include "materials/materials.h"
#include "objects/hittables.h"
#include "utility/render.h"

int main() {
    // Output file temp.ppm
    std::ofstream outFile("temp.ppm");

    // Parameters of renderer
    Renderer renderer(500, 250, 400, 2.0);

    // Create materials
    auto materialCenter = make_shared<Lambertian>(vec3(0.1, 0.2, 0.5));
    auto materialGround = make_shared<Lambertian>(vec3(0.8, 0.8, 0.0));

    // Create world and pass to renderer
    HittableList world = HittableList();
    world.add(make_shared<Sphere>(vec3(0.0, 0.0, -1.0), 0.5, materialCenter));
    world.add(make_shared<Sphere>(vec3(0.0, -100.5, -1.0), 100.0, materialGround));
    renderer.setWorld(make_shared<HittableList>(world));
    
    renderer.render(outFile);
}