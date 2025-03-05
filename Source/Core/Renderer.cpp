#include "Renderer.h"

Renderer::Renderer() = default;

void Renderer::Initialize()
{
    shader = Shader("./Shaders/vert.glsl", "./Shaders/frag.glsl");
    screenTriangle = ScreenTriangle(shader);
}

void Renderer::Render(int screenWidth, int screenHeight)
{
    width = screenWidth;
    height = screenHeight;

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glUseProgram(shader.shaderProgram);
    glUniform2f(glGetUniformLocation(shader.shaderProgram, "iResolution"), (float)screenWidth, (float)screenHeight);
    glUniform1f(glGetUniformLocation(shader.shaderProgram, "iTime"), (float)glfwGetTime());

    screenTriangle.RenderScreenTriangle();
}

void Renderer::Destroy()
{
    //delete shader;
    //shader = nullptr;
}
