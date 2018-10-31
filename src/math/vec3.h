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

	Vec3 &Add(const Vec3 &other);
	Vec3 &Subscract(const Vec3 &other);
	Vec3 &Multiply(const Vec3 &other);
	Vec3 &Divide(const Vec3 &other);
	Vec3 &Divide(const float &value);

	friend Vec3 operator+(Vec3 left, const Vec3 &right);
	friend Vec3 operator-(Vec3 left, const Vec3 &right);
	friend Vec3 operator*(Vec3 left, const Vec3 &right);
	friend Vec3 operator/(Vec3 left, const Vec3 &right);

	friend Vec3 operator/(Vec3 left, const float &right);

	friend Vec3 operator*(Vec3 left, const Mat4 &right);

	bool operator==(Vec3 &other);
	bool operator!=(Vec3 &other);

	Vec3 &operator+=(const Vec3 &other);
	Vec3 &operator-=(const Vec3 &other);
	Vec3 &operator*=(const Vec3 &other);
	Vec3 &operator/=(const Vec3 &other);

	Vec3 &operator/=(const float &value);

	Vec3 &operator*=(const Mat4 &matrix);

	friend std::ostream &operator<<(std::ostream &, const Vec3 &vector);

	const static Vec3 GetUnitVector(const Vec3& vector);
	const static Vec3 CrossProduct(const Vec3& left, const Vec3& right);
};

} // namespace math
} // namespace Engene
