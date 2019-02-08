#include "renderer.h"
#include "../drawing/mesh.h"
#include "../drawing/draw.h"
#include "../math/triangle.h"
#include "../math/vec3.h"
#include "../utils/utils.h"
#include "projector.h"
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>

namespace Engene
{
namespace Rendering
{

Renderer::Renderer()
{
    cubeTall = {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}};

    cubeLittle = {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.5f},
        {0.0f, 0.5f, 0.0f},
        {0.0f, 0.5f, 0.5f},
        {0.5f, 0.0f, 0.0f},
        {0.5f, 0.0f, 0.5f},
        {0.5f, 0.5f, 0.0f},
        {0.5f, 0.5f, 0.5f}};

    origin = {0.0f, 0.0f, 0.0f};

    basis = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, 0.1f, 0.0f},
        {0.0f, 0.0f, 1.0f}};
};

void Renderer::Render(GLFWwindow *win, float count)
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

    glClearColor(255.0f, 255.0f, 255.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Math::Vec3 objectLocation = {0.0f, 0.0f, 0.0f};
    Math::Vec3 viewingLocation = {4.0f, 2.0f, 0.0f};

    Projector projector = Projector(200, Math::Vec3 { WIDTH / 2, HEIGHT / 2, 0.0f });

    Math::Mat4 rotation = Projector::CreateRotationMatrix(Projector::Axis::Z, count / 4);

    auto transform = [rotation](Math::Vec3 vector) { 
        return std::map<std::string, Math::Vec3> { { "model", vector }, { "projection", vector * rotation } };
    };

    std::vector<std::map<std::string, Math::Vec3>> cubeTallProjected = map(cubeTall, transform);
    std::vector<std::map<std::string, Math::Vec3>> cubeLittleProjected = map(cubeLittle, transform);

    DrawVectorArray(projector, objectLocation, viewingLocation, cubeTallProjected);
    DrawVectorArray(projector, objectLocation, viewingLocation, cubeLittleProjected);
    DrawOrigin(projector, viewingLocation);

    return;
}

void Renderer::DrawOrigin(Projector projector, Math::Vec3 viewingLocation)
{
    // Project
    Math::Vec3 projectedOrigin = projector.Project(origin, origin, viewingLocation);
    Math::Vec3 projectedBasis1 = projector.Project(basis[0], origin, viewingLocation);
    Math::Vec3 projectedBasis2 = projector.Project(basis[1], origin, viewingLocation);
    Math::Vec3 projectedBasis3 = projector.Project(basis[2], origin, viewingLocation);

    // Draw
    Drawing::DrawBoard::DrawLine(projectedOrigin, projectedBasis1, Drawing::DrawBoard::Color::RED);
    Drawing::DrawBoard::DrawLine(projectedOrigin, projectedBasis2, Drawing::DrawBoard::Color::GREEN);
    Drawing::DrawBoard::DrawLine(projectedOrigin, projectedBasis3, Drawing::DrawBoard::Color::BLUE);
}

void Renderer::DrawVectorArray(Projector projector, Math::Vec3 objectLocation, Math::Vec3 viewingLocation, std::vector<std::map<std::string, Math::Vec3>> vectors)
{
    Math::Vec3 projectedOrigin = projector.Project(origin, origin, viewingLocation);
    for (auto vector : vectors)
    {
        // Project
        Math::Vec3 projectedVector = projector.Project(vector["projection"], objectLocation, viewingLocation);
        // Draw
        Drawing::DrawBoard::DrawCircle(projectedVector, 2, Drawing::DrawBoard::Color::BLACK);

        for (auto vector2 : vectors)
        {
            if (vector["model"] != vector2["model"]) 
            {
                Math::Vec3 projectedVector2 = projector.Project(vector2["projection"], objectLocation, viewingLocation);
                Drawing::DrawBoard::DrawLine(projectedVector, projectedVector2, Drawing::DrawBoard::Color::BLACK);
            }
        }
    }
}

} //  namespace Rendering
} // namespace Engene