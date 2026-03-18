#version 330 core

in VS_OUT
{
    vec2 texCoord;
    vec3 normal;
} fs_in;

out vec4 FragColor;

uniform float r;
uniform float g;
uniform float b;

void main()
{
    FragColor = vec4(fs_in.normal, 1.0);
}