# basicRayTracer
> Writing directly to image files ???

## Workflow
Instead of having to deal with graphics APIs in addition to writing a ray-tracer, this project renders images directly, without creating a window to display it to a screen.
<p></p>

I write data directly to a `.ppm` file, which format is specified below:  
```
P3
C R
maxval
r1 g1 b1
r2 g2 b2
...
rn gn bn
```
Where `C` is the number of columns (width of image), `R` is the number of rows (height of image), and `maxval` is the maximum value for colour values (255 here). `n` is the number of pixels (`C` * `R`).
<p></p>

Then, I convert the intermediate `temp.ppm` file to a `.png` image file using `ffmpeg`. This results in a final image file, placed in the `output` directory.

## Versions
I test my code regularly, resulting in many different "versions", all with numbered output `.png`s. They are described below:

1. Initial test, essentially a gradient.
2. Test of `vec3` class (a class represnting a 3-dimensional vector).
3. Adding `Ray` and `Camera` class, simple representation of shooting rays out of a camera.
4. Implementing abstract class `Hittable`, which shoots a given ray and checks if it intersects with an object, and returns information in a `HittableRecord`. Implementation of a primitive `Sphere`, as well as list of primitives `HittableList`. Additional implementation of anti-aliasing by sending multiple rays randomly within the same pixel.
5. Implement abstract class `Material`, which allows rays to gain color and scatter off surfaces. Implemented `Lambertian` material, which allows for diffuse reflections. Minor cleanup of code.
6. Implemented other materials `Metal`, specular reflections with variable glossy-ness, `Dielectric`, glass material with refractions. More minor cleanup of code.
7. Implemented variable `Camera` positioning, as well as depth blurring.
8. (End of Book 1) Implementation of `RandomSphereScene`, a generator of the scene shown on the cover page of Book 1. Constants are increased for a higher quality render.
9. (Extension of Book 1) Implementation of `Light` and shadow rays, as well as more organisation of code. Added simple implementation of coloured `Dielectric`s.

## Usage
1. Enter one of the sub-directories corresponding to the target version of ray-tracer.
2. Make sure `temp.ppm` is cleared from this directory. If not, delete it.
3. Compile `main.cpp` using a compiler.  
Example: `gcc -I ./ main.cpp -o main`
4. Run the compiled program:  
`main`
5. Use `ffmpeg` (or any other converter) to convert `temp.ppm` into a `.png` file:  
`ffmpeg -i temp.ppm temp.png`
6. The `temp.png` is the output file!

The collated output files are also located in the `output` directory.