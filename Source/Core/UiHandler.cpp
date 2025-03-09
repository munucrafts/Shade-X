#pragma once
#include "UiHandler.h"
#include "../Utils/Fonts.h"

UiHandler::UiHandler() = default;

void UiHandler::Initialize(GLFWwindow* window)
{
    currentWindow = window;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    SetFont(aoval, aovalSize);
    ImGui::StyleColorsLight();

    
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

void UiHandler::SetFont(unsigned char* fontData, int fontSize)
{
    io = ImGui::GetIO();
    ImFontConfig fontConfig;
    fontConfig.FontDataOwnedByAtlas = false; 
    io.Fonts->AddFontFromMemoryTTF(fontData, fontSize, 20.0f, &fontConfig);
    io.Fonts->Build();
}


void UiHandler::UiRendering()
{
    bool showWindowButtons = true;
    int gridColumns = 4;
    int totalShaders = shaderMain->shaderCount;
    ImVec2 shaderThumbnailSize = ImVec2(200, 120);

    ImGui::Begin("Shade-X", &showWindowButtons, ImGuiWindowFlags_NoResize);
    ImGui::SetWindowFontScale(1.2f);
    ImGui::SetWindowSize(ImVec2(gridColumns * shaderThumbnailSize.x, 0), true);

    ImGui::PushItemWidth(150);
    ImGui::ShowStyleSelector("Themes");

    ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("xxxxx FPS").x);
    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);

    if (!showWindowButtons)
    {
        glfwSetWindowShouldClose(currentWindow, 1);
    }

    if (ImGui::BeginTable("ShaderGrid", gridColumns))
    {
        for (int i = 0; i < totalShaders; i++)
        {
            ImGui::TableNextColumn();
            std::string shaderName = "Shader " + std::to_string(i);

            if (ImGui::ImageButton(shaderName.c_str(), 0, shaderThumbnailSize, ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), ImVec4(0,0,0,0)) && (shaderMain->currentShaderIndex != i))
            {
                shaderMain->UpdateShader(i);
            }
        }

        ImGui::EndTable();
    }

    ImGui::End();
}


