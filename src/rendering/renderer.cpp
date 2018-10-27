#include "renderer.h"
#include "../drawing/mesh.h"
#include "../math/triangle.h"

namespace engene { namespace rendering {

    

    renderer::renderer() {

        engene::math::vec3 vector = { 1.0f, 0.1f, 0.4f };

        engene::math::triangle triangle = { { { 1.0f, 0.1f, 0.4f } , { 1.0f, 0.1f, 0.4f }, { 1.0f, 0.1f, 0.4f } } };

        engene::drawing::mesh meshCube;

        meshCube.triangles = {
            { 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		    { 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f }
        };
    };

	int renderer::render()
    {
        return 1;
    }

} }