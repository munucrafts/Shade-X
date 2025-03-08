#pragma once
#include "glad/glad.h"
#include "stb/stb_image.h"
#include "iostream"
#include "fstream"
#include "string"
#include <vector>

struct ShaderInfo
{
	const char* shaderName;
	const char* vsSource;
	const char* fsSource;
};

class Shader
{
public:
	GLuint shaderProgram;

private:
	const char* LoadShaderFromPath(const char* shaderPath);
	void CreateShaderProgram();
	void CompileShader(ShaderInfo& newShader);

private:
	unsigned int shaderCount;
	std::vector<ShaderInfo> shadersArray;

public:
	Shader();
	~Shader();
	void InitShaders();
	void UpdateShader(int shaderNumber);
};

