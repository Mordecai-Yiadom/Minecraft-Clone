#version 330 core

// in VS_OUT
// {
//     vec2 TexCoord;
//     vec3 Normal;
// } fs_in;

out vec4 FragColor;

uniform float r;
uniform float g;
uniform float b;

void main()
{
    FragColor = vec4(r, g, b, 1.0);
}