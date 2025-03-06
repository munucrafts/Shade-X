#include "ScreenTriangle.h"

ScreenTriangle::ScreenTriangle() = default;

ScreenTriangle::~ScreenTriangle()
{
    vao.Delete();
    vbo.Delete();
}

void ScreenTriangle::InitScreenTriangle()
{
    float triVertices[] = 
        { 
            -1.0f, -1.0f, 
             3.0f, -1.0f, 
            -1.0f,  3.0f 
        };

    vao.InitVao();
    vbo.InitVbo(triVertices, sizeof(triVertices));
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
