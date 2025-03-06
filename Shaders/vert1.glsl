#version 330 core
layout (location = 0) in vec2 aPos;

out vec2 vUV;

void main()
{
    gl_Position = vec4(aPos, 0.0, 1.0);
    vUV = aPos * 0.5 + 0.5;  // Convert from NDC (-1 to +1) to UV (0 to 1)
}