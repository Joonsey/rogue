#version 400 core
in vec3 color;
out vec4 FragColor;
uniform float time = 0.0f;
void main()
{
    FragColor = vec4(color, 1.0f);
}
