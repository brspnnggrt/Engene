#pragma once

#include "../math/mat4.h"

namespace Engene
{
 namespace Rendering
{

class Projector
{
  public:
    enum Axis { X, Y, Z };
    static Engene::Math::Mat4 CreateRotationMatrix(float fTheta, Axis axis);
};

} //  namespace Rendering
} // namespace Engene