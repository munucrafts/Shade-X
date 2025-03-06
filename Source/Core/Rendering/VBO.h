#pragma once
#include "..\..\Utils\Commons.h"
#include <iostream>

class VBO
{
public:
	GLuint ID;

public:
	VBO();
	void InitVbo(GLfloat vertices[], GLuint size);
	void Bind();
	void Unbind();
	void Delete();
};

