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
  Engene::Drawing::Mesh cube;
  Engene::Math::Mat4 projectionMatrix;

  float fTheta;
  std::chrono::system_clock::time_point renderTimeStamp = std::chrono::system_clock::now();

public:
  static constexpr float WIDTH = 1600; 
  static constexpr float HEIGHT = 1200;
  Renderer();
  int Render(GLFWwindow* win, int count);
};

} //  namespace Rendering
} // namespace Engene