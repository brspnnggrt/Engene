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
        // SOUTH
        {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},

        // EAST
        {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},

        // NORTH
        {1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},

        // WEST
        {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},

        // TOP
        {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},

        // BOTTOM
        {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}};
};

int renderer::render(GLFWwindow *win, int count)
{
    std::chrono::system_clock::time_point nowTimeStamp = std::chrono::system_clock::now();
    std::chrono::duration<double> timepassed = renderTimeStamp - nowTimeStamp;
    if (timepassed != std::chrono::nanoseconds(0))
    {
        float fps = abs(std::chrono::milliseconds(1000) / timepassed);
        char str[8];
        sprintf(str, "Engene - %2.*f FPS", 0, fps);
        glfwSetWindowTitle(win, str);
    }
    renderTimeStamp = nowTimeStamp;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fFov = 90.0f;
    float fAspectRatio = (float)height / (float)width;
    float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.1459f); // convert from degrees to radiance

    projectionMatrix.cells[0][0] = fAspectRatio * fFovRad;
    projectionMatrix.cells[1][1] = fFovRad;
    projectionMatrix.cells[2][2] = fFar / (fFar - fNear);
    projectionMatrix.cells[3][2] = (-fFar * fNear) / (fFar - fNear);
    projectionMatrix.cells[2][3] = 1.0f;
    projectionMatrix.cells[3][3] = 0.0f;

    // Set up rotation matrices
    engene::math::mat4 matRotZ, matRotX;
    fTheta += 1.0f * count / 100;

    // Rotation Z
    matRotZ.cells[0][0] = cosf(fTheta);
    matRotZ.cells[0][1] = sinf(fTheta);
    matRotZ.cells[1][0] = -sinf(fTheta);
    matRotZ.cells[1][1] = cosf(fTheta);
    matRotZ.cells[2][2] = 1;
    matRotZ.cells[3][3] = 1;

    // Rotation X
    matRotX.cells[0][0] = 1;
    matRotX.cells[1][1] = cosf(fTheta * 0.5f);
    matRotX.cells[1][2] = sinf(fTheta * 0.5f);
    matRotX.cells[2][1] = -sinf(fTheta * 0.5f);
    matRotX.cells[2][2] = cosf(fTheta * 0.5f);
    matRotX.cells[3][3] = 1;

    for (auto triangle : cube.triangles)
    {
        engene::math::triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

        // Rotate in Z-Axis
        triRotatedZ.points[0] = triangle.points[0] * matRotZ;
        triRotatedZ.points[1] = triangle.points[1] * matRotZ;
        triRotatedZ.points[2] = triangle.points[2] * matRotZ;

        // Rotate in X-Axis
        triRotatedZX.points[0] = triangle.points[0] * matRotX;
        triRotatedZX.points[1] = triangle.points[1] * matRotX;
        triRotatedZX.points[2] = triangle.points[2] * matRotX;

        // Offset into the screen
        triTranslated = triRotatedZX;
        triTranslated.points[0].z = triRotatedZX.points[0].z + 3.0f;
        triTranslated.points[1].z = triRotatedZX.points[1].z + 3.0f;
        triTranslated.points[2].z = triRotatedZX.points[2].z + 3.0f;

        // Project triangles from 3D --> 2D
        triProjected.points[0] = triTranslated.points[0] * projectionMatrix;
        triProjected.points[1] = triTranslated.points[1] * projectionMatrix;
        triProjected.points[2] = triTranslated.points[2] * projectionMatrix;

        // Scale into view
        triProjected.points[0].x += 1.0f;
        triProjected.points[0].y += 1.0f;
        triProjected.points[1].x += 1.0f;
        triProjected.points[1].y += 1.0f;
        triProjected.points[2].x += 1.0f;
        triProjected.points[2].y += 1.0f;
        triProjected.points[0].x *= 0.5f * (float)width;
        triProjected.points[0].y *= 0.5f * (float)height;
        triProjected.points[1].x *= 0.5f * (float)width;
        triProjected.points[1].y *= 0.5f * (float)height;
        triProjected.points[2].x *= 0.5f * (float)width;
        triProjected.points[2].y *= 0.5f * (float)height;

        engene::drawing::drawTriangle(triProjected);
    }

    return 1;
}

} // namespace rendering
} // namespace engene