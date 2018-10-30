#include "draw.h"
#include "../math/Vec2.h"
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Engene
{
namespace Drawing
{

const DrawBoard::Color DrawBoard::Color::RED = Color{1, 0, 0};
const DrawBoard::Color DrawBoard::Color::GREEN = Color{0, 1, 0};
const DrawBoard::Color DrawBoard::Color::BLUE = Color{0, 0, 1};
const DrawBoard::Color DrawBoard::Color::WHITE = Color{1, 1, 1};
const DrawBoard::Color DrawBoard::Color::BLACK = Color{0, 0, 0};

void DrawBoard::DrawCircle(Engene::Math::Vec3 point, int radius, Color color)
{
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * M_PI;

	glColor3f(color.R, color.G, color.B);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(point.x, point.y); // center of circle
	for (i = 0; i <= triangleAmount; i++)
	{
		glVertex2f(
			point.x + (radius * cos(i * twicePi / triangleAmount)),
			point.y + (radius * sin(i * twicePi / triangleAmount)));
	}
	glEnd();
}

void DrawBoard::DrawLine(Engene::Math::Vec3 start, Engene::Math::Vec3 end, Color color)
{
	glPointSize(10);
	glLineWidth(2.5);
	glColor3f(color.R, color.G, color.B);
	glBegin(GL_LINES);
	glVertex3f(start.x, start.y, 0.0);
	glVertex3f(end.x, end.y, 0.0);
	glEnd();
}

void DrawBoard::DrawTriangle(Engene::Math::Triangle triangle, Color color)
{
	DrawLine(triangle.points[0], triangle.points[1], color);
	DrawLine(triangle.points[1], triangle.points[2], color);
	DrawLine(triangle.points[2], triangle.points[0], color);
}

} // namespace Drawing
} // namespace Engene