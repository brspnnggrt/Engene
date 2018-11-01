#include <iostream>
#include <GLFW/glfw3.h>
#include "math/vec2.h"
#include "drawing/draw.h"
#include "rendering/renderer.h"
#include <thread>
#include <chrono>
#include <emscripten.h>

GLFWwindow* window;
float count = 0;
Engene::Rendering::Renderer renderer;

void render()
{
       
    /* Render here */
    count += 0.05f;
    int a = renderer.Render(window, count);
    
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

int main(void)
{

    printf("This should be output to JavaScript console.log if run on web.");
    
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
	// glfwSwapInterval(0);

	// Set up viewport
	glViewport(0, 0, Engene::Rendering::Renderer::WIDTH, Engene::Rendering::Renderer::HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
	glOrtho(0.0, Engene::Rendering::Renderer::WIDTH, 0.0, Engene::Rendering::Renderer::HEIGHT, 0.0, 1.0); // this creates a canvas you can do 2D drawing on

    emscripten_set_main_loop(render, 0, 1);

    glfwTerminate();

    return 0;
}