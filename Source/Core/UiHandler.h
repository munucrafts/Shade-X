#pragma once
#include "../Utils/Commons.h"
#include "../ThirdParty/imgui/imgui.h"
#include "../ThirdParty/imgui/imgui_impl_glfw.h"
#include "../ThirdParty/imgui/imgui_impl_opengl3.h"
#include "Rendering/Shader.h"


class UiHandler
{
public:
	UiHandler();
	void Initialize(GLFWwindow* window);
	void Render(Shader* shader);
	void Destroy();

private:
	GLFWwindow* currentWindow;
	ImGuiIO io;
	Shader* shaderMain;
	void SetFont(unsigned char font[], int size);
	void UiRendering();
};

