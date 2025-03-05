// Beginning of Making My Shader Wallpaper Graphics Application - Shade-X

#define GLM_ENABLE_EXPERIMENTAL
#include "Utils/Commons.h"
#include "App/ShadeX.h"
#include "stb/stb_image.h"
#include <iostream>

int main()
{
    ShadeX shadexApp;

    if (!shadexApp.Initialize())
    {
        std::cerr << "Error: Failed to initialize Shade-X!" << std::endl;
        return EXIT_FAILURE;
    }

    shadexApp.Run();
    shadexApp.Shutdown();

    return EXIT_SUCCESS;
}
