#pragma once
#include "../Core/WindowHandler.h"
#include "../Core/Renderer.h"
#include "../Core/UiHandler.h"

class ShadeX
{
private:
	WindowHandler winHandler;
	Renderer renderer;
	UiHandler uiHandler;

public:
	ShadeX();
	void Initialize();
	void Run();
	void Shutdown();
};

