#pragma once

#include "../math/mat4.h"
#include "../math/vec3.h"

namespace Engene
{
 namespace Rendering
{

class Projector
{
  public:
    enum Axis { X, Y, Z };
    static Engene::Math::Mat4 CreateTranslationMatrix(float x, float y, float z);
    static Engene::Math::Mat4 CreateRotationMatrix(Axis axis, float fTheta);
    static Engene::Math::Mat4 CreateScalingMatrix(float scale);
    static Engene::Math::Mat4 CreateProjectionMatrix(float d, float z);
    static Engene::Math::Vec3 Project(Engene::Math::Vec3 vector);
};

} //  namespace Rendering
} // namespace Engene