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
    static Engene::Math::Mat4 CreateRotationMatrix(Axis axis, float fTheta);
    static Engene::Math::Mat4 CreateScalingMatrix(float scale);
};

} //  namespace Rendering
} // namespace Engene