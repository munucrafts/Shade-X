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
	std::string vsSource;
	std::string fsSource;

	ShaderUniforms uniforms;
};

class Shader
{
public:
	GLuint shaderProgram;
	unsigned int currentShaderIndex;
	unsigned int shaderCount;

private:
	std::vector<ShaderInfo> shadersArray;

private:
	std::string LoadShaderFromPath(std::string shaderPath);
	void CreateShaderProgram();
	void CompileShader(ShaderInfo& newShader);
	int GetShadersCountFromFolder();

public:
	Shader();
	~Shader();
	void InitShaders();
	void UpdateShader(int shaderNumber);
	void UpdateUniforms(ShaderUniforms* uniforms);
	ShaderUniforms& GetUniforms();
};