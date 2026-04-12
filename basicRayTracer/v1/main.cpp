#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <cstdio>

#define DEBUG 0

std::chrono::system_clock::time_point start;

// Finds seconds elapsed since start of program
double secondsElapsed() {
    auto now = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedTime = now - start;
    return elapsedTime.count();
}

// Converts time in seconds to HH::MM::SS format
std::string formatTime(int seconds) {
    int h = seconds / 3600;
    int m = (seconds % 3600) / 60;
    int s = seconds % 60;

    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%d:%02d:%02d", h, m, s);
    return std::string(buffer);
}

// Print a progress bar to console. Also prints time elapsed.
void progressBar(int current, int total, int width, double elapsedSeconds) {
    int percent = 100.0 * current / total;
    int progress = (double)(width) * current / total;

    std::cout << "\rRendering " << percent << "% [";
    for (int i = 0; i < width; i++) {
        std::cout << (i < progress ? '#' : '.');
    }
    std::cout << "] " << formatTime(elapsedSeconds) << std::flush;
}

int main() {
    start = std::chrono::system_clock::now();

    // Output file temp.ppm
    std::ofstream outFile("temp.ppm");

    // Parameters of renderer. Can be changed using DEBUG
#if DEBUG
    int nx = 200, ny = 100;
#else
    int nx = 1000, ny = 500;
#endif

    // Print header
    outFile << "P3\n" << nx << ' ' << ny << "\n255\n";

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

            int ir = 255.99 * u;
            int ig = 255.99 * v;
            int ib = 255.99 * 0.2;

            outFile << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    progressBar(nx * ny, nx * ny, 50, secondsElapsed());

    double elapsedSeconds = secondsElapsed();
    printf("\nRendering completed in %.02f seconds.\n", elapsedSeconds);
}