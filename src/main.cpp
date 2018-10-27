#include <iostream>
#include <GLFW/glfw3.h>
#include "math/vec2.h"
#include "drawing/draw.h"
#include "rendering/renderer.h"

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
	glViewport(0, 0, engene::rendering::renderer::width, engene::rendering::renderer::height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
	glOrtho(0.0, engene::rendering::renderer::width, 0.0, engene::rendering::renderer::height, 0.0, 1.0); // this creates a canvas you can do 2D drawing on

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