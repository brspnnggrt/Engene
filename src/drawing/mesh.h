#pragma once

#include <vector>
#include <iostream>
#include "../math/triangle.h"

namespace Engene
{
namespace Drawing
{

struct Mesh
{
	std::vector<Engene::Math::Triangle> triangles;
};

} // namespace Drawing
} // namespace Engene