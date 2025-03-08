#pragma once
#include "..\Utils\Commons.h"

class WindowHandler
{
private:
	bool run;
	GLFWwindow* window;

public:
	WindowHandler();
	void Initialize();
	void Destroy();
	void InitializeGlfw(GLuint width, GLuint height);
	void Render(int& width, int& height);
	bool ShouldRun();
	GLFWwindow* GetWindow();
};

