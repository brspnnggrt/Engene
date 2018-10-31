#include "projector.h"

#include <math.h>

namespace Engene
{
namespace Rendering
{

Projector::Projector(float scaling, Math::Vec3 translation, Math::Vec3 viewUpVector) : scaling(scaling), translation(translation), viewUpVector(viewUpVector)
{
}

Math::Mat4 Projector::CreateTranslationMatrix(float x, float y, float z) 
{
    Math::Mat4 matrix = 
    { 
        1.0f , 0.0f , 0.0f , x   ,
        0.0f , 1.0f , 0.0f , y   , 
        0.0f , 0.0f , 1.0f , z   , 
        0.0f , 0.0f , 0.0f , 1.0f 
    };
    return matrix;
}

Math::Mat4 Projector::CreateRotationMatrix(Axis axis, float theta)
{
    switch (axis)
    {
        case X:
        {
            // Rotation over angle theta around X-axis
            Math::Mat4 matrix = 
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
            Math::Mat4 matrix = 
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
            Math::Mat4 matrix = 
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

Math::Mat4 Projector::CreateScalingMatrix(float scale)
{
    Math::Mat4 matrix = 
    { 
        scale, 0.0f , 0.0f , 0.0f,
        0.0f , scale, 0.0f , 0.0f, 
        0.0f , 0.0f , scale, 0.0f, 
        0.0f , 0.0f , 0.0f , 1.0f 
    };
    return matrix;
};

Math::Mat4 Projector::CreateProjectionMatrix(float d, float z) 
{
    Math::Mat4 matrix = 
    { 
        -d/z , 0.0f , 0.0f , 0.0f,
        0.0f , -d/z , 0.0f , 0.0f, 
        0.0f , 0.0f , -d/z , 0.0f, 
        0.0f , 0.0f , 0.0f , 1.0f 
    };
    return matrix;
}

Math::Vec3 Projector::Project(Math::Vec3 vector, Math::Vec3 objectLocation, Math::Vec3 viewingLocation) 
{
    // Convert to world coordinate system
    vector *= Projector::CreateTranslationMatrix(objectLocation.x, objectLocation.y, objectLocation.z); // Where do you want the object from which this vector is part of?

    // Convert to viewing coordinate system
    Math::Mat4 translateViewPoint = Projector::CreateTranslationMatrix(-viewingLocation.x, -viewingLocation.y, -viewingLocation.z); // Where are you looking from?
    
    Math::Vec3 w = Math::Vec3::GetUnitVector(viewingLocation);
    Math::Vec3 u = Math::Vec3::CrossProduct(viewUpVector, w);
    u = Math::Vec3::GetUnitVector(u);
    Math::Vec3 v = Math::Vec3::GetUnitVector(viewUpVector);
    Math::Mat4 r = {
        u.x , u.y , u.z , 0 ,
        v.x , v.y , v.z , 0 ,
        w.x , w.y , w.z , 0 ,
        0   , 0   , 0   , 1
    }; 

    vector *= r * translateViewPoint;

    // Convert to 2D coordinate system (perspective projection from 3D to 2D)
    vector *= Projector::CreateProjectionMatrix(2.0f, vector.z);

    // Apply scaling & translation
    vector *= Projector::CreateScalingMatrix(scaling);
    vector *= Projector::CreateTranslationMatrix(translation.x, translation.y, translation.z); // Can be used to center to screen

    return vector;
}

} //  namespace Rendering
} // namespace Engene