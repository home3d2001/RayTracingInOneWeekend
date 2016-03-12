#include <cmath>
#include "vec3.h"

vec3& vec3::operator+=(const vec3 &rhs) {
	e[0] += rhs.e[0];
	e[1] += rhs.e[1];
	e[2] += rhs.e[2];
	return *this;
}

vec3& vec3::operator-=(const vec3 &rhs) {
	e[0] -= rhs.e[0];
	e[1] -= rhs.e[1];
	e[2] -= rhs.e[2];
	return *this;
}

vec3& vec3::operator*=(const vec3 &rhs) {
	e[0] *= rhs.e[0];
	e[1] *= rhs.e[1];
	e[2] *= rhs.e[2];
	return *this;
}

vec3& vec3::operator/=(const vec3 &rhs) {
	e[0] /= rhs.e[0];
	e[1] /= rhs.e[1];
	e[2] /= rhs.e[2];
	return *this;
}

vec3& vec3::operator*=(const float t) {
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

vec3& vec3::operator/=(const float t) {
	e[0] /= t;
	e[1] /= t;
	e[2] /= t;
	return *this;
}

const vec3 vec3::operator+(const vec3& rhs) const {
	return vec3(e[0] + rhs.e[0], e[1] + rhs.e[1], e[2] + rhs.e[2]);
}

const vec3 vec3::operator-(const vec3& rhs) const {
	return vec3(e[0] - rhs.e[0], e[1] - rhs.e[1], e[2] - rhs.e[2]);
}

const vec3 vec3::operator*(const vec3& rhs) const {
	return vec3(e[0] * rhs.e[0], e[1] * rhs.e[1], e[2] * rhs.e[2]);
}

const vec3 vec3::operator/(const vec3& rhs) const {
	return vec3(e[0] / rhs.e[0], e[1] / rhs.e[1], e[2] / rhs.e[2]);
}

const vec3 vec3::operator/(const float rhs) const {
	return vec3(e[0] / rhs, e[1] / rhs, e[2] / rhs);
}

float vec3::length() const {
	return std::sqrt(squared_length());
}

float vec3::squared_length() const {
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

vec3 make_unit_vector(vec3 v) {
	return v / v.length();
}

float dot(const vec3& v1, const vec3& v2) {
	return v1.e[0] * v2.e[0] +
		   v1.e[1] * v2.e[1] +
		   v1.e[2] * v2.e[2];
}

vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
				(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
				(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}
