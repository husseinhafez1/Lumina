#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
	vec4 offset = vec4(0.3, 0.0, 0.0, 0.0);
    gl_Position = vec4(aPos.x, -aPos.y, aPos.z , 1.0) + offset;
    ourColor = gl_Position.xyz;
}