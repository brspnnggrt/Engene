#include "projector.h"

#include <math.h>

namespace Engene
{
namespace Rendering
{

Engene::Math::Mat4 Projector::CreateTranslationMatrix(float x, float y, float z) 
{
    Engene::Math::Mat4 matrix = 
    { 
        0.0f , 0.0f , 0.0f , x   ,
        0.0f , 0.0f , 0.0f , y   , 
        0.0f , 0.0f , 0.0f , z   , 
        0.0f , 0.0f , 0.0f , 1.0f 
    };
    return matrix;
}

Engene::Math::Mat4 Projector::CreateRotationMatrix(Axis axis, float theta)
{
    switch (axis)
    {
        case X:
        {
            // Rotation over angle theta around X-axis
            Engene::Math::Mat4 matrix = 
            { 
                1.0f, 0.0f         , 0.0f        , 0.0f,
                0.0f, cosf(theta)  , -sinf(theta) , 0.0f, 
                0.0f, sinf(theta) , cosf(theta) , 0.0f, 
                0.0f, 0.0f         , 0.0f        , 1.0f 
            };
            return matrix;
        } 
        case Y:
        {
            // Rotation over angle theta around Y-axis
            Engene::Math::Mat4 matrix = 
            { 
                cosf(theta)  , 0.0f, sinf(theta) , 0.0f,
                0.0f         , 1.0f, 0.0f        , 0.0f, 
                -sinf(theta) , 0.0f, cosf(theta) , 0.0f, 
                0.0f         , 0.0f, 0.0f        , 1.0f 
            };
            return matrix;
        } 
        case Z:
        {
            // Rotation over angle theta around Z-axis
            Engene::Math::Mat4 matrix = 
            { 
                cosf(theta) , -sinf(theta) , 0.0f , 0.0f,
                sinf(theta) , cosf(theta)  , 0.0f , 0.0f, 
                0.0f        , 0.0f         , 1.0f , 0.0f, 
                0.0f        , 0.0f         , 0.0f , 1.0f 
            };
            return matrix;
        } 
    }
}

Engene::Math::Mat4 Projector::CreateScalingMatrix(float scale)
{
    Engene::Math::Mat4 matrix = 
    { 
        scale, 0.0f , 0.0f , 0.0f,
        0.0f , scale, 0.0f , 0.0f, 
        0.0f , 0.0f , scale, 0.0f, 
        0.0f , 0.0f , 0.0f , 1.0f 
    };
    return matrix;
};

Engene::Math::Mat4 Projector::CreateProjectionMatrix(float d, float z) 
{
    Engene::Math::Mat4 matrix = 
    { 
        -d/z , 0.0f , 0.0f , 0.0f,
        0.0f , -d/z , 0.0f , 0.0f, 
        0.0f , 0.0f , -d/z , 0.0f, 
        0.0f , 0.0f , 0.0f , 1.0f 
    };
    return matrix;
}

} //  namespace Rendering
} // namespace Engene