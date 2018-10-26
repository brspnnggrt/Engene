#include "draw.h"
#include "../math/vec2.h"
#include <GLFW/glfw3.h>

namespace engene { namespace drawing {

	void drawLine(engene::math::vec2 start, engene::math::vec2 end)
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPointSize(10);
        glLineWidth(2.5); 
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
        glVertex3f(start.x, end.y, 0.0);
        glVertex3f(end.x, end.y, 0.0);
        glEnd();
    }

} }