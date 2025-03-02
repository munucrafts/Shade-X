#include "Shader.h"

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

Shader::Shader()
{
    shaderProgram, vertexShaderPath, fragmentShaderPath = nullptr;
}

Shader::Shader(const char* vShaderPath, const char* fShaderPath)
{
    vertexShaderPath = vShaderPath;
    fragmentShaderPath = fShaderPath;
    CreateShaderProgram();
}

Shader::~Shader()
{
    glDeleteProgram(shaderProgram);
}

void Shader::CreateShaderProgram()
{
    const char* vertexShaderSource, * fragmentShaderSource;
    vertexShaderSource = LoadShaderFromPath(vertexShaderPath);
    fragmentShaderSource = LoadShaderFromPath(fragmentShaderPath);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
