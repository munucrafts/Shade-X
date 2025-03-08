#include "WindowHandler.h"

WindowHandler::WindowHandler()
{
    run = true;
    window = nullptr;
}

void WindowHandler::Initialize()
{
    InitializeGlfw(500, 500);
}

void WindowHandler::Destroy()
{
    if (window)
    {
        glfwDestroyWindow(window);
        window = nullptr;
    }

    run = false;
}

void WindowHandler::Render(int& width, int& height)
{
    glfwGetFramebufferSize(window, &width, &height);
}

bool WindowHandler::ShouldRun()
{
    if (glfwWindowShouldClose(window))
        run = false;

    return run;
}

GLFWwindow* WindowHandler::GetWindow()
{
    if (window) return window;

    std::cout << "Window not available" << std::endl;
    return nullptr;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void WindowHandler::InitializeGlfw(GLuint width, GLuint height)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        Destroy();
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    window = glfwCreateWindow(width, height, "Shade-X", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        Destroy();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        Destroy();
    }

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwMaximizeWindow(window);
}
