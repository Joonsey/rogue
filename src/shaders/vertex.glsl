#version 400 core
layout (location = 0) in vec3 aPos;
uniform int y_ratio = 1;
void main()
{
	gl_Position = vec4(aPos.x, aPos.y * mod, aPos.z, 1.0);
};

