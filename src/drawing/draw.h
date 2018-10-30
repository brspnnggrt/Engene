#pragma once

#include "../math/triangle.h"
#include "../math/Vec2.h"

namespace Engene
{
namespace Drawing
{

class DrawBoard
{
  public:
  	struct Color
	{
	  public:
		float R;
		float G;
		float B;
		static const Color RED;
		static const Color GREEN;
		static const Color BLUE;
		static const Color WHITE;
		static const Color BLACK;
	};
	static void DrawCircle(Engene::Math::Vec3 point, int radius, Color color = Color::WHITE);
	static void DrawLine(Engene::Math::Vec3 start, Engene::Math::Vec3 end, Color color = Color::WHITE);
	static void DrawTriangle(Engene::Math::Triangle triangle, Color color = Color::WHITE);
};

} // namespace Drawing
} // namespace Engene