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

    for (auto vector : points)
    {
        // Project
        Math::Vec3 projectedVector = Projector::Project(vector);

        // Draw
        Drawing::DrawBoard::DrawCircle(projectedVector, 3, Drawing::DrawBoard::Color::WHITE);

        // Save
        projectedVectors.push_back(projectedVector);
    }

    std::vector<Math::Vec3> bottom;
    std::copy_if(points.begin(), points.end(), std::back_inserter(bottom), [](Math::Vec3 vector) { return vector.z == 0; });
    std::sort(bottom.begin(), bottom.end(), [](Math::Vec3 a, Math::Vec3 b) { return a.x + (2 * a.y); });

    for (std::size_t i = 0; i != bottom.size(); ++i) 
    {
        Math::Vec3 vector = bottom[i];
        Math::Vec3 projectedVector = Projector::Project(vector);

        Math::Vec3 vector2 = bottom[0];
        if (i + 1 != bottom.size())
            vector2 = bottom[i + 1];    

        Math::Vec3 projectedVector2 = Projector::Project(vector2);

        Drawing::DrawBoard::DrawLine(projectedVector, projectedVector2, Drawing::DrawBoard::Color::BLUE);
    }

    return 1;
}

} //  namespace Rendering
} // namespace Engene