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

## Usage
1. Enter one of the sub-directories corresponding to the target version of ray-tracer.
2. Make sure `temp.ppm` is cleared from this directory. If not, delete it.
3. Compile `main.cpp` using a compiler.  
Example: `gcc main.cpp -o main`
4. Run the compiled program:  
`main`
5. Use `ffmpeg` (or any other converter) to convert `temp.ppm` into a `.png` file:  
`ffmpeg -i temp.ppm temp.png`
6. The `temp.png` is the output file!

The collated output files are also located in the `output` directory.