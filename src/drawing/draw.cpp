#include "draw.h"
#include "../math/Vec2.h"
#include <GLFW/glfw3.h>

namespace Engene
{
namespace Drawing
{

void DrawLine(Engene::Math::Vec3 start, Engene::Math::Vec3 end)
{
    glPointSize(10);
    glLineWidth(2.5);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(start.x, start.y, 0.0);
    glVertex3f(end.x, end.y, 0.0);
    glEnd();
}

void DrawTriangle(Engene::Math::Triangle triangle)
{
    DrawLine(triangle.points[0], triangle.points[1]);
    DrawLine(triangle.points[1], triangle.points[2]);
    DrawLine(triangle.points[2], triangle.points[0]);
}

} // namespace drawing
} // namespace Engene