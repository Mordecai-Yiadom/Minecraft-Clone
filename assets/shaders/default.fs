#version 330 core

// in VS_OUT
// {
//     vec2 TexCoord;
//     vec3 Normal;
// } fs_in;

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.5, 0.5, 0.9, 1.0);
}