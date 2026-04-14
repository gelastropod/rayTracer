#ifndef RANDOMSPHERESCENE_H
#define RANDOMSPHERESCENE_H

#include "materials/materials.h"
#include "sphere.h"

class RandomSphereScene: public HittableList {
public:
    RandomSphereScene() {}

    // Generate random scene
    void generateRandomScene();
};

void RandomSphereScene::generateRandomScene() {
    auto groundMaterial = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    add(make_shared<Sphere>(vec3(0.0, -1000.0, 0.0), 1000.0, groundMaterial));

    for (int x = -11; x < 11; x++) {
        for (int y = -11; y < 11; y++) {
            double materialDouble = randDouble();
            vec3 sphereCenter(x + 0.9 * randDouble(), 0.2, y + 0.9 * randDouble());

            if (materialDouble < 0.6) {
                Color albedo = randVec3() * randVec3();
                auto lambertianMaterial = make_shared<Lambertian>(albedo);
                add(make_shared<Sphere>(sphereCenter, 0.2, lambertianMaterial));
            }
            else if (materialDouble < 0.9) {
                Color albedo = randVec3() * randVec3();
                double glossy = pow(randDouble(), 0.2);
                auto metalMaterial = make_shared<Metal>(albedo, glossy);
                add(make_shared<Sphere>(sphereCenter, 0.2, metalMaterial));
            }
            else {
                auto dielectricMaterial = make_shared<Dielectric>(1.5);
                add(make_shared<Sphere>(sphereCenter, 0.2, dielectricMaterial));
            }
        }
    }

    auto sphereMaterial1 = make_shared<Dielectric>(1.5);
    add(make_shared<Sphere>(vec3(0.0, 1.0, 0.0), 1.0, sphereMaterial1));
    auto sphereMaterial2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    add(make_shared<Sphere>(vec3(-4.0, 1.0, 0.0), 1.0, sphereMaterial2));
    auto sphereMaterial3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 1.0);
    add(make_shared<Sphere>(vec3(4.0, 1.0, 0.0), 1.0, sphereMaterial3));
}

#endif