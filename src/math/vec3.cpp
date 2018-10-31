#include "vec3.h"
#include <math.h>

namespace Engene
{
namespace Math
{

Vec3 &Vec3::Add(const Vec3 &other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vec3 &Vec3::Subscract(const Vec3 &other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vec3 &Vec3::Multiply(const Vec3 &other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

Vec3 &Vec3::Divide(const Vec3 &other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

Vec3 &Vec3::Divide(const float &value)
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

Vec3 operator+(Vec3 left, const Vec3 &right)
{
	return left.Add(right);
}

Vec3 operator-(Vec3 left, const Vec3 &right)
{
	return left.Subscract(right);
}

Vec3 operator*(Vec3 left, const Vec3 &right)
{
	return left.Multiply(right);
}

Vec3 operator/(Vec3 left, const Vec3 &right)
{
	return left.Divide(right);
}

Vec3 operator/(Vec3 left, const float &value)
{
	return left.Divide(value);
}

Vec3 operator*(Vec3 left, const Mat4 &right)
{
	Vec3 result = {
		left.x * right.cells[0][0] + left.y * right.cells[0][1] + left.z * right.cells[0][2] + right.cells[0][3],
		left.x * right.cells[1][0] + left.y * right.cells[1][1] + left.z * right.cells[1][2] + right.cells[1][3],
		left.x * right.cells[2][0] + left.y * right.cells[2][1] + left.z * right.cells[2][2] + right.cells[2][3],
	};
	float w = left.x * right.cells[3][0] + left.y * right.cells[3][1] + left.z * right.cells[3][2] + right.cells[3][3];
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
	return Add(other);
}

Vec3 &Vec3::operator-=(const Vec3 &other)
{
	return Subscract(other);
}

Vec3 &Vec3::operator*=(const Vec3 &other)
{
	return Multiply(other);
}

Vec3 &Vec3::operator/=(const Vec3 &other)
{
	return Divide(other);
}

Vec3 &Vec3::operator/=(const float &value) 
{
	return Divide(value);
}

Vec3 &Vec3::operator*=(const Mat4 &matrix)
{
	Vec3 result = *this * matrix;
	*this = result;
	return *this;
}

std::ostream &operator<<(std::ostream &stream, const Vec3 &vector)
{
	stream << "Vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
	return stream;
}

const Vec3 Vec3::GetUnitVector(const Vec3& vector) {
	float viewingFromVectorLength = sqrt(pow(vector.x, 2.0f) + pow(vector.y, 2.0f) + pow(vector.z, 2.0f));
	Math::Vec3 result = vector / viewingFromVectorLength;
	return result;
}

const Vec3 Vec3::CrossProduct(const Vec3& left, const Vec3& right) 
{
	return Vec3 {
		left.y*right.z - left.z*right.y,
		left.z*right.x - left.x*right.z,
		left.x*right.y - left.y*right.x
	};
}

} // namespace Math
} // namespace Engene
