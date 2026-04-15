#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "materials/materials.h"
#include "objects/hittables.h"
#include "objects/lights.h"
#include "objects/skybox.h"
#include "utility/common.h"

class Scene {
    friend class Renderer;

protected:
    shared_ptr<Hittable> world;
    vector<shared_ptr<Light>> lights;
    Skybox skybox;
};

#endif