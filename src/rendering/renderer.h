#pragma once

#include <chrono>
#include "../drawing/mesh.h"
#include "../math/Mat4.h"
#include <GLFW/glfw3.h>

namespace Engene
{
 namespace Rendering
{

class Renderer
{
private:
  std::vector<Math::Vec3> points;
  Math::Vec3 origin;
  std::vector<Math::Vec3> basis;
  Engene::Drawing::Mesh cube;
  Engene::Math::Mat4 projectionMatrix;

  float theta;
  std::chrono::system_clock::time_point renderTimeStamp = std::chrono::system_clock::now();

public:
  static constexpr float WIDTH = 400; 
  static constexpr float HEIGHT = 400;
  Renderer();
  int Render(GLFWwindow* win, float count);
};

} //  namespace Rendering
} // namespace Engene