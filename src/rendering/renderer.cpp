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
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}};

    origin = {0.0f, 0.0f, 0.0f};

    basis = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 0.1f, 0.0f},
        {0.0f, 0.0f, 1.0f}};
};

int Renderer::Render(GLFWwindow *win, float count)
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

    Math::Vec3 objectLocation = {2.0f, 1.0f, -1.0f};
    Math::Vec3 viewingLocation = {4.0f, 2.0f, 0.0f};

    Projector projector = Projector(200, Math::Vec3 { WIDTH / 2, HEIGHT / 2, 0.0f });

    for (auto vector : points)
    {
        // Project
        Math::Vec3 projectedVector = projector.Project(vector, objectLocation, viewingLocation);
        // Draw
        Drawing::DrawBoard::DrawCircle(projectedVector, 2, Drawing::DrawBoard::Color::WHITE);
    }

    std::vector<std::function<bool(Math::Vec3 vector)>> tests = {
        [](Math::Vec3 vector) { return vector.z == 0; },
        [](Math::Vec3 vector) { return vector.z == 1; },
        [](Math::Vec3 vector) { return vector.x == 0; },
        [](Math::Vec3 vector) { return vector.x == 1; },
        [](Math::Vec3 vector) { return vector.y == 0; },
        [](Math::Vec3 vector) { return vector.y == 1; }};

    for (auto test : tests)
    {
        std::vector<Math::Vec3> bottom;
        std::copy_if(points.begin(), points.end(), std::back_inserter(bottom), test);

        Math::Vec3 projectedVector = projector.Project(bottom[0], objectLocation, viewingLocation);
        Math::Vec3 projectedVector2 = projector.Project(bottom[1], objectLocation, viewingLocation);
        Math::Vec3 projectedVector3 = projector.Project(bottom[2], objectLocation, viewingLocation);
        Math::Vec3 projectedVector4 = projector.Project(bottom[3], objectLocation, viewingLocation);
        Drawing::DrawBoard::DrawLine(projectedVector, projectedVector2, Drawing::DrawBoard::Color::WHITE);
        Drawing::DrawBoard::DrawLine(projectedVector, projectedVector3, Drawing::DrawBoard::Color::WHITE);
        Drawing::DrawBoard::DrawLine(projectedVector2, projectedVector4, Drawing::DrawBoard::Color::WHITE);
        Drawing::DrawBoard::DrawLine(projectedVector3, projectedVector4, Drawing::DrawBoard::Color::WHITE);
    }

    // Project
    Math::Vec3 projectedOrigin = projector.Project(origin, origin, viewingLocation);
    Math::Vec3 projectedBasis1 = projector.Project(basis[0], origin, viewingLocation);
    Math::Vec3 projectedBasis2 = projector.Project(basis[1], origin, viewingLocation);
    Math::Vec3 projectedBasis3 = projector.Project(basis[2], origin, viewingLocation);

    // Draw
    Drawing::DrawBoard::DrawLine(projectedOrigin, projectedBasis1, Drawing::DrawBoard::Color::RED);
    Drawing::DrawBoard::DrawLine(projectedOrigin, projectedBasis2, Drawing::DrawBoard::Color::GREEN);
    Drawing::DrawBoard::DrawLine(projectedOrigin, projectedBasis3, Drawing::DrawBoard::Color::BLUE);

    return 1;
}

} //  namespace Rendering
} // namespace Engene