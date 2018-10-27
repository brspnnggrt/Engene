#include "renderer.h"
#include "../drawing/mesh.h"
#include "../drawing/draw.h"
#include "../math/triangle.h"
#include "../math/vec3.h"
#include <GLFW/glfw3.h>
#include <math.h>

namespace engene
{
namespace rendering
{

float renderer::width = 400;
float renderer::height = 400;

renderer::renderer()
{
    cube.triangles = {
        {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f}};
};

int renderer::render()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fFov = 90.0f;
    float fAspectRatio = (float) height / (float) width;
    float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.1459f); // convert from degrees to radiance

    projectionMatrix.cells[0][0] = fAspectRatio * fFovRad;
    projectionMatrix.cells[1][1] = fFovRad;

    for (auto triangle : cube.triangles)
    {
        engene::math::triangle triProjected;

        triProjected.points[0] = triangle.points[0] * projectionMatrix;
        triProjected.points[1] = triangle.points[1] * projectionMatrix;
        triProjected.points[2] = triangle.points[2] * projectionMatrix;

        engene::drawing::drawTriangle(triProjected);
    }

    // glPointSize(10);
    // glLineWidth(2.5);
    // glColor3f(1.0, 0.0, 0.0);
    // glBegin(GL_LINES);
    // glVertex3f(start.x, end.y, 0.0);
    // glVertex3f(end.x, end.y, 0.0);
    // glEnd();
    return 1;
}

} // namespace rendering
} // namespace engene