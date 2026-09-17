#version 460 core

layout (location = 0) out vec4 fragColor;
layout (location = 0) in vec2 v_TexCoord;
layout (location = 0) uniform float iTime;
layout (location = 1) uniform vec2 iResolution;

void main()
{
    fragColor = vec4(1.0);
}
