#include "Renderer.h"
#include "../Utils/CommonStructs.h"

Renderer::Renderer() = default;

void Renderer::Initialize()
{
    shader = Shader();
    shader.InitShaders();

    screenTriangle = ScreenTriangle();
    screenTriangle.InitScreenTriangle();
}

void Renderer::Render(int screenWidth, int screenHeight)
{
    glClearColor(0.2f, 0.40f, 0.8f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader.shaderProgram);
    glValidateProgram(shader.shaderProgram);

    glUniform2f(glGetUniformLocation(shader.shaderProgram, "iResolution"), (float)screenWidth, (float)screenHeight);
    glUniform1f(glGetUniformLocation(shader.shaderProgram, "iTime"), (float)glfwGetTime());

    ShaderUniforms currentUniforms = shader.GetUniforms();

    glUniform1f(glGetUniformLocation(shader.shaderProgram, "speed"), currentUniforms.speed);
    glUniform1f(glGetUniformLocation(shader.shaderProgram, "intensity"), currentUniforms.intensity);
    glUniform1f(glGetUniformLocation(shader.shaderProgram, "brightness"), currentUniforms.brightness);

    GLfloat color[4] = { currentUniforms.color.x, currentUniforms.color.y, currentUniforms.color.z, currentUniforms.color.w };
    glUniform4fv(glGetUniformLocation(shader.shaderProgram, "color"), 1, color);

    screenTriangle.RenderScreenTriangle();
}

void Renderer::Destroy()
{
    
}
