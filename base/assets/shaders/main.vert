#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 transform;

void main()
{
    gl_Position = projection * view * transform * vec4(pos, 1.0);
    TexCoord = texCoord;
}
