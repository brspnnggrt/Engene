#pragma once

#include "../drawing/mesh.h"

namespace engene
{
namespace rendering
{

class renderer
{
  private:
    engene::drawing::mesh cube;

  public:
    int render();
};

}
}