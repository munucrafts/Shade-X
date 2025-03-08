#pragma once
#include "../ThirdParty/imgui/imgui.h"
#include "../ThirdParty/imgui/imgui_impl_glfw.h"
#include "../ThirdParty/imgui/imgui_impl_opengl3.h"

class UiHandler
{
public:
	UiHandler();
	void Initialize(GLFWwindow* window);
	void Render();
	void Destroy();

private:
	GLFWwindow* currentWindow;
	ImGuiIO io;

private:
	void UiRendering();
};

