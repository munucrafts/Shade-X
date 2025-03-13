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
    ImGui::StyleColorsClassic();
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
    HandleShaderUniforms(gridColumns * shaderThumbnailSize.x - 16.0f);

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
    ImGui::Text("Shader Controls");
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 6.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 3));
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.8f, 0.8f, 0.8f, 0.0f));

    ImGui::BeginChild("ShaderControls", ImVec2(width, 170), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    if (ImGui::BeginTable("UniformsGrid", 2, ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_BordersInnerV))
    {
        ImGui::TableSetupColumn("Uniforms", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Values", ImGuiTableColumnFlags_WidthStretch);

        ShaderUniforms& currentUniforms = shaderMain->GetUniforms();
        float speed = currentUniforms.speed;
        float brightness = currentUniforms.brightness;
        ImVec4 color = currentUniforms.color;
        float intensity = currentUniforms.intensity;

        ImGui::TableNextColumn();
        ImGui::Text("Speed");
        ImGui::TableNextColumn();
        if (ImGui::SliderFloat("##Speed", &speed, 0.0f, 1.0f, "%.2f"))
            currentUniforms.speed = speed; 

        ImGui::TableNextColumn();
        ImGui::Text("Brightness");
        ImGui::TableNextColumn();
        if (ImGui::SliderFloat("##Brightness", &brightness, 0.0f, 1.0f, "%.2f"))
            currentUniforms.brightness = brightness;

        ImGui::TableNextColumn();
        ImGui::Text("Color");
        ImGui::TableNextColumn();
        if (ImGui::ColorEdit3("##Color", (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel))
            currentUniforms.color = color;

        ImGui::TableNextColumn();
        ImGui::Text("Intensity");
        ImGui::TableNextColumn();
        if (ImGui::SliderFloat("##Intensity", &intensity, 0.0f, 1.0f, "%.2f"))
            currentUniforms.intensity = intensity;

        shaderMain->UpdateUniforms(&currentUniforms);

        ImGui::EndTable();
    }

    ImGui::EndChild();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(2);
}

