#pragma once

#include "../drawing/mesh.h"
#include "../math/mat4.h"

namespace engene
{
namespace rendering
{

class renderer
{
private:
  engene::drawing::mesh cube;
  engene::math::mat4 projectionMatrix;

public:
  static float width;
  static float height;
  renderer();
  int render();
};

} // namespace rendering
} // namespace engene