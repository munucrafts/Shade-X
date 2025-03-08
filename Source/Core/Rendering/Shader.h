#pragma once
#include "glad/glad.h"
#include "stb/stb_image.h"
#include "iostream"
#include "fstream"
#include "string"
#include <vector>

struct ShaderInfo
{
	const char* vsSource;
	const char* fsSource;
};

class Shader
{
public:
	GLuint shaderProgram;
	unsigned int shaderCount;
	unsigned int currentShaderIndex;

private:
	const char* LoadShaderFromPath(const char* shaderPath);
	void CreateShaderProgram();
	void CompileShader(ShaderInfo& newShader);

private:
	std::vector<ShaderInfo> shadersArray;

public:
	Shader();
	~Shader();
	void InitShaders();
	void UpdateShader(int shaderNumber);
};

