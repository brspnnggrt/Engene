#pragma once

#include <iostream>

namespace Engene
{
namespace Math
{

struct Vec2
{
	float x, y;

	Vec2();
	Vec2(const float &x, const float &y);

	Vec2 &add(const Vec2 &other);
	Vec2 &subscract(const Vec2 &other);
	Vec2 &multiply(const Vec2 &other);
	Vec2 &divide(const Vec2 &other);

	friend Vec2 operator+(Vec2 left, const Vec2 &right);
	friend Vec2 operator-(Vec2 left, const Vec2 &right);
	friend Vec2 operator*(Vec2 left, const Vec2 &right);
	friend Vec2 operator/(Vec2 left, const Vec2 &right);

	bool operator==(Vec2 &other);
	bool operator!=(Vec2 &other);

	Vec2 &operator+=(const Vec2 &other);
	Vec2 &operator-=(const Vec2 &other);
	Vec2 &operator*=(const Vec2 &other);
	Vec2 &operator/=(const Vec2 &other);

	friend std::ostream &operator<<(std::ostream &, const Vec2 &vector);
};

} // namespace Math
} // namespace Engene
