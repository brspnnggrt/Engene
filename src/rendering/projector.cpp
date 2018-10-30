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
        1.0f , 0.0f , 0.0f , x   ,
        0.0f , 1.0f , 0.0f , y   , 
        0.0f , 0.0f , 1.0f , z   , 
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

Engene::Math::Vec3 Projector::Project(Engene::Math::Vec3 vector) 
{
    // Convert to world coordinate system
    vector *= Projector::CreateTranslationMatrix(0.0f, 0.0f, 2.0f);

    // Convert to viewing coordinate system
    Engene::Math::Mat4 translateViewPoint = Projector::CreateTranslationMatrix(-4.0f, -2.0f, 0.0f);
    Engene::Math::Mat4 r = {
        -sqrt(5.0f)/5    , (2*sqrt(5.0f))/5 , 0 , 0 ,
        0                , 0                , 1 , 0 ,
        (2*sqrt(5.0f))/5 , sqrt(5.0f)/5     , 0 , 0 ,
        0                , 0                , 0 , 1
    };
    Engene::Math::Mat4 combinedMatrix = r * translateViewPoint;
    // projectedVector *= translateViewPoint;
    vector *= combinedMatrix;

    // Convert to 2D coordinate system (perspective projection from 3D to 2D)
    vector *= Projector::CreateProjectionMatrix(2.0f, vector.z);

    // Scale so cube is visible in screen 400x400
    vector *= Projector::CreateScalingMatrix(200.0f);

    // Center to screen
    vector *= Projector::CreateTranslationMatrix(200, 0, 0);

    return vector;
}

} //  namespace Rendering
} // namespace Engene