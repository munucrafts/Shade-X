#pragma once
#include "VAO.h"
#include "Shader.h"

class ScreenTriangle
{
public:
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


