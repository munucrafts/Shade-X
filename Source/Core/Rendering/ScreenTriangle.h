#pragma once
#include "Shader.h"
#include "VAO.h"

class ScreenTriangle
{
public:
    ScreenTriangle();
    ScreenTriangle(Shader& shader);
    ~ScreenTriangle();
    void RenderScreenTriangle();

private:
    VAO vao;
    VBO vbo;
    Shader shaderMain;

private:
    void SetupScreenTriangle();
};


