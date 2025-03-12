#pragma once
#include "glad/glad.h"
#include "stb/stb_image.h"
#include "iostream"
#include "fstream"
#include "string"
#include <vector>
#include "../../Utils/CommonStructs.h"
#include "../SavingSystem.h"

struct ShaderInfo
{
	const char* vsSource;
	const char* fsSource;

	ShaderUniforms uniforms;
};

class Shader
{
public:
	GLuint shaderProgram;
	unsigned int shaderCount;
	unsigned int currentShaderIndex;

private:
	std::vector<ShaderInfo> shadersArray;

private:
	const char* LoadShaderFromPath(const char* shaderPath);
	void CreateShaderProgram();
	void CompileShader(ShaderInfo& newShader);

public:
	Shader();
	~Shader();
	void InitShaders();
	void UpdateShader(int shaderNumber);
	void UpdateUniforms(ShaderUniforms* uniforms);
	ShaderUniforms& GetUniforms();
};

