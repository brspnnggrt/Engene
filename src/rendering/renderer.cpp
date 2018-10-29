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
    points = {
        { 0.0f , 0.0f , 0.0f } , { 0.0f , 0.0f , 1.0f } , { 0.0f , 1.0f , 0.0f } , { 0.0f , 1.0f , 1.0f },
        { 1.0f , 0.0f , 0.0f } , { 1.0f , 0.0f , 1.0f } , { 1.0f , 1.0f , 0.0f } , { 1.0f , 1.0f , 1.0f },
    };
    // cube.triangles = {
    //     // SOUTH
    //     {0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f},
    //     {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f},

    //     // EAST
    //     {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f},
    //     {1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},

    //     // NORTH
    //     {1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f},
    //     {1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f},

    //     // WEST
    //     {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f},
    //     {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},

    //     // TOP
    //     {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f},
    //     {0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},

    //     // BOTTOM
    //     {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
    //     {1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f}};
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


    theta += 1.0f * count / 1000;

    for (auto vector : points)
    {
        Engene::Math::Vec3 projectedVector = vector;

        // Convert to world coordinate system
        projectedVector *= Projector::CreateTranslationMatrix(0.0f, 0.0f, 2.0f);

        // Convert to viewing coordinate system
        Engene::Math::Mat4 translateViewPoint = Projector::CreateTranslationMatrix(-4.0f, -2.0f, 0.0f);
        Engene::Math::Mat4 r = {
          -1/5 * sqrt(5) , 2/5 * sqrt(5) , 0 , 0               ,
          0              , 0             , 1 , 0               ,
          2/5 * sqrt(5)  , 1/5 * sqrt(5) , 0 , -10/5 * sqrt(5) ,
          0              , 0             , 0 , 1
        };
        projectedVector *= translateViewPoint;
        projectedVector *= r;

        // Convert to 2D coordinate system (perspective projection from 3D to 2D)
        projectedVector *= Projector::CreateProjectionMatrix(2.0f, -2 * sqrt(5));
        projectedVector *= Projector::CreateProjectionMatrix(2.0f, -2 * sqrt(5));
        projectedVector *= Projector::CreateProjectionMatrix(2.0f, -2 * sqrt(5));

        // Draw
        Engene::Math::Vec3 origin = {0.0f, 0.0f, 0.0f};
        Engene::Drawing::DrawBoard::DrawLine(origin, projectedVector, Drawing::DrawBoard::Color::BLUE);
    }

    return 1;
}

} //  namespace Rendering
} // namespace Engene