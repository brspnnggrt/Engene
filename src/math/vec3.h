#pragma once

#include <iostream>
#include "mat4.h"

namespace engene
{
namespace math
{

struct vec3
{
	float x, y, z;

	vec3 &add(const vec3 &other);
	vec3 &subscract(const vec3 &other);
	vec3 &multiply(const vec3 &other);
	vec3 &divide(const vec3 &other);

	friend vec3 operator+(vec3 left, const vec3 &right);
	friend vec3 operator-(vec3 left, const vec3 &right);
	friend vec3 operator*(vec3 left, const vec3 &right);
	friend vec3 operator/(vec3 left, const vec3 &right);

	friend vec3 operator*(vec3 left, const mat4 &right);

	bool operator==(vec3 &other);
	bool operator!=(vec3 &other);

	vec3 &operator+=(const vec3 &other);
	vec3 &operator-=(const vec3 &other);
	vec3 &operator*=(const vec3 &other);
	vec3 &operator/=(const vec3 &other);

	vec3 &operator*=(const mat4 &matrix);

	friend std::ostream &operator<<(std::ostream &, const vec3 &vector);
};

} // namespace math
} // namespace engene
