#include "Renderer.h"

Renderer::Renderer() = default;

void Renderer::Initialize()
{
    shader = Shader("././Shaders/vert.glsl", "././Shaders/frag.glsl");
    shader.CreateShaderProgram();

    screenTriangle = ScreenTriangle();
    screenTriangle.InitScreenTriangle();
}

void Renderer::Render(int screenWidth, int screenHeight)
{
    width = screenWidth;
    height = screenHeight;

    glClearColor(0.2f, 0.40f, 0.8f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader.shaderProgram);
    glValidateProgram(shader.shaderProgram);

    glUniform2f(glGetUniformLocation(shader.shaderProgram, "iResolution"), (float)screenWidth, (float)screenHeight);
    glUniform1f(glGetUniformLocation(shader.shaderProgram, "iTime"), (float)glfwGetTime());

    screenTriangle.RenderScreenTriangle();
}

void Renderer::Destroy()
{
    
}
