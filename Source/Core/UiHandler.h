#pragma once
#include "../Utils/Commons.h"
#include "../ThirdParty/imgui/imgui.h"
#include "../ThirdParty/imgui/imgui_impl_glfw.h"
#include "../ThirdParty/imgui/imgui_impl_opengl3.h"
#include "Rendering/Shader.h"
#include "../Utils/CommonStructs.h"
#include "SavingSystem.h"


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

private:
	void SetFont(unsigned char font[], int size);
	void UiRendering();
	void HandleShaderThumbnailGrid(int columns, ImVec2 thumbnailSize, int totalShaderCount);
	void HandleShaderUniforms(float width);
};

