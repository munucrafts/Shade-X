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

    int columns = 3;
    int totalShaders = shaderMain->shaderCount;

    if (ImGui::BeginTable("ShaderGrid", columns))
    {
        for (int i = 0; i < totalShaders; i++)
        {
            ImGui::Spacing();
            ImGui::TableNextColumn();
            std::string shaderName = "Shader " + std::to_string(i);

            if (ImGui::Button(shaderName.c_str(), ImVec2(200, 120)) && (shaderMain->currentShaderIndex != i))
            {
                shaderMain->UpdateShader(i);
            }
        }

        ImGui::EndTable();
    }

    ImGui::End();
}

