#ifndef RENDER_H
#define RENDER_H

#include <chrono>
#include <ctime>
#include <cstdio>

#include "scenes/camera.h"
#include "objects/hittable.h"
#include "objects/lights.h"
#include "objects/skybox.h"

// Class for rendering an image
class Renderer {
private:
    int nx, ny, ns, nd;
    double aspectRatio;
    std::chrono::system_clock::time_point start;
    Camera camera;
    shared_ptr<Scene> scene;
    vector<pair<int, int>> debug;
    static const Color debugColor;

public:
    Renderer() : start(std::chrono::system_clock::now()) {}
    Renderer(int _nx, int _ny, int _ns, int _nd, Camera _camera);

    void setScene(shared_ptr<Scene> _scene);

private:
    // Get color from ray. Uses recursion
    Color getColor(const Ray& ray, int depth, bool traceShadowRays, bool debug) const;

    // Get current number of seconds elapsed since start of render
    double secondsElapsed() const;
    // Convert seconds as an integer into hh:mm:ss format
    static std::string formatTime(int seconds);
    // Print a progressbar based on current progress. Also displays time elapsed
    void progressBar(int current, int total, int width, double elapsedSeconds) const;

public:
    // Render image
    void render(std::ostream& os);

    // For debugging, shoots a ray through the given pixel, shoots multiple rays
    void debugRay(int x, int y);
};

const Color Renderer::debugColor = Color(1.0, 0.0, 0.0);

Renderer::Renderer(int _nx, int _ny, int _ns, int _nd, Camera _camera) : nx(_nx), ny(_ny), ns(_ns), nd(_nd), camera(_camera) {
    start = std::chrono::system_clock::now();
    aspectRatio = (double)(nx) / ny;
}

void Renderer::setScene(shared_ptr<Scene> _scene) {
    scene = _scene;
}

Color Renderer::getColor(const Ray& ray, int depth, bool traceShadowRays, bool debug = false) const {
    if (depth <= 0) return Color(0.0, 0.0, 0.0);

    Interval tInterval(0.001, MAX);

    if (debug) std::cout << "Ray from " << ray.origin << " direction " << ray.direction << ":\n";

    HittableRecord record;
    if (scene->world->hit(ray, tInterval, record)) {
        if (debug) std::cout << "Ray hit at " << record.hitPosition << '\n';

        Color direct(0.0, 0.0, 0.0);

        if (traceShadowRays && record.materialPtr->traceShadowRays()) {
            for (const auto& light : scene->lights) {
                vec3 lightPoint;
                Color emission, attenuation;
                light->sampleLight(lightPoint, emission);
                Ray lightRay(record.hitPosition, lightPoint - record.hitPosition);
                HittableRecord lightRayRecord;
                Interval crntInterval = tInterval;

                if (debug) std::cout << "Shadow ray to light sampled at " << lightPoint;

                bool hasHitOpaque = false;

                while (scene->world->hit(lightRay, crntInterval, lightRayRecord)) {
                    if (lightRayRecord.materialPtr->trace(lightRay, lightRayRecord, attenuation)) {
                        emission *= attenuation;
                        crntInterval.min = lightRayRecord.t + 0.001;
                    }
                    else {
                        hasHitOpaque = true;
                        break;
                    }
                }

                if (!hasHitOpaque) {
                    double cosTheta = std::fmax(0.0, dot(unitVector(lightRay.direction), record.normal));
                    double squaredLightDistance = lightRay.direction.squaredLength();
                    Color lightContribution = emission * cosTheta / squaredLightDistance;
                    direct += lightContribution;

                    if (debug) std::cout << ", light contribution " << lightContribution;
                }
                if (debug) std::cout << '\n';
            }

            if (debug) std::cout << "Total light contribution " << direct << '\n';
        }

        Color attenuation;
        Ray scattered;

        if (record.materialPtr->scatter(ray, record, attenuation, scattered)) {
            if (debug) std::cout << "Scattered ray direction " << scattered.direction << " with attenuation " << attenuation << "\n\n";

            Color prevColor = getColor(scattered, depth - 1, false, debug);
            return direct + attenuation * prevColor;
        }
        if (debug) std::cout << '\n';
        return direct;
    }

    Color skyboxColor = scene->skybox.getColor(ray);
    if (debug) std::cout << "Ray hit skybox, color " << skyboxColor << "\n\n";
    return skyboxColor;
}

double Renderer::secondsElapsed() const {
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = now - start;
    return elapsedTime.count();
}

std::string Renderer::formatTime(int seconds) {
    int h = seconds / 3600;
    int m = (seconds % 3600) / 60;
    int s = seconds % 60;

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d:%02d:%02d", h, m, s);
    return std::string(buffer);
}

void Renderer::progressBar(int current, int total, int width, double elapsedSeconds) const {
    int percent = 100.0 * current / total;
    int progress = (double)(width) * current / total;

    std::cout << "\rRendering " << percent << "% [";
    for (int i = 0; i < width; i++) {
        std::cout << (i < progress ? '#' : '.');
    }
    std::cout << "] " << formatTime(elapsedSeconds) << std::flush;
}

void Renderer::render(std::ostream& os) {
    // Camera setup
    camera.setUp();

    // Log options
    std::cout << "Rendering with options:\n";
    std::cout << "Image width      = " << nx << '\n';
    std::cout << "Image height     = " << ny << '\n';
    std::cout << "Samples taken    = " << ns << '\n';
    std::cout << "Max ray bounces  = " << nd << '\n';
    printf("Vertical FOV     = %.1f\n", degrees(camera.vfov));
    printf("Defocus angle    = %.1f\n", degrees(camera.focusAngle));
    printf("Defocus distance = %.1f\n\n", camera.focusDistance);

    // Print header
    os << "P3\n" << nx << ' ' << ny << "\n255\n";

    // Main render loop
    double prevElapsedSeconds = -1.0;
    int numOper = 0;
    for (int y = ny - 1; y >= 0; y--) {
        for (int x = 0; x < nx; x++) {
            double u = (double)(x) / nx;
            double v = (double)(y) / ny;

            bool debugged = false;
            for (const auto& debugPixel : debug) {
                if (x == debugPixel.first && y == debugPixel.second) {
                    debugged = true;
                    break;
                }
            }

            if (debugged) std::cout << "\n\n";

            Color color(0.0, 0.0, 0.0);
            for (int s = 0; s < ns; s++) {
                if (debugged) std::cout << "Shooting ray " << s << ":\n";

                double uOffset = randDouble() / nx;
                double vOffset = randDouble() / ny;

                Ray currentRay = camera.getRay(u + uOffset, v + vOffset);
                Color currentColor = getColor(currentRay, nd, true, debugged);
                color += currentColor;

                if (debugged) std::cout << "Ray color " << normalise(currentColor) << "\n\n\n";
            }
            
            color /= ns;
            color = normalise(color);

            if (debugged) std::cout << "Pixel (" << x << ", " << y << "): " << color << "\n\n\n";

            printColor(os, (debugged ? debugColor : color));

            if (debugged) continue;

            double elapsedSeconds = secondsElapsed();
            int crntOper = (ny - 1 - y) * nx + x + 1;
            if (elapsedSeconds - prevElapsedSeconds > 1.0 || crntOper - numOper > nx * ny * 0.005) {
                numOper = crntOper;
                prevElapsedSeconds = elapsedSeconds;
                progressBar(crntOper, nx * ny, 50, elapsedSeconds);
            }
        }
    }

    progressBar(nx * ny, nx * ny, 50, secondsElapsed());

    double elapsedSeconds = secondsElapsed();
    printf("\nRendering completed in %.02f seconds.\n", elapsedSeconds);
}

void Renderer::debugRay(int x, int y) {
    debug.push_back(std::make_pair(x, y));
}

#endif