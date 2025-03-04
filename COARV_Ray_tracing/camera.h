#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"

class camera {
public:
	camera() {
        // Defining the corner of the image, the directions and the origin
        lower_left_corner = vec3(-2.0, -1.0, -1.0);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
	}

    // Function to create the ray originating from the camera and going to u,v
    ray get_ray(float u, float v) { return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin); }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif // CAMERA_H