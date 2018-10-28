#pragma once

#include <chrono>
#include "../drawing/mesh.h"
#include "../math/mat4.h"
#include <GLFW/glfw3.h>

namespace engene
{
namespace rendering
{

class renderer
{
private:
  engene::drawing::mesh cube;
  engene::math::mat4 projectionMatrix;

  float fTheta;
  std::chrono::system_clock::time_point renderTimeStamp = std::chrono::system_clock::now();

public:
  static float width;
  static float height;
  renderer();
  int render(GLFWwindow* win, int count);
};

} // namespace rendering
} // namespace engene