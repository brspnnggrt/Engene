#pragma once

#include "../math/mat4.h"
#include "../math/vec3.h"

namespace Engene
{
 namespace Rendering
{

class Projector
{
  private:
    float scaling = 1.0f;
    Math::Vec3 translation = { 0.0f, 0.0f, 0.0f };
    Math::Vec3 viewUpVector = { 0.0f, 0.0f, 1.0f };
  public:
    enum Axis { X, Y, Z };
    Projector();
    Projector(float scaling = 1.0f, Math::Vec3 translation = { 0.0f, 0.0f, 0.0f }, Math::Vec3 viewUpVector = { 0.0f, 0.0f, 1.0f });
    static Engene::Math::Mat4 CreateTranslationMatrix(float x, float y, float z);
    static Engene::Math::Mat4 CreateRotationMatrix(Axis axis, float fTheta);
    static Engene::Math::Mat4 CreateScalingMatrix(float scale);
    static Engene::Math::Mat4 CreateProjectionMatrix(float d, float z);
    Engene::Math::Vec3 Project(Math::Vec3 vector, Math::Vec3 objectLocation, Math::Vec3 viewingLocation);
};

} //  namespace Rendering
} // namespace Engene