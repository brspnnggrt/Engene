#include "renderer.h"
#include "../drawing/mesh.h"
#include "../drawing/draw.h"
#include "../math/triangle.h"
#include "../math/Vec3.h"
#include "projector.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>

namespace Engene
{
namespace Rendering
{

Renderer::Renderer()
{
    points = {
        { 0.0f , 0.0f , 0.0f } , { 0.0f , 0.0f , 1.0f } , { 0.0f , 1.0f , 0.0f } , { 0.0f , 1.0f , 1.0f } ,
        { 1.0f , 0.0f , 0.0f } , { 1.0f , 0.0f , 1.0f } , { 1.0f , 1.0f , 0.0f } , { 1.0f , 1.0f , 1.0f } ,
    };
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

    theta += 1.0f * count / 1000;

    std::vector<Math::Vec3> projectedVectors;

    Math::Vec3 objectLocation = { 0.0f, 0.0f, 2.0f };
    Math::Vec3 viewingLocation = { 4.0f, 2.0f, 0.0f };

    for (auto vector : points)
    {
        // Project
        Math::Vec3 projectedVector = Projector::Project(vector, objectLocation, viewingLocation);

        // Draw
        Drawing::DrawBoard::DrawCircle(projectedVector, 5, Drawing::DrawBoard::Color::RED);

        // Save
        projectedVectors.push_back(projectedVector);
    }

    std::vector<std::function<bool(Math::Vec3 vector)>> tests = {
        [](Math::Vec3 vector) { return vector.z == 0; },
        [](Math::Vec3 vector) { return vector.z == 1; },
        [](Math::Vec3 vector) { return vector.x == 0; },
        [](Math::Vec3 vector) { return vector.x == 1; },
        [](Math::Vec3 vector) { return vector.y == 0; },
        [](Math::Vec3 vector) { return vector.y == 1; }
    };

    for (auto test : tests) 
    {
        std::vector<Math::Vec3> bottom;
        std::copy_if(points.begin(), points.end(), std::back_inserter(bottom), test);
        // std::sort(bottom.begin(), bottom.end(), [](Math::Vec3 a, Math::Vec3 b) { return a.x + a.y; });

        Math::Vec3 projectedVector = Projector::Project(bottom[0], objectLocation, viewingLocation);
        Math::Vec3 projectedVector2 = Projector::Project(bottom[1], objectLocation, viewingLocation);
        Math::Vec3 projectedVector3 = Projector::Project(bottom[2], objectLocation, viewingLocation);
        Math::Vec3 projectedVector4 = Projector::Project(bottom[3], objectLocation, viewingLocation);
        Drawing::DrawBoard::DrawLine(projectedVector, projectedVector2, Drawing::DrawBoard::Color::WHITE);
        Drawing::DrawBoard::DrawLine(projectedVector, projectedVector3, Drawing::DrawBoard::Color::WHITE);
        Drawing::DrawBoard::DrawLine(projectedVector2, projectedVector4, Drawing::DrawBoard::Color::WHITE);
        Drawing::DrawBoard::DrawLine(projectedVector3, projectedVector4, Drawing::DrawBoard::Color::WHITE);
    }
    

    return 1;
}

} //  namespace Rendering
} // namespace Engene