#include "ScreenTriangle.h"

ScreenTriangle::ScreenTriangle(Shader& shader)
{
    shaderMain = shader;
    SetupScreenTriangle();
}

ScreenTriangle::~ScreenTriangle()
{
    vao.Delete();
    vbo.Delete();
}

void ScreenTriangle::SetupScreenTriangle()
{
    float TriVertices[] = 
    {
         -1.0f, -1.0f,
          3.0f, -1.0f,
         -1.0f,  3.0f
    };

    vbo = VBO(TriVertices, sizeof(TriVertices));
    vao.Bind();
    vbo.Bind();
    vao.LinkAttrib(vbo, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
    vao.Unbind();
    vbo.Unbind();
}

void ScreenTriangle::RenderScreenTriangle()
{
    vao.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vao.Unbind();
}
