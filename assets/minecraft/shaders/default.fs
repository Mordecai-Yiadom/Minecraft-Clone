#version 330 core

in VS_OUT
{
    vec2 texCoord;
    vec3 normal;
    float texID;
} fs_in;

out vec4 FragColor;

uniform float r;
uniform float g;
uniform float b;

uniform sampler2D textureID;

void main()
{   
    //vec2 coords = fs_in.texCoord;
    FragColor = texture(textureID, fs_in.texCoord);
    //FragColor = vec4(1, 1, 1.0, 1.0);
}