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

	explicit vec3(int r, int g, int b) {
		e[0] = r / 255.0f;
		e[1] = g / 255.0f;
		e[2] = b / 255.0f;
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
		return std::sqrt(squaredLength());
	}
	inline float squaredLength() const {
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

inline vec3 normalize(vec3 v) {
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

inline vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2.0f * dot(v, n) * n;
}

inline vec3 gammaCorrect(const vec3& v, float gamma) {
	return vec3(std::pow(v.r(), gamma), std::pow(v.g(), gamma), std::pow(v.b(), gamma));
}
