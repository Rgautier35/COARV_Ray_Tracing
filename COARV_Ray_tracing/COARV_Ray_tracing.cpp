
#include <iostream>
#include <fstream>
#include <string>
#include "ray.h"
using namespace std;



// Function that blends white and blue depending on the position of the coordinate
vec3 color(const ray& r) {
    // Else we return the same linear blend as before.
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    int nx = 400; // Image width
    int ny = 200; // Image height
    string output_name = "ch3";

    ofstream fichier("../../Images/" + output_name + ".ppm"); // Open a file in writing mode

    if (!fichier) {
        cerr << "Error : " + output_name + ".ppm  cannot be written or created" << endl;
        return 1;
    }

    // We write the header of the ppm file (ASCII P3 format)
    fichier << "P3\n" << nx << " " << ny << "\n255\n";


    // Defining the corners of the image
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
      

    // We generate the image
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            // We generate the u,v parameters of direction of the ray
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            // We create the ray originating from 0,0,0 and going to u,v
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);
            
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());

            // We write the image with the 3 colors for each pixels in the ppm file
            fichier << ir << " " << ig << " " << ib << "\n";
        }
    }

    fichier.close(); // We close the ppm file

    cout << "Image is saved under '" + output_name + ".ppm'" << endl;
    return 0;
}
