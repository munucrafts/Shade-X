#include "ShadeX.h"

ShadeX::ShadeX()
{}

bool ShadeX::Initialize()
{
    winHandler.Initialize();
    renderer.Initialize();

    return true;
}

void ShadeX::Run()
{
    int screenWidth = 500;
    int screenHeight = 500;

    while (winHandler.ShouldRun())
    {
        winHandler.GetFrameBufferSize(screenWidth, screenHeight);
        renderer.Render(screenWidth, screenHeight);

        glfwSwapBuffers(winHandler.GetWindow());
        glfwPollEvents();
    }
}

void ShadeX::Shutdown()
{
    renderer.Destroy();
    winHandler.Destroy();
}
