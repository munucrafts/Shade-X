#pragma once
#include "UiHandler.h"

UiHandler::UiHandler() = default;

void UiHandler::Initialize(GLFWwindow* window)
{
    currentWindow = window;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();
}

void UiHandler::Render(Shader* shader)
{
    shaderMain = shader;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    UiRendering();
    UiInteraction();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UiHandler::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UiHandler::UiRendering()
{
    ImGui::Begin("Shade-X");
    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);

    ImGui::Spacing();

    for (int i = 0; i < 10; i++)
    {
        std::string shaderName = "shader : " + std::to_string(i);

        if (ImGui::Button(shaderName.c_str(), ImVec2(100, 20)))
        {
            shaderMain->UpdateShader(i);
        }
    }

    ImGui::SetNextWindowSize(ImVec2(200, 25 * 10));
    ImGui::End();
}

void UiHandler::UiInteraction()
{
    // Add UI Interactions Here
}
