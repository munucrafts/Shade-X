#pragma once
#include "glad/glad.h"
#include "stb/stb_image.h"
#include "iostream"
#include "fstream"
#include "string"

class Shader
{
public:
	GLuint shaderProgram;

private:
	const char* vertexShaderPath;
	const char* fragmentShaderPath;

private:
	const char* LoadShaderFromPath(const char* shaderPath);

public:
	Shader();
	Shader(const char* vShaderPath, const char* fShaderPath);
	~Shader();
	void CreateShaderProgram();
};

