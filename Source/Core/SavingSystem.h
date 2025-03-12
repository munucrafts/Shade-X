#pragma once
#include "../Utils/CommonStructs.h"
#include <windows.h>
#include <shlobj.h>
#include <string>
#include <filesystem>

class SavingSystem
{
public:
    static SavingSystem& GetInstance();
    void SaveProject(std::vector<ShaderUniforms>& shadersUniformsArray);
    void LoadProject(std::vector<ShaderUniforms>& shadersUniformsArray);

private:
    std::string filePath;

private:
    SavingSystem();
    ~SavingSystem() = default;
    SavingSystem(const SavingSystem&) = delete;
    SavingSystem& operator=(const SavingSystem&) = delete;

    std::string GetSaveFilePath();
};
