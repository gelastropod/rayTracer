#ifndef RENDER_H
#define RENDER_H

#include <chrono>
#include <ctime>
#include <cstdio>

#include "camera.h"

// Class for rendering an image
class Renderer {
public:
    int nx, ny;
    double halfViewportHeight, aspectRatio;
    std::chrono::system_clock::time_point start;
    Camera camera;

    Renderer() : start(std::chrono::system_clock::now()) {}
    Renderer(int _nx, int _ny, double _viewportHeight);

    Color colorRay(const Ray& ray) const;

    // Helper functions for render
    double secondsElapsed() const;
    static std::string formatTime(int seconds);
    void progressBar(int current, int total, int width, double elapsedSeconds) const;
    // Render image
    void render(std::ostream& os) const;
};

// Get color from ray
Color Renderer::colorRay(const Ray& ray) const {
    vec3 unitDir = unitVector(ray.direction);
    double t = 0.5 * (unitDir[1] + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

Renderer::Renderer(int _nx, int _ny, double _viewportHeight) : nx(_nx), ny(_ny), halfViewportHeight(_viewportHeight / 2.0), start(std::chrono::system_clock::now()) {
    aspectRatio = (double)(nx) / ny;

    double halfViewportWidth = halfViewportHeight / aspectRatio;
    camera = Camera(
        vec3(0.0, 0.0, 0.0),
        vec3(-halfViewportWidth, -halfViewportHeight, -1.0),
        vec3(2.0 * halfViewportWidth, 0.0, 0.0),
        vec3(0.0, 2.0 * halfViewportHeight, 0.0)
    );
}

// Finds seconds elapsed since start of program
double Renderer::secondsElapsed() const {
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = now - start;
    return elapsedTime.count();
}

// Converts time in seconds to HH::MM::SS format
std::string Renderer::formatTime(int seconds) {
    int h = seconds / 3600;
    int m = (seconds % 3600) / 60;
    int s = seconds % 60;

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d:%02d:%02d", h, m, s);
    return std::string(buffer);
}

// Print a progress bar to console. Also prints time elapsed.
void Renderer::progressBar(int current, int total, int width, double elapsedSeconds) const {
    int percent = 100.0 * current / total;
    int progress = (double)(width) * current / total;

    std::cout << "\rRendering " << percent << "% [";
    for (int i = 0; i < width; i++) {
        std::cout << (i < progress ? '#' : '.');
    }
    std::cout << "] " << formatTime(elapsedSeconds) << std::flush;
}

void Renderer::render(std::ostream& os) const {
    // Print header
    os << "P3\n" << nx << ' ' << ny << "\n255\n";

    // Main render loop
    double prevElapsedSeconds = -1.0;
    for (int y = ny - 1; y >= 0; y--) {
        for (int x = 0; x < nx; x++) {
            double elapsedSeconds = secondsElapsed();
            if (elapsedSeconds - prevElapsedSeconds > 1.0) {
                prevElapsedSeconds = elapsedSeconds;
                progressBar((ny - 1 - y) * nx + x + 1, nx * ny, 50, elapsedSeconds);
            }

            double u = (double)(x) / nx;
            double v = (double)(y) / ny;

            Ray currentRay = camera.getRay(u, v);
            Color color = colorRay(currentRay);

            printColor(os, color);
        }
    }

    progressBar(nx * ny, nx * ny, 50, secondsElapsed());

    double elapsedSeconds = secondsElapsed();
    printf("\nRendering completed in %.02f seconds.\n", elapsedSeconds);
}

#endif