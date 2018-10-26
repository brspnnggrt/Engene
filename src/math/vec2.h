#pragma once

#include <iostream>

namespace engene { namespace math {

	struct vec2
	{
		float x, y;

		vec2();
		vec2(const float& x, const float& y);

		vec2& add(const vec2& other);
		vec2& subscract(const vec2& other);
		vec2& multiply(const vec2& other);
		vec2& divide(const vec2& other);

		friend vec2 operator+(vec2 left, const vec2& right);
		friend vec2 operator-(vec2 left, const vec2& right);
		friend vec2 operator*(vec2 left, const vec2& right);
		friend vec2 operator/(vec2 left, const vec2& right);

		bool operator==(vec2& other);
		bool operator!=(vec2& other);

		vec2& operator+=(const vec2& other);
		vec2& operator-=(const vec2& other);
		vec2& operator*=(const vec2& other);
		vec2& operator/=(const vec2& other);

		friend std::ostream& operator<<(std::ostream&, const vec2& vector);
	};

} }
