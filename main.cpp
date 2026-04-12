#include <chrono>
#include <ctime>
#include <fstream>
#include <random>

#include "camera.h"
#include "dielectric.h"
#include "hitableList.h"
#include "lambertian.h"
#include "metal.h"
#include "sphere.h"

#define DEBUG 1

std::chrono::system_clock::time_point start;

Color color(const Ray& r, const Hitable& world, int depth, int rayID, bool debug = false) {
    HitRecord record;
    if (world.hit(r, Interval(0.001, +infinity), record)) {
        Ray scattered;
        Color attenuation;
        if (depth > 0 && record.matPtr->scatter(r, record, attenuation, scattered)) {
            Color prevColor = color(scattered, world, depth - 1, rayID, debug);
            Color resColor = attenuation * prevColor;
            if (debug) std::cout << resColor << '\n';
            return resColor;
        }
        else {
            return Color(0.0, 0.0, 0.0);
        }
    }
    else {
        vec3 unitDirection = unitVector(r.direction());
        double t = 0.5 * (unitDirection[1] + 1.0);
        return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
    }
}

std::string formatTime(double seconds) {
    int h = seconds / 3600;
    int m = (int(seconds) % 3600) / 60;
    int s = int(seconds) % 60;
    char buf[32];
    snprintf(buf, sizeof(buf), "%d:%02d:%02d", h, m, s);
    return buf;
}

void printProgress(int current, int total, int width) {
    auto crnt = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsedSeconds = crnt - start;

    int filled = static_cast<double>(width) * current / total;
    int percent = 100.0 * current / total;
    std::cout << "\rRendering " << percent << "% [";
    for (int i = 0; i < width; i++)
        std::cout << (i < filled ? '#' : '.');
    std::cout << "] " << formatTime(elapsedSeconds.count()) << std::flush;
}

int main() {
    start = std::chrono::system_clock::now();

    srand(time(0));

    std::ofstream outFile("temp.ppm");

#if DEBUG
    int nx = 200, ny = 100, ns = 100, nr = 50;
#else
    int nx = 1000, ny = 500, ns = 200, nr = 50;
#endif
    double aspect = static_cast<double>(nx) / ny;
    
    outFile << "P3\n" << nx << " " << ny << "\n255\n";

    HitableList world;
    world.add(make_shared<Sphere>(vec3(0.0, 0.0, -1.0), 0.5, new Lambertian(Color(0.1, 0.2, 0.5))));
    world.add(make_shared<Sphere>(vec3(0.0, -100.5, -1.0), 100.0, new Lambertian(Color(0.8, 0.8, 0.0))));
    world.add(make_shared<Sphere>(vec3(1.0, 0.0, -1.0), 0.5, new Metal(Color(0.8, 0.6, 0.2))));
    world.add(make_shared<Sphere>(vec3(-1.0, 0.0, -1.0), 0.5, new Dielectric(1.5)));
    world.add(make_shared<Sphere>(vec3(-1.0, 0.0, -1.0), -0.45, new Dielectric(1.5)));

    vec3 lookFrom = vec3(3.0, 3.0, 2.0);
    vec3 lookAt = vec3(0.0, 0.0, -1.0);
    double focusDist = (lookFrom - lookAt).length();
    double aperture = 2.0;

    Camera cam(lookFrom, lookAt, vec3(0.0, 1.0, 0.0), 20.0, aspect, aperture, focusDist);

    //color(Ray(vec3(0.0, 0.0, 0.0), vec3(-1.0, 0.0, -1.0)), world, 50, true);

    for (int y = ny - 1; y >= 0; y--) {
        printProgress(ny - 1 - y, ny - 1, 50);

        for (int x = 0; x < nx; x++) {
            Color col(0.0, 0.0, 0.0);
            double u = static_cast<double>(x) / nx;
            double v = static_cast<double>(y) / ny;

            for (int s = 0; s < ns; s++) {
                double uOffset = randDouble() / nx;
                double vOffset = randDouble() / ny;
                Ray r = cam.getRay(u + uOffset, v + vOffset);
                int rayID = y * nx + x;
                col += color(r, world, nr, rayID);
            }

            col /= ns;
            col = Color(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            writeColor(outFile, col);
        }
    }
    std::cout << "\n";

    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsedSeconds = end - start;
    std::cout << "Rendering finished in " << elapsedSeconds.count() << " seconds." << std::endl;
}