#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class VBO
{
public:
	GLuint ID;

public:
	VBO(GLfloat Vertices[], GLuint size);
	void Bind();
	void Unbind();
	void Delete();
};

