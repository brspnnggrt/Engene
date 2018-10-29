#include "renderer.h"
#include "../drawing/mesh.h"
#include "../drawing/draw.h"
#include "../math/triangle.h"
#include "../math/Vec3.h"
#include "projector.h"
#include <GLFW/glfw3.h>
#include <math.h>

namespace Engene
{
namespace Rendering
{

Renderer::Renderer()
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

int Renderer::Render(GLFWwindow *win, int count)
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

    // float near = 0.1f;
    // float far = 1000.0f;
    // float fov = 90.0f;
    // float aspectRatio = (float)HEIGHT / (float)WIDTH;
    // float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.1459f); // convert from degrees to radiance


    fTheta += 1.0f * count / 1000;

    for (auto triangle : cube.triangles)
    {
        Engene::Math::Triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

        Engene::Math::Mat4 rotateZ = Projector::CreateRotationMatrix(Projector::Axis::Z, fTheta);
        Engene::Math::Mat4 rotateX = Projector::CreateRotationMatrix(Projector::Axis::X, fTheta);

        // Rotate in Z-Axis
        // triRotatedZ.points[0] = triangle.points[0] * rotateZ;
        // triRotatedZ.points[1] = triangle.points[1] * rotateZ;
        // triRotatedZ.points[2] = triangle.points[2] * rotateZ;

        // // Rotate in X-Axis
        // triRotatedZX.points[0] = triangle.points[0] * rotateX;
        // triRotatedZX.points[1] = triangle.points[1] * rotateX;
        // triRotatedZX.points[2] = triangle.points[2] * rotateX;

        // Offset into the screen
        // triTranslated = triRotatedZX;
        // triTranslated.points[0].z = triRotatedZX.points[0].z + 3.0f;
        // triTranslated.points[1].z = triRotatedZX.points[1].z + 3.0f;
        // triTranslated.points[2].z = triRotatedZX.points[2].z + 3.0f;

        // Project triangles from 3D --> 2D
        triProjected.points[0] = triTranslated.points[0] * Projector::CreateProjectionMatrix(90.0f, triTranslated.points[0].z);;
        triProjected.points[1] = triTranslated.points[1] * Projector::CreateProjectionMatrix(90.0f, triTranslated.points[1].z);;
        triProjected.points[2] = triTranslated.points[2] * Projector::CreateProjectionMatrix(90.0f, triTranslated.points[2].z);;

        
        // triProjected.points[0] *= Projector::CreateScalingMatrix(0.01);
        // triProjected.points[1] *= Projector::CreateScalingMatrix(0.01);
        // triProjected.points[2] *= Projector::CreateScalingMatrix(0.01);

        // Draw
        Engene::Drawing::DrawBoard::DrawTriangle(triProjected, Drawing::DrawBoard::Color::BLUE);

        // Math::Triangle triProjected2;

        // triProjected2.points[0] = triProjected.points[0];
        // triProjected2.points[1] = triProjected.points[1];
        // triProjected2.points[2] = triProjected.points[2];


        // triProjected2.points[0] *= Projector::CreateScalingMatrix(2);
        // triProjected2.points[1] *= Projector::CreateScalingMatrix(2);
        // triProjected2.points[2] *= Projector::CreateScalingMatrix(2);

        // Scale into view
        // triProjected.points[0].x += 1.0f;
        // triProjected.points[0].y += 1.0f;
        // triProjected.points[1].x += 1.0f;
        // triProjected.points[1].y += 1.0f;
        // triProjected.points[2].x += 1.0f;
        // triProjected.points[2].y += 1.0f;
        // triProjected.points[0].x *= 0.5f * (float)WIDTH;
        // triProjected.points[0].y *= 0.5f * (float)HEIGHT;
        // triProjected.points[1].x *= 0.5f * (float)WIDTH;
        // triProjected.points[1].y *= 0.5f * (float)HEIGHT;
        // triProjected.points[2].x *= 0.5f * (float)WIDTH;
        // triProjected.points[2].y *= 0.5f * (float)HEIGHT;

        // triProjected2.points[0].x += 1.0f;
        // triProjected2.points[0].y += 1.0f;
        // triProjected2.points[1].x += 1.0f;
        // triProjected2.points[1].y += 1.0f;
        // triProjected2.points[2].x += 1.0f;
        // triProjected2.points[2].y += 1.0f;
        // triProjected2.points[0].x *= 0.5f * (float)WIDTH;
        // triProjected2.points[0].y *= 0.5f * (float)HEIGHT;
        // triProjected2.points[1].x *= 0.5f * (float)WIDTH;
        // triProjected2.points[1].y *= 0.5f * (float)HEIGHT;
        // triProjected2.points[2].x *= 0.5f * (float)WIDTH;
        // triProjected2.points[2].y *= 0.5f * (float)HEIGHT;

        // Engene::Drawing::DrawBoard::DrawTriangle(triProjected2, Drawing::DrawBoard::Color::RED);
    }

    return 1;
}

} //  namespace Rendering
} // namespace Engene