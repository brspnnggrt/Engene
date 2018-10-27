#include "vec3.h"

namespace engene { namespace math {

	vec3& vec3::add(const vec3& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	vec3& vec3::subscract(const vec3& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	vec3& vec3::multiply(const vec3& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	vec3& vec3::divide(const vec3& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	vec3 operator+(vec3 left, const vec3& right) {
		return left.add(right);
	}

	vec3 operator-(vec3 left, const vec3& right) {
		return left.subscract(right);
	}

	vec3 operator*(vec3 left, const vec3& right) {
		return left.multiply(right);
	}

	vec3 operator/(vec3 left, const vec3& right) {
		return left.divide(right);
	}

	vec3 operator*(vec3 left, const mat4& right) {
		vec3 result = {
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

	bool vec3::operator==(vec3& other) {
		return other.x == x && other.y == y && other.z == z;
	}

	bool vec3::operator!=(vec3& other) {
		return !(*this == other);
	}

	vec3& vec3::operator+=(const vec3& other) {
		return add(other);
	}

	vec3& vec3::operator-=(const vec3& other) {
		return subscract(other);
	}

	vec3& vec3::operator*=(const vec3& other) {
		return multiply(other);
	}

	vec3& vec3::operator/=(const vec3& other) {
		return divide(other);
	}

	vec3& vec3::operator*=(const mat4& matrix) {
		vec3 result = {
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
		return result;
	}

	std::ostream& operator<<(std::ostream& stream, const vec3& vector) {
		stream << "vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return stream;
	}

} }
