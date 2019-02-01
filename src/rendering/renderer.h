#pragma once

#include <chrono>
#include "../drawing/mesh.h"
#include "../math/mat4.h"
#include "../rendering/projector.h"
#include <GLFW/glfw3.h>
#include <map>

namespace Engene
{
namespace Rendering
{

class Renderer
{
private:
  std::vector<Math::Vec3> cubeLittle;
  std::vector<Math::Vec3> cubeTall;
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
  void Render(GLFWwindow *win, float count);
  void DrawOrigin(Projector projector, Math::Vec3 viewingLocation);
  void DrawVectorArray(Projector projector, Math::Vec3 objectLocation, Math::Vec3 viewingLocation, std::vector<std::map<std::string, Math::Vec3>> vectors);
};

} //  namespace Rendering
} // namespace Engene