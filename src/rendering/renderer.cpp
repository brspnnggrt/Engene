#include "renderer.h"
#include "../drawing/mesh.h"
#include "../math/triangle.h"

namespace engene { namespace rendering {

    renderer::renderer() {

        cube.triangles = {
            { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		    { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f }
        };
    };

	int renderer::render()
    {
        return 1;
    }

} }