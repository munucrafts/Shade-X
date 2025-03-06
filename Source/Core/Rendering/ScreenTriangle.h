#pragma once
#include "Shader.h"
#include "VAO.h"

class ScreenTriangle
{
public:
    ScreenTriangle();
    ~ScreenTriangle();
    void RenderScreenTriangle();
    void InitScreenTriangle();

private:
    VAO vao;
    VBO vbo;
};


