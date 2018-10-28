#pragma once

#include "../math/triangle.h"
#include "../math/Vec2.h"

namespace Engene
{
namespace Drawing
{

void DrawLine(Engene::Math::Vec2 start, Engene::Math::Vec2 end);
void DrawTriangle(Engene::Math::Triangle triangle);

} // namespace drawing
} // namespace Engene