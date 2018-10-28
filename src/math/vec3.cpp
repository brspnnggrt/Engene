#include "vec3.h"

namespace Engene
{
namespace Math
{

Vec3 &Vec3::add(const Vec3 &other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3 &Vec3::subscract(const Vec3 &other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vec3 &Vec3::multiply(const Vec3 &other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

Vec3 &Vec3::divide(const Vec3 &other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

Vec3 operator+(Vec3 left, const Vec3 &right)
{
	return left.add(right);
}

Vec3 operator-(Vec3 left, const Vec3 &right)
{
	return left.subscract(right);
}

Vec3 operator*(Vec3 left, const Vec3 &right)
{
	return left.multiply(right);
}

Vec3 operator/(Vec3 left, const Vec3 &right)
{
	return left.divide(right);
}

Vec3 operator*(Vec3 left, const Mat4 &right)
{
	Vec3 result = {
		left.x * right.cells[0][0] + left.y * right.cells[1][0] + left.z * right.cells[2][0] + right.cells[3][0],
		left.x * right.cells[0][1] + left.y * right.cells[1][1] + left.z * right.cells[2][1] + right.cells[3][1],
		left.x * right.cells[0][2] + left.y * right.cells[1][2] + left.z * right.cells[2][2] + right.cells[3][2],
	};
	float w = left.x * right.cells[0][3] + left.y * right.cells[1][3] + left.z * right.cells[2][3] + right.cells[3][3];

	if (w != 0.0f)
	{
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}
	return result;
}

bool Vec3::operator==(Vec3 &other)
{
	return other.x == x && other.y == y && other.z == z;
}

bool Vec3::operator!=(Vec3 &other)
{
	return !(*this == other);
}

Vec3 &Vec3::operator+=(const Vec3 &other)
{
	return add(other);
}

Vec3 &Vec3::operator-=(const Vec3 &other)
{
	return subscract(other);
}

Vec3 &Vec3::operator*=(const Vec3 &other)
{
	return multiply(other);
}

Vec3 &Vec3::operator/=(const Vec3 &other)
{
	return divide(other);
}

Vec3 &Vec3::operator*=(const Mat4 &matrix)
{
	Vec3 result = {
		x * matrix.cells[0][0] + y * matrix.cells[1][0] + z * matrix.cells[2][0] + matrix.cells[3][0],
		x * matrix.cells[0][1] + y * matrix.cells[1][1] + z * matrix.cells[2][1] + matrix.cells[3][1],
		x * matrix.cells[0][2] + y * matrix.cells[1][2] + z * matrix.cells[2][2] + matrix.cells[3][2],
	};
	float w = x * matrix.cells[0][3] + y * matrix.cells[1][3] + z * matrix.cells[2][3] + matrix.cells[3][3];

	if (w != 0.0f)
	{
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}
	x = result.x;
	y = result.y;
	z = result.z;	
}

std::ostream &operator<<(std::ostream &stream, const Vec3 &vector)
{
	stream << "Vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return stream;
}

} // namespace Math
} // namespace Engene
