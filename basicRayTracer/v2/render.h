#ifndef RENDER_H
#define RENDER_H

#include <chrono>
#include <ctime>
#include <cstdio>

#include "common.h"

// Class for rendering an image
class Renderer {
public:
    int nx, ny;
    std::chrono::system_clock::time_point start;

    Renderer() : start(std::chrono::system_clock::now()) {}
    Renderer(int _nx, int _ny) : nx(_nx), ny(_ny), start(std::chrono::system_clock::now()) {}

    // Helper functions for render
    double secondsElapsed() const;
    static std::string formatTime(int seconds);
    void progressBar(int current, int total, int width, double elapsedSeconds) const;
    // Render image
    void render(std::ostream& os) const;
};

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

            vec3 color(u, v, 0.2);

            printColor(os, color);
        }
    }

    progressBar(nx * ny, nx * ny, 50, secondsElapsed());

    double elapsedSeconds = secondsElapsed();
    printf("\nRendering completed in %.02f seconds.\n", elapsedSeconds);
}

#endif