#pragma once
#include "..\..\Utils\Commons.h"
#include <iostream>

class VBO
{
public:
	GLuint ID;

public:
	VBO();
	VBO(GLfloat Vertices[], GLuint size);
	void Bind();
	void Unbind();
	void Delete();
};

