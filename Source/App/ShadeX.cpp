#include "ShadeX.h"

ShadeX::ShadeX() = default;

void ShadeX::Initialize()
{
    winHandler.Initialize();
    renderer.Initialize();
    uiHandler.Initialize(winHandler.GetWindow());
}

void ShadeX::Run()
{
    int screenWidth = 500;
    int screenHeight = 500;

    while (winHandler.ShouldRun())
    {
        winHandler.Render(screenWidth, screenHeight);
        renderer.Render(screenWidth, screenHeight);
        uiHandler.Render(&renderer.shader);

        glfwSwapBuffers(winHandler.GetWindow());
        glfwPollEvents();
    }
}

void ShadeX::Shutdown()
{
    renderer.Destroy();
    winHandler.Destroy();
    uiHandler.Destroy();

    glfwTerminate();
}
