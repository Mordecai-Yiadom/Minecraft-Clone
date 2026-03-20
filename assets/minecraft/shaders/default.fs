#version 330 core

in VS_OUT
{
    vec2 texCoord;
    vec3 normal;
    flat int texIndex;
} fs_in;

out vec4 FragColor;

uniform sampler2D blockTextures[10];


void main()
{   

    FragColor = texture(blockTextures[fs_in.texIndex], fs_in.texCoord);
}