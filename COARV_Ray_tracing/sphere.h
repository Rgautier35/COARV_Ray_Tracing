#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class sphere : public hitable {
public:
	// methods
	sphere() {}
	sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m) {};
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;

	// attributes
	vec3 center;
	float radius;
	material *mat_ptr;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	// We compute the discriminant of the intersection of the ray and the sphere
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b -  4 * a * c; // erreur ici

	// IF discriminant >0, the sphere is hit by the ray on two points
	if (discriminant > 0) {
		// temp for the first hit solution
		float temp = (-b - sqrt(discriminant)) / (2*a);
		if (temp < t_max && temp > t_min) {
			// The float t at which the ray hits the sphere
			rec.t = temp;
			// The point where the sphere is hit
			rec.p = r.point_at_parameter(rec.t);
			// The normal of the sphere at the hit point
			rec.normal = (rec.p - center) / radius;
			// The material of the sphere
			rec.mat_ptr = mat_ptr;
			return true;
		}
		// temp becomes the seconds solution
		temp = (-b + sqrt(discriminant)) / (2*a);
		if (temp < t_max && temp > t_min) {
			// The float t at which the ray hits the sphere
			rec.t = temp;
			// The point where the sphere is hit
			rec.p = r.point_at_parameter(rec.t);
			// The normal of the sphere at the hit point
			rec.normal = (rec.p - center) / radius;
			// The material of the sphere
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	// If discriminant <= 0 we consider that the ray does not hit the sphere.
	return false;
}

#endif // SPHERE_H