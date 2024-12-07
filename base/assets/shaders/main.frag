#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform bool useTexture;
uniform vec4 materialColor;
uniform sampler2D materialTexture;

void main()
{
    if (useTexture) FragColor = texture(materialTexture, TexCoord) * materialColor;
    else FragColor = materialColor;
}
