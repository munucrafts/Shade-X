#include "Shader.h"

Shader::Shader()
{
    shaderProgram = 0;
    shaderCount = 10;

    shadersArray.resize(shaderCount);
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}

const char* Shader::LoadShaderFromPath(const char* shaderPath)
{
    std::ifstream shaderFile(shaderPath);
    std::string shaderText;
    std::string line;

    if (shaderFile.is_open())
    {
        while (std::getline(shaderFile, line)) shaderText += line + "\n";
        shaderFile.close();
    }

    char* shaderCode = new char[shaderText.size() + 1];
    std::copy(shaderText.begin(), shaderText.end(), shaderCode);
    shaderCode[shaderText.size()] = '\0';

    return shaderCode;
}

void Shader::CreateShaderProgram()
{
    shaderProgram =  glCreateProgram();
}

void Shader::InitShaders()
{
    for (int i = 0; i < shaderCount; i++)
    {
        std::string vertPath = "./Shaders/vert" + std::to_string(i) + ".glsl";
        std::string fragPath = "./Shaders/frag" + std::to_string(i) + ".glsl";

        shadersArray[i].vsSource = LoadShaderFromPath(vertPath.c_str());
        shadersArray[i].fsSource = LoadShaderFromPath(fragPath.c_str());
    }

    CreateShaderProgram();
    UpdateShader(0);
}

void Shader::UpdateShader(int shaderNumber)
{
    CompileShader(shadersArray[shaderNumber]);
}

void Shader::CompileShader(ShaderInfo& newShader)
{
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &newShader.vsSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &newShader.fsSource, nullptr);
    glCompileShader(fragmentShader);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
