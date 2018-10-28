#include "vec2.h"

namespace Engene
{
namespace Math
{

Vec2::Vec2()
{
	x = 0.0f;
	y = 0.0f;
}

Vec2::Vec2(const float &_x, const float &_y)
{
	x = _x;
	y = _y;
}

Vec2 &Vec2::add(const Vec2 &other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vec2 &Vec2::subscract(const Vec2 &other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vec2 &Vec2::multiply(const Vec2 &other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

Vec2 &Vec2::divide(const Vec2 &other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

Vec2 operator+(Vec2 left, const Vec2 &right)
{
	return left.add(right);
}

Vec2 operator-(Vec2 left, const Vec2 &right)
{
	return left.subscract(right);
}

Vec2 operator*(Vec2 left, const Vec2 &right)
{
	return left.multiply(right);
}

Vec2 operator/(Vec2 left, const Vec2 &right)
{
	return left.divide(right);
}

bool Vec2::operator==(Vec2 &other)
{
	return other.x == x && other.y == y;
}

bool Vec2::operator!=(Vec2 &other)
{
	return !(*this == other);
}

Vec2 &Vec2::operator+=(const Vec2 &other)
{
	return add(other);
}

Vec2 &Vec2::operator-=(const Vec2 &other)
{
	return subscract(other);
}

Vec2 &Vec2::operator*=(const Vec2 &other)
{
	return multiply(other);
}

Vec2 &Vec2::operator/=(const Vec2 &other)
{
	return divide(other);
}

std::ostream &operator<<(std::ostream &stream, const Vec2 &vector)
{
	stream << "Vec2: (" << vector.x << ", " << vector.y << ")";
	return stream;
}

} // namespace Math
} // namespace Engene
