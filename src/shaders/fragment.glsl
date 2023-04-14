#version 400 core
out vec4 FragColor;
uniform float time = 0.0f;
void main()
{
    FragColor = vec4(1.0f, time, 0.2f, 1.0f);
}
