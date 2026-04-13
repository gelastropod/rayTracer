#include <fstream>

#include "materials/materials.h"
#include "objects/hittables.h"
#include "utility/render.h"

int main() {
    srand(time(0));

    std::cout << '\n';

    // Output file temp.ppm
    std::ofstream outFile("temp.ppm");

    // Read parameters from file
    std::ifstream optionsFile("options.txt");
    int nx, ny, ns;
    double viewportHeight;
    optionsFile >> nx >> ny >> ns >> viewportHeight;

    // Parameters of renderer
    Renderer renderer(nx, ny, ns, viewportHeight);

    // Create materials
    auto materialCenter = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto materialGround = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto materialLeftOuter = make_shared<Dielectric>(1.50);
    auto materialLeftInner = make_shared<Dielectric>(1.0 / 1.50);
    auto materialRight = make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

    // Create world and pass to renderer
    HittableList world = HittableList();
    world.add(make_shared<Sphere>(vec3(0.0, 0.0, -1.2), 0.5, materialCenter));
    world.add(make_shared<Sphere>(vec3(0.0, -100.5, -1.0), 100.0, materialGround));
    world.add(make_shared<Sphere>(vec3(-1.0, 0.0, -1.0), 0.5, materialLeftOuter));
    world.add(make_shared<Sphere>(vec3(-1.0, 0.0, -1.0), 0.4, materialLeftInner));
    world.add(make_shared<Sphere>(vec3(1.0, 0.0, -1.0), 0.5, materialRight));
    renderer.setWorld(make_shared<HittableList>(world));
    
    renderer.render(outFile);

    std::cout << '\n';
}