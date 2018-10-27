#pragma once

#include <vector>
#include <iostream>
#include "../math/triangle.h"

namespace engene { namespace drawing {

	struct mesh
	{
		std::vector<engene::math::triangle> triangles;
    };

} }