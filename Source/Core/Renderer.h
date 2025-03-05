#pragma once
#include "Rendering/Shader.h"
#include "Rendering/ScreenTriangle.h"

class Renderer
{
public:
    Renderer();
    void Initialize();
    void Render(int screenWidth, int screenHeight);
    void Destroy();

private:
    Shader shader;
    ScreenTriangle screenTriangle;
    int width, height;
};
