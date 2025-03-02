// Beginning of Making My Shader Wallpaper Graphics Application - Shade-X

#define GLM_ENABLE_EXPERIMENTAL
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb/stb_image.h"
#include "iostream"
#include "Shader.h"
#include "ScreenTriangle.h"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* InitializeGlfw(GLuint width, GLuint height)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(width, height, "Shade-X", nullptr, nullptr);

    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1); 
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwMaximizeWindow(window);

    return window;
}

int main()
{
    GLuint width = 1600;
    GLuint height = 1000;
    GLFWwindow* window = InitializeGlfw(width, height);

    Shader defaultShader("./Shaders/default.vert", "./Shaders/default.frag");
    ScreenTriangle screenTriangle(defaultShader);

    GLint resLoc = glGetUniformLocation(defaultShader.shaderProgram, "iResolution");
    GLint timeLoc = glGetUniformLocation(defaultShader.shaderProgram, "iTime");

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(defaultShader.shaderProgram);

        glUniform2f(glGetUniformLocation(defaultShader.shaderProgram, "iResolution"), width, height);
        glUniform1f(glGetUniformLocation(defaultShader.shaderProgram, "iTime"), (float)glfwGetTime());

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        screenTriangle.RenderScreenTriangle();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}
