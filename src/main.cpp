#include <iostream>
#include <GLFW/glfw3.h>
#include "math/vec2.h"
#include "drawing/draw.h"
#include "rendering/renderer.h"

// void render(int count)
// {
//     if (count == 0)
//         count = 1;
//     engene::math::vec2 start(5 * count, 0);
//     engene::math::vec2 end(200 % count, 500 % count);
//     engene::drawing::drawLine(start, end);
// }

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Set up viewport
	glViewport(0, 0, 400, 400);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
	glOrtho(0.0, 400.0, 0.0, 400.0, 0.0, 1.0); // this creates a canvas you can do 2D drawing on

    int count = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		engene::rendering::renderer fff;
        int a = fff.render();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();

        count++;
    }

    glfwTerminate();
    return 0;
}