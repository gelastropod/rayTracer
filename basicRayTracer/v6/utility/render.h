#ifndef RENDER_H
#define RENDER_H

#include <chrono>
#include <ctime>
#include <cstdio>

#include "camera.h"
#include "objects/hittable.h"

// Class for rendering an image
class Renderer {
private:
    int nx, ny, ns;
    static const int nd = 50;
    double halfViewportHeight, aspectRatio;
    std::chrono::system_clock::time_point start;
    Camera camera;
    std::shared_ptr<Hittable> world;

public:
    Renderer() : start(std::chrono::system_clock::now()) {}
    Renderer(int _nx, int _ny, int _ns, double _viewportHeight);

    void setWorld(std::shared_ptr<Hittable> _world);

private:
    // Get color from ray. Uses recursion
    Color colorRay(const Ray& ray, int depth) const;

    // Get current number of seconds elapsed since start of render
    double secondsElapsed() const;
    // Convert seconds as an integer into hh:mm:ss format
    static std::string formatTime(int seconds);
    // Print a progressbar based on current progress. Also displays time elapsed
    void progressBar(int current, int total, int width, double elapsedSeconds) const;

public:
    // Render image
    void render(std::ostream& os) const;
};

void Renderer::setWorld(std::shared_ptr<Hittable> _world) {
    world = _world;
}

Color Renderer::colorRay(const Ray& ray, int depth) const {
    HittableRecord record;
    if (world->hit(ray, Interval(0.001, MAX), record)) {
        Color attenuation;
        Ray scattered;

        if (depth > 0 && record.materialPtr->scatter(ray, record, attenuation, scattered)) {
            Color prevColor = colorRay(scattered, depth - 1);
            return attenuation * prevColor;
        }
        else {
            return Color(0.0, 0.0, 0.0);
        }
    }

    vec3 unitDir = unitVector(ray.direction);
    double t = 0.5 * (unitDir[1] + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

Renderer::Renderer(int _nx, int _ny, int _ns, double _viewportHeight) : nx(_nx), ny(_ny), ns(_ns), halfViewportHeight(_viewportHeight / 2.0), start(std::chrono::system_clock::now()) {
    aspectRatio = (double)(nx) / ny;

    double halfViewportWidth = halfViewportHeight * aspectRatio;
    camera = Camera(
        vec3(0.0, 0.0, 0.0),
        vec3(-halfViewportWidth, -halfViewportHeight, -1.0),
        vec3(2.0 * halfViewportWidth, 0.0, 0.0),
        vec3(0.0, 2.0 * halfViewportHeight, 0.0)
    );
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

void Renderer::render(std::ostream& os) const {
    // Log options
    std::cout << "Rendering with options:\n";
    std::cout << "Image width     = " << nx << '\n';
    std::cout << "Image height    = " << ny << '\n';
    std::cout << "Samples taken   = " << ns << '\n';
    printf("Viewport height = %.2f\n\n", halfViewportHeight * 2.0);

    // Print header
    os << "P3\n" << nx << ' ' << ny << "\n255\n";

    // Main render loop
    double prevElapsedSeconds = -1.0;
    int numOper = 0;
    for (int y = ny - 1; y >= 0; y--) {
        for (int x = 0; x < nx; x++) {
            double elapsedSeconds = secondsElapsed();
            int crntOper = (ny - 1 - y) * nx + x + 1;
            if (elapsedSeconds - prevElapsedSeconds > 1.0 || crntOper - numOper > nx * ny * 0.005) {
                numOper = crntOper;
                prevElapsedSeconds = elapsedSeconds;
                progressBar(crntOper, nx * ny, 50, elapsedSeconds);
            }

            double u = (double)(x) / nx;
            double v = (double)(y) / ny;
            
            Color color(0.0, 0.0, 0.0);
            for (int s = 0; s < ns; s++) {
                double uOffset = randDouble() / nx;
                double vOffset = randDouble() / ny;

                Ray currentRay = camera.getRay(u + uOffset, v + vOffset);
                Color currentColor = colorRay(currentRay, nd);
                color += currentColor;
            }
            
            color /= ns;
            color = normalise(color);
            printColor(os, color);
        }
    }

    progressBar(nx * ny, nx * ny, 50, secondsElapsed());

    double elapsedSeconds = secondsElapsed();
    printf("\nRendering completed in %.02f seconds.\n", elapsedSeconds);
}

#endif