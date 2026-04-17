#ifndef RANDOMSPHERESCENE_H
#define RANDOMSPHERESCENE_H

#include "scene.h"

class RandomSphereScene: public Scene {
public:
    RandomSphereScene() {}

    // Generate random scene
    void generateRandomScene(int sceneSize);
};

void RandomSphereScene::generateRandomScene(int sceneSize) {
    HittableList objects;

    auto groundMaterial = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    objects.add(make_shared<Sphere>(vec3(0.0, -1000.0, 0.0), 1000.0, groundMaterial));

    for (int x = -sceneSize; x < sceneSize; x++) {
        for (int y = -sceneSize; y < sceneSize; y++) {
            double materialDouble = randDouble();
            vec3 sphereCenter(x + 0.9 * randDouble(), 0.2, y + 0.9 * randDouble());

            if (materialDouble < 0.6) {
                Color albedo = randVec3() * randVec3();
                auto lambertianMaterial = make_shared<Lambertian>(albedo);
                objects.add(make_shared<Sphere>(sphereCenter, 0.2, lambertianMaterial));
            }
            else if (materialDouble < 0.8) {
                Color albedo = randVec3() * randVec3();
                double glossy = pow(randDouble(), 0.2);
                auto metalMaterial = make_shared<Metal>(albedo, glossy);
                objects.add(make_shared<Sphere>(sphereCenter, 0.2, metalMaterial));
            }
            else {
                Color absorbtion = randVec3() * randVec3();
                auto dielectricMaterial = make_shared<Dielectric>(1.5, absorbtion);
                objects.add(make_shared<Sphere>(sphereCenter, 0.2, dielectricMaterial));
            }
        }
    }

    auto sphereMaterial1 = make_shared<Dielectric>(1.5, Color(1.0, 1.0, 1.0));
    objects.add(make_shared<Sphere>(vec3(0.0, 1.0, 0.0), 1.0, sphereMaterial1));
    auto sphereMaterial2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    objects.add(make_shared<Sphere>(vec3(-4.0, 1.0, 0.0), 1.0, sphereMaterial2));
    auto sphereMaterial3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 1.0);
    objects.add(make_shared<Sphere>(vec3(4.0, 1.0, 0.0), 1.0, sphereMaterial3));

    world = make_shared<HittableList>(objects);

    lights.push_back(make_shared<SphereLight>(vec3(0.0, 1.0, 1.5), 0.2, Color(1.0, 0.2, 0.2)));
    lights.push_back(make_shared<SphereLight>(vec3(5.5, 1.0, 0.0), 0.2, Color(0.2, 0.2, 1.0)));

    skybox = Skybox(Color(0.1, 0.1, 0.1), Color(0.05, 0.07, 0.1));
}

#endif