#pragma once
#include "../Core/WindowHandler.h"
#include "../Core/Renderer.h"

class ShadeX
{
private:
	WindowHandler winHandler;
	Renderer renderer;

public:
	ShadeX();
	bool Initialize();
	void Run();
	void Shutdown();
};

