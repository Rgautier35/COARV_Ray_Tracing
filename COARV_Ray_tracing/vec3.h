#pragma once

#ifndef VEC3_H
#define VEC3_H

// Libraries
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <random>
using namespace std;

// We initiate a random generator
random_device rd;
mt19937 gen(rd()); // Mersenne Twister generator
uniform_real_distribution<float> dist(0.0, 1.0);

class vec3 {
public:
	// Attribute with 3 values
	float e[3];

	// Constructors
	vec3() : e{ 0,0,0 } {}
	vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

	// Access to elements (x,y,z) or (r,g,b)
	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	// Overloading of operator
	inline const vec3& operator+() const { return *this; } // +vec3 operator
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } // -vec3 operator
	inline float operator [](int i) const { return e[i]; } // [] access operator
	inline float& operator[](int i) { return e[i]; };

	// Overloading of calculus operators on vectors
	inline vec3& operator+=(const vec3& v2) {
		e[0] += v2.x();
		e[1] += v2.y();
		e[2] += v2.z();
		return *this;
	};
	inline vec3& operator-=(const vec3& v2) {
		e[0] -= v2.x();
		e[1] -= v2.y();
		e[2] -= v2.z();
		return *this;
	};
	inline vec3& operator*=(const vec3& v2) {
		e[0] *= v2.x();
		e[1] *= v2.y();
		e[2] *= v2.z();
		return *this;
	};
	inline vec3& operator/=(const vec3& v2) {
		e[0] /= v2.x();
		e[1] /= v2.y();
		e[2] /= v2.z();
		return *this;
	};
	inline vec3& operator*=(const float t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	};
	inline vec3& operator/=(const float t) {
		e[0] /= t;
		e[1] /= t;
		e[2] /= t;
		return *this;
	};

	inline float length() const {
		return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}
	inline float squared_length() const {
		return (e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
	}
	inline void make_unit_vector() {
		float k = 1.0 / squared_length();
		*this *= k; // check if that works
	};



};



// Overload of the input >> operator
inline istream& operator >>(istream& is, vec3& t) {
	is >> t.e[0] >> t.e[1] >> t.e[2];
	return is;
}

// Overload of the output << operator
inline ostream& operator >>(ostream& os, const vec3& t) {
	os << t.e[0] << " " << t.e[1] << " " << t.e[2];
	return os;
}

// Overload of calculus operator
inline vec3 operator+(const vec3& v1, const vec3& v2) {
	return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline vec3 operator-(const vec3& v1, const vec3& v2) {
	return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

inline vec3 operator*(const vec3& v1, const vec3& v2) {
	return vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}

inline vec3 operator/(const vec3& v1, const vec3& v2) {
	return vec3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}

inline vec3 operator*(float t, const vec3& v) {
	return vec3(t * v.x(), t *  v.y(), t * v.z());
}

inline vec3 operator/(const vec3& v, float t) {
	return vec3(v.x() / t, v.y() / t, v.z() / t);
}

inline vec3 operator*(const vec3& v, float t) {
	return vec3(v.x() * t, v.y() * t, v.z() * t);
}

// Overload of dot operator on vec3
inline float dot(const vec3& v1, const vec3& v2) {
	return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

// Overload of cross operator on vec3
inline vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3((v1.y() * v2.z() - v1.z() * v2.y()),
		(v1.z() * v2.x() - v1.x() * v2.z()),
		(v1.x() * v2.y() - v1.y() * v2.x()));
}

inline vec3 unit_vector(vec3 v) {
	return v / v.length();
}

vec3 random_in_unit_sphere() {
	vec3 p;
	do {
		p = 2.0 * vec3(dist(gen), dist(gen), dist(gen)) - vec3(1.0, 1.0, 1.0);
	} while (p.squared_length() >= 1.0);
	return p;
}

#endif // !VEC3_H