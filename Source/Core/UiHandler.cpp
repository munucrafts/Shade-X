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

void UiHandler::SetFont(unsigned char font[], int size)
{
    io = ImGui::GetIO();
    ImFontConfig fontConfig;
    fontConfig.FontDataOwnedByAtlas = false; 
    io.Fonts->AddFontFromMemoryTTF(font, size, 20.f, &fontConfig);
    io.Fonts->Build();
}

void UiHandler::UiRendering()
{
    bool showWindowButtons = true;
    int gridColumns = 4;
    int totalShaders = shaderMain->shaderCount;
    ImVec2 shaderThumbnailSize = ImVec2(200, 120);

    ImGui::Begin("Shade-X", &showWindowButtons, ImGuiWindowFlags_NoResize);
    ImGui::SetWindowSize(ImVec2(gridColumns * shaderThumbnailSize.x, 0), true);

    ImGui::PushItemWidth(150);
    ImGui::ShowStyleSelector("Themes");

    ImGui::SameLine(ImGui::GetContentRegionAvail().x - ImGui::CalcTextSize("xxxxx FPS").x);
    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);

    if (!showWindowButtons) glfwSetWindowShouldClose(currentWindow, 1);

    HandleShaderThumbnailGrid(gridColumns, shaderThumbnailSize, totalShaders);
    HandleShaderUniforms(gridColumns * shaderThumbnailSize.x);

    ImGui::End();
}

void UiHandler::HandleShaderThumbnailGrid(int columns, ImVec2 thumbnailSize, int totalShaderCount)
{
    if (ImGui::BeginTable("ShaderGrid", columns))
    {
        for (int i = 0; i < totalShaderCount; i++)
        {
            ImGui::TableNextColumn();
            std::string shaderName = "Shader " + std::to_string(i);

            if (ImGui::ImageButton(shaderName.c_str(), 0, thumbnailSize, ImVec2(0, 0), ImVec2(1, 1), ImVec4(0, 0, 0, 0), ImVec4(0, 0, 0, 0)) && (shaderMain->currentShaderIndex != i))
            {
                shaderMain->UpdateShader(i);
            }
        }

        ImGui::EndTable();
    }
}

void UiHandler::HandleShaderUniforms(float width)
{
    ImGui::Spacing();
    ImGui::Text("🎨 Shader Controls");
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.0f); // Rounded sliders
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(6, 4)); // Compact spacing

    ImGui::BeginChild("ShaderControls", ImVec2(width, 150), true, ImGuiWindowFlags_NoScrollbar);

    if (ImGui::BeginTable("UniformsGrid", 2, ImGuiTableFlags_SizingStretchSame))
    {
        // Speed
        ImGui::TableNextColumn();
        ImGui::Text("⏩ Speed");
        static float speed = 0.5f;
        ImGui::SliderFloat("##Speed", &speed, 0.0f, 1.0f, "%.1f");

        // Brightness
        ImGui::TableNextColumn();
        ImGui::Text("🔆 Brightness");
        static float brightness = 0.5f;
        ImGui::SliderFloat("##Brightness", &brightness, 0.0f, 1.0f, "%.1f");

        // Color
        ImGui::TableNextColumn();
        ImGui::Text("🎨 Color");
        static ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        ImGui::ColorEdit3("##Color", (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

        // Intensity
        ImGui::TableNextColumn();
        ImGui::Text("💡 Intensity");
        static float intensity = 0.5f;
        ImGui::SliderFloat("##Intensity", &intensity, 0.0f, 1.0f, "%.1f");

        ImGui::EndTable();
    }

    ImGui::EndChild();

    ImGui::PopStyleVar(2); // Restore styles
}





