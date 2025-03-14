#include "Shader.h"

Shader::Shader()
{
    shaderProgram = 0;
    currentShaderIndex = 0;
    shaderCount = GetShadersCountFromFolder();
    shadersArray.resize(shaderCount);

    std::vector<ShaderUniforms> shaderUniformsArray;
    shaderUniformsArray.resize(shaderCount);
    SavingSystem::GetInstance().LoadProject(shaderUniformsArray);

    for (int i = 0; i < shaderCount; i++)
    {
        shadersArray[i].uniforms = shaderUniformsArray[i];
    }
}

Shader::~Shader()
{
    std::vector<ShaderUniforms> shaderUniformsArray;
    shaderUniformsArray.resize(shaderCount);

    for (int i = 0; i < shaderCount; i++)
    {
        shaderUniformsArray[i] = shadersArray[i].uniforms;
    }

    SavingSystem::GetInstance().SaveProject(shaderUniformsArray);
    glDeleteProgram(shaderProgram);
}

std::string Shader::LoadShaderFromPath(std::string shaderPath)
{
    std::ifstream shaderFile(shaderPath);

    if (!shaderFile.is_open())
    {
        std::cout << "Failed to open shader file: " << shaderPath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << shaderFile.rdbuf();
    return buffer.str();
}

void Shader::CreateShaderProgram()
{
    shaderProgram = glCreateProgram();
}

void Shader::InitShaders()
{
    for (int i = 0; i < shaderCount; i++)
    {
        std::string vertPath = "./Shaders/vert" + std::to_string(i) + ".glsl";
        std::string fragPath = "./Shaders/frag" + std::to_string(i) + ".glsl";

        shadersArray[i].vsSource = LoadShaderFromPath(vertPath);
        shadersArray[i].fsSource = LoadShaderFromPath(fragPath);
    }

    UpdateShader(0);
}

void Shader::UpdateShader(int shaderNumber)
{
    CreateShaderProgram();
    CompileShader(shadersArray[shaderNumber]);
    currentShaderIndex = shaderNumber;
}

void Shader::UpdateUniforms(ShaderUniforms* uniforms)
{
    shadersArray[currentShaderIndex].uniforms = *uniforms;
}

ShaderUniforms& Shader::GetUniforms()
{
    return (shadersArray[currentShaderIndex].uniforms);
}

void Shader::CompileShader(ShaderInfo& newShader)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vs = newShader.vsSource.c_str();
    glShaderSource(vertexShader, 1, &vs, nullptr);
    glCompileShader(vertexShader);

    const char* fs = newShader.fsSource.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs, nullptr);
    glCompileShader(fragmentShader);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

int Shader::GetShadersCountFromFolder()
{
    const std::string shaderPath = "./Shaders/";
    int shaderCount = 0;

    for (const auto& entry : std::filesystem::directory_iterator(shaderPath)) 
    {
        if (entry.path().extension() == ".glsl") 
        {
            shaderCount++;
        }
    }

    return shaderCount / 2;
}

