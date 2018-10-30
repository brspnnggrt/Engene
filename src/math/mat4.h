#pragma once

namespace Engene
{
namespace Math
{

struct Mat4
{
	float cells[4][4] = {{0}}; // row by column, initialize all to 0

	friend Mat4 operator*(Mat4 left, const Mat4 &right);
};

} // namespace Math
} // namespace Engene
