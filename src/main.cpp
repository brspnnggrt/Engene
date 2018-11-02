#include <iostream>
#include <GLFW/glfw3.h>
#include "math/vec2.h"
#include "drawing/draw.h"
#include "rendering/renderer.h"
#include <thread>
#include <chrono>

#ifndef NATIVE_COMPILER
#ifndef __INTELLISENSE__
#include <emscripten.h>
#endif
#endif

GLFWwindow* window;
float count = 0.0f;
Engene::Rendering::Renderer renderer = Engene::Rendering::Renderer();

void StartRenderingEngene() {
    /* Render here */
    count += 0.05f;
    int a = renderer.Render(window, count);
    
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

void EmscriptenRender()
{

    #ifndef NATIVE_COMPILER
    #ifndef __INTELLISENSE__
    emscripten_set_main_loop(StartRenderingEngene, 0, 1);
    #endif
    #endif
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

    #ifdef NATIVE_COMPILER
	    glfwSwapInterval(1);
    #endif

	// Set up viewport
	glViewport(0, 0, Engene::Rendering::Renderer::WIDTH, Engene::Rendering::Renderer::HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
	glOrtho(0.0, Engene::Rendering::Renderer::WIDTH, 0.0, Engene::Rendering::Renderer::HEIGHT, 0.0, 1.0); // this creates a canvas you can do 2D drawing on

    #ifndef NATIVE_COMPILER
        EmscriptenRender();
    #else
        while (!glfwWindowShouldClose(window)) 
        {
            StartRenderingEngene();
        }
    #endif

    glfwTerminate();

    return 0;
}