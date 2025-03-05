#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "hitable.h"
#include <random>
using namespace std;


// We initiate a random generator
random_device rd;
mt19937 gen(rd()); // Mersenne Twister generator
uniform_real_distribution<float> dist(0.0, 1.0);

vec3 reflect(const vec3& v, const vec3& n) {
	return (v - 2*dot(v, n)*n);
}

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
	if (discriminant > 0) {
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else {
		return false;
	}
}

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0 * vec3(dist(gen), dist(gen), dist(gen)) - vec3(1.0, 1.0, 1.0);
	} while (p.squared_length() >= 1.0);
	return p;
}

float schlick(float cosine, float ref_idx) {
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

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
	float fuzz;

	metal(const vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		// The incoming ray is reflected on the material
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);


		// The scatter is (mostly) in the direction of the reflection
		scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere() );
		attenuation = albedo;

		// If the scatter goes outside the sphere, scatter = true
		return (dot(scattered.direction(), rec.normal) > 0);
	}
};

class dielectric : public material {
public: 
	float ref_idx;

	dielectric(float ri): ref_idx(ri) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		attenuation = vec3(1.0, 1.0, 1.0);
		vec3 refracted;
		float reflect_prob;
		float cosine;

		// Ray coming from inside the sphere
		if (dot(r_in.direction(), rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		// Ray coming from outside the sphere
		else {
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}

		// We define the probabilities of reflection and refraction
		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
			reflect_prob = schlick(cosine, ref_idx);
		}
		else {
			scattered = ray(rec.p, reflected);
			reflect_prob = 1.0;
		}

		// Reflection case
		if ( dist(gen) < reflect_prob) {
			scattered = ray(rec.p, reflected);
		}
		// Refraction case
		else {
			scattered = ray(rec.p, refracted);
		}
		return true;

	}

};




#endif // MATERIAL_H