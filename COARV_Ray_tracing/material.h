#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "hitable.h"

class material {
public:
	// A function that returns whether an incoming ray is scattered by the material and how much
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
public:
	vec3 albedo;

	lambertian(const vec3& a) : albedo(a) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}
};

class metal : public material {
public:
	vec3 albedo;

	metal (const vec3& a) : albedo(a) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		// The incoming ray is reflected on the material
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		// The scattering is (mostly) in the direction of the reflection
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		// If the scattering goes outside the sphere, scatter = true
		return (dot(scattered.direction(), rec.normal) > 0);
	}
};

#endif // MATERIAL_H