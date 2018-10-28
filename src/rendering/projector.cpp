#include "projector.h"

#include <math.h>

namespace Engene
{
namespace Rendering
{

Engene::Math::Mat4 Projector::CreateRotationMatrix(float fTheta, Axis axis)
{
    Engene::Math::Mat4 matrix = Engene::Math::Mat4();
    switch (axis)
    {
        case X:
        {
            // Rotation over angle theta around X-axis
            matrix.cells[0][0] = 1;
            matrix.cells[1][1] = cosf(fTheta * 0.5f);
            matrix.cells[1][2] = sinf(fTheta * 0.5f);
            matrix.cells[2][1] = -sinf(fTheta * 0.5f);
            matrix.cells[2][2] = cosf(fTheta * 0.5f);
            matrix.cells[3][3] = 1;
            break;
        } 
        case Y:
        {
            // Rotation over angle theta around Y-axis
            matrix.cells[0][0] = cosf(fTheta * 0.5);
            matrix.cells[0][2] = -sinf(fTheta * 0.5f);
            matrix.cells[1][1] = 1;
            matrix.cells[2][0] = sinf(fTheta * 0.5f);
            matrix.cells[2][2] = cosf(fTheta * 0.5f);
            matrix.cells[3][3] = 1;
            break;
        } 
        case Z:
        {
            // Rotation over angle theta around Z-axis
            matrix.cells[0][0] = cosf(fTheta);
            matrix.cells[0][1] = sinf(fTheta);
            matrix.cells[1][0] = -sinf(fTheta);
            matrix.cells[1][1] = cosf(fTheta);
            matrix.cells[2][2] = 1;
            matrix.cells[3][3] = 1;
            break;
        } 
    }
    return matrix;
}
} //  namespace Rendering
} // namespace Engene