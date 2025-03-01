// Beginning of Making My Shader Wallpaper Graphics Application - Shade-X

#define GLM_ENABLE_EXPERIMENTAL
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"
#include "iostream"

GLFWwindow* InitializeGlfw(GLuint width, GLuint height)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(1);
    }

    // Configure OpenGL version (3.3 core profile)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(width, height, "Shade-X", nullptr, nullptr);
    glfwMaximizeWindow(window);

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }

    // Make window current context
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    gladLoadGL();

    // Enabling depth testing
    glEnable(GL_DEPTH_TEST);

    // Return window reference
    return window;
}

int main()
{
    // Initialize GLFW and create a window
    GLuint width = 1600;
    GLuint height = 1000;
    GLFWwindow* window = InitializeGlfw(width, height);

    // Enter the render loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear the screen
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate
    glfwTerminate();

	return 0;
}