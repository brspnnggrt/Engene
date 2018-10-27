#pragma once

#include "../math/triangle.h"
#include "../math/vec2.h"

namespace engene
{
namespace drawing
{

void drawLine(engene::math::vec2 start, engene::math::vec2 end);
void drawTriangle(engene::math::triangle triangle);

} // namespace drawing
} // namespace engene