
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <random>

#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
using namespace std;

// We initiate a random generator
random_device rd;
mt19937 gen(rd()); // Mersenne Twister generator
uniform_real_distribution<float> dist(0.0, 1.0);

vec3 random_in_unit_sphere() {
    vec3 p;
    do {
        p = 2.0 * vec3(dist(gen), dist(gen), dist(gen)) - vec3(1.0, 1.0, 1.0);
    } while (p.squared_length() >= 1.0);
    return p;
}

// Function that return the color of the image depending of the ray in argument
vec3 color(const ray& r, hitable *world) {
    hit_record rec;

    // We test if anything in the world is hit by the ray
    if (world->hit(r, 0.001, numeric_limits<float>::max(), rec)) {
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * color( ray(rec.p, target-rec.p), world);
    }
    else {
        // Else we return the ch3 white-blue linear blend 
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    int nx = 400; // Image width
    int ny = 200; // Image height
    int ns = 100;
    string output_name = "ch7";

    ofstream fichier("../../Images/" + output_name + ".ppm"); // Open a file in writing mode

    if (!fichier) {
        cerr << "Error : " + output_name + ".ppm  cannot be written or created" << endl;
        return 1;
    }

    // We write the header of the ppm file (ASCII P3 format)
    fichier << "P3\n" << nx << " " << ny << "\n255\n";
      

    // We define the objects in the world in the hitable_list
    hitable *list[2];
    list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5);
    list[1] = new sphere(vec3(0.0, -100.5, -1), 100);
    hitable *world = new hitable_list(list, 2);

    // We instantiate the camera
    camera cam;

    

    // We generate the image
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0.0, 0.0, 0.0);
            for (int s = 0; s < ns; s++) {

                // We generate the u,v parameters of direction of the ray
                // We add a random factor to make an antialiasing (blur effect)
                float u = float(i + dist(gen)) / float(nx);
                float v = float(j + dist(gen)) / float(ny);

                // We create the ray originating from 0,0,0 and going to u,v
                ray r = cam.get_ray(u, v);
                //ray r(origin, lower_left_corner + u * horizontal + v * vertical);
                vec3 p = r.point_at_parameter(2.0);
                col += color(r, world);

            }
            col /= float(ns);
            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

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
