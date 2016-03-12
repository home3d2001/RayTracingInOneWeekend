#pragma once
#include <cmath>

class vec3 
{
public:
	vec3() {
		e[0] = e[1] = e[2] = 0.0f;
	}

	explicit vec3(float e0, float e1, float e2) {
		e[0] = e0;
		e[1] = e1;
		e[2] = e2;
	}

	vec3(float e0) {
		e[0] = e0;
		e[1] = e0;
		e[2] = e0;
	}

	inline float x() const { return e[0]; }
	inline float y() const { return e[1]; }
	inline float z() const { return e[2]; }

	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vec3& operator+() const { return *this; }
	inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }

	inline vec3& vec3::operator+=(const vec3 &rhs) {
		e[0] += rhs.e[0];
		e[1] += rhs.e[1];
		e[2] += rhs.e[2];
		return *this;
	}

	inline vec3& vec3::operator-=(const vec3 &rhs) {
		e[0] -= rhs.e[0];
		e[1] -= rhs.e[1];
		e[2] -= rhs.e[2];
		return *this;
	}

	inline vec3& vec3::operator*=(const vec3 &rhs) {
		e[0] *= rhs.e[0];
		e[1] *= rhs.e[1];
		e[2] *= rhs.e[2];
		return *this;
	}

	inline vec3& vec3::operator/=(const vec3 &rhs) {
		e[0] /= rhs.e[0];
		e[1] /= rhs.e[1];
		e[2] /= rhs.e[2];
		return *this;
	}

	inline vec3& vec3::operator*=(const float t) {
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	inline vec3& vec3::operator/=(const float t) {
		e[0] /= t;
		e[1] /= t;
		e[2] /= t;
		return *this;
	}

	inline float length() const {
		return std::sqrt(squared_length());
	}
	inline float squared_length() const {
		return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
	}

	float e[3];
};

inline vec3 operator+(vec3 lhs, const vec3& rhs) {
	lhs += rhs;
	return lhs;
}

inline vec3 operator-(vec3 lhs, const vec3& rhs) {
	lhs -= rhs;
	return lhs;
}

inline vec3 operator*(vec3 lhs, const vec3& rhs) {
	lhs *= rhs;
	return lhs;
}

inline vec3 operator*(vec3 lhs, const float& rhs) {
	lhs *= rhs;
	return lhs;
}

inline vec3 operator/(vec3 lhs, const vec3& rhs) {
	lhs /= rhs;
	return lhs;
}

inline vec3 operator/(vec3 lhs, const float rhs) {
	lhs /= rhs;
	return lhs;
}

inline vec3 make_unit_vector(vec3 v) {
	return v / v.length();
}

inline float dot(const vec3& v1, const vec3& v2) {
	return v1.e[0] * v2.e[0] +
		v1.e[1] * v2.e[1] +
		v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
	return vec3((v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
		(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]));
}