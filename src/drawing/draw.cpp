#include "draw.h"
#include "../math/vec2.h"
#include <GLFW/glfw3.h>

namespace engene
{
namespace drawing
{

void drawLine(engene::math::vec3 start, engene::math::vec3 end)
{
    glPointSize(10);
    glLineWidth(2.5);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(start.x, start.y, 0.0);
    glVertex3f(end.x, end.y, 0.0);
    glEnd();
}

void drawTriangle(engene::math::triangle triangle)
{
    drawLine(triangle.points[0], triangle.points[1]);
    drawLine(triangle.points[1], triangle.points[2]);
    drawLine(triangle.points[2], triangle.points[0]);
}

} // namespace drawing
} // namespace engene