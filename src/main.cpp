#include <iostream>
#include <GLFW/glfw3.h>
#include "math/vec2.h"
#include "drawing/draw.h"
#include "rendering/renderer.h"
#include <thread>
#include <chrono>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(Engene::Rendering::Renderer::WIDTH, Engene::Rendering::Renderer::HEIGHT, "Engene", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Set up viewport
	glViewport(0, 0, Engene::Rendering::Renderer::WIDTH, Engene::Rendering::Renderer::HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
	glOrtho(0.0, Engene::Rendering::Renderer::WIDTH, 0.0, Engene::Rendering::Renderer::HEIGHT, 0.0, 1.0); // this creates a canvas you can do 2D drawing on

    float count = 0;
    Engene::Rendering::Renderer renderer;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        /* Render here */
        count += 0.05f;
        int a = renderer.Render(window, count);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    };

    glfwTerminate();

    return 0;
}