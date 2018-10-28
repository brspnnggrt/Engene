#pragma once

#include <iostream>
#include "mat4.h"

namespace Engene
{
namespace Math
{

struct Vec3
{
	float x, y, z;

	Vec3 &add(const Vec3 &other);
	Vec3 &subscract(const Vec3 &other);
	Vec3 &multiply(const Vec3 &other);
	Vec3 &divide(const Vec3 &other);

	friend Vec3 operator+(Vec3 left, const Vec3 &right);
	friend Vec3 operator-(Vec3 left, const Vec3 &right);
	friend Vec3 operator*(Vec3 left, const Vec3 &right);
	friend Vec3 operator/(Vec3 left, const Vec3 &right);

	friend Vec3 operator*(Vec3 left, const Mat4 &right);

	bool operator==(Vec3 &other);
	bool operator!=(Vec3 &other);

	Vec3 &operator+=(const Vec3 &other);
	Vec3 &operator-=(const Vec3 &other);
	Vec3 &operator*=(const Vec3 &other);
	Vec3 &operator/=(const Vec3 &other);

	Vec3 &operator*=(const Mat4 &matrix);

	friend std::ostream &operator<<(std::ostream &, const Vec3 &vector);
};

} // namespace math
} // namespace Engene
