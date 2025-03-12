#include "SavingSystem.h"
#include <fstream>
#include <iostream>
#include "../ThirdParty/json.hpp"

using json = nlohmann::json;

SavingSystem& SavingSystem::GetInstance()
{
    static SavingSystem instance;
    return instance;
}

SavingSystem::SavingSystem()
{
    filePath = GetSaveFilePath();
}

std::string SavingSystem::GetSaveFilePath()
{
    char path[MAX_PATH];

    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, 0, path)))
    {
        std::filesystem::path savePath = std::string(path) + "\\ShadeX\\Saved\\SavedSession.json";
        std::filesystem::create_directories(savePath.parent_path());
        return savePath.string();
    }

    std::string fallbackPath = std::filesystem::temp_directory_path().string() + "\\ShadeX_Session.json";
    return fallbackPath;
}

void SavingSystem::SaveProject(std::vector<ShaderUniforms>& shadersUniformsArray)
{
    json jsonData;

    for (size_t i = 0; i < shadersUniformsArray.size(); i++)
    {
        ShaderUniforms& data = shadersUniformsArray[i];

        json shaderData;
        shaderData["speed"] = data.speed;
        shaderData["brightness"] = data.brightness;
        shaderData["intensity"] = data.intensity;
        shaderData["color"] = { data.color.x, data.color.y, data.color.z, data.color.w };

        jsonData["shaders"].push_back(shaderData);
    }

    std::ofstream file(filePath);
    if (!file.is_open())
    {
        std::cout << "Failed to open save file: " << filePath << std::endl;
        return;
    }

    file << jsonData.dump(4);
    file.close();
}


void SavingSystem::LoadProject(std::vector<ShaderUniforms>& shadersUniformsArray)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "No saved session found. Using default values." << std::endl;
        return;
    }

    json jsonData;
    file >> jsonData;
    file.close();

    if (!jsonData.contains("shaders") || !jsonData["shaders"].is_array())
    {
        std::cout << "Invalid save file format!" << std::endl;
        return;
    }

    size_t shaderCount = shadersUniformsArray.size();

    for (size_t i = 0; i < shaderCount; i++)
    {
        ShaderUniforms& data = shadersUniformsArray[i];
        json shaderData = jsonData["shaders"][i];

        if (shaderData.contains("speed"))       data.speed = shaderData["speed"];
        if (shaderData.contains("brightness"))  data.brightness = shaderData["brightness"];
        if (shaderData.contains("intensity"))   data.intensity = shaderData["intensity"];
        if (shaderData.contains("color"))
        {
            data.color.x = shaderData["color"][0];
            data.color.y = shaderData["color"][1];
            data.color.z = shaderData["color"][2];
            data.color.w = shaderData["color"][3];
        }
    }
}

