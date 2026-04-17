#include <fstream>

#include "scenes/scenes.h"
#include "utility/render.h"

int main() {
    srand(time(0));

    std::cout << '\n';

    // Output file temp.ppm
    std::ofstream outFile("temp.ppm");

    // Read parameters from file
    std::ifstream optionsFile("options.txt");
    int nx, ny, ns, nd;
    double vfov, focusAngle, focusDistance;
    optionsFile >> nx >> ny >> ns >> nd >> vfov >> focusAngle >> focusDistance;

    double aspectRatio = (double)(nx) / ny;

    // Parameters of renderer
    Camera camera;
    camera.origin = vec3(13.0, 2.0, 3.0);
    camera.lookAt = vec3(0.0, 0.0, 0.0);
    camera.up = vec3(0.0, 1.0, 0.0);
    camera.aspectRatio = aspectRatio;
    camera.vfov = radians(vfov);
    camera.focusAngle = radians(focusAngle);
    camera.focusDistance = focusDistance;

    Renderer renderer(nx, ny, ns, nd, camera);

    // Create scene and pass to renderer
    RandomSphereScene world;
    world.generateRandomScene(5);
    renderer.setScene(make_shared<RandomSphereScene>(world));
    
    // For debugging
    //renderer.debugRay(313, 211);
    //renderer.debugRay(275, 145);
    
    // Render scene
    renderer.render(outFile);

    std::cout << '\n';
}